#include "Array.h"
using namespace std;
static void ensureCapacity(DynamicArray* arr, int needed) {
    if (needed <= arr->capacity) return;
    int newCap = arr->capacity;
    while (newCap < needed) newCap *= 2;
    if (newCap < 4) newCap = 4;
    string* newData = new string[newCap];
    for (int i = 0; i < arr->size; ++i) newData[i] = arr->data[i];
    delete[] arr->data;
    arr->data = newData;
    arr->capacity = newCap;
}
DynamicArray* createArray(int initialCapacity) {
    if (initialCapacity < 1) initialCapacity = 1;
    DynamicArray* arr = new DynamicArray;
    arr->capacity = initialCapacity;
    arr->size = 0;
    arr->data = new string[arr->capacity];
    return arr;
}
void deleteArray(DynamicArray* arr) {
    if (!arr) return;
    delete[] arr->data;
    delete arr;
}
void pushBack(DynamicArray* arr, const string& value) {
    if (!arr) return;
    ensureCapacity(arr, arr->size + 1);
    arr->data[arr->size++] = value;
}
void pushFront(DynamicArray* arr, const string& value) { insertAt(arr, 0, value); }
void insertAt(DynamicArray* arr, int index, const string& value) {
    if (!arr) return;
    if (index < 0) index = 0;
    if (index > arr->size) index = arr->size;
    ensureCapacity(arr, arr->size + 1);
    for (int i = arr->size; i > index; --i) { arr->data[i] = arr->data[i - 1]; }
    arr->data[index] = value;
    arr->size++;
}
void popBack(DynamicArray* arr) {
    if (!arr || arr->size == 0) return;
    arr->size--;
}
void popFront(DynamicArray* arr) { removeAt(arr, 0); }
void removeAt(DynamicArray* arr, int index) {
    if (!arr) return;
    if (index < 0 || index >= arr->size) return;
    for (int i = index; i < arr->size - 1; ++i) { arr->data[i] = arr->data[i + 1]; }
    arr->size--;
}
string getAt(const DynamicArray* arr, int index) {
    if (!arr || index < 0 || index >= arr->size) return "";
    return arr->data[index];
}
int getSize(const DynamicArray* arr) { return arr ? arr->size : 0; }
bool isEmpty(const DynamicArray* arr) { return !arr || arr->size == 0; }
