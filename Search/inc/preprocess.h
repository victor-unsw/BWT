//
// Created by Demon on 15/04/16.
//

#ifndef SEARCH_INDEXING_H
#define SEARCH_INDEXING_H

#include "fstream"
#include "iostream"
#include "cstring"
#include "string.h"
#include "FBucket.h"
#include "cmath"

class PreProcess{

    //============================================================
    // Instance Variables
    //============================================================

    std::ifstream*          fin;                                                                        // file input stream
    const unsigned          FILE_SIZE;                                                                  // size of file
    const unsigned          PARTITION_SIZE;                                                             // data partition limit
    const unsigned          TOTAL_PATITIONS;                                                            // total partitions
    const char*             INDEX_FILE;                                                                 // index file path & name
    FBucket*                globalBucket;


public:
    //============================================================
    // Constructor & Destructor
    //============================================================
    PreProcess(std::ifstream* stream,const char* INDEX_PATH, const unsigned F_SIZE,const unsigned P_SIZE,const unsigned T_PARTITIONS):fin(stream),
                                                                                                                                            FILE_SIZE(F_SIZE),
                                                                                                                                            PARTITION_SIZE(P_SIZE),
                                                                                                                                            globalBucket(new FBucket),
                                                                                                                                            INDEX_FILE(INDEX_PATH),
                                                                                                                                            TOTAL_PATITIONS(T_PARTITIONS){}

    /*
     * POINT input_stream to NULL;
     * fin = NULL
     *
     * delete global Bucket.
     */
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

};



#endif //SEARCH_INDEXING_H
