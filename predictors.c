#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "predictors.h"
#include <string.h>
#include <math.h>

#define INC 100

FILE *_fp;
uint32_t _addr;
bool _taken;


/* Implement assignment 2 here */
void bht22Algo(const char *filePath) {
    typedef struct {
        uint32_t historyBits:2;
    } historyRegister;

    int totalBranches = 0;
    int uniqueBranchesCount = 0;
    int correctlyPredicted = 0;
    int incorrectlyPredicted = 0;
    int bht_size = 1024;
    int globalHistoryBits = 2;
    int globalHistoryNumber = (int) pow(2, globalHistoryBits);
    historyRegister history;
    history.historyBits = 0;

    printf("Number of global histories (Number of bhts kept) = %d\n", globalHistoryNumber);

    bht *bhts;
    bhts = calloc(globalHistoryNumber, sizeof(bht));
    for (int i = 0; i < globalHistoryNumber; ++i) {
        bhts[i].size = bht_size;
        bhts[i].branches = (branch *) calloc(bht_size, sizeof(branch));
        initializeBht(&bhts[i], 0);
    }

    uniqueBranches uBranches;
    initializeUniqueBranches(&uBranches);

    openFile(filePath);

    while (parseNextLine2() != -1) {
        totalBranches++;
        addUniqueBranch(&uBranches, _addr, &uniqueBranchesCount);
        _addr = _addr & (bht_size - 1);

        branch *br = &((bhts + history.historyBits)->branches[_addr]);

        int predictionValue = br->predictor;
        bool prediction = predictionValue > 1 ? true : false;

        set22bhtvalue(br, _taken, predictionValue);

        //set history register
        history.historyBits = history.historyBits << 1;
        if (_taken) {
            history.historyBits = history.historyBits | 0b1;
        }
        (_taken == prediction) ? correctlyPredicted++ : incorrectlyPredicted++;
    }

    //Print statistics
    printf("Total number of branches = %d\n", totalBranches);
    printf("Total number of unique branches = %d\n", uniqueBranchesCount);
    printf("Total number of correctly predicted branches = %d\n", correctlyPredicted);
    printf("Total number of incorrectly predicted branches = %d\n", incorrectlyPredicted);
    printf("Mis-prediction rate = %f%%\n", incorrectlyPredicted * 1.0 / totalBranches * 100);


}

/* Implement 1-bit bht Algorithm */
void bht1bitAlgo(const char *filePath) {
    int totalBranches = 0;
    int uniqueBranchesCount = 0;
    int correctlyPredicted = 0;
    int incorrectlyPredicted = 0;
    int bht_size = 8192;

    bht *bht1;
    bht1 = malloc(sizeof(bht));
    bht1->size = bht_size;
    bht1->branches = (branch *) calloc(bht_size, sizeof(branch));

    uniqueBranches uBranches;
    initializeUniqueBranches(&uBranches);

    openFile(filePath);

    initializeBht(bht1, 0);

    while (parseNextLine2() != -1) {
        totalBranches++;
        addUniqueBranch(&uBranches, _addr, &uniqueBranchesCount);
        _addr = _addr & (bht_size - 1);

        branch *br = &(bht1->branches[_addr]);


        //get prediction for 1 bit bht
        int predictionValue = br->predictor;
        bool prediction = predictionValue == 0 ? false : true;
        //set actual value
        br->predictor = (_taken == 0) ? false : true;
        (_taken == prediction) ? correctlyPredicted++ : incorrectlyPredicted++;

    }
    //Print statistics
    printf("Total number of branches = %d\n", totalBranches);
    printf("Total number of unique branches = %d\n", uniqueBranchesCount);
    printf("Total number of correctly predicted branches = %d\n", correctlyPredicted);
    printf("Total number of incorrectly predicted branches = %d\n", incorrectlyPredicted);
    printf("Mis-prediction rate = %f%%\n", incorrectlyPredicted * 1.0 / totalBranches * 100);

}

/* Implement 2-bit bht Algorithm */
void bht2bitAlgo(const char *filepath) {

    int totalBranches = 0;
    int uniqueBranchesCount = 0;
    int correctlyPredicted = 0;
    int incorrectlyPredicted = 0;
    int bht_size = 4096;

    bht *bht1;
    bht1 = malloc(sizeof(bht));
    bht1->size = bht_size;
    bht1->branches = calloc(bht_size, sizeof(branch));

    uniqueBranches uBranches;
    initializeUniqueBranches(&uBranches);

    openFile(filepath);

    initializeBht(bht1, 0);

    for (int j = 0; j < bht1->size; ++j) {
//        printf("%zd %d %d\n",bht1->branches[j].address,bht1->branches[j].one,bht1->branches[j].two);
    }
    while (parseNextLine2() != -1) {
        totalBranches++;
        addUniqueBranch(&uBranches, _addr, &uniqueBranchesCount);
        _addr = _addr & (bht_size - 1);

        branch *br = &(bht1->branches[_addr]);

        //get prediction for 1 bit bht

        int predictionValue = br->predictor;
        bool prediction = predictionValue > 1 ? true : false;

        set22bhtvalue(br, _taken, predictionValue);
        (_taken == prediction) ? correctlyPredicted++ : incorrectlyPredicted++;

    }
    //Print statistics
    printf("Total number of branches = %d\n", totalBranches);
    printf("Total number of unique branches = %d\n", uniqueBranchesCount);
    printf("Total number of correctly predicted branches = %d\n", correctlyPredicted);
    printf("Total number of incorrectly predicted branches = %d\n", incorrectlyPredicted);
    printf("Mis-prediction rate = %f%%\n", incorrectlyPredicted * 1.0 / totalBranches * 100);


}

/* Implement custom bht Algorithm */
void bhtCustomAlgo(const char *filePath) {
    typedef struct {
        uint32_t historyBits:7;
    } historyRegister;

    int totalBranches = 0;
    int uniqueBranchesCount = 0;
    int correctlyPredicted = 0;
    int incorrectlyPredicted = 0;
    int bht_size = 32;
    int globalHistoryBits = 7;
    int globalHistoryNumber = (int) pow(2, globalHistoryBits);
    historyRegister history;
    history.historyBits = 0;

    printf("Number of global histories (Number of bhts kept) = %d\n", globalHistoryNumber);

    bht *bhts;
    bhts = calloc(globalHistoryNumber, sizeof(bht));
    for (int i = 0; i < globalHistoryNumber; ++i) {
        bhts[i].size = bht_size;
        bhts[i].branches = (branch *) calloc(bht_size, sizeof(branch));
        initializeBht(&bhts[i], 0);
    }

    uniqueBranches uBranches;
    initializeUniqueBranches(&uBranches);

    openFile(filePath);

    while (parseNextLine2() != -1) {
        totalBranches++;
        addUniqueBranch(&uBranches, _addr, &uniqueBranchesCount);
        _addr = _addr & (bht_size - 1);

        branch *br = &((bhts + history.historyBits)->branches[_addr]);

        int predictionValue = br->predictor;
        bool prediction = predictionValue > 1 ? true : false;

        set22bhtvalue(br, _taken, predictionValue);

        //set history register
        history.historyBits = history.historyBits << 1;
        if (_taken) {
            history.historyBits = history.historyBits | 0b1;
        }
        (_taken == prediction) ? correctlyPredicted++ : incorrectlyPredicted++;
    }

    //Print statistics
    printf("Total number of branches = %d\n", totalBranches);
    printf("Total number of unique branches = %d\n", uniqueBranchesCount);
    printf("Total number of correctly predicted branches = %d\n", correctlyPredicted);
    printf("Total number of incorrectly predicted branches = %d\n", incorrectlyPredicted);
    printf("Mis-prediction rate = %f%%\n", incorrectlyPredicted * 1.0 / totalBranches * 100);


}


void openFile(const char *path) {
    _fp = fopen(path, "r");
    if (_fp == NULL) {
        fprintf(stderr, "%s\n", strerror(errno));
        return;
    }
    return;
}

void initializeBht(bht *bht1, uint32_t predictor) {
    for (int i = 0; i < bht1->size; i++) {
        bht1->branches[i].address = i;
        bht1->branches[i].predictor = predictor;
    }
}

void addBranch(bht *bht1, uint32_t addr, int *unique) {
    for (int i = 0; i < bht1->size; ++i) {
        if (bht1->branches[i].address == addr) {
            return;
        }
    }


}

int parseNextLine2() {
    //Read a new line and fill the stuff
    char *line = NULL;
    size_t n = 0;
    size_t res = getline(&line, &n, _fp);

    /* Check if we have reached EOF */
    if (res == -1) {
        free(line);
        return res;
    }

    /* Parse address of branch */
    char *l = strtok(line, ",");
    _addr = atoi(l);

    /* Parse taken or not taken */
    l = strtok(NULL, ",");
    _taken = false;
    if (atoi(l) == 1) {
        _taken = true;
    }

    free(line);
    return res;
}


void set22bhtvalue(branch *br, bool actual, int predictionValue) {
    //set actual value
    if (actual == false) {
        if (predictionValue == 3) {
            br->predictor = 2;
        } else {
            br->predictor = 0;
        }
    } else {
        if (predictionValue == 0) {
            br->predictor = 1;
        } else {
            br->predictor = 3;
        }
    }
}

void initializeUniqueBranches(uniqueBranches *ub) {
    ub->size = 100;
    ub->pos = 1;
    ub->addresses = (uint32_t *) calloc(100, sizeof(uint32_t));
}

void addUniqueBranch(uniqueBranches *branches, uint32_t address, int *ubCount) {
    if (branches->pos == branches->size) {
        branches->addresses = realloc(branches->addresses, sizeof(uint32_t) * (branches->size + INC));
    }
    for (int i = 0; i < branches->pos; ++i) {
        if (branches->addresses[i] == address) {
            return;
        }
    }

    branches->pos = branches->pos + 1;
    branches->addresses[branches->pos - 1] = address;
    ++*ubCount;

}