import numpy as np
from numpy import linalg as LA
import os, sys, glob

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

#En esta parte se implementó el mismo algoritmo de la media generalida pero usando descenso de gradiente
#El gradiente de la función
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

#El Hessiano de la función
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
		#Se obtiene el tamaño de paso exacto
		gamma = np.inner(g, g) / np.inner(g, gaux)
		gm1 = gm - (gamma * g)
		gm = gm1
		t += 1

	return gm

#Función objetivo de PCA
def PCA_J_fn(X, W):
	(n, m) = X.shape
	WW = W.dot(W.T)
	res = 0.0
	for i in range(n):
		res += LA.norm(X[i, :] - WW.dot(X[i, :])) ** 2

	res /= float(n)
	return res

#Función objetivo de GM PCA
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

.#Obtiene la descomposición SVD de la matriz M y diagonaliza los valores singulares
def diagonal(M):
	U, s, Vt = LA.svd(M, full_matrices = False)
	S = np.diag(s)

	return U, S

#Calcula los valores residuales
def computeResiduals(Xgc, U):
	XProj = Xgc.dot(U)
	R = np.subtract(Xgc.dot(Xgc.T), XProj.dot(XProj.T))
	#R = Xgc.dot(Xgc.T) - XProj.dot(XProj.T)
	errors = np.diag(R)

	return errors

#Implementación de PCA usando la descomposición SVD
def PCA(X, noEig):
	nPoints, nVar = X.shape
	meanPoints = np.mean(X, axis = 0)
	Xc = X - meanPoints
	#Calcular la matriz de covarianza dependiendo si hay más datos que dimensiones o al revés
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

def PCAGM(X, gm, noEig, U_0, p):
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
		#Calcular las alphas
		alphas = np.power(residue, p - 1.0)
		A = np.sqrt(np.diag(alphas))
		S = Xgc.T.dot(A)
		#Resolver problema de eigenvectores
		Un, _, _ = LA.svd(S, full_matrices = False)
		U = Un[:, 0 : noEig].copy()

		residue = computeResiduals(Xgc, U)
		v_aux = np.float_power(residue + delta * np.ones(np.size(residue), dtype = 'float'), p)
		objF = np.sum(v_aux)
		f_act = PCAGM_J_fn(Xgc, U, p)
		print("Función objetivo: ", f_act)
		f_evals.append(f_act)

		if lst_objF - objF < tol:
			flag = True
		elif objF >= lst_objF:
			flag = True
			U = lst_U.copy()
		elif cnt >= maxIter:
			flag = True
		else:
			yield

	return f_evals, U