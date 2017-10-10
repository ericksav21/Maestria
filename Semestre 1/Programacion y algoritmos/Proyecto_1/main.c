#include <stdio.h>
#include <string.h>

#include "imagen.h"

int main(int argc, char **argv) {
	char files_name[30];
	strcpy(files_name, argv[1]);

	IMG img = read_img(files_name);
	IMG resized = resize_img(img);
	/*for(int i = 0; i < resized.height; i++)
		for(int j = 0; j < resized.width; j++)
			resized.mat[i][j] = (resized.mat[i][j] == 0 ? 255 : 0);*/
	IMG sk = skeletonize(resized);
	print_img(resized, "out1.pgm");
	print_img(sk, "out2.pgm");

	free_img(img);
	free_img(sk);
	free_img(resized);

	return 0;
}