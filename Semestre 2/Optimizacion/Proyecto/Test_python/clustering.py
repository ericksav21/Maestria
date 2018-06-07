import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt
from sklearn.cluster import KMeans

import mnist, utils, optimization

def make_clustering(X, labels, k):
	d_max_1, d_max_2 = 0.0, 0.0
	v_max_1 = np.zeros((X.shape[1]), dtype = 'float')
	v_max_2 = np.zeros((X.shape[1]), dtype = 'float')
	v_max_3 = np.zeros((X.shape[1]), dtype = 'float')
	for i in range(X.shape[0] - 1):
		for j in range(i + 1, X.shape[0]):
			v_aux = X[i, :] - X[j, :]
			d_aux = LA.norm(v_aux, 2)
			if d_aux > d_max_1:
				d_max_1 = d_aux
				v_max_1 = X[i, :].copy()
				v_max_2 = X[j, :].copy()

	for i in range(X.shape[0]):
		v_aux_1 = X[i, :] - v_max_1
		v_aux_2 = X[i, :] - v_max_2
		d_aux_1 = LA.norm(v_aux_1, 2)
		d_aux_2 = LA.norm(v_aux_2, 2)
		if d_aux_1 + d_aux_2 > d_max_2:
			d_max_2 = d_aux_1 + d_aux_2
			v_max_3 = X[i, :].copy()

	init_v = np.matrix([v_max_1, v_max_2, v_max_3], dtype = 'float')
	kmeans = KMeans(n_clusters = k, init = 'k-means++', n_init = 30, max_iter = 500, tol = 1e-5)
	kmeans = kmeans.fit(X)
	p_labels = kmeans.predict(X)

	#9 es a 2, 0 es a 3, 1 es a 8
	tp, fp = 0, 0
	for i in range(labels.shape[0]):
		if labels[i, 0] == 9 and p_labels[i] == 2:
			tp += 1
		elif labels[i, 0] == 3 and p_labels[i] == 0:
			tp += 1
		elif labels[i, 0] == 8 and p_labels[i] == 1:
			tp += 1
		elif labels[i, 0] == 9 or labels[i, 0] == 3 or labels[i, 0] == 8:
			fp += 1

	prec = float(tp) / float(tp + fp)
	print("Precision de la clasificacion: ", prec)

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

	m = 300
	p = 0.4
	W_PCA = optimization.PCA(data, m)

	data_proj_PCA = data.dot(W_PCA)
	data_mean = np.zeros((data.shape[1]), dtype = 'float')
	for i in range(data.shape[1]):
		data_mean[i] = np.mean(data[:, i])
	
	gm = optimization.gen_mean(data, data_mean, p)
	_, W_PCAGM = optimization.PCAGM(data, gm, m, W_PCA, p)
	data_proj_PCAGM = data.dot(W_PCAGM)

	k = 3
	make_clustering(data_proj_PCA, labels, 3)
	make_clustering(data_proj_PCAGM, labels, 3)

if __name__ == '__main__':
	main()