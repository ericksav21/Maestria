#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <utility>
#include <queue>

using namespace std;

#include "util.hpp"

int main(int argc, char **argv) {
	if(argc < 3) {
		cout << "Error. Ejecuta: " << string(argv[0]) << " [Tasks] [Machinefile]." << endl;
		return 0;
	}

	queue<pair<string, string> > tasks = read_tasksfile(string(argv[1]));
	vector<NODE> nodes = read_machinefile(string(argv[2]));
	int free_nodes = nodes.size(), running_proc = 0;
	int pid;
	//2 segundos
	int wait_time = 2000000;
	string node_act;
	pair<string, string> taks_act;

	while(true) {
		while(free_nodes > 0 && !tasks.empty()) {
			int free_node_id = get_next_free_node(nodes);
			node_act = nodes[free_node_id].name;
			taks_act = tasks.front(); tasks.pop();

			pid = fork();
			if(pid >= 0) {
				if(pid == 0) {
					//Proceso hijo
					break;
				}
				else {
					nodes[free_node_id].in_use = true;
					nodes[free_node_id].pid = pid;
					usleep(wait_time);
					free_nodes--;
					running_proc++;
				}
			}
			else {
				cout << "Error al crear un nuevo proceso.\n";
				return -1;
			}
		}

		//Proceso padre, esperar a que alguno termine
		if(pid > 0) {
			if(running_proc == 0 && tasks.empty()) {
				cout << "Terminado.\n";
				break;
			}
			int wstatus;
			cout << "Esperando...\n";
			int cpid = waitpid(-1, &wstatus, 0);
			cout << "Proceso hijo terminado con pid: " << cpid << ".\n";
			if(WEXITSTATUS(wstatus) != 0) {
				cout << "Aviso: un proceso terminó de manera anormal: " << WEXITSTATUS(wstatus) << "\n";
			}
			//Actualizar la lista de nodos
			for(int i = 0; i < nodes.size(); i++) {
				if(nodes[i].pid == cpid) {
					nodes[i].in_use = false;
					nodes[i].pid = 0;
					free_nodes++;
					running_proc--;
				}
			}
		}
		//Proceso hijo, ejecutar el programa
		else {
			/*string prog = "ssh " + node_act + " " + taks_act.first + " " + taks_act.second;
			int e_res = execl("/bin/sh", "sh", "-c", prog.c_str(), (char *)NULL);

			if(e_res == -1) {
				return -1;
			}
			else {
				return 0;
			}*/
			cout << "Ejecutando proceso hijo: " << node_act << " " << taks_act.first << " " << taks_act.second << endl;
			usleep(wait_time);
			break;
		}
	}

	return 0;
}