//
// Created by Demon on 15/04/16.
//

#include "../inc/preprocess.h"

//============================================================
// Core Methods
//============================================================

/*
 * index().
 * - method to index the 'bwt file' and
 *   write output to index file.
 */
void PreProcess::index(){

    clock_t t = clock();

    std::ofstream out("/Users/victorchoudhary/Documents/output.txt",std::ios_base::out|std::ios_base::binary);

    unsigned totalCount         = 0;
    unsigned partitionCount     = 0;
    unsigned currentPartition   = 0;
    FBucket*  bucket            = buckets+currentPartition;

    int c = 0;
    while ((c = fin->get()) != EOF){
        // start reading the file

        if (partitionCount >= partition_limit){
            // write the bucket data to index
            out.write((char*)bucket->freq,bucket->getSize()*sizeof(int));

            partitionCount = 0;
            currentPartition++;
            bucket = buckets+currentPartition;
            clone_bucket(buckets+(currentPartition-1),bucket);
        }

        bucket->freq[c]++;

        partitionCount++;
        totalCount++;
    }
    clone_bucket(bucket,globalBucket);
    out.write((char*)globalBucket->freq,globalBucket->getSize()*sizeof(int));
    t = (clock()-t);
    out.close();
    std::cout << "[index time] \t: ";printf("%-5.3f sec.\n",double(t)/CLOCKS_PER_SEC);
    globalBucket->show();
}


/*
 * bot()
 * - bot;
 * - performs indexing if '.index' file
 *   not present.
 * - if present; then does as per logic.
 */
void PreProcess::bot() {
    info();
    const std::string TARGET = "/Users/victorchoudhary/Documents/output.txt";

    std::ifstream INDEX_FILE(TARGET,std::ios_base::in|std::ios_base::binary);

    // if file doesn't exist
    // create index file.
    if (!INDEX_FILE.is_open()) {
        INDEX_FILE.close();
        index();
        INDEX_FILE.open(TARGET,std::ios_base::in|std::ios_base::binary);
    }
   // show_buckets();

    /*
    while (true) {
        int location = 0;
        int t = 0;
        std::cout << "Enter partition : ";
        std::cin >> location;

        if (location == -1)
            break;

        if (location >= 0 && location < total_partitions) {
            INDEX_FILE.seekg(location*508, std::ios_base::beg);
            std::cout << "current lcoation : " << INDEX_FILE.tellg() << "\n";
            FBucket output;
            INDEX_FILE.read((char *) output.freq, output.getSize() * sizeof(int));
            output.show();
            if (INDEX_FILE.eof()){
                std::cout << "end of bit active\n";
                INDEX_FILE.clear();
            }
        }

    }*/
    clock_t cc = clock();
    char c = 'c';
    //std::cout << "Enter character : ";
    //std::cin >> c;

    int location = 10000;
    //std::cout << "Enter location : ";
    //std::cin >> location;
    std::cout << "start location : " << location << std::endl;

    int start = location;
    int end = int(FILE_SIZE);

    for (int k = 0; k < 5000; ++k) {

        int position = k & 1 ? (start+location) : (end-location);

        int count = 0;
        int CHUNK = 508;            // hardcoded count of 127*4 bytes

        // find partition number of location
        int c_partition = int(position / partition_limit);
        int precount_partition = c_partition - 1;
        if (precount_partition >= 0) {
            INDEX_FILE.seekg(CHUNK * precount_partition, std::ios_base::beg);
            FBucket output;
            INDEX_FILE.read((char *) output.freq, output.getSize() * sizeof(int));
            count = output.freq[c];
            if (INDEX_FILE.eof())
                INDEX_FILE.clear();
        }
        //std::cout << "character partition: " << c_partition << "\n";
        //std::cout << "precount frequency : " << count << "\n";

        int start_position = c_partition * partition_limit;
        //std::cout << "file read position : " << start_position << std::endl;
        fin->seekg(start_position, std::ios_base::beg);

        int i = 0, j = 0;
        int limit = (position - start_position);
        //std::cout << "characters left : " << limit << std::endl << "[";

        while ((i = fin->get()) != EOF && j < limit) {
            //std::cout << char(i);
            if (i == c)
                count++;
            j++;
        }
        //std::cout << "]\n";
        //std::cout << "after linear count: " << count << std::endl;
        location+=1000;
    }
    std::cout << "end location : " << location << std::endl;
    cc = clock()-cc;
    std::cout << "[time] \t: ";printf("%-5.3f sec.\n",double(cc)/CLOCKS_PER_SEC);
}

//============================================================
// Utility methods
//============================================================

/*
     * clone_bucket(..)
     * - updates the 't' bucket with
     *   frequency count from 'f' bucket.
     */
inline void PreProcess::clone_bucket(FBucket* const f,FBucket* const t){
    for (int i = 0; i < f->getSize(); ++i)
        t->freq[i] = f->freq[i];
}