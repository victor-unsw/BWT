//
// Created by Demon on 15/04/16.
//

#ifndef SEARCH_FREQUENCYBUCKET_H
#define SEARCH_FREQUENCYBUCKET_H

#include <string.h>

class FBucket{
public:
    const unsigned BUCKET_SIZE;

public:
    unsigned *  freq;

    FBucket(const int SIZE = 127):BUCKET_SIZE(SIZE),freq(new unsigned[SIZE]){
        memset(freq,0,SIZE* sizeof(unsigned));
    }
    ~FBucket(){
        delete[]freq;
    }

    /*
     * getSize().
     * - returns size of the bucket.
     */
    unsigned getSize(){
        return BUCKET_SIZE;
    }

    /*
     * show().
     * - display bucket.
     * (temporary method)
     */
    void show(){
        std::cout << "BUCKET [ ";
        for (size_t i = 0; i < BUCKET_SIZE; ++i) {
            if (freq[i] == 0)
                continue;
            std::cout << char(i) << " : " << freq[i] << "\t";
        }
        std::cout  << "]"<< std::endl;
    }

    bool isEmpty(){
        for (size_t i=0;i<BUCKET_SIZE;++i) {
            if (freq[i] != 0)
                return false;
        }
        return true;
    }

};

#endif //SEARCH_FREQUENCYBUCKET_H
