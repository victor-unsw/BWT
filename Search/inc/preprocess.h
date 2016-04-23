//
// Created by Demon on 15/04/16.
//

#ifndef SEARCH_INDEXING_H
#define SEARCH_INDEXING_H

#include "fstream"
#include "iostream"
#include "cstring"
#include "FBucket.h"
#include "cmath"

class PreProcess{

    //============================================================
    // Instance Variables
    //============================================================

    std::ifstream*  fin;                                                                        // file input stream
    long long       FILE_SIZE;
    double          PARTITION_SIZE;                                                            // data partition limit
    unsigned        total_partitions;                                                           // total partitions
    const char*     INDEX_FILE;
    FBucket*        globalBucket;

    //============================================================
    // Utility methods
    //============================================================

public:
    //============================================================
    // Constructor & Destructor
    //============================================================
    PreProcess(std::ifstream* stream,const char* output,int F_SIZE,unsigned P_SIZE, unsigned T_PARTITIONS):fin(stream),
                                                                                                             FILE_SIZE(F_SIZE),
                                                                                                             PARTITION_SIZE(P_SIZE),
                                                                                                             globalBucket(new FBucket),
                                                                                                             INDEX_FILE(output),total_partitions(T_PARTITIONS){}

    ~PreProcess(){
        fin = NULL;
        delete globalBucket;
    }



    //============================================================
    // Core Methods
    //============================================================

    /*
     * index().
     * - method to index the 'bwt file' and
     *   write output to index file.
     */
    void index();


    //============================================================
    // Temporary Methods
    //============================================================

    void partition(){
        std::ofstream part("/Users/victorchoudhary/Documents/partition.txt");
        fin->seekg(0,std::ios_base::beg);
        int c = 0;      // character
        int i = 0;      // flag
        int p = 1;      // parition number

        part << "PARTITION : " << p << std::endl;
        while ((c = fin->get()) != EOF){
            if (i == PARTITION_SIZE){
                part << "\nPARTITION : " << ++p << std::endl;
                i = 0;
            }
            part.put(c);
            i++;
        }
        if (fin->eof())
            fin->clear();
        fin->seekg(0,std::ios_base::beg);
    }

};



#endif //SEARCH_INDEXING_H
