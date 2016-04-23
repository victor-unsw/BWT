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
inline bool BPool::getPage(int partition) {
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
inline void BPool::releasePage(int partition) {
    //Buffer* temp = pool[partition];
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
inline int BPool::victim(int p) {
    bool    found = false;
    int j = p+1 >= TOTAL_PARTITIONS ? 0 : p+1;

    for (int i = 0; i < TOTAL_PARTITIONS-1; ++i,++j) {

        if (pool[j] != NULL && popularity[j] < pivot)
            return j;
        if (j+1 == TOTAL_PARTITIONS)        // ring access
            j = -1;
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
const char* BPool::getBuffer(int partition) {
    //cout << "getting p : " << partition << endl;
    total_attempt++;                                                // attempt to access a partition
    popularity[partition]++;
    updateMax(partition);

    if (pool[partition] != NULL){
        total_safe++;
        //cout << partition << " already there\n";
        return pool[partition]->b;
    }

    // if buffer doesn't exist in memory and pool is full
    if (SIZE >= CAPACITY){
        //cout << partition << " needs replacement \n";

        int nextVictim = -1;
        while ((nextVictim = victim(partition)) == -1)
            pivot += pivot;
        cout << "releasing page : " << nextVictim << endl;
        releasePage(nextVictim);
        total_replacement++;

        SIZE--;
    }

    // fill the required buffer with data
    getPage(partition);
    total_access++;
    SIZE++;
    //cout << "sending p : " << partition << endl;
    if (pool[partition] != NULL)
        return pool[partition]->b;
    std::cout << "returning null\n";
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
inline void BPool::updateMax(int partition) {
    max_popular = popularity[partition] > max_popular ? popularity[partition] : max_popular;
    double fraction = ((max_popular*1.0)/total_attempt)*0.1;
    pivot = int(ceil(fraction*max_popular));
}
