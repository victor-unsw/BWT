//
// Created by Demon on 15/04/16.
//

#include "../inc/preprocess.h"

//============================================================
// Core Methods
//============================================================

/*
 * index().
 * - method to index the 'bwt file' and
 *   write output to index file.
 */
void PreProcess::index(){

    // open output stream
    // in binary mode
    std::ofstream out(INDEX_FILE,std::ios_base::out|std::ios_base::binary);

    unsigned totalCount         = 0;
    unsigned partitionCount     = 0;

    // start reading the file
    int c = 0;
    while ((c = fin->get()) != EOF){

        if (partitionCount >= PARTITION_SIZE){
            // write the bucket data to index
            out.write((char*)globalBucket->freq,globalBucket->getSize()*sizeof(unsigned));
            partitionCount = 0;
        }

        globalBucket->freq[c]++;
        partitionCount++;
        totalCount++;
    }
    if (fin->eof())
        fin->clear();

    out.write((char*)globalBucket->freq,globalBucket->getSize()*sizeof(unsigned));

    out.close();
}