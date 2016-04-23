//
// Created by Demon on 19/04/16.
//

#ifndef SEARCH_FIDOSEARCH_H
#define SEARCH_FIDOSEARCH_H

#include "iostream"
#include "preprocess.h"
#include "FBucket.h"
#include "cmath"
#include "fstream"
#include "string"
#include "vector"
#include "algorithm"
#include "pool.h"

class FidoSearch{
private:
    PreProcess*     indexer;                                             // indexer object; initialized only when required
    BPool*          pool;                                                // buffer pool
    std::ifstream*  fin;                                                 // file input stream
    std::ifstream   index;                                               // later to be merged into single buffer utility
    bool            INDEX_EXISTS;                                        // does index exists already; thus no need to do indexing
    FBucket         globalBucket;
    FBucket         sortBucket;

    const long      MEMORY_CAP = 10*1000000;
    size_t          FILE_SIZE;
    unsigned        PARTITION_SIZE;                                                             // data partition limit
    unsigned        TOTAL_PARTITIONS;                                                           // total partitions
    const char*     INDEX_FILE;

    //============================================================
    // CORE METHODS
    //============================================================

    /*
     * C(c).
     * - core method.
     * - finds the total number of text chars in 'T'
     *   which are alphabetically smaller than 'c'.
     *
     * RETURNS :-
     * - integer; i.e. total count of smaller characters.
     */
    inline unsigned C(const char c);

    /*
     * Occ(c,q).
     * - core method
     * - finds number of occurance of char 'c' in prefix L[1,q]
     *
     * RETURNS :-
     * - integer; i.e. total occurance of char 'c' in L[1,q].
     */
    unsigned Occ(const char c,const unsigned q);

    /*
     * BS(P)
     * - backward search.
     * - returns total occurrance of pattern 'P'.
     * - return -1 if no occurrance found.
     */
    int BS(const std::string P);

    /*
     * decode(i).
     * - core method.
     * - decodes the bwt text from index
     *   until '[' found.
     */
    void decode(unsigned index);

    //============================================================
    // UTILITY METHODS
    //============================================================

    /*
     * fillBucket(b,o).
     * - fills the bucket from 'Index file' according
     *   to given offset
     */
    inline void fillBucket(FBucket* bucket,int partition);

    /*
     * nextAlive(c).
     * - return next character 'c'
     *   available in globalBucket.
     */
    inline char nextAlive(const char c);

public:
    //============================================================
    // CONSTRUCTOR & DESTRUCTOR
    //============================================================
    FidoSearch(std::ifstream* stream,const char* INDEX, const unsigned MAX_SIZE):indexer(NULL),
                                                                                fin(stream),
                                                                                FILE_SIZE(0),
                                                                                PARTITION_SIZE(MAX_SIZE),
                                                                                TOTAL_PARTITIONS(0),
                                                                                INDEX_EXISTS(false),
                                                                                INDEX_FILE(INDEX),
                                                                                pool(NULL)
    {
        if (stream == NULL) {
            std::cout << "no stream found in FSearch\n";
            exit(1);
        }

        std::streampos begin,end;
        begin       = fin->tellg();    fin->seekg(0,std::ios::end);
        end         = fin->tellg();    fin->seekg(0,std::ios::beg);
        FILE_SIZE   = (size_t) (end-begin);

        TOTAL_PARTITIONS = (unsigned)ceil(FILE_SIZE/(PARTITION_SIZE*1.0));

        index.open(INDEX_FILE);
        INDEX_EXISTS = index.is_open();

        // create new buffer pool
        pool = new BPool(fin,PARTITION_SIZE,TOTAL_PARTITIONS,MEMORY_CAP);
    }

    ~FidoSearch(){
        delete pool;
    }


    //============================================================
    // CORE METHODS
    //============================================================

    /*
     * crunch().
     * - core method to search & decode
     *   pattern.
     */
    void crunch(const char* P);


    //============================================================
    // UTILITY METHODS
    //============================================================
    void showStats();

};

#endif //SEARCH_FIDOSEARCH_H
