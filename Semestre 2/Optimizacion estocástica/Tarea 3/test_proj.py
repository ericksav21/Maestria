import numpy as np
import math, sys, os, glob
import utils_proj as ut
from matplotlib import pyplot as plt
from scipy import stats

def read_sets(path):
	files = sorted(glob.glob(os.path.join(path, "*.bestfitness")))
	sets = np.zeros((10, 30), dtype = "float")
	method_name = []
	i = 0
	for file in files:
		method_name.append(os.path.basename(file).split(".")[0])
		f = open(file, "r")
		for j in range(30):
			fit_i = float(f.readline())
			sets[i][j] = fit_i
		f.close()
		i += 1

	return sets, method_name

def do_statistical_comp(sets, method_name, instance):
	n = len(method_name)
	#0: Ganó, 1: Perdió, 2: Empató
	table = []
	for i in range(len(method_name)):
		table.append({"win": 0, "lost": 0, "tie": 0})

	for i in range(n - 1):
		for j in range(i + 1, n):
			#Aplicar los tests
			a1 = sets[i]
			a2 = sets[j]
			check_means = False
			is_tie = False
			if apply_test(a1, a2, "shapiro"):
				#print("Normalidad encontrada en: " + method_name[i] + ", " + method_name[j] + ", instancia: " + instance)
				if apply_test(a1, a2, "levene"):
					if apply_test(a1, a2, "anova"):
						is_tie = True
					else:
						check_means = True
				else:
					if apply_test(a1, a2, "welch"):
						is_tie = True
					else:
						check_means = True

			elif apply_test(a1, a2, "kruskal"):
				is_tie = True
			else:
				check_means = True

			if check_means:
				if a1.mean() > a2.mean():
					table[i]["win"] += 1
					table[j]["lost"] += 1
				else:
					table[i]["lost"] += 1
					table[j]["win"] += 1
			if is_tie:
				table[i]["tie"] += 1
				table[j]["tie"] += 1

	return table

def apply_test(a1, a2, type):
	#Todos los tests se hacen con un 95% de confianza.
	if type == "shapiro":
		_, p1 = stats.shapiro(a1)
		_, p2 = stats.shapiro(a2)

		return (p1 > 0.05 and p2 > 0.05)
	elif type == "levene":
		_, p = stats.levene(a1, a2)

		return p > 0.05
	elif type == "anova":
		_, p = stats.f_oneway(a1, a2)

		return p > 0.05
	elif type == "welch":
		_, p = stats.ttest_ind(a1, a2, equal_var = False)

		return p > 0.05
	elif type == "kruskal":
		_, p = stats.kruskal(a1, a2)

		return p > 0.05
	else:
		print("Test no identificado.")

		return -1