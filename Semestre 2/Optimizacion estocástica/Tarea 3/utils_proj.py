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
			
def data_entropy(path, base):
	f = open(os.path.join(path, base), "r")
	entropy_set = []
	fitness_set = []
	n = 400
	while True:
		line = f.readline()
		if not line:
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
		F = np.zeros((n, n), dtype = "int")

		for i in range(font_size):
			line = f.readline()
			individuals = line.split(" ")
			for j in range(n):
				pop[i][j] = int(individuals[j])
			fitness = int(individuals[n])
			fitness_set.append(fitness)

		for i in range(n):
			for j in range(font_size):
				row = pop[j][i]
				F[row][i] += 1

		#pop /= float(font_size * n)
		Hi = np.zeros((n), dtype = "float")
		for i in range(n):
			res = 0.0
			for j in range(n):
				if float(F[j][i]) / float(font_size) > 0.0:
					res += (float(F[j][i]) / float(font_size)) * log(float(F[j][i]) / float(font_size), n)
			Hi[i] = -res

		entropy_set.append((act_time, Hi.mean()))
		print(Hi.mean())
		f.readline()

	return fitness_set, entropy_set

def make_plot(x, y, files_name):
	yield