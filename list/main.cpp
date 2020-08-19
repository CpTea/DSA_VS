#include "list.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
    //List<int> l1({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 });
    //List<int> l1({ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 });
    List<int> l1({ 0, 2, 5, 6, 8, 7, 6, 4, 3, 1, 9 });
    //cout << l1.deduplicate() << endl;
    l1.sort(cptea::Desc, 2);
    l1.deduplicate();
    cout << l1;
    cout << l1[5];
    //cout << l1.max() << endl;
    return 0;
}
