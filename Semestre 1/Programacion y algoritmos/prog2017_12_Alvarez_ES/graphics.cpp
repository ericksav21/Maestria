#include "graphics.hpp"

Graphics::Graphics() {}

Graphics::~Graphics() {}

void Graphics::plot_data() {
	FILE *pipe = popen("gnuplot inst.gpl", "w");
	if(pipe) {
		cout << "Gráfica creada." << endl;
		fflush(pipe);
		pclose(pipe);
	}
	else {
		cout << "Error al crear la gráfica." << endl;
	}
}