#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math, sys, os
import glob, re
from math import *
from matplotlib import pyplot as plt

#Cambiar el path
path_data = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 7/Code/data/f7/"

def make_plot(x, y, files_name, title = "", ylabel = ""):
	plt.clf()
	plt.figure(figsize = (7, 7))
	plt.plot(x, y)
	plt.title(title)
	plt.xlabel("Iteraciones")
	plt.ylabel(ylabel)
	plt.savefig(files_name, dpi = 100)

def main():
	file = "offspring_1p.txt"
	f = open(file, "r")
	v1 = []
	v2 = []
	kind = []
	plt.figure(figsize = (7, 7))
	iter = 1
	while True:
		line = f.readline()
		if not line:
			break
		v1_act = float(line.split(" ")[0].strip())
		v2_act = float(line.split(" ")[1].strip())
		kind_act = int(line.split(" ")[2].strip())
		if kind_act == 1:
			v1.append(v1_act)
			v2.append(v2_act)
		else:
			plt.plot(v1_act, v2_act, 'bs')
		print(iter)
		iter = iter + 1

	for i in range(len(v1)):
		plt.plot(v1[i], v2[i], 'g^')

	plt.xlabel("X1")
	plt.ylabel("X2")
	plt.ylim((-700, 700))
	plt.savefig("Grafica", dpi = 100)


	f.close()

if __name__ == '__main__':
	main()