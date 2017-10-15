#include <stdio.h>
#include <string.h>

#include "imagen.h"
#include "lista_ligada.h"

int main(int argc, char **argv) {
	/*char files_name[30];
	strcpy(files_name, argv[1]);*/

	for(int i = 7; i <= 7; i++) {
		char files_name[30], out_name[30];
		sprintf(files_name, "frame_%drata3_bin.pgm", i);
		sprintf(out_name, "out%d.pgm", i);
		IMG img = read_img(files_name);
		IMG resized = resize_img(img);
		IMG sk = skeletonize(resized);
		IMG csk = clean_skeletonize(sk);
		print_img(csk, out_name);
		//print_img(resized, "out1.pgm");
		//get_lines(sk, resized, i);

		free_img(img);
		free_img(sk);
		free_img(csk);
		free_img(resized);		
	}

	return 0;
}