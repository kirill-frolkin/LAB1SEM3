#pragma once
#include <string>
using namespace std;
struct Queue { string* data; int front; int rear; int size; int capacity; };
Queue* createQueue(int initialCapacity = 10);
void deleteQueue(Queue* queue);
void enqueue(Queue* queue, const string& value);
string dequeue(Queue* queue);
string peekFront(Queue* queue);
