import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

import test4

def gen_points_no_out():
	n = 100
	X = np.zeros((n, 2), dtype = 'float')
	cnt = 0
	for i in range(100):
		xi = np.random.normal(0, 1, 1)
		yi = xi + np.random.normal(0, 0.5 ** 2, 1)
		X[cnt, 0] = xi
		X[cnt, 1] = yi
		cnt += 1

	return X

def gen_points_ex():
	n = 110
	X = np.zeros((n, 2), dtype = 'float')
	cnt = 0
	for i in range(100):
		xi = np.random.normal(0, 1, 1)
		yi = xi + np.random.normal(0, 0.5 ** 2, 1)
		X[cnt, 0] = xi
		X[cnt, 1] = yi
		cnt += 1
	for i in range(10):
		xi = np.random.normal(0, 1)
		yi = xi + np.random.normal(0, 3 ** 2, 1)
		X[cnt, 0] = xi
		X[cnt, 1] = yi
		cnt += 1

	return X


def main():
	p = 0.3
	X = gen_points_ex()
	X_wo = gen_points_no_out()

	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	gm = test4.gen_mean(X, sm_x, sm_y, p)
	Y = X.copy()
	Y[:, 0] -= sm_x
	Y[:, 1] -= sm_y
	W = test4.PCA(X, 1)
	W_wo = test4.PCA(X_wo, 1)
	W_0 = np.matrix('0.86607; 0.49991', dtype = 'float')

	f_eval, V = test4.g_PCA(X, gm, 1, W_0, p)
	PCA_fn = test4.PCA_J_fn(X, W)
	idx = 0
	mmax = 10000000
	for i in range(len(f_eval)):
		if(f_eval[i] < mmax):
			mmax = f_eval[i]
			idx = i

	print(W_wo)
	print(V)
	print(PCA_fn)
	plt.plot(f_eval, color = 'g')
	plt.plot(idx, PCA_fn, 'ro')
	plt.show()

	return 0

if __name__ == '__main__':
	main()