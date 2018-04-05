#!/usr/bin/env python
# -*- coding: utf-8 -*-

import numpy as np
import scipy as sc
import sys, os
import glob, re
from math import *
from matplotlib import pyplot as plt

def generate_graphs(path, base):
	path = os.path.join(path, base)
	files = glob.glob(os.path.join(path, "*_stats.txt"))
	for file in files:
		time = []
		fitness = []
		temp = []

		f = open(file, "r")
		while True:
			line1 = f.readline()
			if not line1:
				break

			line2 = f.readline()
			line3 = f.readline()
			time.append(float(line1.split(" ")[1]))
			fitness.append(int(line2.split(" ")[1]))
			temp.append(float(line3.split(" ")[1]))

			line_s = f.readline()

		graph_name = file.split(path)[1]
		graph_name = graph_name.split(".")[0]
		graph_name = graph_name[:-6] + "_" + base.replace("/", "_") + "graph.png"

		plt.clf()
		plt.subplot(2, 1, 1)
		plt.plot(time, fitness)
		plt.title("Evolucion del fitness")
		plt.ylabel("Fitness")

		plt.subplot(2, 1, 2)
		plt.plot(time, temp)
		plt.title("Evolucion de la temperatura")
		plt.xlabel("Tiempo")
		plt.ylabel("Temperatura")

		plt.savefig(graph_name, dpi = 100)

		f.close()

def main():
	#En esta parte se leerán los archivos de la evolución del fitness
	#para generar sus gráficas.

	#Hay que actualizar el directorio absoluto y la base de los archivos '_stats.txt'.
	dir_path = '/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 5/Code/results/'
	base = 'long_60/heuristic_log/'
	generate_graphs(dir_path, base)
	print "Gráficas generadas."

if __name__ == '__main__':
	main()