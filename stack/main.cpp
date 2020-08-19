#include "stack.h"
#include <iostream>
#include "list.h"
using namespace std;

int main(int argc, char* argv[])
{
    Stack<int, Vector<int>> s;
    s.push(6);
    s.push(5);
    s.push(4);
    s.push(9);
    s.sort();
    cout << s << endl;
    cout << s.pop() << endl;
    cout << s << endl;
    cout << s.pop() << endl;
    cout << s << endl;
    cout << s.top() << endl;
    return 0;
}
