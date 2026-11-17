#pragma once
#include <string>
using namespace std;
struct DynamicArray { string* data; int size; int capacity; };
DynamicArray* createArray(int initialCapacity = 10);
void deleteArray(DynamicArray* arr);
void pushBack(DynamicArray* arr, const string& value);
void pushFront(DynamicArray* arr, const string& value);
void insertAt(DynamicArray* arr, int index, const string& value);
void popBack(DynamicArray* arr);
void popFront(DynamicArray* arr);
void removeAt(DynamicArray* arr, int index);
string getAt(const DynamicArray* arr, int index);
int getSize(const DynamicArray* arr);
bool isEmpty(const DynamicArray* arr);
