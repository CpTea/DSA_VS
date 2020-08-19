#include "queue.h"
#include <iostream>
using namespace std;

int main()
{
    Queue<int> q;
    q.enqueue(6);
    q.enqueue(5);
    q.enqueue(8);
    q.enqueue(0);
    cout << q << endl;
    cout << q.dequeue() << endl;
    cout << q << endl;
    cout << q.dequeue() << endl;
    cout << q << endl;
    q.sort(cptea::Asc, 2);
    cout << q << endl;
    return 0;
}
