#include <stdio.h>
#include <string.h>

#include "imagen.h"

int main(int argc, char **argv) {
	char files_name[30];
	strcpy(files_name, argv[1]);

	IMG img = read_img(files_name);
	//IMG resized = resize_img(img);
	draw_line(img, 100, 100, 250, 250);
	print_img(img);

	free_img(img);
	//free_img(resized);

	return 0;
}