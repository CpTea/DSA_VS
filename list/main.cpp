#include "list.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
    List<int> li({ 1, 2, 3, 4, 5, 6 });
    float arr[6] = { 0.1, 5., 0.5, 4, 6, 6 };
    List<float> l2(arr, 6);
    cout << l2 << endl;
    return 0;
}
