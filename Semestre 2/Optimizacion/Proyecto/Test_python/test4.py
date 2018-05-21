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
	#p2 = np.random.multivariate_normal([0.5, 0.5], [[0.5, 0], [0, 0.5]], 10)
	p2 = np.random.multivariate_normal([5, 5], [[0.3, 0], [0, 0.3]], 0)
	X = np.concatenate((p1, p2), axis = 0)

	return X

def gen_points3():
	p1 = gen_points(100)
	#p2 = np.random.multivariate_normal([4, 4], [[1.0, 0], [0, 1.0]], 1)
	p2 = np.random.multivariate_normal([-0.5, -0.5], [[0.3, 0], [0, 0.3]], 5)
	X = np.concatenate((p1, p2), axis = 0)

	return X

#---- Parte de optimizacion ----#
def gen_mean(x, sm_x, sm_y, p):
	t = 0
	sz = len(x)
	delta = 0.0001
	tol = 1e-12
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

def diagonal(M):
	U, s, Vt = LA.svd(M, full_matrices = False)
	S = np.diag(s)

	return U, S

def computeResiduals(Xgc, U):
	XProj = Xgc.dot(U)
	R = Xgc.dot(Xgc.T) - XProj.dot(XProj.T)
	#print(R)
	errors = np.diag(R)

	return errors

def PCA(X):
	nPoints, nVar = X.shape
	meanPoints = np.mean(X, axis = 0)
	Xc = X - meanPoints
	C = Xc.T.dot(Xc) / float(nPoints)
	W, _ = diagonal(C)

	return W

def g_PCA(X, gm, p):
	maxIter = 100
	rat = 0.01
	tol = 1e-13
	delta = 1e-13

	U = PCA(X)
	Xgc = X
	M_aux = np.ones((X.shape[0], X.shape[1]), dtype = 'float')
	#Xgc -= np.mean(Xgc, axis = 0)
	M_aux[:, 0] *= gm[0]
	M_aux[:, 1] *= gm[1]
	Xgc -= M_aux
	residue = computeResiduals(Xgc, U)
	residue = residue + delta
	v_aux = np.zeros(np.size(residue), dtype = 'float')
	for i in range(np.size(residue)):
		v_aux[i] = np.power(residue[i], p)

	objF = np.sum(v_aux)
	minRes = residue.min()
	eps = rat * minRes
	flag = False
	cnt = 0

	while flag == False:
		cnt = cnt + 1
		lst_U = U
		lst_objF = objF
		print("Iter: ", cnt)

		residue = residue + eps * np.ones(np.size(residue), dtype = 'float')
		alphas = np.power(residue, p - 1.0)
		A = np.sqrt(np.diag(alphas))
		S = Xgc.T.dot(A)
		Un, _, _ = LA.svd(S, full_matrices = False)
		U = Un

		residue = computeResiduals(Xgc, U)
		residue = residue + delta
		objF = (np.sum(np.power(residue, p)))
		print(lst_objF - objF)

		if lst_objF - objF < tol:
			print(1)
			flag = True
		elif objF >= lst_objF:
			print(2)
			flag = True
			U = lst_U
		elif cnt >= maxIter:
			print(3)
			flag = True
		else:
			print(4)

	return U

#---- Main ----#
def main():
	X = gen_points3()
	p = 0.5
	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	gm = gen_mean(X, sm_x, sm_y, p)
	Y = X
	Y[:, 0] -= sm_x
	Y[:, 1] -= sm_y
	W = PCA(X)
	V = g_PCA(X, gm, p)
	print(W)
	print(V)
	#plt.plot(X[:, 0], X[:, 1], 'ro')
	plt.plot(Y[:, 0], Y[:, 1], 'ro', color = 'g')
	plt.quiver([0], [0], [W[0, 0]], [W[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['black'])
	plt.quiver([0], [0], [V[0, 0]], [V[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['b'])
	plt.axis([-2, 7, -2, 7])
	plt.show()

if __name__ == '__main__':
	main()