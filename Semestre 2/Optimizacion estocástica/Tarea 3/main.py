import numpy as np
import math, sys, os
import utils_proj as ut
from matplotlib import pyplot as plt

#path = "/home/e-082017-04/Documents/Maestria/OptEst-Tarea3/"
path = "/home/ericksav22/Documentos/Maestria/OptEst-Tarea3/"
instance_dir = ["GECCO-contest", "instance_10_10_400_0.05_7", "instance_10_10_400_0.10_8",
				"instance_10_10_400_0.15_9", "instance_15_15_400_0.05_4", "instance_15_15_400_0.10_5",
				"instance_15_15_400_0.15_6"]
methods = ["CHC", "CLR_1", "CLR_5", "COMB", "DETCR", "Multi", "MultiDynamic", "RW", "SawToothGA", "SPOBCR"]

def main():
	#Leer archivos base
	if len(sys.argv) < 2:
		print("Indique el nombre de archivo base.")
		return

	base = sys.argv[1]
	for method in methods:
		_, fit = ut.data_fitness(os.path.join(path, instance_dir[6]), method)
		file = open(method + ".bestfitness", "w")
		for i in range(len(fit)):
			file.write(str(fit[i]) + "\n")

		file.close()
		print("\n")

	'''ent = ut.data_entropy(os.path.join(path, instance_dir[0]), base)
	x1 = np.arange(1, len(fit) + 1)
	x2 = []
	y2 = []
	file = open(base + ".entropyEvolution", "w")
	for k, v in ent.items():
		x2.append(k)
		y2.append(v)
		file.write(str(k) + " " + str(v) + "\n")

	file.close()

	ut.make_plot(x2, y2, "entropy")
	ut.make_plot(x1, fit, "fitness")'''
	#ut.precalculated_entropy(os.path.join(path, instance_dir[0]), base)


if __name__ == "__main__":
	main()