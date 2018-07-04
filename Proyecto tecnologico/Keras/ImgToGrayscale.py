from skimage.color import rgb2lab, lab2rgb, rgb2gray, xyz2lab
from skimage.io import imread, imsave
import numpy as np
from matplotlib import pyplot as plt
import os
import random

TEST_PATH = 'C:/Users/erick/OneDrive/Documentos/Erick/Tensorflow/Proyecto/Keras/Test3/Ab/'

def main():
	X = []
	i = 1
	for filename in os.listdir(TEST_PATH):
		image_act = imread(TEST_PATH + filename)
		image_gray = rgb2gray(image_act)
		imsave(TEST_PATH + "test_img_" + str(i) + ".jpg", image_gray)
		i = i + 1

if __name__ == '__main__':
	main()