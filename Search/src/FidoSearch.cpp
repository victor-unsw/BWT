//
// Created by Demon on 19/04/16.
//

//
//  ' we have to fix 'a' query from tiny.bwt


#include "../inc/FidoSearch.h"
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
inline unsigned FidoSearch::C(const char c) {
    return sortBucket.freq[c];
}

/*
 * Occ(c,q).
 * - core method
 * - finds number of occurance of char 'c' in prefix L[1,q]
 *
 * c := character of which we need to find occurance
 * q := exact index till which you wish to count.
 *
 * RETURNS :-
 * - integer; i.e. total occurance of char 'c' in L[1,q].
 */
unsigned FidoSearch::Occ(const char c, const unsigned q) {

    int         current_partition   = int(q/PARTITION_SIZE);
    int         pre_partition       = current_partition - 1;
    unsigned    frequency           = 0;
    FBucket     tempBucket;

    // fill bucket with pre partition frequencies
    if (pre_partition >= 0){
        fillBucket(&tempBucket,pre_partition);
        frequency = (unsigned)tempBucket.freq[c];
    }


    // do linear frequency count over current partition
    int         start   = int(current_partition * PARTITION_SIZE);                      // start position for read in 'bwt' file
    const char* buffer  = pool->getBuffer(current_partition);                           // get buffer from pool
    if (buffer == NULL){
        std::cout << "no buffer received";
        exit(1);
    }

    int LIMIT = (q-start)+1;
    for (int i = 0; i < LIMIT; ++i)
        if (buffer[i] == c)
            frequency++;

    return frequency;
}

/*
 * BS(P)
 * - backward search.
 * - returns total occurrance of pattern 'P'.
 * - return -1 if no occurrance found.
 */
int FidoSearch::BS(const std::string P) {
    clock_t t = clock();
    size_t      loc     = P.size()-1;
    char        c       = P[loc];
    char        n       = nextAlive(c);                 // next character in global bucket
    if (n == 0)
        return -1;

    unsigned    FIRST   = C(c);
    unsigned    LAST    = C(n) - 1;

    while ((FIRST <= LAST) && loc >= 1){
        c       = P[--loc];
        FIRST   = C(c) + Occ(c,FIRST-1);
        LAST    = C(c) + Occ(c,LAST) - 1;
    }

    if (FIRST > LAST) {
        return -1;
    }

    int total_records = (LAST-FIRST+1);
    t = clock() - t;
    printf("%10s : %u\n","[-n]",total_records);
    printf("%10s : %-5.5f sec.\n","[-n]",double(t)/CLOCKS_PER_SEC);

    for (int i = FIRST; i <= LAST; ++i)
        decode(i);
    return total_records;
}

/*
 * decode(i).
 * - core method.
 * - decodes the bwt text from index
 *   until '[' found.
 */
void FidoSearch::decode(unsigned index) {
    char c = 0;
    unsigned next = index;

    //std::string value;value.reserve(5000);
    //bool fill = false;
    while (c != '['){
        int p = int(next/PARTITION_SIZE);                                               // partition of character we need

        int PSTART = int(p * PARTITION_SIZE);
        int target = next - PSTART;

        const char * buffer = pool->getBuffer(p);
        if (buffer == NULL){
            std::cout << "no buffer received";
            exit(1);
        }
        c = buffer[target];
        //value.insert(value.begin(),c);

        unsigned o = Occ(c,next);                               // major time con
        unsigned u = C(c);
        next = u + o - 1;

        //if (c == ']')
        //    fill = true;
    }
    //std::cout << "-> " << value << std::endl;
}

/*
 * crunch().
 * - core method to search & decode
 *   pattern.
 */
void FidoSearch::crunch(char* P) {
    clock_t t = clock();

    if (!INDEX_EXISTS){
        indexer = new PreProcess(fin,PARTITION_SIZE);
        indexer->index();
        delete indexer;
        index.open(INDEX_FILE);
    }

    if (!index.is_open()){
        std::cout << "ERROR IN OPENING Index File\n";
        exit(1);
    }

    // fill global frequency bucket
    fillBucket(&globalBucket,TOTAL_PARTITIONS-1);
    index.seekg(0);
    if (globalBucket.isEmpty()){
        std::cout << "Global bucket empty\n";
        exit(1);
    } else{
        // fill the sort bucket frequency
        int size = sortBucket.getSize();
        for (int i = 0,count = 0; i < size; ++i) {
            if (globalBucket.freq[i] == 0)
                continue;
            sortBucket.freq[i] = count;
            count += globalBucket.freq[i];
        }
    };

    std::string pattern(P);
    int r = BS(pattern);
    if (r == -1)
        std::cout << "no pattern exist\n";

    t = clock() - t;

    printf("%10s : %-5.5f sec.\n","[per match]",(double(t)/CLOCKS_PER_SEC)/r);
    pool->stats();
}


//============================================================
// UTILITY METHODS
//============================================================

/*
 * fillBucket(b,o).
 * - fills the bucket from 'Index file' according
 *   to given offset
 */
inline void FidoSearch::fillBucket(FBucket *bucket, int partition) {
    if (index.eof())
        index.clear();

    index.seekg(partition*int(bucket->getSize()* sizeof(int)),std::ios_base::beg);
    index.read((char*)bucket->freq,bucket->getSize()* sizeof(int));
}

/*
 * nextAlive(c).
 * - return next character 'c'
 *   available in globalBucket.
 *
 * - return 0 if no next bucket alive.
 */
inline char FidoSearch::nextAlive(const char c) {
    for (int i = c+1; i < globalBucket.getSize(); ++i)
        if (globalBucket.freq[i] != 0)
            return char(i);
    return 0;
}


void FidoSearch::showStats() {
    std::cout << "\n\t--------xxxxxxxxxxxxx--------\n";
    printf("%20s :: [%lu]\n","FILE SIZE",FILE_SIZE);
    printf("%20s :: [%.0lf]\n","PARTITION SIZE",PARTITION_SIZE);
    printf("%20s :: [%d]\n","TOTAL PARTITIONS",TOTAL_PARTITIONS);
    std::cout << "\t--------xxxxxxxxxxxxx--------\n\n";
}