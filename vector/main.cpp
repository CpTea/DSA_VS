﻿#include <iostream>
#include "vector.h"
using namespace std;


int main(int argc, char* argv[])
{
    Vector<int> v({ 1, 2, 3, 4, 5, 6, 7 });
    v.sort(cptea::Desc);
    cout << v;
    return 0;
}
