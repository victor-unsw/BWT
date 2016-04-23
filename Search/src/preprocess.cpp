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

    clock_t t = clock();

    std::ofstream out(INDEX_FILE,std::ios_base::out|std::ios_base::binary);

    unsigned totalCount         = 0;
    unsigned partitionCount     = 0;

    int c = 0;
    while ((c = fin->get()) != EOF){
        // start reading the file

        if (partitionCount >= PARTITION_SIZE){
            // write the bucket data to index
            out.write((char*)globalBucket->freq,globalBucket->getSize()*sizeof(int));
            //globalBucket->show();
            partitionCount = 0;
        }

        globalBucket->freq[c]++;
        partitionCount++;
        totalCount++;
    }

    out.write((char*)globalBucket->freq,globalBucket->getSize()*sizeof(int));

    t = (clock()-t);
    out.close();
    std::cout << "[index time] \t: ";printf("%-5.3f sec.\n",double(t)/CLOCKS_PER_SEC);
}