#include <iostream>
#include "vector.h"
using namespace std;


int main(int argc, char* argv[])
{
    Vector<int>({ 1, 2, 3, 4, 5, 6, 7 }).sort(cptea::Desc);
    return 0;
}
