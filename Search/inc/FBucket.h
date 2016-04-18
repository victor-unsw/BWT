//
// Created by Demon on 15/04/16.
//

#ifndef SEARCH_FREQUENCYBUCKET_H
#define SEARCH_FREQUENCYBUCKET_H

#include <string.h>

class FBucket{
private:
    int BUCKET_SIZE;

public:
    int *  freq;

    FBucket(int SIZE = 127):freq(new int[SIZE]){
        BUCKET_SIZE = SIZE;
        memset(freq,0,SIZE);
    }
    ~FBucket(){
        delete [] freq;
    }

    void increment(int c){
        freq[c]++;
    }
    int  get(int c){
        return freq[c];
    }
    int getSize(){
        return BUCKET_SIZE;
    }

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
