#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math, sys, os
import glob, re
import skimage
from skimage import data, img_as_float, feature
from skimage.transform import resize
from math import *
from matplotlib import pyplot as plt
import matplotlib.image as mpimg
import matplotlib.cm as cm
import cv2

path_data = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Procesamiento de señales/Tarea 10/input/"
out_dir = path_data.replace("/input/", "/output/")

def main():
	files = sorted(glob.glob(os.path.join(path_data, "*.jpg")))
	for file in files:
		img = mpimg.imread(file)
		res = cv2.resize(img, (256, 256), interpolation = cv2.INTER_CUBIC)
		gray = cv2.cvtColor(res, cv2.COLOR_RGB2GRAY)

		# Define a kernel size for Gaussian smoothing / blurring
		kernel_size = 5 # Must be an odd number (3, 5, 7...)
		blur_gray = cv2.GaussianBlur(gray, (kernel_size, kernel_size), 0)

		# Define our parameters for Canny and run it
		low_threshold = 55
		high_threshold = 110
		edges = cv2.Canny(blur_gray, low_threshold, high_threshold)
		mpimg.imsave(os.path.join(out_dir, os.path.basename(file)), edges, cmap = cm.Greys_r)

if __name__ == '__main__':
	main()