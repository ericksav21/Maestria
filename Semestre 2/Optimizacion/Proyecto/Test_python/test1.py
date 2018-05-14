import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

def gen_mean(x, sm_x, sm_y, p):
	t = 0
	sz = len(x)
	delta = 0.0001
	tol = 1e-8
	gm = np.array([sm_x, sm_y], dtype = 'float')
	last_gm = gm
	alphas = np.zeros(sz, dtype = 'float')
	while True:
		#Calcular los coeficientes alpha
		for i in range(sz):
			na = LA.norm(x[i] - gm, 2)
			alphas[i] = np.power(na * na + delta, p - 1.0)
		aux = np.sum(alphas)
		aux2 = np.zeros(2, dtype = 'float')
		for i in range(sz):
			aux2 = aux2 + (alphas[i] * x[i])
		gm = (1.0 / aux) * aux2
		#Verificar criterio de paro
		norm = (LA.norm(gm - last_gm, 2) / max(1.0, LA.norm(gm, 2)))
		print(norm)
		if norm < tol:
			break
		t = t + 1
		last_gm = gm

	return gm

def gradient_m(x, m, p):
	sz = len(x)
	g = np.zeros(2, dtype = 'float')
	for i in range(sz):
		na = LA.norm(x[i] - m, 2)
		aux = np.power(na * na, p - 1.0)
		g[0] += aux * (x[i, 0] + m[0])
		g[1] += aux * (x[i, 1] + m[1])
	g = g * (-2.0 * p)

	return g

def Hessian_m(x, m, p):
	sz = len(x)
	H = np.zeros((2, 2), dtype = 'float')
	for i in range(sz):
		na = LA.norm(x[i] - m, 2)
		aux1 = np.power(na * na, p - 1.0)
		aux2 = np.power(na * na, p - 2.0)
		H[0, 0] += (aux2 * (x[i, 0] - m[0]) ** 2 + aux1)
		H[1, 1] += (aux2 * (x[i, 1] - m[1]) ** 2 + aux1)
		H[0, 1] += (aux2 * (x[i, 0] - m[0]) * (x[i, 1] - m[1]))
		H[1, 0] += (aux2 * (x[i, 0] - m[0]) * (x[i, 1] - m[1]))
	H = H * 4.0 * p * (p - 1.0)

	return H

def gen_mean2(x, sm_x, sm_y, p):
	t = 0
	sz = len(x)
	delta = 0.0001
	tol = 1e-3
	gm = np.array([sm_x, sm_y], dtype = 'float')
	while True:
		g = gradient_m(x, gm, p)
		H = Hessian_m(x, gm, p)
		na = LA.norm(g, 2)
		print(na)
		if na < tol:
			break

		gaux = H.dot(g)
		gamma = np.inner(g, g) / np.inner(g, gaux)
		gm1 = gm - (gamma * g)
		gm = gm1
		t += 1

	return gm

def main():
	p1 = np.random.multivariate_normal([0, 0], [[0.5, 0], [0, 0.5]], 100)
	p2 = np.random.multivariate_normal([5, 5], [[0.3, 0], [0, 0.3]], 10)
	data = np.concatenate((p1, p2), axis = 0)
	(x, y) = (p1[:, 0], p1[:, 1])
	x = np.append(x, p2[:, 0])
	y = np.append(y, p2[:, 1])

	sm_x = np.mean(x)
	sm_y = np.mean(y)
	#gm = gen_mean(data, sm_x, sm_y, 0.1)
	gm = gen_mean2(data, sm_x, sm_y, 0.1)
	print(gm)

	plt.plot(x, y, 'ro')
	plt.plot(sm_x, sm_y, 'bs')
	plt.plot(gm[0], gm[1], 'bs')
	plt.axis([-2, 7, -2, 7])
	plt.show()

if __name__ == '__main__':
	main()