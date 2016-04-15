#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const string LARGE = "/Users/victorchoudhary/Documents/Workspace/Data/BWT/large.bwt";

int main() {

    ifstream fin(LARGE);

    int c = 0;
    int count = 0;

    clock_t it = clock();                                   // input time

    while ((c = fin.get()) != EOF)
        count++;
    it = (clock() - it);

    cout << "[reading time] \t: ";printf("%-5.3f sec.\n",double(it)/CLOCKS_PER_SEC);
    cout << "total : " << (count/(1000*1000.0))<< " MB" << endl;

    return 0;
}