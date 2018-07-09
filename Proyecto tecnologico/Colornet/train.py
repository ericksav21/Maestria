# -*- coding: utf-8 -*-

import os.path, glob
import shutil
import skimage, skimage.data
import skimage.io as io
from skimage.color import rgb2lab, rgb2gray, lab2rgb
from skimage.transform import rescale, resize, downscale_local_mean
import numpy as np
import tensorflow as tf
from matplotlib import pyplot as plt

import utils
import colornet2

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

	#Importar el modelo
	no_inputs = 224 * 224
	no_classes = train_generator.no_classes
	x_img = tf.placeholder(tf.float32, [None, 224, 224], name = "Train_images")
	x_ab = tf.placeholder(tf.float32, [None, 224, 224, 2], name = "AB_images")
	y_class = tf.placeholder(tf.int32, [None], name = "Train_labels")
	y_class_oh = tf.one_hot(indices = tf.cast(y_class, tf.int32), depth = no_classes)
	
	color_obj = colornet2.ColorNet(True, no_classes)
	class_model, color_model = color_obj._init_model(x_img)
	#class_model = color_obj._init_model(x_img)
	#Obtener el error de la clasificación
	loss_alpha = tf.constant(1.0 / 300.0, name = "alpha", dtype = "float32")
	loss_class = tf.losses.softmax_cross_entropy(onehot_labels = y_class_oh, logits = class_model)
	loss_class = loss_class * loss_alpha

	#Obtener el error de la colorización
	loss_color = tf.reduce_mean(tf.square(tf.subtract(x_ab, color_model)))
	total_loss = loss_color + loss_class
	train_opt = tf.train.AdadeltaOptimizer(learning_rate = 1.0).minimize(total_loss)

	predictions = {
		"classes": tf.argmax(input = class_model, axis = 1),
		"probabilities": tf.nn.softmax(class_model, name = "softmax_tensor")
	}
	correct_pred_class = predictions["classes"]
	_, class_accuracy = tf.metrics.accuracy(labels = y_class, predictions = correct_pred_class)

	epochs = 1000
	model_name = 'color-model'
	saver = tf.train.Saver()
	#with tf.Session(config = tf.ConfigProto(device_count = {'GPU': 0})) as sess:
	with tf.Session() as sess:
		sess.run(tf.global_variables_initializer())
		sess.run(tf.local_variables_initializer())
		
		#Restaurar el modelo
		loader = tf.train.import_meta_graph(utils.TrainGenerator.MODELS_PATH + model_name + '.meta')
		loader.restore(sess, tf.train.latest_checkpoint(utils.TrainGenerator.MODELS_PATH))
		print("Modelo cargado.")

		sess.run(training_init_op)
		for i in range(epochs):
			images = []
			images_ab = []
			labels = []
			l_batch = sess.run(next_element)
			for j in range(l_batch.shape[0]):
				image_act = skimage.data.imread(l_batch[j, 0].decode("utf-8"))
				#Reescalar y hacer un random crop
				image_resized = resize(image_act, (224, 224), anti_aliasing = True)
				#image_cropped = utils.random_crop(image_resized, 224, 224)
				image_lab = rgb2lab(image_resized)
				#image_lab = (image_lab + 128.0) / 255.0
				image_org = image_lab[:, :, 0]
				image_ab = image_lab[:, :, 1 :]
				image_ab = (image_ab + 128.0) / 255.0

				labels.append(int(l_batch[j, 1].decode("utf-8")))
				images.append(image_org)
				images_ab.append(image_ab)

			images_np = np.array(images)
			#images_np = images_np.reshape(batch_size, 224, 224)
			images_ab_np = np.array(images_ab)
			labels_np = np.array(labels)

			_, accuracy_val, class_ac = sess.run([train_opt, loss_color, class_accuracy],
				feed_dict = {x_img: images_np, x_ab: images_ab_np, y_class: labels_np})
			if i % 1 == 0:
				print("Epoca:", i)
				print("Accuracy (clasificación):", class_ac)
				#print("Labels (clasificación):", labels_np)
				print("Accuracy (colorizacion):", accuracy_val)
		
		saver.save(sess, utils.TrainGenerator.MODELS_PATH + model_name)
		print("Entrenamiento terminado.")

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

		results = sess.run([color_model], feed_dict = {x_img: images_np})
		results_np = np.array(results)
		results_np = results_np[0]
		for i in range(len(images_np)):
			image_ab = results_np[i]
			image_ab_real = images_ab_np[i]

			image_reconstructed = np.zeros([224, 224, 3], dtype = np.float64)
			image_gray_act = images_np[i]
			image_reconstructed[:, :, 0] = image_gray_act[:, :]
			image_reconstructed[:, :, 1] = image_ab[:, :, 0]
			image_reconstructed[:, :, 2] = image_ab[:, :, 1]
			image_reconstructed[:, :, 1 : 3] = image_reconstructed[:, :, 1 : 3] * 255.0 - 128.0

			colored_image = lab2rgb(image_reconstructed)
			org_name = utils.TrainGenerator.RESULTS_PATH + "org" + str(i + 1) + ".jpg"
			color_name = utils.TrainGenerator.RESULTS_PATH + "color" + str(i + 1) + ".jpg"
			plt.imsave(color_name, colored_image)

		print("Validación Terminada.")


if __name__ == '__main__':
	main()