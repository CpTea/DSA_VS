#include <iostream>
#include "vector.h"
using namespace std;

int main(int argc, char* argv[]) {
    //vector<int, 3> v(2, -1);
    vector<int> v({ 0, 1, 2, 3, 4, 5 }, 0, 6);
    cout << v
        << endl;
    return 0;
}
