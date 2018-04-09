#!/usr/bin/env python
# -*- coding: utf-8 -*-
import numpy as np
import math, sys, os
import glob, re
from math import *
from matplotlib import pyplot as plt

#Cambiar el path
path_data = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 7/Code/data/f7/"

def read_data(path):
	files = sorted(glob.glob(os.path.join(path, "*.txt")))
	rows = 100
	cols = 150
	min_fit = {}
	entropy_set = {}
	for file in files:
		print file
		f = open(file, "r")
		while True:
			line = f.readline()
			if not line:
				break
			act_time = int(line.split("=")[1].strip())
			pop = np.zeros((rows, cols), dtype = "int")
			F = np.zeros((2, cols), dtype = "float")

			for i in range(rows):
				line = f.readline()
				individuals = line.split(" ")
				for j in range(cols):
					pop[i][j] = int(individuals[j])
			line = f.readline()
			fit = float(line)
			#Espacio en blanco
			line = f.readline()

			for i in range(cols):
				for j in range(rows):
					row = pop[j][i]
					F[row][i] += 1
				for j in range(2):
					F[j][i] /= float(rows)

			Hi = np.zeros((cols), dtype = "float")
			for i in range(cols):
				res = 0.0
				for j in range(2):
					if F[j][i] > 0.0:
						res += F[j][i] * log(F[j][i], cols)
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
	plt.xlabel("Iteraciones")
	plt.ylabel(ylabel)
	plt.savefig(files_name, dpi = 100)

def main():
	file = "data_fitness.txt"
	entropy_set, min_fit = read_data(path_data)
	x = []
	y = []
	for k, v in sorted(entropy_set.items()):
		x.append(k)
		y.append(v)
	make_plot(x, y, "entropy", "Evolucion de la entropia de la funcion: Rastrigin", "Entropia")

	x = []
	y = []
	for k, v in sorted(min_fit.items()):
		x.append(k)
		y.append(v)
	make_plot(x, y, "fitness", "Evolucion del fitness de la funcion: Rastrigin", "Fitness")

if __name__ == '__main__':
	main()