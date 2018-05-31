# -*- coding: utf-8 -*-

import numpy as np
from numpy import linalg as LA
import os, sys, glob
import matplotlib.pyplot as plt

import utils, optimization

#Este es la primer prueba del paper, donde se compara el algoritmo de la media generalizada
#con la media normal, al ejecutar el codigo se llamarán ambos algoritmos y se mostrara en una grafica
#los resultados obtenidos donde el punto verde es la media normal y el azul es la media generalida.

#Los puntos son generados en base a una distribucion bivariada gaussiana con media 0 y matriz de covarianza de 0.5
#para los inliers y media 5 y matriz de covarianza de 0.3 para los outliers.
def main():
	p1 = np.random.multivariate_normal([0, 0], [[0.5, 0], [0, 0.5]], 100)
	p2 = np.random.multivariate_normal([5, 5], [[0.3, 0], [0, 0.3]], 10)
	data = np.concatenate((p1, p2), axis = 0)
	(x, y) = (p1[:, 0], p1[:, 1])
	x = np.append(x, p2[:, 0])
	y = np.append(y, p2[:, 1])

	sm_x = np.mean(x)
	sm_y = np.mean(y)
	m_d = np.array([sm_x, sm_y], dtype = 'float')
	p = 0.3
	gm = optimization.gen_mean(data, m_d, p)
	print(gm)

	plt.plot(x, y, 'ro')
	plt.plot(sm_x, sm_y, 'bs', color = 'g')
	plt.plot(gm[0], gm[1], 'bs')
	plt.axis([-2, 7, -2, 7])
	plt.show()

if __name__ == '__main__':
	main()