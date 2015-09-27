//
//  main.c
//  parallel
//
//  Created by Катаев Денис on 25.09.15.
//  Copyright (c) 2015 Катаев Денис. All rights reserved.
//


#include <stdio.h>
//#include <omp.h>


int main(int argc, const char * argv[]) {
#ifdef _OPENMP
    printf("OpenMP\n");
#endif
    int result = 0;

# pragma omp parallel for
    for (int i=0; i<=1000; i++) {
        result+=i;
    }

    printf("kek: %i\n", result);
    return result != 500500;
}
