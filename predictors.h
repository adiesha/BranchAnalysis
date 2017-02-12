#ifndef PREDICTORS_H
#define PREDICTORS_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    uint32_t address;
    uint32_t predictor:2;
} branch;

typedef struct {
    branch *branches;
    int size;
} bht;

typedef struct {
    unsigned int size;
    unsigned int pos;
    uint32_t *addresses;
} uniqueBranches;


/* Implement bht (2,2) Algorithm here */
void bht22Algo(const char *filePath);

/* Implement bht 1-bit Algorithm here */
void bht1bitAlgo(const char *filepath);

/* Implement bht 2-bit Algorithm here */
void bht2bitAlgo(const char *filepath);

/* Implement custom bht Algorithm here */
void bhtCustomAlgo(const char *filePath);

void openFile(const char *path);

void initializeBht(bht *bht1, uint32_t predictor);

void addBranch(bht *bht1, uint32_t addr, int *unique);

int parseNextLine2();

void set22bhtvalue(branch *br, bool actual, int predictionValue);

void initializeUniqueBranches(uniqueBranches *ub);

void addUniqueBranch(uniqueBranches *branches, uint32_t address, int *ubCount);

#endif
