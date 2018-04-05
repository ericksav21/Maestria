# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import matplotlib.cm as cm
from skimage import data, img_as_ubyte
from skimage.color import rgb2gray, rgb2grey
from skimage.filters import threshold_otsu
from numpy import linalg as LA
import math, sys, os
from PIL import Image

def read_data():
	nFile = 'res.txt'

	lines = []

	for line in open(nFile):
		lines.append(line)

	nbins, ngaus, sigma = list(map(int, lines[0].split()))

	alp = []
	mu = []

	alp.append(np.array(list(map(float, lines[1].split()))))
	mu.append(np.array(list(map(float, lines[2].split()))))

	alp.append(np.array(list(map(float, lines[3].split()))))
	mu.append(np.array(list(map(float, lines[4].split()))))

	return nbins, ngaus, sigma, alp, mu

def vec_c(nbins):
	res = np.zeros((nbins ** 3, 3), dtype = np.float)
	cnt = 0
	for r in range(nbins):
		for g in range(nbins):
			for b in range(nbins):
				res[cnt, 0] = float(r)
				res[cnt, 1] = float(g)
				res[cnt, 2] = float(b)
				cnt = cnt + 1

	return res

def faux(c_k, mu_i, sigma):
    return np.exp(-0.5 * np.linalg.norm(c_k - mu_i) / (sigma ** 2))

def main():
	sigma, ngaus, sigma, alpha, mu = read_data()
	#v_c = vec_c(nbins)

	#Cambiar el nombre de la imagen.
	img = np.array(Image.open('rose.png'))
	#img = np.array(Image.open('person1.bmp'))

	#Cambiar los nombres de los histogramas.
	txth0 = np.loadtxt('H_0.txt', usecols=(0,))
	txth1 = np.loadtxt('H_1.txt', usecols=(0,))
	Nbins = int(txth0[0])

	hc0 = txth0[1 : Nbins ** 3 + 1]
	H0 = np.zeros((Nbins, Nbins, Nbins), np.int32)
	hc1 = txth1[1 : Nbins ** 3 + 1]
	H1 = np.zeros((Nbins, Nbins, Nbins), np.int32)

	k = 0
	for r in range(Nbins):
		for g in range(Nbins):
			for b in range(Nbins):
				H0[r][g][b] = hc0[k]
				H1[r][g][b] = hc1[k]
				k+=1

	img2 = img.copy()
	img3 = img.copy()

	umbral = int(256 / Nbins)

	epsilon = 0.01
	Fcol1 = 0
	Fcol2 = 0
	sigma = float(sigma)

	for i in range(np.shape(img)[0]):
		for j in range(np.shape(img)[1]):
			bin_x = int(float(img[i, j, 0]) / 256.0 * Nbins)
			bin_y = int(float(img[i, j, 1]) / 256.0 * Nbins)
			bin_z = int(float(img[i, j, 2]) / 256.0 * Nbins)
			c_k = np.array([bin_x, bin_y, bin_z])
			mu_k1 = np.zeros((3), dtype = 'float')
			mu_k2 = np.zeros((3), dtype = 'float')
			fbin1 = 0
			fbin2 = 0
			for ng in range(ngaus):
				for ax in range(3):
					mu_k1[ax] = mu[0][ng * 3 + ax]
					mu_k2[ax] = mu[1][ng * 3 + ax]
				fbin1 += alpha[0][ng] * faux(c_k, mu_k1, sigma)
				fbin2 += alpha[1][ng] * faux(c_k, mu_k2, sigma)

			Fcol1 = (fbin1 + epsilon) / (fbin1 + fbin2 + 2.0 * epsilon)
			Fcol2 = (fbin2 + epsilon) / (fbin1 + fbin2 + 2.0 * epsilon)
			if Fcol1 < Fcol2:
				img2[i][j][:] = (0, 0, 255)
			else:
				img2[i][j][:] = (255, 0, 0)

			hbin1 = H0[c_k[0]][c_k[1]][c_k[2]]
			hbin2 = H1[c_k[0]][c_k[1]][c_k[2]]
			Hcol1 = (hbin1 + epsilon) / (hbin1 + hbin2 + 2.0 * epsilon)
			Hcol2 = (hbin2 + epsilon) / (hbin1 + hbin2 + 2.0 * epsilon)
			if Hcol1 < Hcol2:
				img3[i][j][:] = (0, 0, 255)
			else:
				img3[i][j][:] = (255, 0, 0)

	plt.figure(1)
	plt.imshow(img2)
	plt.show()
	plt.figure(2)
	plt.imshow(img3)
	plt.show()

if __name__ == "__main__":
	main()