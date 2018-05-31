import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

import utils, optimization

def main():
	X = utils.gen_points_ex()
	Y = X.copy()
	p = 0.3

	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	m_d = np.array([sm_x, sm_y], dtype = 'float')
	gm = optimization.gen_mean(X, m_d, p)
	X[:, 0] -= gm[0]
	X[:, 1] -= gm[1]

	meanPoints = np.mean(Y, axis = 0)
	Y = Y - meanPoints

	linf, lsup = 0.0, 180.0
	n = 150
	dx = (lsup - linf) / float(n - 1)
	angle = np.zeros((n), dtype = 'float')
	y_PCA = np.zeros((n), dtype = 'float')
	y_PCAGM = np.zeros((n), dtype = 'float')
	for i in range(n):
		angle[i] = float(linf) + i * dx
		r_aux = np.radians(angle[i])
		W_aux = np.zeros((2, 1), dtype = 'float')
		W_aux[0, 0] = np.cos(r_aux)
		W_aux[1, 0] = np.sin(r_aux)
		y_PCA[i] = optimization.PCA_J_fn(Y, W_aux)
		y_PCAGM[i] = optimization.PCAGM_J_fn(X, W_aux, p)

	plt.plot(angle, y_PCA, color = 'g')
	plt.plot(angle, y_PCAGM, color = 'b')
	plt.show()


if __name__ == '__main__':
	main()