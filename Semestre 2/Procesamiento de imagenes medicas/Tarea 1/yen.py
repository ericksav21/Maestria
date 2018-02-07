import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import matplotlib.cm as cm
from skimage import data, img_as_ubyte
from skimage.color import rgb2gray, rgb2grey
from skimage.filters import threshold_otsu
import math, sys, os

def threshold_yen(data):
	tot = np.sum(data)
	data_f = data.astype(np.float)

	norm_hist = data_f / tot
	#Funcion prob. acum.
	P = np.zeros(256)
	P1 = np.zeros(256)
	P2 = np.zeros(256)

	P[0] = norm_hist[0]
	P1[0] = norm_hist[0]**2
	for i in xrange(1, 256):
		P[i] = P[i - 1] + norm_hist[i]
		P1[i] = P1[i - 1] + (norm_hist[i] ** 2)

	for i in reversed(range(255)):
		P2[i] = P2[i + 1] + (norm_hist[i + 1] ** 2)

	threshold = -1
	mmax = sys.float_info.min
	for i in range(256):
		c1 = math.log(P1[i] * P2[i]) if P1[i] * P2[i] > 0.0 else 0.0
		c2 = math.log(P[i] * (1.0 - P[i])) if P[i] * (1.0 - P[i]) > 0.0 else 0.0
		aux = -1.0 * c1 + 2.0 * c2
		if aux > mmax:
			mmax = aux
			threshold = i
	
	return threshold

def main():
	file_name = sys.argv[1]
	name = os.path.splitext(file_name)[0]
	img = img_as_ubyte(mpimg.imread('Images/{}'.format(file_name)))
	img = img_as_ubyte(rgb2gray(img))
	print "Tamano de la imagen: ({}, {})".format(img.shape[0], img.shape[1])

	#Calcular el histograma
	hist = np.zeros(256, dtype = 'uint')
	for i in xrange(img.shape[0]):
		for j in xrange(img.shape[1]):
			hist[img[i, j]] += 1


	threshold = threshold_yen(hist)
	thresholded = img > threshold
	print "Valor de umbral: {}".format(threshold)

	#Guardar el histograma
	x = np.linspace(0, 255, 256)
	plt.plot(x, hist)
	plt.axvline(x = threshold, color = 'black')
	plt.savefig('Images/{}_hist.png'.format(name))

	mpimg.imsave('Images/{}_yen.png'.format(name), thresholded, cmap = cm.Greys_r)

	#Aplicar el algoritmo de OTSU
	otsu_thresh = threshold_otsu(img)
	otsu_thresholded = img > otsu_thresh
	mpimg.imsave('Images/{}_otsu.png'.format(name), otsu_thresholded, cmap = cm.Greys_r)

if __name__ == "__main__":
	main()