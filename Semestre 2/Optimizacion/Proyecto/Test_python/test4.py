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

def gen_mean(x, sm_x, sm_y, p):
	maxIter = 50
	sz = len(x)
	sm_x_iter, sm_y_iter = sm_x, sm_y
	x_centered = x.copy()
	x_centered[:, 0] -= sm_x
	x_centered[:, 1] -= sm_y
	objF = np.sum(np.power(np.diag(x_centered.dot(x_centered.T)), p))

	cnt = 0
	flag = False
	meanSampsIter = np.array([sm_x, sm_y])
	while flag == False:
		cnt += 1
		print(cnt)
		last_meanSamps = meanSampsIter
		last_objF = objF

		x_centered = x.copy()
		x_centered[:, 0] -= meanSampsIter[0]
		x_centered[:, 1] -= meanSampsIter[1]

		alphas = np.power(np.diag(x_centered.dot(x_centered.T)), p - 1.0)
		meanSampsIter = x.T.dot(alphas / np.sum(alphas)).T

		x_centered = x.copy()
		x_centered[:, 0] -= meanSampsIter[0]
		x_centered[:, 1] -= meanSampsIter[1]

		objF = np.sum(np.power(np.diag(x_centered.dot(x_centered.T)), p))
		
		diffMean = meanSampsIter - last_meanSamps
		diffMeanNorm = np.sqrt(np.inner(diffMean, diffMean))

		if cnt >= maxIter:
			flag = True
		elif diffMeanNorm / np.sqrt(np.inner(meanSampsIter, meanSampsIter)) * 100.0 < 0.01:
			flag = True
		elif objF >= last_objF:
			flag = True
			meanSampsIter = last_meanSamps


	return meanSampsIter

def PCA_J_fn(X, W):
	(n, m) = X.shape
	WW = W.dot(W.T)
	res = 0.0
	for i in range(n):
		res += LA.norm(X[i, :] - WW.dot(X[i, :])) ** 2

	res /= float(n)
	return res

def PCAGM_J_fn(X, W, p):
	#Se asume que los datos estan centrados
	(n, m) = X.shape
	WW = W.dot(W.T)
	res = 0.0
	for i in range(n):
		aux = WW.dot(X[i, :])
		ei = np.inner(X[i, :], X[i, :]) - np.inner(X[i, :], aux)
		res += np.float_power(ei, p)

	res /= float(n)
	res = np.float_power(res, 1.0 / p)
	return res

def diagonal(M):
	U, s, Vt = LA.svd(M, full_matrices = False)
	S = np.diag(s)

	return U, S

def computeResiduals(Xgc, U):
	XProj = Xgc.dot(U)
	R = np.subtract(Xgc.dot(Xgc.T), XProj.dot(XProj.T))
	#R = Xgc.dot(Xgc.T) - XProj.dot(XProj.T)
	errors = np.diag(R)

	return errors

def PCA(X, noEig):
	nPoints, nVar = X.shape
	meanPoints = np.mean(X, axis = 0)
	Xc = X - meanPoints
	if nPoints < nVar:
		C = Xc.dot(Xc.T) / float(nPoints)
		W, _ = diagonal(C)
		W_sh = W[:, 0 : noEig]
		W_PCA = Xc.T.dot(W_sh)
		for i in range(noEig):
			W_PCA[:, i] = W_PCA[:, i] / np.sqrt(W_PCA[:, i].T.dot(W_PCA[:, i]))
	else:	
		C = Xc.T.dot(Xc) / float(nPoints)
		W, _ = diagonal(C)
		W_PCA = W[:, 0 : noEig]

	return W_PCA

def g_PCA(X, gm, noEig, U_0, p):
	maxIter = 100
	rat = 1.0
	tol = 1e-5
	delta = 1e-10

	U = U_0.copy()
	Xgc = X.copy()
	M_aux = np.ones((X.shape[0], X.shape[1]), dtype = 'float')
	M_aux[:, 0] *= gm[0]
	M_aux[:, 1] *= gm[1]
	Xgc -= M_aux
	residue = computeResiduals(Xgc, U)
	v_aux = np.float_power(residue, p)
	objF = np.sum(v_aux)

	minRes = residue.min()
	eps = rat * minRes
	flag = False
	cnt = 0

	f_evals = [PCAGM_J_fn(Xgc, U, p)]
	while flag == False:
		cnt = cnt + 1
		lst_U = U.copy()
		lst_objF = objF
		print("Iter: ", cnt)

		residue = residue + eps * np.ones(np.size(residue), dtype = 'float')
		alphas = np.power(residue, p - 1.0)
		A = np.sqrt(np.diag(alphas))
		S = Xgc.T.dot(A)
		Un, _, _ = LA.svd(S, full_matrices = False)
		U = Un[:, 0 : noEig].copy()

		residue = computeResiduals(Xgc, U)
		v_aux = np.float_power(residue + delta * np.ones(np.size(residue), dtype = 'float'), p)
		objF = np.sum(v_aux)
		f_evals.append(PCAGM_J_fn(Xgc, U, p))

		if lst_objF - objF < tol:
			print(1)
			flag = True
		elif objF >= lst_objF:
			print(2)
			flag = True
			U = lst_U.copy()
		elif cnt >= maxIter:
			print(3)
			flag = True
		else:
			print(4)

	return f_evals, U

#---- Main ----#
def main():
	X = gen_points3()
	p = 0.3
	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	gm = gen_mean(X, sm_x, sm_y, p)
	Y = X.copy()
	Y[:, 0] -= sm_x
	Y[:, 1] -= sm_y
	W = PCA(X, 1)
	_, V = g_PCA(X, gm, 1, W, p)
	print("PCA")
	print(W)
	print(V)

	plt.plot(Y[:, 0], Y[:, 1], 'ro', color = 'g')
	plt.quiver([0], [0], [W[0, 0]], [W[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['black'])
	plt.quiver([0], [0], [V[0, 0]], [V[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['b'])
	plt.axis([-2, 7, -2, 7])
	plt.show()

if __name__ == '__main__':
	main()