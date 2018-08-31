import numpy as np
from numpy import linalg as LA
import sys
from matplotlib import pyplot as plt
from keras.datasets import mnist

def NN(x_train, y_train, test_img):
	ind = -1
	min_len = sys.float_info.max
	for i in range(x_train.shape[0]):
		act_len = LA.norm(x_train[i] - test_img, 2)
		if act_len < min_len:
			min_len = act_len
			ind = i

	return (min_len, y_train[ind])

def main():
	(x_train, y_train), (x_test, y_test) = mnist.load_data()
	train_shape = x_train.shape
	test_shape = x_test.shape
	x_train = np.reshape(x_train, (train_shape[0], train_shape[1] * train_shape[2]))
	x_test = np.reshape(x_test, (test_shape[0], test_shape[1] * test_shape[2]))

	cnt = 0
	for i in range(2000):
		_, pred = NN(x_train, y_train, x_test[i])
		print("Imagen {0}: Real: {1} / Prediccion: {2}".format(str(i + 1), y_test[i], pred))
		if y_test[i] == pred:
			cnt += 1

	print("Terminado. Porcentaje de imagenes correctamente clasificadas: {0}".format(float(cnt) / float(2000)))


if __name__ == '__main__':
	main()