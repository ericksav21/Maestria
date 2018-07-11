from skimage.color import rgb2lab, lab2rgb, rgb2gray, xyz2lab
from skimage.io import imread, imsave
import numpy as np
from matplotlib import pyplot as plt
import os
import random

IMG_PATH = 'Set images path'

#This script is used for convert 3-Channel RGB images to grayscale images inside a folder.
def main():
	X = []
	i = 1
	for filename in os.listdir(IMG_PATH):
		image_act = imread(IMG_PATH + filename)
		image_gray = rgb2gray(image_act)
		imsave(IMG_PATH + "test_img_" + str(i) + ".jpg", image_gray)
		i = i + 1

if __name__ == '__main__':
	main()