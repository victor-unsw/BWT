#include <iostream>
#include <string>
#include <fstream>

#include "inc/preprocess.h"

using namespace std;

const string LARGE = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/large.bwt";
const string TINY = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/tiny.bwt";
const string TEST100KB = "/Users/victorchoudhary/Documents/Workspace/Data/Shakespear/DOC1.txt";
const string OUTPUT= "/Users/victorchoudhary/Documents/output.txt";

int main() {
    //ifstream fin(TEST100KB);
    //ifstream fin(OUTPUT);
    ifstream fin(LARGE);
    //ifstream fin(TINY);

    PreProcess* process = new PreProcess(&fin,8000);
    //process->partition();
    process->bot();
    //process->show_buckets();

    delete process;
    fin.close();

    return 0;
}