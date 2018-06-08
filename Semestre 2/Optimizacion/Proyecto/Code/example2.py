import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

import utils, optimization

#---- Main ----#
def main():
	if len(sys.argv) == 1:
		print("Ejecuta: python3 example2.py [p].")
		return
	p = float(sys.argv[1])

	X = utils.gen_points3()
	(x, y) = (X[:, 0], X[:, 1])
	sm_x = np.mean(x)
	sm_y = np.mean(y)
	m_d = np.array([sm_x, sm_y], dtype = 'float')
	gm = optimization.gen_mean(X, m_d, p)
	Y = X.copy()
	no_eig = 1
	Y[:, 0] -= sm_x
	Y[:, 1] -= sm_y
	W = optimization.PCA(X, no_eig)
	_, V = optimization.PCAGM(X, gm, no_eig, W, p)
	print("PCA (primera direccion):")
	print(W)
	print("PCAGM (primera direccion):")
	print(V)

	plt.plot(Y[:, 0], Y[:, 1], 'ro', color = 'g')
	plt.quiver([0], [0], [W[0, 0]], [W[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['black'])
	plt.quiver([0], [0], [V[0, 0]], [V[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1, color = ['b'])
	plt.axis([-2, 7, -2, 7])
	plt.show()

if __name__ == '__main__':
	main()
