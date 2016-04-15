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

private:
    std::ifstream*  fin;                                                                        // file input stream
    long long       FILE_SIZE;
    double          partition_limit;                                                            // data partition limit
    unsigned        total_partitions;                                                           // total partitions
    FBucket*        buckets;

public:
    PreProcess(std::ifstream* stream = NULL, unsigned MAX_SIZE = 25000):fin(stream),partition_limit(MAX_SIZE){
        std::streampos begin,end;
        begin       = fin->tellg();    fin->seekg(0,std::ios::end);
        end         = fin->tellg();    fin->seekg(0,std::ios::beg);
        FILE_SIZE   = end-begin;

        total_partitions = (unsigned int)ceil(FILE_SIZE/partition_limit);
        buckets          = new FBucket[total_partitions];
    }

    ~PreProcess(){
        //fin = NULL;
        //delete fin;
        delete [] buckets;
    }

    void info(){
        std::cout << "FILE STREAM :-\nFILE SIZE\t["<<FILE_SIZE<<"]\n";
        std::cout << "PARTITION SIZE\t["<<partition_limit<<"]\n";
        std::cout << "TOTAL PARTITIONS\t["<<total_partitions<<"]\n";
    }

    void show_buckets(){
        for (int i = 0; i < total_partitions; ++i) {
            std::cout << (i+1) << " : ";
            buckets[i].show();
        }
    }

    void index();

};

#endif //SEARCH_INDEXING_H