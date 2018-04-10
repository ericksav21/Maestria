#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math, sys, os
import glob, re
from math import *
from matplotlib import pyplot as plt

#Cambiar el path
path_data = "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 6/Code/results/Medium/"

def read_data(path):
	files = sorted(glob.glob(os.path.join(path, "*13_info.txt")))
	rows = 100
	cols = 53
	min_fit = {}
	entropy_set = {}
	for file in files:
		print file
		f = open(file, "r")
		while True:
			line = f.readline()
			if not line:
				break
			act_time = float(line.split(":")[1].strip())
			pop = np.zeros((rows, cols), dtype = "int")
			F = np.zeros((10, cols), dtype = "float")

			for i in range(rows):
				line = f.readline()
				individuals = line.split(" ")
				for j in range(cols):
					pop[i][j] = int(individuals[j])
			line = f.readline()
			fit = int(line)
			#Espacio en blanco
			line = f.readline()

			for i in range(cols):
				for j in range(rows):
					row = pop[j][i]
					F[row][i] += 1
				for j in range(10):
					F[j][i] /= float(rows)

			Hi = np.zeros((cols), dtype = "float")
			for i in range(cols):
				res = 0.0
				for j in range(10):
					if F[j][i] > 0.0:
						res += F[j][i] * log(F[j][i], 9)
				Hi[i] = -res

			if act_time in entropy_set:
				entropy_set[act_time] += Hi.mean()
			else:
				entropy_set[act_time] = Hi.mean()
			if act_time in min_fit:
				min_fit[act_time] += fit
			else:
				min_fit[act_time] = fit
		
		f.close()
	for k, _ in entropy_set.items():
		entropy_set[k] /= float(len(files))
	for k, _ in min_fit.items():
		min_fit[k] /= float(len(files))

	return entropy_set, min_fit

def make_plot(x, y, files_name, title = "", ylabel = ""):
	plt.clf()
	plt.figure(figsize = (7, 7))
	plt.plot(x, y)
	plt.title(title)
	plt.xlabel("Tiempo")
	plt.ylabel(ylabel)
	plt.savefig(files_name, dpi = 100)

def main():
	entropy_set, _ = read_data(path_data)
	x = []
	y = []
	for k, v in sorted(entropy_set.items()):
		x.append(k)
		y.append(v)
	make_plot(x, y, "entropyDF1", "Evolucion de la diversidad en la instancia: Hard", "Entropia")
	print("Grafica creada.")

if __name__ == '__main__':
	main()