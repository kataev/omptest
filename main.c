//
//  main.c
//  parallel
//
//  Created by Катаев Денис on 25.09.15.
//  Copyright (c) 2015 Катаев Денис. All rights reserved.
//
#include <stdio.h>
#include <omp.h>
#include <unistd.h>
#include <string.h>


int procceed(char *in_file, int vector_len) {
    int data[vector_len];
    int buffer_len = 80;
    char line[buffer_len];
    FILE *in, *out;

    char out_file;

    if (access(in_file, F_OK) != -1) {
        printf("file in exists\n");
        in = fopen(in_file, "rt");
    } else {
        printf("file in not exists\n");
        return 1;
    }

    if (access(out_file, F_OK) != -1) {
        printf("file out exists\n");
        out = fopen(out_file, "wt");
    } else {
        printf("file out not exists\n");
        return 1;
    }

    int i = 0;
    char *pch;
    while (fgets(line, buffer_len, in) != NULL) {
        pch = strtok(line, " ");
        while (pch != NULL) {
            if (i > vector_len) {
                printf("File size mismatch with array size");
                return 1;
            }
            if (sscanf(pch, "%i", &data[i++]) == EOF) {
                printf("Error with parse error");
                return 1;
            }
            pch = strtok(NULL, " ");
        }
        for (i; i < vector_len; i++) {
            data[i] = 0;
        }
    }
    fclose(in);

    int matrix[vector_len][vector_len];
    for (i = 0; i < vector_len; i++) {
        for (int j = 0; j < vector_len; j++) {
            matrix[i][j] = data[i] * data[j];
        }
    }


    return 0;
}


int main(int argc, const char *argv[]) {
#ifdef _OPENMP
    printf("OpenMP\n");
#endif

    int files_len = 2;
    char *files[files_len];
    files[0] = '/Users/pk/cprojects/omptest/kek.txt';
    files[1] = '/Users/pk/cprojects/omptest/kek2.txt';

    int vector_len = 10;
//    int data[vector_len];

    for (int i = 0; i < files_len; i++){
        if (!procceed(files[i], vector_len))
            return 1;
    }

//    if (!procceed("kek.txt", vector_len, data))
//        return 0;
//    if (!procceed("kek2.txt", vector_len, data2))
//        return 0;

//
//    printf("\ndata:\t");
//
//    for (int i = 0; i < vector_len; i++) {
//        printf("%i ", data[i]);
//    }

//    for (int i = 0; i < vector_len; i++) {
//        for (int j = 0; j < vector_len; j++) {
//            printf("%i\t\t", matrix[i][j]);
//        }
//        printf("\n");
//    }

    return 0;
}
