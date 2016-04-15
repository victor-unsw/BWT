//
// Created by Demon on 15/04/16.
//

#include "../inc/preprocess.h"

void PreProcess::index(){

    clock_t t = clock();

    unsigned totalCount         = 0;
    unsigned partitionCount     = 0;
    unsigned currentPartition   = 0;
    FBucket*  bucket            = buckets+currentPartition;


    int c = 0;
    while ((c = fin->get()) != EOF){
        // start reading the file

        if (partitionCount >= partition_limit){
            partitionCount = 0;
            currentPartition++;
            bucket = buckets+currentPartition;
        }

        bucket->freq[c]++;

        partitionCount++;
        totalCount++;
    }
    t = (clock()-t);

    std::cout << "[index time] \t: ";printf("%-5.3f sec.\n",double(t)/CLOCKS_PER_SEC);
}