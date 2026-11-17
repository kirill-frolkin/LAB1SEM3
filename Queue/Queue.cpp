#include "Queue.h"
using namespace std;
Queue* createQueue(int initialCapacity) {
    Queue* q = new Queue;
    q->capacity = initialCapacity;
    q->data = new string[q->capacity];
    q->front = 0; q->rear = -1; q->size = 0;
    return q;
}
void deleteQueue(Queue* q) {
    if (q) { delete[] q->data; delete q; }
}
void enqueue(Queue* q, const string& value) {
    if(q->size == q->capacity) return; 
    q->rear = (q->rear + 1) % q->capacity;
    q->data[q->rear] = value; 
    q->size++;
}
string dequeue(Queue* q) {
    if(q->size == 0) return "";
    string val = q->data[q->front];
    q->front = (q->front + 1) % q->capacity; 
    q->size--;
    return val;
}
string peekFront(Queue* q) {
    if(q->size == 0) return "";
    return q->data[q->front];
}
