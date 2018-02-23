import numpy as np
import scipy as sc
import sys, os
import glob, re
from math import *
from matplotlib import pyplot as plt

def tryint(s):
    try:
        return int(s)
    except:
        return s

def alphanum_key(s):
    """ Turn a string into a list of string and number chunks.
        "z23a" -> ["z", 23, "a"]
    """
    return [ tryint(c) for c in re.split('([0-9]+)', s) ]

def read_instance(path, base):
	files = glob.glob(os.path.join(path, base + ".*"))
	return sorted(files, key = alphanum_key)

def precalculated_entropy(path, base):
	f = open(os.path.join(path, base), "r")
	entropy_set = []
	is_first = True
	while True:
		line = f.readline()
		if is_first:
			is_first = False
			continue
		if not line:
			break
		t, e = line.split(" ")
		entropy_set.append((float(t.strip()), float(e.strip())))
	return entropy_set

def data_fitness(path, base):
	files = read_instance(path, base)
	fitness_set = {}
	n = 400
	for file in files:
		f = open(file, "r")
		print("Fitness: " + str(f))
		while True:
			line = f.readline()
			if not line or line.startswith("MonoObjective"):
				break
			#Leer el tiempo actual
			if not line.startswith("Current"):
				continue

			mmax = -1
			act_time = line.split("=")[1].strip()
			act_time = int(act_time.split("(")[0])

			line = f.readline()
			if not line:
				break
			font_size = int(line.split("=")[1].strip())

			for i in range(font_size):
				line = f.readline()
				individuals = line.split(" ")
				fitness = int(individuals[n])
				if fitness > mmax:
					mmax = fitness

			if act_time in fitness_set:
				fitness_set[act_time] += mmax
			else:
				fitness_set[act_time] = mmax
			f.readline()

		f.close()

	return fitness_set
			
def data_entropy(path, base):
	files = read_instance(path, base)
	entropy_set = {}
	n = 400
	for file in files:
		f = open(file, "r")
		print("Entropía: " + str(f))
		while True:
			line = f.readline()
			if not line or line.startswith("MonoObjective"):
				break
			#Leer el tiempo actual
			if not line.startswith("Current"):
				continue

			act_time = line.split("=")[1].strip()
			act_time = int(act_time.split("(")[0])

			line = f.readline()
			if not line:
				break
			font_size = int(line.split("=")[1].strip())
			pop = np.zeros((font_size, n), dtype = "int")
			F = np.zeros((n, n), dtype = "float")

			for i in range(font_size):
				line = f.readline()
				individuals = line.split(" ")
				for j in range(n):
					pop[i][j] = int(individuals[j])
				fitness = int(individuals[n])

			for i in range(n):
				for j in range(font_size):
					row = pop[j][i]
					F[row][i] += 1
				for j in range(n):
					F[j][i] /= float(font_size)


			Hi = np.zeros((n), dtype = "float")
			for i in range(n):
				res = 0.0
				for j in range(n):
					if F[j][i] > 0.0:
						res += F[j][i] * log(F[j][i], n)
				Hi[i] = -res

			if act_time in entropy_set:
				entropy_set[act_time] += Hi.mean()
			else:
				entropy_set[act_time] = Hi.mean()
			f.readline()

		f.close()

	return entropy_set

def make_plot(x, y, files_name, title = ""):
	plt.clf()
	plt.figure(figsize = (7, 7))
	plt.plot(x, y)
	plt.title(title)
	plt.savefig(files_name, dpi = 100)