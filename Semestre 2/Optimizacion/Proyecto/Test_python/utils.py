import numpy as np
from numpy import linalg as LA
import os, sys, glob

def gen_points(n):
	X = np.zeros((n, 2), dtype = 'float')
	cx1 = 0.0
	cy1 = 0.0
	cnt = 0
	while True:
		xi = np.random.rand(1, 1)
		yi = np.random.rand(1, 1)
		if ((xi - cx1) ** 2 / 0.9) + ((yi - cy1) ** 2 / 0.1) <= 1:
			X[cnt, 0] = xi
			X[cnt, 1] = yi
			cnt += 1
		if cnt == n:
			break

	return X

def gen_points2():
	p1 = np.random.multivariate_normal([0, 0], [[0.5, 0], [0, 0.5]], 100)
	#p2 = np.random.multivariate_normal([0.5, 0.5], [[0.5, 0], [0, 0.5]], 10)
	p2 = np.random.multivariate_normal([5, 5], [[0.3, 0], [0, 0.3]], 0)
	X = np.concatenate((p1, p2), axis = 0)

	return X

def gen_points3():
	p1 = gen_points(100)
	#p2 = np.random.multivariate_normal([4, 4], [[1.0, 0], [0, 1.0]], 1)
	p2 = np.random.multivariate_normal([1, 1], [[0.3, 0], [0, 0.3]], 5)
	X = np.concatenate((p1, p2), axis = 0)

	return X

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