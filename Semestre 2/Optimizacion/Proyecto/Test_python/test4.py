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
	p1 = gen_points(20)
	#p2 = np.random.multivariate_normal([4, 4], [[1.0, 0], [0, 1.0]], 1)
	p2 = np.random.multivariate_normal([3, 3], [[0.3, 0], [0, 0.3]], 2)
	X = np.concatenate((p1, p2), axis = 0)

	return X

#---- Parte de optimizacion ----#
'''def gen_mean(x, sm_x, sm_y, p):
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

	return gm'''

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


def diagonal(M):
	U, s, Vt = LA.svd(M, full_matrices = False)
	S = np.diag(s)

	return U, S

def computeResiduals(Xgc, U):
	Xgc_aux = np.array(Xgc, dtype = np.longdouble)
	U_aux = np.array(U, dtype = np.longdouble)
	XProj = np.longdouble(Xgc_aux.dot(U_aux))
	R = np.longdouble(np.subtract(Xgc_aux.dot(Xgc_aux.T), XProj.dot(XProj.T)))
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

def g_PCA(X, gm, noEig, p):
	maxIter = 100
	rat = 1.0
	tol = 1e-5
	delta = 1e-13

	U = PCA(X, noEig)
	Xgc = X.copy()
	M_aux = np.ones((X.shape[0], X.shape[1]), dtype = 'float')
	M_aux[:, 0] *= gm[0]
	M_aux[:, 1] *= gm[1]
	Xgc -= M_aux
	residue = np.longdouble(computeResiduals(Xgc, U))
	#residue = residue + delta
	v_aux = np.longdouble(np.float_power(residue, p))
	objF = np.sum(v_aux)

	minRes = residue.mean()
	eps = rat * minRes
	flag = False
	cnt = 0

	while flag == False:
		cnt = cnt + 1
		lst_U = U.copy()
		lst_objF = objF
		print("Iter: ", cnt)

		residue = residue + eps * np.ones(np.size(residue), dtype = 'float')
		alphas = np.power(residue, p - 1.0)
		A = np.sqrt(np.diag(alphas))
		S = np.float64(Xgc.T.dot(A))
		Un, _, _ = LA.svd(S, full_matrices = False)
		U = Un[:, 0 : noEig].copy()

		residue = computeResiduals(Xgc, U)
		#residue = residue + delta
		v_aux = np.longdouble(np.float_power(residue + eps, p))
		objF = np.sum(v_aux)

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

	return U

#---- Main ----#
def main():
	X = gen_points3()
	'''X = np.array([[4.26626625e-01, 1.56283527e-01],
					 [6.59907107e-01, 5.65598772e-02],
					 [5.51226781e-01, 6.67020756e-02],
					 [9.43067169e-02, 1.31892281e-01],
					 [1.72283828e-01, 2.02385756e-01],
					 [5.61692330e-01, 9.67861317e-02],
					 [3.39888746e-02, 2.50193632e-02],
					 [1.08184376e-01, 1.40396619e-01],
					 [4.07350906e-01, 1.90069896e-01],
					 [1.62481740e-01, 2.77166196e-01],
					 [9.71744212e-02, 1.13628924e-01],
					 [2.82885520e-02, 6.50027667e-02],
					 [4.35261216e-01, 1.94798811e-01],
					 [2.18142741e-01, 1.33335477e-01],
					 [1.02873443e-01, 1.39007032e-01],
					 [2.37791407e-01, 1.20676655e-01],
					 [2.41890881e-01, 2.02274347e-03],
					 [3.82936607e-01, 2.15804912e-01],
					 [1.24889117e-01, 1.46707311e-01],
					 [4.50116919e-01, 2.42119830e-01],
					 [3.15527909e+00, 3.19645919e+00],
					 [3.26713497e+00, 3.01798668e+00]]
					)'''
	p = 0.2
	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	gm = gen_mean(X, sm_x, sm_y, p)
	Y = X.copy()
	Y[:, 0] -= sm_x
	Y[:, 1] -= sm_y
	W = PCA(X, 2)
	V = g_PCA(X, gm, 2, p)
	print("PCA")
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