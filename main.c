//
// Created by adiesha on 2/9/17.
//

#include <stdio.h>
#include <stdlib.h>
#include "predictors.h"

int main(int argc, char **argv) {
    int bPredictor = 1;
    bPredictor = atoi(argv[1]);
    char *filePath = argv[2];


    if (bPredictor == 1) {
        printf("starting 1-bit BHT with 8192 entries \n");
        bht1bitAlgo(filePath);
    } else if (bPredictor == 2) {
        printf("starting 2-bit BHT with 4096 entries \n");
        bht2bitAlgo(filePath);
    } else if (bPredictor == 3) {
        printf("starting (2,2) BHT with 1024 entries \n");
        printf("Please wait this will take up some time \n");
        bht22Algo(filePath);
    } else if (bPredictor == 4) {
        printf("starting of custom branch prediction algorithm \n");
        bhtCustomAlgo(filePath);
    } else {
        fprintf(stderr, "Wrong input for the predictor value");
    }

}