#include <iostream>
#include <string>
#include <fstream>

#include "inc/preprocess.h"

using namespace std;

const string LARGE = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/large.bwt";
const string TEST100KB = "/Users/victorchoudhary/Documents/Workspace/Data/Shakespear/DOC1.txt";

int main() {

    ifstream fin(TEST100KB);
    //ifstream fin(LARGE);

    PreProcess* process = new PreProcess(&fin,25000);
    process->info();
    process->index();
    process->show_buckets();

    delete process;
    fin.close();

    return 0;
}