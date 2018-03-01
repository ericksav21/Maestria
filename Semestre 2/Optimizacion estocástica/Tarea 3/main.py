import numpy as np
import math, sys, os
import utils_proj as ut
import test_proj as test
from matplotlib import pyplot as plt

path = "/home/e-082017-04/Documents/Maestria/OptEst-Tarea3/"
#path = "/home/ericksav22/Documentos/Maestria/OptEst-Tarea3/"
path_data = "../data/best_fitness/"
#path_data = "/home/ericksav22/Documentos/Maestria/GIT/Semestre 2/Optimizacion estocástica/Tarea 3/data/best_fitness/"

instance_dir = ["GECCO-contest", "instance_10_10_400_0.05_7", "instance_10_10_400_0.10_8",
				"instance_10_10_400_0.15_9", "instance_15_15_400_0.05_4", "instance_15_15_400_0.10_5",
				"instance_15_15_400_0.15_6", "instance_20_20_400_0.05_1", "instance_20_20_400_0.10_2",
				"instance_20_20_400_0.15_3"]
methods = ["CHC", "CLR_1", "CLR_5", "COMB", "DETCR", "Multi", "MultiDynamic", "RW", "SawToothGA", "SPOBCR"]

def main():
	#Leer archivos base
	if len(sys.argv) < 2:
		print("Error. Ejecute el script usando los parámetros: [Tipo de cálculo], [No. de archivo], [Archivo base].")
		return


	c_type = sys.argv[1]

	if c_type == "entropy":
		for method in methods:
			if method == "SawToothGA":
				method = "SawTooth"
			no_file = int(sys.argv[2]) if len(sys.argv) == 3 else -1
			entropy_set = ut.data_entropy(os.path.join(path, instance_dir[0]), method, no_file)
			x = []
			y = []
			f = open(method + "_Centropy", "w")
			for k, v in entropy_set.items():
				x.append(k / 3600.0)
				y.append(v)
				f.write(str("{0:.3g}".format(k / 3600.0)) + " " + str(v) + "\n")
			ut.make_plot(x, y, method + "_entropy", "Entropía del método: " + method, "Entropía")
			f.close()
	elif c_type == "fitness":
		for method in methods:
			if method == "SawToothGA":
				method = "SawTooth"
			fitness_set, _ = ut.data_fitness(os.path.join(path, instance_dir[0]), method)
			x = []
			y = []
			f = open(method + "_Cfitness", "w")
			for k, v in fitness_set.items():
				x.append(k / 3600.0)
				y.append(v)
				f.write(str("{0:.3g}".format(k / 3600.0)) + " " + str(v) + "\n")
			ut.make_plot(x, y, method + "_fitness", "Fitness del método: " + method, "Fitness")
			f.close()
	elif c_type == "prec_entropy":
		for method in methods:
			if method == "SawToothGA":
				method = "SawTooth"
			ut.precalculated_entropy(os.path.join(path, instance_dir[0]), method)
	elif c_type == "statistical":
		for instance in instance_dir:
			sets, method_name = test.read_sets(os.path.join(path_data, instance))
			results = test.do_statistical_comp(sets, method_name, instance)

			f = open(instance + "_results", "w")
			for i in range(len(method_name)):
				f.write(method_name[i] + ":")
				s = []
				for k, v in results[i].items():
					f.write(" " + str(v))
					s.append(v)
				f.write(" " + str(s[0] - s[1]) + "\n")

			f.close()
		print("Cálculo de las pruebas estadísticas terminado.")

if __name__ == "__main__":
	main()