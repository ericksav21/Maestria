import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

def gen_points(n):
	X = np.zeros((n, 2), dtype = 'float')
	cx1 = 0.0
	cy1 = 0.0
	cnt = 0
	while True:
		xi = np.random.rand(1, 1)
  		yi = np.random.rand(1, 1)
  		if ((xi - cx1) ** 2 / 0.5) + ((yi - cy1) ** 2 / 0.1) <= 1:
  			X[cnt, 0] = xi
  			X[cnt, 1] = yi
  			cnt += 1
  		if cnt == n:
  			break

  	return X

def gen_points2():
	p1 = np.random.multivariate_normal([0, 0], [[0.5, 0], [0, 0.5]], 100)
	#p2 = np.random.multivariate_normal([0, 0], [[0.5, 0], [0, 0.5]], 10)
	p2 = np.random.multivariate_normal([5, 5], [[0.3, 0], [0, 0.3]], 10)
	X = np.concatenate((p1, p2), axis = 0)

	return X

def gen_points3():
	p1 = gen_points(100)
	p2 = np.random.multivariate_normal([6, 6], [[1.0, 0], [0, 1.0]], 1)
	#p2 = np.random.multivariate_normal([5, 5], [[0.3, 0], [0, 0.3]], 10)
	X = np.concatenate((p1, p2), axis = 0)

	return X

def inf_n(X):
	return np.max(np.sum(np.abs(X), axis = 1))

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
		#print(norm)
		if norm < tol:
			break
		t = t + 1
		last_gm = gm

	return gm

def PCA(X, n):
	C = np.cov(X, rowvar = False)
	#print(X.T.dot(X) / float(n - 1))
	S, V = LA.eig(C)
	#idx = S.argsort()[::-1]
	#S, V = S[idx], V[:, idx]
	return S, V

def er(xi, W, delta):
	W_aux = W.dot(W.T)
	t1 = np.inner(xi, xi)
	t2 = W_aux.dot(xi)
	t3 = np.inner(xi, t2)

	return t1 - t3 + delta

def g_PCA(x, W, n, p):
	t = 0
	sz = len(x)
	delta = 0.001
	tol = 1e-8
	Wm = W
	last_Wm = W
	last_S = np.zeros(x.shape[1], dtype = 'float')
	betas = np.zeros(sz, dtype = 'float')
	while True:
		#Calcular los coeficientes beta
		for i in range(sz):
			aux = er(x[i], Wm, delta)
			betas[i] = np.power(aux, p - 1.0)
		#Generar la matrix de covarianza
		C = np.zeros((x.shape[1], x.shape[1]), dtype = 'float')
		for i in range(sz):
			aux = np.outer(x[i], x[i])
			aux = aux + (delta / float(sz) * np.identity(x.shape[1], dtype = 'float'))
			aux = aux * betas[i]
			C = C + aux
		#C = C / (sz - 1.0)
		last_S, V = LA.eig(C)
		print(last_S)
		Wm = V
		norm = (inf_n(Wm - last_Wm) / max(1.0, inf_n(Wm)))
		#print(norm)
		print(Wm)
		print("\n")
		if t == 100:
			break
		t = t + 1
		last_Wm = Wm

	return last_S, Wm

def main():
	#np.random.seed(7007)
	n, p = 100, 0.3
	#X = np.random.rand(n, 2)
	#X = gen_points(n)
	X = gen_points3()
	Y = X
	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	gm = gen_mean(X, sm_x, sm_y, p)
	Y[:, 0] -= sm_x
	Y[:, 1] -= sm_y
	X[:, 0] -= gm[0]
	X[:, 1] -= gm[1]
	S1, V = PCA(X, n)
	S2, W = g_PCA(X, V, n, p)
	
	idx1 = S1.argsort()[::-1]
	S1, V = S1[idx1], V[:, idx1]
	idx2 = S2.argsort()[::-1]
	S2, W = S2[idx2], W[:, idx2]
	print(V)
	print(W)

	plt.plot(X[:, 0], X[:, 1], 'ro')
	plt.quiver([0], [0], [V[0, 0]], [V[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['r'])
	plt.quiver([0], [0], [W[0, 0]], [W[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['g'])
	plt.axis([-2, 7, -2, 7])
	plt.show()

if __name__ == '__main__':
	main()
