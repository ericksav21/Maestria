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

def GPCA(X, p, q, nComps)

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
	p = 0.3
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