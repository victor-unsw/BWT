//
// Created by Demon on 15/04/16.
//

#ifndef SEARCH_FREQUENCYBUCKET_H
#define SEARCH_FREQUENCYBUCKET_H

#include <string.h>

class FBucket{
public:
    const int BUCKET_SIZE;

public:
    int *  freq;

    FBucket(int SIZE = 127):BUCKET_SIZE(SIZE),freq(new int[SIZE]){
        memset(freq,0,SIZE);
    }
    ~FBucket(){
        delete[]freq;
    }

    /*
     * increment(c)
     * - increments frequency of 'c' by 1.
     */
    void increment(int c){
        freq[c]++;
    }

    /*
     * get(c).
     * - returns frequency of character 'c'.
     */
    int  get(int c){
        return freq[c];
    }

    /*
     * getSize().
     * - returns size of the bucket.
     */
    int getSize(){
        return BUCKET_SIZE;
    }

    /*
     * show().
     * - display bucket.
     * (temporary method)
     */
    void show(){
        std::cout << "BUCKET [ ";
        for (int i = 0; i < BUCKET_SIZE; ++i) {
            if (freq[i] == 0)
                continue;
            std::cout << char(i) << " : " << freq[i] << "\t";
        }
        std::cout  << "]"<< std::endl;
    }

};

#endif //SEARCH_FREQUENCYBUCKET_H
