#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math, sys, os
import glob, re
from math import *
import matplotlib.image as mpimg
import matplotlib.cm as cm
import cv2

#path_data = "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Procesamiento de señales/Tarea 10/dataset/"
path_data = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Procesamiento de señales/Tarea 10/dataset/"
input_dir = path_data.replace("/dataset/", "/input/")
out_dir = path_data.replace("/dataset/", "/output/")

def main():
	files = sorted(glob.glob(os.path.join(path_data, "*.jpg")))
	cnt = 1
	for file in files:
		img = cv2.imread(file)
		res = cv2.resize(img, (256, 256), interpolation = cv2.INTER_CUBIC)
		#cv2.imwrite(os.path.join(input_dir, os.path.basename(file)), res)
		cv2.imwrite(os.path.join(input_dir, "img_" + str(cnt) + os.path.splitext(file)[1]), res)
		gray = cv2.cvtColor(res, cv2.COLOR_RGB2GRAY)

		# Define a kernel size for Gaussian smoothing / blurring
		kernel_size = 5 # Must be an odd number (3, 5, 7...)
		blur_gray = cv2.GaussianBlur(gray, (kernel_size, kernel_size), 0)

		# Define our parameters for Canny and run it
		low_threshold = 30
		high_threshold = 80
		edges = cv2.Canny(blur_gray, low_threshold, high_threshold)

		laplacian = cv2.Laplacian(gray, cv2.CV_64F)
		cv2.imwrite(os.path.join(out_dir, "img_" + str(cnt) + os.path.splitext(file)[1]), edges)
		#cv2.imwrite(os.path.join(out_dir, os.path.basename(file)), edges, (cv2.IMWRITE_PXM_BINARY, 0))
		cnt += 1

if __name__ == '__main__':
	main()
