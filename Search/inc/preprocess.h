//
// Created by Demon on 15/04/16.
//

#ifndef SEARCH_INDEXING_H
#define SEARCH_INDEXING_H

#include "fstream"
#include "iostream"
#include "FBucket.h"
#include "cmath"

class PreProcess{

    //============================================================
    // Instance Variables
    //============================================================

    std::ifstream*  fin;                                                                        // file input stream
    long long       FILE_SIZE;
    double          partition_limit;                                                            // data partition limit
    unsigned        total_partitions;                                                           // total partitions
    FBucket*        globalBucket;

    //============================================================
    // Utility methods
    //============================================================

    /*
     * clone_bucket(..)
     * - updates the 't' bucket with
     *   frequency count from 'f' bucket.
     */
    inline void clone_bucket(FBucket* f,FBucket* t);


public:
    //============================================================
    // Constructor & Destructor
    //============================================================
    PreProcess(std::ifstream* stream = NULL, unsigned MAX_SIZE = 8000):fin(stream),partition_limit(MAX_SIZE),globalBucket(new FBucket){
        std::streampos begin,end;
        begin       = fin->tellg();    fin->seekg(0,std::ios::end);
        end         = fin->tellg();    fin->seekg(0,std::ios::beg);
        FILE_SIZE   = end-begin;

        total_partitions = (unsigned)ceil(FILE_SIZE/partition_limit);
    }

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
            if (i == partition_limit){
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
