import numpy as np
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import matplotlib.cm as cm
from skimage import data, img_as_ubyte

def dilation(img, ele_struct):
	# element structure analysis
	es_width = len(ele_struct[0])
	es_height = len(ele_struct)

	# loop definition
	h_begin = 0
	h_end = img.shape[0] - es_height + 1
	w_begin = 0
	w_end = img.shape[1] - es_width + 1
	kl_bin = [[0 for i in range(img.shape[1])] for i in range(img.shape[0])]

	for i in range(h_begin, h_end):
		for j in range(w_begin, w_end):
			hash = 0
			for m in range(0, es_height):
				for n in range(0, es_width):
					hash += img[i + m][j + n] & ele_struct[m][n]
			if hash > 0:
				kl_bin[int(i + es_height / 2)][int(j + es_width / 2)] = 1

	sbin = np.zeros((img.shape[0], img.shape[1]), dtype = 'int')
	for i in range(0, img.shape[0]):
		for j in range(0, img.shape[1]):
			if img[i][j] == 1 or kl_bin[i][j] == 1:
				sbin[i][j] = 255
	
	return sbin

def main():
	img = img_as_ubyte(mpimg.imread("CC.png"))
	es = [
		[0, 1, 0],
		[1, 1, 1],
		[0, 1, 0]
	]
	thresholded = img > 254
	thresholded = thresholded.astype(int)
	dilated = dilation(img, es)
	mpimg.imsave("CC_res.png", dilated, cmap = cm.Greys_r)

	return 0

if __name__ == "__main__":
	main()