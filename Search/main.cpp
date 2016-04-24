#include <iostream>
#include <string>
#include <fstream>

#include "inc/preprocess.h"
#include "inc/FidoSearch.h"

using namespace std;

const string LARGE = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/large.bwt";
const string TINY = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/tiny.bwt";
const string DBLP = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/dblp.bwt";
const string TEST100KB = "/Users/victorchoudhary/Documents/Workspace/Data/Shakespear/DOC1.txt";
const string OUTPUT= "/Users/victorchoudhary/Documents/output.txt";
const string MISSI= "/Users/victorchoudhary/Documents/missi.txt";
const string TEST= "/Users/victorchoudhary/Documents/test.txt";

int main(int argc,char** argv) {

    clock_t tt = clock();
    cout << "total : " << argc << endl;
    ifstream            fin;
    const char*         indexFile   = NULL;
    const char*         search      = NULL;
    int                 buffer      = 0;
    int                 cap         = 0;

    if (argc >= 5){
        fin.open(argv[1]);
        indexFile   = argv[2];
        search      = argv[3];
        buffer      = atoi(argv[4]);
        cap         = atoi(argv[5]);
    }else{
        fin.open(LARGE);
        indexFile   = "/Users/victorchoudhary/Documents/test/large.indx";
        search      = "aa";
        buffer      = 4000;
        cap         = 10000000;
    }

    FidoSearch fido(&fin,indexFile,buffer,cap);
    fido.showStats();

    fido.crunch(search);

    fin.close();
    tt = clock() - tt;
    printf("\n\n%10s : %-5.5f sec.\n","[total time]",double(tt)/CLOCKS_PER_SEC);

    return 0;
}