import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

def flip_signs(A, B):
    """
    utility function for resolving the sign ambiguity in SVD
    http://stats.stackexchange.com/q/34396/115202
    """
    signs = np.sign(A) * np.sign(B)
    return A, B * signs

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

def main():
	n, p = 100, 2
	#X = np.random.rand(n, p)
	X = gen_points(n)
	# Let us assume that it is centered
	X -= np.mean(X, axis = 0)
	# the p x p covariance matrix
	C = np.cov(X, rowvar = False)
	print(C)
	#print(X.T.dot(X) / float(n - 1))
	l, principal_axes = LA.eig(C)
	# sort results wrt. eigenvalues
	idx = l.argsort()[::-1]
	l, principal_axes = l[idx], principal_axes[:, idx]
	# the eigenvalues in decreasing order
	print("l = \n", l)
	# a matrix of eigenvectors (each column is an eigenvector)
	print("V = \n", principal_axes)
	# projections of X on the principal axes are called principal components
	principal_components = X.dot(principal_axes)
	print("Y = \n", principal_components)

	# we now perform singular value decomposition of X
	# "economy size" (or "thin") SVD
	U, s, Vt = LA.svd(X, full_matrices=False)
	V = Vt.T
	S = np.diag(s)

	print("V = \n", V)

	plt.plot(X[:, 0], X[:, 1], 'ro')
	plt.quiver([0], [0], [principal_axes[0, 0]], [principal_axes[1, 0]], angles = 'xy', scale_units = 'xy', scale = 1)
	plt.axis([-2, 2, -2, 2])
	plt.show()

	# 1) then columns of V are principal directions/axes.
	assert np.allclose(*flip_signs(V, principal_axes))

	# 2) columns of US are principal components
	assert np.allclose(*flip_signs(U.dot(S), principal_components))

	# 3) singular values are related to the eigenvalues of covariance matrix
	assert np.allclose((s ** 2) / (n - 1), l)

if __name__ == '__main__':
	main()