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
            clone_bucket(buckets+(currentPartition-1),bucket);
        }

        bucket->freq[c]++;

        partitionCount++;
        totalCount++;
    }
    clone_bucket(bucket,globalBucket);
    t = (clock()-t);

    std::cout << "[index time] \t: ";printf("%-5.3f sec.\n",double(t)/CLOCKS_PER_SEC);
}

/*
     * clone_bucket(..)
     * - updates the 't' bucket with
     *   frequency count from 'f' bucket.
     */
inline void PreProcess::clone_bucket(FBucket* const f,FBucket* const t){
    for (int i = 0; i < f->getSize(); ++i)
        t->freq[i] = f->freq[i];
}