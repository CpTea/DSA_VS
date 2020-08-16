#include "list.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
    List<int> l1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    cout << l1 << endl;
    cout << l1.indexOfSorted(15) << endl;
    return 0;
}
