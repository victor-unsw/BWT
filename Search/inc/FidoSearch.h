//
// Created by Demon on 19/04/16.
//

#ifndef SEARCH_FIDOSEARCH_H
#define SEARCH_FIDOSEARCH_H

#include "iostream"
#include "preprocess.h"
#include "FBucket.h"
#include "fstream"
#include "string"

class FidoSearch{
private:
    PreProcess*     indexer;                                             // indexer object; initialized only when required
    std::ifstream*  fin;                                                 // file input stream
    std::ifstream   index;          // later to be merged into single buffer utility
    bool            INDEX_EXISTS;                                        // does index exists already; thus no need to do indexing
    FBucket         globalBucket;

    size_t          FILE_SIZE;
    double          PARTITION_SIZE;                                                             // data partition limit
    unsigned        TOTAL_PARTITIONS;                                                           // total partitions
    const std::string INDEX_FILE;

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
    unsigned C(const char c);

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
    FidoSearch(std::ifstream* stream = NULL, const unsigned MAX_SIZE = 25000):indexer(NULL),fin(stream),FILE_SIZE(0),PARTITION_SIZE(MAX_SIZE),TOTAL_PARTITIONS(0),INDEX_EXISTS(
            false),INDEX_FILE("/Users/victorchoudhary/Documents/output.txt"){
        if (stream!=NULL){
            std::streampos begin,end;
            begin       = fin->tellg();    fin->seekg(0,std::ios::end);
            end         = fin->tellg();    fin->seekg(0,std::ios::beg);
            FILE_SIZE   = (size_t) (end-begin);

            TOTAL_PARTITIONS = (unsigned)ceil(FILE_SIZE/PARTITION_SIZE);
        }
        index.open(INDEX_FILE);
        INDEX_EXISTS = index.is_open();
    }


    //============================================================
    // CORE METHODS
    //============================================================

    /*
     * crunch().
     * - core method to search & decode
     *   pattern.
     */
    void crunch(char* P);


    //============================================================
    // UTILITY METHODS
    //============================================================
    void showStats();

};

#endif //SEARCH_FIDOSEARCH_H
