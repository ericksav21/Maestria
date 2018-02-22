import numpy as np
import math, sys, os
import utils_proj as ut
from matplotlib import pyplot as plt

path = "/home/e-082017-04/Documents/Maestria/OptEst-Tarea3/"
methods_dir = ["GECCO-contest"]

def main():
	#Leer archivos base
	if len(sys.argv) < 2:
		print("Indique el nombre de archivo base.")
		return

	base = sys.argv[1]
	#ut.read_instance(os.path.join(path, methods_dir[0]), base)
	fit, ent = ut.data_entropy(os.path.join(path, methods_dir[0]), base)
	x1 = np.arange(1, len(fit) + 1)
	x2, y2 = zip(*ent)
	fig = plt.figure(figsize = (30, 30))
	ax1 = fig.add_subplot(1, 2, 1)
	ax2 = fig.add_subplot(1, 2, 2)
	ax1.plot(fit)
	ax1.set_title("Fitness")
	ax2.plot(x2, y2)
	ax2.set_title("Entropía")
	fig.savefig("Test")

	#ut.make_plot(x1, fit, "fitness")
	#ut.make_plot(x2, y2, "entropy")


if __name__ == "__main__":
	main()