import os, sys
import datetime

#os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID"   # see issue #152
#os.environ["CUDA_VISIBLE_DEVICES"] = '-1'

import keras
from keras.preprocessing import image
from keras.engine import Layer
from keras.layers import Conv2D, UpSampling2D, InputLayer, Conv2DTranspose, Input, Reshape, merge, concatenate, Activation, Dense, Dropout, Flatten
from keras.layers.normalization import BatchNormalization
from keras.callbacks import TensorBoard 
from keras.models import Sequential, Model
from keras.layers.core import RepeatVector, Permute
from keras.preprocessing.image import ImageDataGenerator, array_to_img, img_to_array, load_img
from skimage.color import rgb2lab, lab2rgb, rgb2gray, gray2rgb
from skimage.transform import resize
from skimage.io import imsave
from matplotlib import pyplot as plt
import numpy as np
import random
import tensorflow as tf

TRAIN_PATH = '/home/e-082017-04/Documents/Maestria/GIT/Proyecto tecnologico/Colornet/Colorizacion/Train/'
TEST_PATH = '/home/e-082017-04/Documents/Maestria/GIT/Proyecto tecnologico/Colornet/Colorizacion/Test/'
RESULTS_PATH = '/home/e-082017-04/Documents/Maestria/GIT/Proyecto tecnologico/Colornet/Colorizacion/Results/'
MODELS_PATH = '/home/e-082017-04/Documents/Maestria/GIT/Proyecto tecnologico/Colornet/Colorizacion/Models/'

def main():
	X = None
	for filename in os.listdir(TRAIN_PATH):
		X = img_to_array(load_img(TRAIN_PATH + filename))
		break
	X = np.array(X, dtype = 'float')
	X = 1.0 / 255.0 * X
	X = resize(X, (224, 224))
	X_lab = rgb2lab(X)

	img_gray = X_lab[:, :, 0]
	img_gray = img_gray.reshape(1, 224, 224, 1)
	img_ab = X_lab[:, :, 1 : ]
	img_ab = (img_ab + 128.0) / 255.0
	img_ab = img_ab.reshape(1, 224, 224, 2)

	model = Sequential()
	model.add(InputLayer(input_shape = (224, 224, 1,)))
	#low level
	model.add(Conv2D(64, (3, 3), padding = 'same', strides = 2))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(128, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(128, (3, 3), padding = 'same', strides = 2))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(256, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(256, (3, 3), padding = 'same', strides = 2))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(512, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	#mid level
	model.add(Conv2D(512, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(256, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	#Color
	model.add(Conv2D(128, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(UpSampling2D((2, 2)))
	model.add(Conv2D(64, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(64, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(UpSampling2D((2, 2)))
	model.add(Conv2D(32, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('relu'))
	model.add(Conv2D(2, (3, 3), padding = 'same', strides = 1))
	model.add(BatchNormalization())
	model.add(Activation('sigmoid'))
	model.add(UpSampling2D((2, 2)))

	model.compile(optimizer = keras.optimizers.Adadelta(), loss = 'mse')
	model.load_weights("model.h5")
	#print(model.summary())

	model.fit(x = img_gray, y = img_ab, batch_size = 1, epochs = 10)

	model_json = model.to_json()
	with open("model.json", "w") as json_file:
		json_file.write(model_json)
	model.save_weights("model.h5")

	print(model.evaluate(img_gray, img_ab, batch_size = 1))
	output = model.predict(img_gray)
	output = (output * 255.0) - 128.0

	cur = np.zeros((224, 224, 3), dtype = 'float')
	cur[:, :, 0] = img_gray[0][:, :, 0]
	cur[:, :, 1 : ] = output[0]

	imsave("res.png", lab2rgb(cur))

if __name__ == '__main__':
	main()