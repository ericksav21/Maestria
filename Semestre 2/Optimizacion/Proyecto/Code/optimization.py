import numpy as np
from numpy import linalg as LA
import os, sys, glob

def gen_mean(x, m_d, p):
	maxIter = 50
	sz = len(x)
	x_centered = x.copy()
	for i in range(x_centered.shape[1]):
		x_centered[:, i] -= m_d[i]
	objF = np.sum(np.power(np.diag(x_centered.dot(x_centered.T)), p))

	cnt = 0
	flag = False
	meanSampsIter = m_d.copy()
	while flag == False:
		cnt += 1
		last_meanSamps = meanSampsIter
		last_objF = objF

		x_centered = x.copy()
		for i in range(x_centered.shape[1]):
			x_centered[:, i] -= meanSampsIter[i]

		alphas = np.power(np.diag(x_centered.dot(x_centered.T)), p - 1.0)
		meanSampsIter = x.T.dot(alphas / np.sum(alphas)).T

		x_centered = x.copy()
		for i in range(x_centered.shape[1]):
			x_centered[:, i] -= meanSampsIter[i]

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

#Funcion objetivo de PCA
def PCA_J_fn(X, W):
	(n, m) = X.shape
	WW = W.dot(W.T)
	res = 0.0
	for i in range(n):
		res += LA.norm(X[i, :] - WW.dot(X[i, :])) ** 2

	res /= float(n)
	return res

#Funcion objetivo de GM PCA
def PCAGM_J_fn(X, W, p):
	delta = 1e-3
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

#Obtiene la descomposicion SVD de la matriz M y diagonaliza los valores singulares
def diagonal(M):
	U, s, Vt = LA.svd(M, full_matrices = False)
	S = np.diag(s)

	return U, S

#Calcula los valores residuales
def computeResiduals(Xgc, U):
	XProj = Xgc.dot(U)
	R = np.subtract(Xgc.dot(Xgc.T), XProj.dot(XProj.T))
	errors = np.diag(R)

	return errors

#Implementacion de PCA usando la descomposicion SVD
def PCA(X, noEig):
	nPoints, nVar = X.shape
	meanPoints = np.mean(X, axis = 0)
	Xc = X - meanPoints
	#Calcular la matriz de covarianza dependiendo si hay mas datos que dimensiones o al reves
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
	maxIter = 1000
	rat = 1.0
	tol = 1e-5
	delta = 1e-10

	U = U_0.copy()
	Xgc = X.copy()
	for i in range(Xgc.shape[1]):
		Xgc[:, i] -= gm[i]
		
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
		print("Funcion objetivo: ", f_act)
		f_evals.append(f_act)

		if lst_objF - objF < tol:
			flag = True
		elif objF >= lst_objF:
			flag = True
			U = lst_U.copy()
		elif cnt >= maxIter:
			flag = True

	return f_evals, U