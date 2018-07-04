import os, sys
import datetime

#os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID"   # see issue #152
#os.environ["CUDA_VISIBLE_DEVICES"] = '-1'

import keras
from keras.applications.inception_resnet_v2 import InceptionResNetV2
from keras.applications.inception_resnet_v2 import preprocess_input
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
import numpy as np
import random
import tensorflow as tf
from mailhandler import send_email

TRAIN_PATH = 'C:/Users/erick/OneDrive/Documentos/Erick/Tensorflow/Proyecto/Keras/Train/'
TEST_PATH = 'C:/Users/erick/OneDrive/Documentos/Erick/Tensorflow/Proyecto/Keras/Test/'
RESULTS_PATH = 'C:/Users/erick/OneDrive/Documentos/Erick/Tensorflow/Proyecto/Keras/Results/'

#Precargar inception
inception = InceptionResNetV2(weights = None, include_top = True)
inception.load_weights('inception_resnet_v2_weights_tf_dim_ordering_tf_kernels.h5')
inception.graph = tf.get_default_graph()

def create_inception_embedding(grayscaled_rgb):
	grayscaled_rgb_resized = []
	for i in grayscaled_rgb:
		i = resize(i, (299, 299, 3), mode = 'constant')
		grayscaled_rgb_resized.append(i)
	grayscaled_rgb_resized = np.array(grayscaled_rgb_resized)
	grayscaled_rgb_resized = preprocess_input(grayscaled_rgb_resized)
	with inception.graph.as_default():
		embed = inception.predict(grayscaled_rgb_resized)
	return embed

def image_a_b_gen(batch_size, datagen, Xtrain):
	for batch in datagen.flow(Xtrain, batch_size = batch_size):
		grayscaled_rgb = gray2rgb(rgb2gray(batch))
		embed = create_inception_embedding(grayscaled_rgb)
		lab_batch = rgb2lab(batch)
		X_batch = lab_batch[:, :, :, 0]
		X_batch = X_batch.reshape(X_batch.shape + (1,))
		Y_batch = lab_batch[:, :, :, 1:] / 128.0
		yield ([X_batch, create_inception_embedding(grayscaled_rgb)], Y_batch)

def main():
	X = []
	for filename in os.listdir(TRAIN_PATH):
		X.append(img_to_array(load_img(TRAIN_PATH + filename)))
	X = np.array(X, dtype = float)

	split = max(int(1.0 * len(X)), 1)
	Xtrain = X[ : split]
	Xtrain = 1.0 / 255.0 * Xtrain

	embed_input = Input(shape = (1000,))

	#Encoder
	encoder_input = Input(shape = (256, 256, 1,))
	encoder_output = Conv2D(64, (3,3), activation = 'relu', padding = 'same', strides = 2)(encoder_input)
	encoder_output = Conv2D(128, (3,3), activation = 'relu', padding = 'same')(encoder_output)
	encoder_output = Conv2D(128, (3,3), activation = 'relu', padding = 'same', strides = 2)(encoder_output)
	encoder_output = Conv2D(256, (3,3), activation = 'relu', padding = 'same')(encoder_output)
	encoder_output = Conv2D(256, (3,3), activation = 'relu', padding = 'same', strides = 2)(encoder_output)
	encoder_output = Conv2D(512, (3,3), activation = 'relu', padding = 'same')(encoder_output)
	encoder_output = Conv2D(512, (3,3), activation = 'relu', padding = 'same')(encoder_output)
	encoder_output = Conv2D(256, (3,3), activation = 'relu', padding = 'same')(encoder_output)

	#Fusion
	fusion_output = RepeatVector(32 * 32)(embed_input) 
	fusion_output = Reshape(([32, 32, 1000]))(fusion_output)
	fusion_output = concatenate([encoder_output, fusion_output], axis = 3) 
	fusion_output = Conv2D(256, (1, 1), activation = 'relu', padding = 'same')(fusion_output) 

	#Decoder
	decoder_output = Conv2D(128, (3,3), activation = 'relu', padding = 'same')(fusion_output)
	decoder_output = UpSampling2D((2, 2))(decoder_output)
	decoder_output = Conv2D(64, (3,3), activation = 'relu', padding = 'same')(decoder_output)
	decoder_output = UpSampling2D((2, 2))(decoder_output)
	decoder_output = Conv2D(32, (3,3), activation = 'relu', padding = 'same')(decoder_output)
	decoder_output = Conv2D(16, (3,3), activation = 'relu', padding = 'same')(decoder_output)
	decoder_output = Conv2D(2, (3, 3), activation = 'tanh', padding = 'same')(decoder_output)
	decoder_output = UpSampling2D((2, 2))(decoder_output)

	model = Model(inputs = [encoder_input, embed_input], outputs = decoder_output)
	model.compile(optimizer = keras.optimizers.Adadelta(), loss = 'mse')

	l_model = int(sys.argv[1])
	if l_model == 1:
		model.load_weights("model.h5")

	#Entrenar el modelo
	datagen = ImageDataGenerator(
		shear_range = 0.2,
		zoom_range = 0.2,
		rotation_range = 20,
		horizontal_flip = True)

	batch_size = 32
	tensorboard = TensorBoard(log_dir = "/output/beta_run")
	model.fit_generator(image_a_b_gen(batch_size, datagen, Xtrain),
		callbacks = [tensorboard],
		epochs = 2500,
		steps_per_epoch = 1)

	#Guardar el modelo
	model_json = model.to_json()
	with open("model.json", "w") as json_file:
		json_file.write(model_json)
	model.save_weights("model.h5")

	color_me = []
	for filename in os.listdir(TEST_PATH):
		color_me.append(img_to_array(load_img(TEST_PATH + filename)))
	color_me = np.array(color_me, dtype = float)
	color_me_embed = create_inception_embedding(color_me)
	color_me = rgb2lab(1.0 / 255.0 * color_me)[:, :, :, 0]
	color_me = color_me.reshape(color_me.shape + (1,))

	# Test model
	output = model.predict([color_me, color_me_embed])
	output = output * 128.0

	# Output colorizations
	for i in range(len(output)):
		cur = np.zeros((256, 256, 3))
		cur[:, :, 0] = color_me[i][:, :, 0]
		cur[:, :, 1 : ] = output[i]
		imsave(RESULTS_PATH + "img_" + str(i) + ".png", lab2rgb(cur))

	#Enviar email
	now = datetime.datetime.now()
	text = 'Entrenamiento terminado el: ' + str(now.day) + '/' + str(now.month)
	text = text + ' A las: ' + str(now.hour) + ':' + str(now.minute)
	img_list = []
	for filename in os.listdir(RESULTS_PATH):
		img_list.append(RESULTS_PATH + filename)

	print("Enviando correo...")
	send_email('erickalv21@gmail.com', 'erick_sav22@hotmail.com', 'Reultados entrenamiento', text, '7rodavlas', img_list)

if __name__ == '__main__':
	main()