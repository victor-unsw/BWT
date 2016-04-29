//
// Created by Demon on 21/04/16.
//

#include <ios>
#include "../inc/pool.h"



//============================================================
// CORE METHODS
//============================================================

/*
 * fillPage(i,o).
 * - new memory is allocated.
 * - reads the data from disk into the memory
 *
 * returns : false if any failure. else true.
 */
inline bool BPool::getPage(unsigned partition) {
    pool[partition]     = new Buffer(BUFFER_SIZE);

    int START = partition * BUFFER_SIZE;

    if (fin->eof())
        fin->clear();

    fin->seekg(START,std::ios_base::beg);
    fin->read(pool[partition]->b,BUFFER_SIZE);

    return true;
}

/*
 * releasePage(p).
 * - releases given partition buffer
 *   from the pool.
 */
inline void BPool::releasePage(unsigned partition) {
    delete pool[partition];
    pool[partition] = NULL;
}

/*
 * victim(p,cp).
 * - finds partition index which has low popularity
 *   than pivot benchmark.
 *
 * - return -1 if no such index exist.
 */
inline int BPool::victim(unsigned p) {
    //unsigned current = unsigned(ceil(active.size()/2));
    unsigned current = 0;
    size_t j = current == active.size() ? 0 : current;

    for (size_t i = 0; i < active.size(); ++i) {
        if (popularity[active[j]] < pivot){
            int temp = active[j];
            active[j]  = p;
            return temp;
        }
        if (j >= active.size())
            j = 0;
    }
    return -1;
}

/*
 * getBuffer(p).
 * - returns address to buffer for given
 *   partition.
 *
 *
 */
const char* BPool::getBuffer(unsigned partition) {
    total_attempt++;                                                // attempt to access a partition
    popularity[partition]++;
    updateMax(partition);

    if (pool[partition] != NULL){
        total_safe++;
        return pool[partition]->b;
    }

    // if buffer doesn't exist in memory and pool is full
    if (SIZE >= CAPACITY){

        int nextVictim = -1;
        while ((nextVictim = victim(partition)) < 0)
            pivot += pivot;
        // therefore, we are sure that nextVictim doesn't contain 8th bit set and is unsigned
        if (nextVictim < 0){
            exit(1);
        }
        releasePage(unsigned(nextVictim));
        total_replacement++;
        SIZE--;
    } else
        active.push_back(partition);

    // fill the required buffer with data
    getPage(partition);
    total_access++;
    SIZE++;
    if (pool[partition] != NULL)
        return pool[partition]->b;
    else{
        cout << "Buffer seems NULL\n";
        exit(1);
    }

    return NULL;
}


//============================================================
// UTILITY METHODS
//============================================================

/*
 * updateMax(p).
 * - update the max_popular if 'p'
 *   partition is more popular.
 * - update pivot value.
 */
inline void BPool::updateMax(unsigned partition) {
    max_popular = popularity[partition] > max_popular ? popularity[partition] : max_popular;
    double fraction = ((max_popular*1.0)/total_attempt)*0.1;
    pivot = unsigned(ceil(fraction*max_popular));
}
