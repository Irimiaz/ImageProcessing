#include <stdio.h>
#include "bmp_header.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>


void edit(char *locatie, bmp_fileheader* header, bmp_infoheader* info, imagine* photo) {
    FILE *f = fopen(locatie,"rb");
    
    fread(header, sizeof(bmp_fileheader), 1, f);
    fread(info, sizeof(bmp_infoheader), 1, f);
    

    photo->height = info->height ;
    photo->width = info->width ;
    photo->matrice = calloc(photo->height, sizeof(RGB*));
    
    for(int i = photo->height-1; i >= 0; i--) {
        photo->matrice[i] = calloc(photo->width, sizeof(RGB));
        fread(photo->matrice[i], photo->width, sizeof(RGB), f);
    }

    fclose(f);
}

void save(char *locatie, bmp_fileheader* header, bmp_infoheader* info, imagine* photo) {
    FILE *f = fopen(locatie,"wb");
    
    int n = info->height;
    int m = info->width;
    //photo->matrice[n-25][15].R = 255;photo->matrice[n - 25][15].G = 255;photo->matrice[n-25][15].B = 255;
    fwrite(header, sizeof(bmp_fileheader), 1, f);
    fwrite(info, sizeof(bmp_infoheader), 1, f);
    
    for(int i = n-1; i >= 0; i--) {
        fwrite(photo->matrice[i], m, sizeof(RGB), f);
    }
    fclose(f);
}

void quit(bmp_fileheader* header, bmp_infoheader* info, imagine* photo) {
    for(int i = photo->height-1; i >= 0; i--) {
        free(photo->matrice[i]);
    }
    free(photo->matrice);
    exit(0);
}

void insert(imagine* photo, imagine* photo_insert, unsigned int x, unsigned int y) {


    for(int i = photo_insert->height -1; i>=0 ;i --){
        for(int j = 0; j < photo_insert->width; j++) {
            if(photo->height - photo_insert->height + i - x < photo->height && j+y < photo->width)
                photo->matrice[photo->height - photo_insert->height + i - x][j+y] = photo_insert->matrice[i][j];
        }
    }
}

void point(punct A, unsigned int grosime, imagine* photo, RGB culoare) {
    int dim = grosime/2;
    for(int i = A.x -dim; i <= A.x+dim; i++){
        for(int j= A.y-dim; j <= A.y+dim; j++){
            if(i >= 0 && i < photo->height && j >= 0 && j <photo->width)
                photo->matrice[photo->height -i -1][j] = culoare;
        }
    }
}

void line(punct A, punct B, unsigned int grosime, imagine* photo, RGB culoare) {
    int dif1 = abs(A.x - B.x);
    int dif2 = abs(A.y - B.y);

    if (dif1 > dif2){

        if(A.x > B.x){
            punct C = A;
            A = B;
            B = C;
        }


        for(int i = A.x ;i <= B.x ; i++){
            int y = (1.0)*(int)(i - A.x) * (B.y - A.y) / (B.x- A.x) + A.y;
            punct D;
            D.x = i;
            D.y = y;
            point(D, grosime, photo, culoare);
        }
    }
    else {

        if(A.y > B.y){
            punct C = A;
            A = B;
            B = C;
        }
        for(int i = A.y; i <= B.y ; i++){
            int x = (1.0)*(int)(i - A.y) * (B.x - A.x) / (B.y- A.y) + A.x;
            punct D;
            D.x = x;
            D.y = i;
            point(D, grosime, photo, culoare);
        }

    }
    
}

void fill(int x, int y, RGB culoare, RGB culoare_init, imagine* photo) {
    int z = photo->height -1 -x;
    //printf("\n%d %u\n",z,y);
    if(x >= 0 && z >= 0 && y >= 0 && y < photo->width){
        if(photo->matrice[z][y].R == culoare_init.R && photo->matrice[z][y].G == culoare_init.G) {
            if (photo->matrice[z][y].B == culoare_init.B) {
                photo->matrice[z][y] = culoare;
                //printf("----------------");
                fill(x+1, y, culoare, culoare_init, photo);
                fill(x, y+1, culoare, culoare_init, photo);
                fill(x-1, y, culoare, culoare_init, photo);
                fill(x, y-1, culoare, culoare_init, photo);
            }
        }
    }
}

int main() {
    
    int size_comanda = 100;
    char *comanda = malloc(size_comanda * sizeof(char));

    bmp_fileheader header;
    bmp_infoheader info;
    imagine photo;

    RGB culoare;
    unsigned int grosime;

    while (scanf("%s", comanda)) {
        if(strcmp(comanda,"edit") == 0) {
            char *locatie;
            locatie = malloc(size_comanda * sizeof(char));
            scanf("%s",locatie);
            edit(locatie, &header, &info, &photo);

        }
        else if(strcmp(comanda,"save") == 0) {
            char *destinatie = malloc(size_comanda * sizeof(char));
            scanf("%s", destinatie);
            save(destinatie, &header, &info, &photo);
        }
        else if(strcmp(comanda,"quit") == 0) {
            quit(&header, &info, &photo);
        }
        else if(strcmp(comanda,"insert") == 0) {

            bmp_fileheader header_insert;
            bmp_infoheader info_insert;
            imagine photo_insert;
            char *locatie = malloc(size_comanda * sizeof(char));
            scanf("%s", locatie);
            edit(locatie, &header_insert, &info_insert, &photo_insert);

            unsigned int x, y;
            scanf("%u %u", &y, &x);
            insert(&photo, &photo_insert, x, y);
            free(photo_insert.matrice);
        }
        else if(strcmp(comanda,"set") == 0){

            char *comanda1 = malloc(size_comanda * sizeof(char));
            scanf("%s", comanda1);
            if (strcmp(comanda1,"draw_color") == 0) {
                scanf("%hhu %hhu %hhu", &culoare.B, &culoare.G, &culoare.R);   
            }
            else if(strcmp(comanda1,"line_width") == 0) {
                scanf("%u" , &grosime);
            }
        }
        else if(strcmp(comanda,"draw") == 0) {
            char *comanda1 = malloc(size_comanda * sizeof(char));
            scanf("%s", comanda1);
            if(strcmp(comanda1,"line") == 0) {
                punct A, B;
                scanf("%d %d %d %d", &A.y, &A.x, &B.y, &B.x);
                line(A, B, grosime, &photo, culoare);
            }
            else if(strcmp(comanda1,"rectangle") == 0) {
                punct A, B, C, D;
                scanf("%d %d", &A.y, &A.x);
                unsigned int lungime, latime;
                scanf("%u %u", &lungime, &latime);
                B.y = A.y + lungime;
                B.x = A.x;
                C.y = A.y + lungime;
                C.x = A.x + latime;
                D.y = A.y;
                D.x = A.x + latime;
                line(A, B, grosime, &photo, culoare);
                line(B, C, grosime, &photo, culoare);
                line(C, D, grosime, &photo, culoare);
                line(D, A, grosime, &photo, culoare);
            }
            else if(strcmp(comanda1,"triangle") == 0) {
                punct A, B, C;
                scanf("%d %d %d %d %d %d", &A.y, &A.x, &B.y, &B.x, &C.y, &C.x);
                line(A, B, grosime, &photo, culoare);
                line(B, C, grosime, &photo, culoare);
                line(C, A, grosime, &photo, culoare);
            }
        }
        else if (strcmp(comanda,"fill") == 0) {
            int x, y;
            scanf("%d %d", &y, &x);
            
            RGB culoare_init = photo.matrice[photo.height -1 - x][y];
            fill(x, y, culoare, culoare_init, &photo);
            
            
        }
        
    }
    return 0;

}