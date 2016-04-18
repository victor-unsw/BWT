#include <iostream>
#include <string>
#include <fstream>

#include "inc/preprocess.h"
#include "inc/FidoSearch.h"

using namespace std;

const string LARGE = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/large.bwt";
const string TINY = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/tiny.bwt";
const string TEST100KB = "/Users/victorchoudhary/Documents/Workspace/Data/Shakespear/DOC1.txt";
const string OUTPUT= "/Users/victorchoudhary/Documents/output.txt";

int main() {

    clock_t tt = clock();

    //ifstream fin(TEST100KB);
    //ifstream fin(OUTPUT);
    //ifstream fin(LARGE);
    ifstream fin(TINY);


    FidoSearch fido(&fin,100);
    fido.showStats();

    char c[] = "jj";

    clock_t t = clock();
    fido.crunch(c);
    t = clock() - t;

    printf("%10s : %-5.5f sec.\n","[-n]",double(t)/CLOCKS_PER_SEC);
    fin.close();
    tt = clock() - tt;
    printf("\n\n%10s : %-5.5f sec.\n","[total time]",double(tt)/CLOCKS_PER_SEC);
    return 0;
}