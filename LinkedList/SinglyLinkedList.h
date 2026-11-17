#pragma once
#include <string>
using namespace std;
struct FNode { string key; FNode* next; };
struct SinglyLinkedList { FNode* head = nullptr; FNode* tail = nullptr; int size = 0; };
SinglyLinkedList* createSList();
void deleteSList(SinglyLinkedList* list);
void FPUSH_HEAD(SinglyLinkedList* list, const string& key);
void FPUSH_TAIL(SinglyLinkedList* list, const string& key);
string FPOP_HEAD(SinglyLinkedList* list);
string FPOP_TAIL(SinglyLinkedList* list);
bool FGET(SinglyLinkedList* list, const string& key);
void FDEL(SinglyLinkedList* list, const string& key);
