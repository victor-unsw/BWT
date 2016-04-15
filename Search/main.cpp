#include <iostream>
#include <string>
#include <fstream>

#include "inc/preprocess.h"

using namespace std;

const string LARGE = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/large.bwt";
const string TEST100KB = "/Users/victorchoudhary/Documents/Workspace/Data/Shakespear/DOC1.txt";

int main() {

    ifstream fin(LARGE);

    PreProcess* process = new PreProcess(&fin,50000);
    process->info();
    process->index();

    delete process;
    fin.close();


    return 0;
}