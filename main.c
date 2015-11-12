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

int proceed(char *in_file, int vector_len) {
    int data[vector_len];
    memset(data, 0, vector_len);
    int buffer_len = 80;
    char line[buffer_len];
    FILE *in, *out;

    char out_file[80] = "";
    strcat(out_file, in_file);
    strcat(out_file, ".out");

    if (access(in_file, F_OK) != -1) {
        printf("%s file in exists\n", in_file);
        in = fopen(in_file, "rt");
    } else {
        printf("%s file in not exists\n", in_file);
        return 1;
    }
    printf("out file: %s\n", out_file);
    out = fopen(out_file, "wt");

    int i = 0;
    char *pch;
    while (fgets(line, buffer_len, in) != NULL) {
        pch = strtok(line, " ");
        while (pch != NULL) {
            if (i > vector_len) {
                printf("File size mismatch with array size\n");
                return 1;
            }
            if (sscanf(pch, "%i", &data[i++]) == EOF) {
                printf("Error with parse error\n");
                return 1;
            }
            pch = strtok(NULL, " ");
        }
    }
    fclose(in);

    for (i = 0; i < vector_len; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
    int j;
//    int matrix[vector_len][vector_len];
    for (i = 0; i < vector_len; i++) {
        for (j = 0; j < vector_len; j++) {
            fprintf(out, "%d ", data[i] * data[j]);
        }
        fprintf(out, "\n");
    }

    return 0;
}


int main(int argc, const char *argv[]) {
#ifdef _OPENMP
    printf("OpenMP\n");
#endif

    int files_len = 2;
    char *files[files_len];
    files[0] = "kek.txt";
    files[1] = "kek2.txt";

    int vector_len = 10;
    int i;
# pragma omp parallel for
    for (i = 0; i < files_len; i++) {
        proceed(files[i], vector_len);
    }

    return 0;
}
