import numpy as np
import math, sys, os
import utils_proj as ut
import test_proj as test
from matplotlib import pyplot as plt

path = "/home/e-082017-04/Documents/Maestria/OptEst-Tarea3/"
#path = "/home/ericksav22/Documentos/Maestria/OptEst-Tarea3/"
path_data = "/home/e-082017-04/Documents/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 3/data/best_fitness/"

instance_dir = ["GECCO-contest", "instance_10_10_400_0.05_7", "instance_10_10_400_0.10_8",
				"instance_10_10_400_0.15_9", "instance_15_15_400_0.05_4", "instance_15_15_400_0.10_5",
				"instance_15_15_400_0.15_6", "instance_20_20_400_0.05_1", "instance_20_20_400_0.10_2",
				"instance_20_20_400_0.15_3"]
methods = ["CHC", "CLR_1", "CLR_5", "COMB", "DETCR", "Multi", "MultiDynamic", "RW", "SawToothGA", "SPOBCR"]

def main():
	#Leer archivos base
	if len(sys.argv) < 2:
		print("Indique el nombre de archivo base.")
		return


	base = sys.argv[1]
	sets, method_name = test.read_sets(os.path.join(path_data, instance_dir[1]))
	results = test.do_statistical_comp(sets, method_name)

	for i in range(len(method_name)):
		sys.stdout.write(method_name[i] + ": ")
		for k, v in results[i].items():
			sys.stdout.write(k + "(" + str(v) + ") ")
		print("")

if __name__ == "__main__":
	main()