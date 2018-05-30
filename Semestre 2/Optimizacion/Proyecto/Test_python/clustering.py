import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

import mnist
import test4

def main():
	x_train, t_train, _, _ = mnist.load()
	n, m = 360, 784
	data = np.zeros((n, m), dtype = 'float')
	labels = np.zeros((n, 1), dtype = 'int')
	cnt, idx = 0, 0
	while cnt < 300:
		if t_train[idx] == 3 or t_train[idx] == 8 or t_train[idx] == 9:
			data[cnt, :] = (x_train[idx, :] / LA.norm(x_train[idx, :], 1))
			labels[cnt] = t_train[idx]
			cnt += 1
		idx += 1
	while cnt < 360:
		if t_train[idx] != 3 and t_train[idx] != 8 and t_train[idx] != 9:
			data[cnt, :] = (x_train[idx, :] / LA.norm(x_train[idx, :], 1))
			labels[cnt] = t_train[idx]
			cnt += 1
		idx += 1

	m = 50
	p = 0.3
	W_PCA = test4.PCA(data, m)
	data_proj_PCA = data.dot(W_PCA)
	data_mean = np.zeros((1, data.shape[1]), dtype = 'float')
	for i in range(data.shape[1]):
		data_mean[0, i] = np.mean(data[:, i])
	print(data_mean)

if __name__ == '__main__':
	main()