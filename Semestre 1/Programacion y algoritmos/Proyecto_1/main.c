#include <stdio.h>
#include <string.h>

#include "imagen.h"
#include "lista_ligada.h"

int main(int argc, char **argv) {
	/*char files_name[30];
	strcpy(files_name, argv[1]);*/
	//int b = atoi(argv[1]);

	for(int i = 1; i <= 21; i++) {
		char files_name[30], out_name[30];
		sprintf(files_name, "frame_%drata3_bin.pgm", i);
		sprintf(out_name, "out%d.pgm", i);
		IMG *img = read_img(files_name);
		IMG *resized = resize_img(img);
		IMG *sk = skeletonize(resized);
		PIXEL p1, p2;
		NODEPTR path = NULL;
		IMG *csk = clean_skeletonize(sk, &p1, &p2, &path);
		get_lines(resized, p1, p2, path, i);
		//print_img(csk, out_name);
		print_img(resized, out_name);
		//get_lines(sk, resized, i);

		free_img(img);
		free_img(sk);
		free_img(csk);
		free_img(resized);
		free_list(path);		
	}

	return 0;
}