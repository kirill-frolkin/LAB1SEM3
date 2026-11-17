#pragma once
#include <string>
using namespace std;
struct Stack { string* data; int top; int capacity; };
Stack* createStack(int initialCapacity = 10);
void deleteStack(Stack* stack);
void push(Stack* stack, const string& value);
string pop(Stack* stack);
string peek(Stack* stack);
bool isEmpty(Stack* stack);
