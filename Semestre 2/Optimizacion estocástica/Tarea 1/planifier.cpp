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
#include "log.hpp"

int main(int argc, char **argv) {
	Log l("log");
	string msg;
	if(argc < 3) {
		msg = "Error. Ejecuta: " + string(argv[0]) + " [Tasks] [Machinefile].";
		l.write(msg, 3);
		l.close();
		return 0;
	}

	string path = "/home/user_demo/ErickAlvarez/";
	queue<pair<string, string> > tasks = read_tasksfile(string(argv[1]));
	vector<NODE> nodes = read_machinefile(string(argv[2]));
	int free_nodes = nodes.size(), running_proc = 0, cnt = 0;
	int pid;
	//2 segundos
	int wait_time = 10000;
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
					l.close();
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
				l.write("Error al crear un nuevo proceso.", 3);
				l.close();
				return -1;
			}
		}

		//Proceso padre, esperar a que alguno termine
		if(pid > 0) {
			if(running_proc == 0 && tasks.empty()) {
				l.write("Sin más tareas por ejecutar.", 1);
				break;
			}
			int wstatus;
			l.write("Esperando...", 1);
			int cpid = waitpid(-1, &wstatus, 0);
			cnt++;
			msg = "Proceso hijo terminado con pid: " + int_to_str(cpid) + ", no. " + int_to_str(cnt);
			l.write(msg, 1);
			if(WEXITSTATUS(wstatus) != 0) {
				msg = "Aviso: un proceso terminó de manera anormal: " + int_to_str(WEXITSTATUS(wstatus));
				l.write(msg, 2);
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
		else if(pid == 0) {
			string prog = path + taks_act.first + " " + taks_act.second;
			string prog_command = "ssh " + node_act + " " + prog;
			/*msg = "Ejecutando proceso hijo: " + prog_command + " en nodo: " + node_act;
			l.write(msg, 1);*/
			int e_res = execl("/bin/sh", "sh", "-c", prog_command.c_str(), (char *)NULL);
			//usleep(wait_time / 2);
			//msg = "Respuesta de execl: " + int_to_str(e_res);
			//l.write(msg, 1);

			if(e_res == -1) {
				//l.close();
				return -1;
			}
			else {
				//l.close();
				return 0;
			}
			break;
		}
	}
	l.close();

	return 0;
}