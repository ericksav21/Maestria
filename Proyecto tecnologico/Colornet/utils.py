# -*- coding: utf-8 -*-

import os.path, glob
import shutil
import skimage, skimage.data
import skimage.io as io
import numpy as np
import tensorflow as tf
from skimage.color import rgb2lab, rgb2gray, lab2rgb
from matplotlib import pyplot as plt
import cv2

#Esta función se encarga de analizar el conjunto completo de imágenes y remover las que estén en escala de grises
#O tengan poca variabilidad de color
def filter_img_dataset(path, useless):
	for parent, dirnames, filenames in os.walk(path):
		print("Filtrando en: ", parent)
		for filename in filenames:
			path = os.path.join(parent, filename)
			img = io.imread(path)

			if len(img.shape) == 2:
				newpath = os.path.join(useless, os.path.split(parent)[1])
				if not os.path.exists(newpath):
					os.makedirs(newpath)
				try:
					shutil.move(path, newpath)
				except:
					os.remove(path)
			else:
				r = img[:, :, 0]
				g = img[:, :, 1]
				b = img[:, :, 2]
				num = r.size
				num_1 = img.size

				#Imagen en escala de grises con 3 canales
				if np.sum(abs(r - g) < 30) / num > 0.9 and np.sum(abs(r - b) < 30) / num > 0.9:
					newpath = os.path.join(useless, os.path.split(parent)[1])
					if not os.path.exists(newpath):
						os.makedirs(newpath)
					try:
						shutil.move(path, newpath)
					except:
						os.remove(path)

				else:
					#Imagen con poca variabilidad de colores
					img = rgb2lab(img)
					ab = [img[:, :, 1], img[:, :, 2]]
					variance = np.sqrt(np.sum(np.power(ab[0] - np.sum(ab[0]) / num, 2)) / num) + \
								np.sqrt(np.sum(np.power(ab[1] - np.sum(ab[1]) / num, 2)) / num)
					if variance < 6:
						newpath = os.path.join(useless, os.path.split(parent)[1])
						if not os.path.exists(newpath):
							os.makedirs(newpath)
						try:
							shutil.move(path, newpath)
						except:
							os.remove(path)

def random_crop(img, width, height):
	assert img.shape[0] >= height
	assert img.shape[1] >= width
	x = np.random.randint(0, img.shape[1] - width, 1)[0]
	y = np.random.randint(0, img.shape[0] - height, 1)[0]
	img = img[y : y + height, x : x + width]
	return img

class TrainGenerator(object):
	IMG_TRAIN_PATH = "D:/Tensorflow/GG/"
	IMG_TEST_PATH = "D:/Tensorflow/GT/"
	RESULTS_PATH = "D:/Tensorflow/results/"
	MODELS_PATH = "C:/Users/erick/OneDrive/Documentos/Erick/Tensorflow/Proyecto/models/"
	USELESS_IMG = "D:/Tensorflow/useless/"

	def __init__(self):
		self.images_dict = None
		self.no_classes = 0
		self.generate_train_image_info(self.IMG_TRAIN_PATH)


	def generate_train_image_info(self, path):
		images = []
		cnt_class = 0
		dict_class = {}
		for parent, dirnames, filenames in os.walk(path):
			print("Leyendo en: ", parent)
			#print(os.path.basename(os.path.dirname(parent)))
			for filename in filenames:
				label = os.path.basename(parent)
				if len(os.path.basename(os.path.dirname(parent))) != 1:
					#Está en una subcarpeta dentro del label original
					label = os.path.basename(os.path.dirname(parent))

				if label in dict_class:
					n_label = dict_class[label]
				else:
					n_label = cnt_class
					dict_class[label] = cnt_class
					cnt_class += 1
				images.append([parent + "\\" + filename, str(n_label)])

		print("Len:", len(images))
		print("No. Etiquetas:", cnt_class)
		self.no_classes = cnt_class
		self.images_dict = tf.stack(images)


	def load_images(self, images_dir):
		labels = []
		images = []
		for img_act in images_dir:
			#TODO: Process label
			images.append(skimage.data.imread(img_act))
			#labels.append(int(d))

		return np.array(images)


	'''
	def generate_train_batch(self, batch_size = 128, min_after_dequeue = 70000):
		capacity = min_after_dequeue * 3 + batch_size
		#images = tf.stack([f for f_ in [glob.glob(IMG_PATH + e) for e in ("*.jpg", "*.png", ".jpeg")] for f in f_])
		batch_shuffle = tf.train.shuffle_batch([self.images_dict], enqueue_many = True, batch_size = batch_size, capacity = capacity, min_after_dequeue = min_after_dequeue)

		with tf.Session() as sess:
			coord = tf.train.Coordinator()
			threads = tf.train.start_queue_runners(coord = coord)
			for i in range(3):
				images_dir = sess.run([batch_shuffle])
				#images_dir_np = np.array([img.decode("utf-8") for img in images_dir[0]])
				#train_images = load_images(images_dir_np)
				print(images_dir)

			coord.request_stop()
			coord.join(threads)
	

	def generate_train_batch(self, batch_size = 128):
		dx_train = tf.data.Dataset.from_tensor_slices(self.images_dict).shuffle(1600000).repeat().batch(batch_size)
		iterator = tf.data.Iterator.from_structure(dx_train.output_types, dx_train.output_shapes)
		next_element = iterator.get_next()
		training_init_op = iterator.make_initializer(dx_train)

		with tf.Session() as sess:
			sess.run(training_init_op)
			for i in range(5):
				print(sess.run(next_element))
	'''

#generate_train_batch(batch_size = 3)
#filter_img_dataset(IMG_TRAIN_PATH)

def test():
	img_name = None
	for parent, dirnames, filenames in os.walk(TrainGenerator.IMG_TRAIN_PATH):
		print("Leyendo en: ", parent)
		#print(os.path.basename(os.path.dirname(parent)))
		for filename in filenames:
			img_name = parent + "\\" + filename
			break
		if img_name != None:
			break
	
	image_act = skimage.data.imread(img_name)
	image_lab = rgb2lab(image_act)
	image_lab_1 = rgb2lab(image_act)
	image_lab = (image_lab + 128) / 255
	image_gray = rgb2gray(image_act)
	#print(image_lab)
	image_ab = image_lab[:, :, 1 : 3]
	random_ab = np.zeros((256, 256, 2), dtype = 'float')
	for i in range(2):
		for x in range(256):
			for y in range(256):
				random_ab[x, y, i] = np.random.uniform(0.0, 1.0, 1)
	
	print(random_ab)
	image_reconstructed = np.zeros([256, 256, 3])
	image_reconstructed[:, :, 0] = image_gray[:, :]
	image_reconstructed[:, :, 1] = random_ab[:, :, 0]
	image_reconstructed[:, :, 2] = random_ab[:, :, 1]
	image_reconstructed[:, :, 0] = image_reconstructed[:, :, 0] * 100
	image_reconstructed[:, :, 1 : 3] = image_reconstructed[:, :, 1 : 3] * 255 - 128
	image_reconstructed = image_reconstructed.astype(np.float64)
	image_reconstructed = lab2rgb(image_reconstructed)
	
	#print(image_reconstructed)

	plt.imshow(image_reconstructed)
	plt.show()

#test()