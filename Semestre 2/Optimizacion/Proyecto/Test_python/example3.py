import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

import utils, optimization

def main():
	p = 0.3
	X = utils.gen_points_ex()
	X_wo = utils.gen_points_no_out()
	no_eig = 1

	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	m_d = np.array([sm_x, sm_y], dtype = 'float')
	gm = optimization.gen_mean(X, m_d, p)

	W = optimization.PCA(X, no_eig)
	W_wo = optimization.PCA(X_wo, no_eig)
	W_0 = np.matrix('0.86607; 0.49991', dtype = 'float')

	_, V = optimization.PCAGM(X, gm, 1, W_0, p)
	PCA_fn = optimization.PCA_J_fn(X, W)

	print("Resultados sin datos atipicos (PCA).")
	print(W_wo)
	print("Resultados con datos atipicos (PCA).")
	print(W)
	print("Resultados con datos atipicos (PCAGM).")
	print(V)

	plt.plot(X[:, 0], X[:, 1], 'ro', color = 'g')
	plt.quiver([0], [0], [W[0, 0]], [W[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['black'])
	plt.quiver([0], [0], [V[0, 0]], [V[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['b'])
	plt.axis([-3, 5, -2, 7])
	plt.show()

	return 0

if __name__ == '__main__':
	main()