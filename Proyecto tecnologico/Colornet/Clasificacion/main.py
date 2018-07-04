# -*- coding: utf-8 -*-

import os.path, glob
import shutil
import skimage, skimage.data
import skimage.io as io
import numpy as np
import tensorflow as tf
from skimage.color import rgb2gray
from skimage.transform import rescale, resize, downscale_local_mean

import utils

class Classification(object):
	def __init__(self, no_classes):
		self.no_classes = no_classes
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

			# Global Conv level features network
			'glo_1_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_1_w'),
			'glo_1_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_1_b'),
			'glo_2_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_2_w'),
			'glo_2_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_2_b'),
			'glo_3_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_3_w'),
			'glo_3_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_3_b'),
			'glo_4_w': tf.Variable(tf.truncated_normal([3, 3, 512, 512]), name = 'glo_4_w'),
			'glo_4_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_4_b'),

			# Global FC  # input, output are reversed.
			'glo_5_w': tf.Variable(tf.truncated_normal([7 * 7 * 512, 1024]), name = 'glo_5_w'),
			#'glo_5_b': tf.Variable(tf.truncated_normal([1024]), name = 'glo_5_b'),
			'glo_5_b': 1024,
			'glo_6_w': tf.Variable(tf.truncated_normal([1024, 512]), name = 'glo_6_w'),
			#'glo_6_b': tf.Variable(tf.truncated_normal([512]), name = 'glo_6_b'),
			'glo_6_b': 512,

			# Classification neural network
			#'class_1_b': tf.Variable(tf.truncated_normal([256]), name = 'glo_1_b'),
			'class_1_b': 256,
			#'class_2_b': tf.Variable(tf.truncated_normal([no_classes]), name = 'glo_2_b'),
			'class_2_b': no_classes
		}
		self.one_stride = [1, 1, 1, 1]
		self.two_stride = [1, 2, 2, 1]

	def _set_conv2d_layer(self, input, f, b, s, name = None):
		conv = tf.nn.conv2d(input, filter = f, strides = s, padding = "SAME", name = name)
		#bn = tf.contrib.layers.batch_norm(conv, activation_fn = tf.nn.relu, decay = 0.9, updates_collections = None, is_training = self.phase)
		bn = tf.nn.bias_add(conv, b)
		bn = tf.nn.relu(bn)
		return bn

	def _set_fc_layer(self, x, b, name = None):
		dense = tf.layers.dense(inputs = x, units = b, activation = tf.nn.relu, use_bias = True, name = name)
		#logits = tf.contrib.layers.fully_connected(inputs = x, num_outputs = b, activation_fn = tf.nn.relu)

		return dense

	def construct_model(self, x):
		x = tf.reshape(x, shape = [-1, 224, 224, 1])
		ll_logits = self._set_conv2d_layer(x, self._config['low_1_w'], self._config['low_1_b'], self.two_stride, name = 'low_c1')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_2_w'], self._config['low_2_b'], self.one_stride, name = 'low_c2')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_3_w'], self._config['low_3_b'], self.two_stride, name = 'low_c3')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_4_w'], self._config['low_4_b'], self.one_stride, name = 'low_c4')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_5_w'], self._config['low_5_b'], self.two_stride, name = 'low_c5')
		ll_logits = self._set_conv2d_layer(ll_logits, self._config['low_6_w'], self._config['low_6_b'], self.one_stride, name = 'low_c6')

		gl_logits = self._set_conv2d_layer(ll_logits, self._config['glo_1_w'], self._config['glo_1_b'], self.two_stride, name = 'global_c1')
		gl_logits = self._set_conv2d_layer(gl_logits, self._config['glo_2_w'], self._config['glo_2_b'], self.one_stride, name = 'global_c2')
		gl_logits = self._set_conv2d_layer(gl_logits, self._config['glo_3_w'], self._config['glo_3_b'], self.two_stride, name = 'global_c3')
		gl_logits_conv = self._set_conv2d_layer(gl_logits, self._config['glo_4_w'], self._config['glo_4_b'], self.one_stride, name = 'global_c4')

		gl_flat = tf.reshape(gl_logits_conv, [-1, 7 * 7 * 512], name = 'global_fl1')
		gl_logits = self._set_fc_layer(gl_flat, self._config['glo_5_b'], name = 'global_fc1')
		gl_logits = self._set_fc_layer(gl_logits, self._config['glo_6_b'], name = 'global_fc2')

		class_logits = self._set_fc_layer(gl_logits, self._config['class_1_b'], name = 'class_fc1')
		class_logits = tf.layers.dense(inputs = class_logits, units = self._config['class_2_b'], use_bias = True, name = 'class_fc2')

		return class_logits

def main():
	train_generator = utils.TrainGenerator()

	#Generar conjunto de entrenamiento
	batch_size = 50
	min_after_dequeue = 70000
	capacity = min_after_dequeue * 3 + batch_size
	batch_shuffle = tf.train.shuffle_batch([train_generator.images_dict], enqueue_many = True, batch_size = batch_size, capacity = capacity, min_after_dequeue = min_after_dequeue)
	dx_train = tf.data.Dataset.from_tensor_slices(train_generator.images_dict).shuffle(9000).repeat().batch(batch_size)
	iterator = tf.data.Iterator.from_structure(dx_train.output_types, dx_train.output_shapes)
	next_element = iterator.get_next()
	training_init_op = iterator.make_initializer(dx_train)

	#Crear el modelo
	no_classes = train_generator.no_classes
	x_img = tf.placeholder(tf.float32, [None, 224, 224], name = "Train_images")
	y_class = tf.placeholder(tf.int32, [None], name = "Train_labels")
	y_class_oh = tf.one_hot(indices = tf.cast(y_class, tf.int32), depth = no_classes)
	classificator = Classification(no_classes)
	logits = classificator.construct_model(x_img)
	loss = tf.losses.softmax_cross_entropy(onehot_labels = y_class_oh, logits = logits)
	train_opt = tf.train.AdadeltaOptimizer(learning_rate = 0.001).minimize(loss)

	correct_pred = tf.argmax(logits, axis = 1)
	accuracy = tf.metrics.accuracy(labels = y_class, predictions = correct_pred)

	epochs = 100
	model_name = 'classifier'
	saver = tf.train.Saver()
	with tf.Session() as sess:
		sess.run(tf.global_variables_initializer())
		sess.run(tf.local_variables_initializer())

		loader = tf.train.import_meta_graph(utils.TrainGenerator.MODELS_PATH + model_name + '.meta')
		loader.restore(sess, tf.train.latest_checkpoint(utils.TrainGenerator.MODELS_PATH))
		print("Modelo restaurado")

		sess.run(training_init_op)

		for i in range(epochs):
			images = []
			labels = []
			l_batch = sess.run(next_element)
			for j in range(l_batch.shape[0]):
				image_act = skimage.data.imread(l_batch[j, 0].decode("utf-8"))
				#Reescalar y hacer un random crop
				image_resized = resize(image_act, (224, 224), anti_aliasing = True)
				image_org = rgb2gray(image_resized)

				labels.append(int(l_batch[j, 1].decode("utf-8")))
				images.append(image_org)

			images_np = np.array(images)
			labels_np = np.array(labels)

			_, accuracy_val, pred = sess.run([train_opt, accuracy, correct_pred],
				feed_dict = {x_img: images_np, y_class: labels_np})
			if i % 1 == 0:
				print("Epoca:", i)
				print("Accuracy (colorizacion):", accuracy_val)
				print("Logits:", pred)
				print("Real:", labels_np)

		saver.save(sess, utils.TrainGenerator.MODELS_PATH + model_name)


if __name__ == '__main__':
	main()