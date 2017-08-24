#include <stdio.h>
#include "memoria.h"

int main() {
    //Declare necesary variables
    char imgf[256], dump[128];
    int width, height, mf, **data;
    int histogram[256];
    int mode = 0, max = 0, cnt = 0;
    FILE *in, *out, *outH;

    for(int i = 0; i < 256; i++)
        histogram[i] = 0;

    //Get the file's name
    printf("Nombre de la imagen: ");
    scanf("%s", imgf);
    if((in = fopen(imgf, "r")) == NULL) {
        printf("File cannot be oppened.\n");
        return 0;
    }
    out = fopen("binarized.pgm", "w");
    outH = fopen("histogram.pgm", "w");

    //Read the first line and depreciate
    fscanf(in, "%s", dump);

    //Get img's width and height
    fscanf(in, "%d %d", &width, &height);

    //Read max frecuency
    fscanf(in, "%d", &mf);
    printf("ancho = %d, alto = %d\n", width, height);

    //This object is used for store the image data
    //We use dynamic memory since the image can be very large
    //This is the same as creating a vector of size (width * height)
    data = MATRIZ(int, width, height);

    //Create the histogram, first I read the image
    //and then I'm incrementing the frequency of the i'th pixel
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            fscanf(in, "%d\n", &data[i][j]);
            histogram[data[i][j]]++;
        }
    }

    //Now we can get the mode, I use the histogram in order to
    //get the max value, which is the mode
    for(int i = 0; i < 256; i++) {
        if(histogram[i] > max) {
            max = histogram[i];
        }
    }

    //Since the image can has too many modes, I find them and
    //I get the mean of the modes.
    for(int i = 0; i < 256; i++) {
        if(histogram[i] == max) {
            mode += i;
            cnt++;
        }
    }
    //The mode is stored in integer value
    mode /= cnt;

    printf("moda = %d, frecuencia = %d\n", mode, max);

    //Create the new binarized image
    int cont = 0;
    fprintf(out, "P2\n");
    fprintf(out, "%d %d\n", width, height);
    fprintf(out, "255\n");
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            //If the pixel is less than the mode we put a zero bit,
            //Otherwise, we put 1 bit
            if(data[i][j] == 0)
                cont++;
            fprintf(out, "%d\n", (data[i][j] <= mode ? 0 : 255));
        }
    }

    //Plot the histogram
    //This value makes an scalation for the width
    int scale = 2;

    //We can change this values in order to adjust histogram's width and height
    int hwidth = 256 * scale;
    int hheight = 600;
    fprintf(outH, "P2\n");
    fprintf(outH, "%d %d\n", hwidth, hheight);
    fprintf(outH, "255\n");

    //First I create the histogram (view) in a matrix, and after I transfer it
    //To PGM Image
    int mat_histogram[hheight][hwidth];

    for(int i = 0; i < hheight; i++)
        for(int j = 0; j < hwidth; j++)
            mat_histogram[i][j] = 255;

    for(int i = 0, c = 0; i < hwidth; i += scale, c++) {
        //Normalize the values
        float da = (float)histogram[c];
        da /= (float)max;
        da *= (hheight - 50);

        //This code fills the histogram matrix (bottom to top and left to right)
        for(int x = 0; x < scale; x++) {
            int dai = (int)da;
            for(int j = hheight - 1; j >=0; j--) {
                if(dai > 0) {
                    mat_histogram[j][i + x] = 70;
                    dai--;
                }
                else break;
            }
        }
    }

    //Create the histogram image
    for(int i = 0; i < hheight; i++)
        for(int j = 0; j < hwidth; j++)
            fprintf(outH, "%d\n", mat_histogram[i][j]);

    //Close all the images and free the memory
    fclose(in);
    fclose(out);
    fclose(outH);
    LIBERAMATRIZ(data);

    return 0;
}

