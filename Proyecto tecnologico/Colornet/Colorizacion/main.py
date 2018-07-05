# -*- coding: utf-8 -*-

import os.path, glob
import shutil
import skimage, skimage.data
import skimage.io as io
import numpy as np
import tensorflow as tf
from numpy import linalg as LA
from skimage.color import rgb2gray, rgb2lab, lab2rgb
from skimage.transform import rescale, resize, downscale_local_mean
from matplotlib import pyplot as plt

import utils

class Colorization(object):
	def __init__(self):
		self._config = {
			# Low level features network
			'low_1_w': tf.Variable(tf.truncated_normal([3, 3, 1, 64]), name = 'low_1_w'),
			'low_1_b': tf.Variable(tf.truncated_normal([64]), name = 'low_1_b'),
			'low_2_w': tf.Variable(tf.truncated_normal([3, 3, 64, 128]), name = 'low_2_w'),
			'low_2_b': tf.Variable(tf.truncated_normal([128]), name = 'low_2_b'),

			'low_3_w': tf.Variable(tf.truncated_normal([3, 3, 128, 128]), name = 'low_3_w'),
			'low_3_b': tf.Variable(tf.truncated_normal([128]), name = 'low_3_b'),
			'low_4_w': tf.Variable(tf.truncated_normal([3, 3, 128, 256]), name = 'low_4_w'),
			'low_4_b': tf.Variable(tf.truncated_normal([256]), name = 'low_4_b'),

			'low_5_w': tf.Variable(tf.truncated_normal([3, 3, 256, 256]), name = 'low_5_w'),
			'low_5_b': tf.Variable(tf.truncated_normal([256]), name = 'low_5_b'),
			'low_6_w': tf.Variable(tf.truncated_normal([3, 3, 256, 512]), name = 'low_6_w'),
			'low_6_b': tf.Variable(tf.truncated_normal([512]), name = 'low_6_b'),

			# Middle level features network
			'mid_1_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'mid_1_w'),
			'mid_1_b': tf.Variable(tf.truncated_normal([512]), name = 'mid_1_b'),
			'mid_2_w': tf.Variable(tf.truncated_normal([3, 3, 512, 256]), name = 'mid_2_w'),
			'mid_2_b': tf.Variable(tf.truncated_normal([256]), name = 'mid_2_b'),

			# Colorization network
			'col_1_w': tf.Variable(tf.truncated_normal([3, 3, 256, 128]), name = 'col_1_w'),
			'col_1_b': tf.Variable(tf.truncated_normal([128]), name = 'col_1_b'),

			'col_2_w': tf.Variable(tf.truncated_normal([3, 3, 128, 64]), name = 'col_2_w'),
			'col_2_b': tf.Variable(tf.truncated_normal([64]), name = 'col_2_b'),
			'col_3_w': tf.Variable(tf.truncated_normal([3, 3, 64, 64]), name = 'col_3_w'),
			'col_3_b': tf.Variable(tf.truncated_normal([64]), name = 'col_3_b'),

			'col_4_w': tf.Variable(tf.truncated_normal([3, 3, 64, 32]), name = 'col_4_w'),
			'col_4_b': tf.Variable(tf.truncated_normal([32]), name = 'col_4_b'),
			'col_5_w': tf.Variable(tf.truncated_normal([3, 3, 32, 2]), name = 'col_5_w'),
			'col_5_b': tf.Variable(tf.truncated_normal([2]), name = 'col_5_b')
		}
		self.one_stride = [1, 1, 1, 1]
		self.two_stride = [1, 2, 2, 1]

	def _set_conv2d_layer(self, input, f, b, s, name = None):
		conv = tf.nn.conv2d(input, filter = f, strides = s, padding = "SAME", name = name)
		#bn = tf.contrib.layers.batch_norm(conv, activation_fn = tf.nn.relu, decay = 0.9, updates_collections = None, is_training = self.phase)
		bn = tf.nn.bias_add(conv, b)
		bn = tf.contrib.layers.batch_norm(bn, center = True, scale = True, is_training = True)
		bn = tf.nn.relu(bn)
		return bn

	def _set_fc_layer(self, x, b, name = None):
		dense = tf.layers.dense(inputs = x, units = b, activation = None, use_bias = True, name = name)
		dense = tf.contrib.layers.batch_norm(dense, center = True, scale = True, is_training = True)

		return dense

	def _up_sample(self, x):
		return tf.image.resize_images(x,
			[2 * tf.shape(x)[1],
			2 * tf.shape(x)[2]],
			method = tf.image.ResizeMethod.NEAREST_NEIGHBOR)

	def construct_model(self, x):
		x = tf.reshape(x, shape = [-1, 224, 224, 1])
		ll_logits = self._set_conv2d_layer(x, self._config['low_1_w'], self._config['low_1_b'], self.two_stride, name = 'low_c1')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_2_w'], self._config['low_2_b'], self.one_stride, name = 'low_c2')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_3_w'], self._config['low_3_b'], self.two_stride, name = 'low_c3')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_4_w'], self._config['low_4_b'], self.one_stride, name = 'low_c4')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_5_w'], self._config['low_5_b'], self.two_stride, name = 'low_c5')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_6_w'], self._config['low_6_b'], self.one_stride, name = 'low_c6')

		ml_logits = self._set_conv2d_layer(ll_logits, self._config['mid_1_w'], self._config['mid_1_b'], self.one_stride, name = 'middle_c1')
		ml_logits = self._set_conv2d_layer(ml_logits, self._config['mid_2_w'], self._config['mid_2_b'], self.one_stride, name = 'middle_c2')

		color_logits = self._set_conv2d_layer(ml_logits, self._config['col_1_w'], self._config['col_1_b'], self.one_stride, name = 'color_c1')
		upsampled_1 = self._up_sample(color_logits)
		color_logits = self._set_conv2d_layer(upsampled_1, self._config['col_2_w'], self._config['col_2_b'], self.one_stride, name = 'color_c2')
		color_logits = self._set_conv2d_layer(color_logits, self._config['col_3_w'], self._config['col_3_b'], self.one_stride, name = 'color_c3')
		upsampled_2 = self._up_sample(color_logits)
		color_logits = self._set_conv2d_layer(upsampled_2, self._config['col_4_w'], self._config['col_4_b'], self.one_stride, name = 'color_c4')
		
		#Esta capa se hace a mano dado que se tiene que usar otra función de activación
		color_logits = tf.nn.conv2d(color_logits, filter = self._config['col_5_w'], strides = self.one_stride, padding = "SAME", name = 'color_c5')
		color_logits = tf.nn.bias_add(color_logits, self._config['col_5_b'])
		color_logits = tf.contrib.layers.batch_norm(color_logits, center = True, scale = True, is_training = True)
		color_logits = tf.nn.sigmoid(color_logits)

		color_out = self._up_sample(color_logits)

		return color_out

def main():
	train_generator = utils.TrainGenerator()

	#Generar conjunto de entrenamiento
	batch_size = 1
	min_after_dequeue = 70000
	capacity = min_after_dequeue * 3 + batch_size
	batch_shuffle = tf.train.shuffle_batch([train_generator.images_dict], enqueue_many = True, batch_size = batch_size, capacity = capacity, min_after_dequeue = min_after_dequeue)
	dx_train = tf.data.Dataset.from_tensor_slices(train_generator.images_dict).shuffle(9000).repeat().batch(batch_size)
	iterator = tf.data.Iterator.from_structure(dx_train.output_types, dx_train.output_shapes)
	next_element = iterator.get_next()
	training_init_op = iterator.make_initializer(dx_train)

	#Crear el modelo
	x_img = tf.placeholder(tf.float32, [None, 224, 224], name = "Train_images")
	x_ab = tf.placeholder(tf.float32, [None, 224, 224, 2], name = "AB_images")
	colorizer = Colorization()
	logits = colorizer.construct_model(x_img)
	loss = tf.reduce_sum(tf.square(tf.subtract(x_ab, logits)))

	train_opt = tf.train.AdadeltaOptimizer(learning_rate = 0.001).minimize(loss)

	epochs = 3000
	model_name = 'colorizer'
	saver = tf.train.Saver()
	with tf.Session() as sess:
		sess.run(tf.global_variables_initializer())
		sess.run(tf.local_variables_initializer())

		#loader = tf.train.import_meta_graph(utils.TrainGenerator.MODELS_PATH + model_name + '.meta')
		#loader.restore(sess, tf.train.latest_checkpoint(utils.TrainGenerator.MODELS_PATH))
		#print("Modelo restaurado")

		sess.run(training_init_op)

		for i in range(epochs):
			images = []
			images_ab = []
			l_batch = sess.run(next_element)
			for j in range(l_batch.shape[0]):
				image_act = skimage.data.imread(l_batch[j, 0].decode("utf-8"))
				#Reescalar y hacer un random crop
				image_resized = resize(image_act, (224, 224), anti_aliasing = True)
				image_lab = rgb2lab(image_resized)
				#image_lab = (image_lab + 128.0) / 255.0
				image_org = image_lab[:, :, 0]
				image_ab = image_lab[:, :, 1 :]
				image_ab = (image_ab + 128.0) / 255.0

				images.append(image_org)
				images_ab.append(image_ab)

			images_np = np.array(images)
			images_ab_np = np.array(images_ab)

			_, color_loss = sess.run([train_opt, loss],
				feed_dict = {x_img: images_np, x_ab: images_ab_np})
			if i % 1 == 0:
				print("Epoca:", i)
				print("Loss (colorizacion):", color_loss)

		saver.save(sess, utils.TrainGenerator.MODELS_PATH + model_name)
		print("Modelo guardado")

		#Conjunto de prueba
		images_org = []
		images_ab = []
		images = []
		for filename in os.listdir(utils.TrainGenerator.IMG_TEST_PATH):
			image_act = skimage.data.imread(utils.TrainGenerator.IMG_TEST_PATH + filename)
			image_resized = resize(image_act, (224, 224), anti_aliasing = True)
			image_act = rgb2lab(image_resized)
			images.append(image_act[:, :, 0])
			images_ab.append(image_act[:, :, 1 :])

		images_np = np.array(images)
		images_ab_np = np.array(images_ab)

		results = sess.run([logits], feed_dict = {x_img: images_np})
		results_np = np.array(results)
		results_np = np.squeeze(results_np)
		for i in range(len(images_np)):
			image_ab = results_np
			image_ab_real = images_ab_np[i]
			'''res = LA.norm(image_ab[:, 0] - image_ab_real[:, 0])
			res += LA.norm(image_ab[:, 1] - image_ab_real[:, 1])
			print(res)
			return'''

			image_reconstructed = np.zeros([224, 224, 3], dtype = np.float64)
			image_gray_act = images_np[i]
			image_reconstructed[:, :, 0] = image_gray_act[:, :]
			image_reconstructed[:, :, 1] = image_ab[:, :, 0]
			image_reconstructed[:, :, 2] = image_ab[:, :, 1]
			image_reconstructed[:, :, 1 : 3] = image_reconstructed[:, :, 1 : 3] * 255.0 - 128.0

			colored_image = lab2rgb(image_reconstructed)
			color_name = utils.TrainGenerator.RESULTS_PATH + "color" + str(i + 1) + ".jpg"
			plt.imsave(color_name, colored_image)

		print("Validación Terminada.")


if __name__ == '__main__':
	main()