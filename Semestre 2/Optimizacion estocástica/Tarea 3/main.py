import numpy as np
import math, sys, os
import utils_proj as ut
from matplotlib import pyplot as plt

path = "/home/e-082017-04/Documents/Maestria/OptEst-Tarea3/"
#path = "/home/ericksav22/Documentos/Maestria/OptEst-Tarea3/"
methods_dir = ["GECCO-contest"]

def main():
	#Leer archivos base
	if len(sys.argv) < 2:
		print("Indique el nombre de archivo base.")
		return

	base = sys.argv[1]
	ent = ut.data_entropy(os.path.join(path, methods_dir[0]), base)
	#x1 = np.arange(1, len(fit) + 1)
	x2 = []
	y2 = []
	file = open(base + ".entropyEvolution", "w")
	for k, v in ent.items():
		x2.append(k)
		y2.append(v / 30.0)
		file.write(str(k) + " " + str(v / 30.0) + "\n")

	file.close()

	ut.make_plot(x2, y2, "entropy")
	#ut.make_plot(x1, fit, "fitness")
	'''ent = ut.precalculated_entropy(os.path.join(path, methods_dir[0]), base)
	x, y = zip(*ent)
	ut.make_plot(x, y, "pentropy")'''


if __name__ == "__main__":
	main()