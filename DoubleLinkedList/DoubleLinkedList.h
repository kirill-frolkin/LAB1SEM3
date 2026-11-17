#pragma once
#include <string>
using namespace std;
struct LNode { string key; LNode* prev; LNode* next; };
struct DoublyLinkedList { LNode* head = nullptr; LNode* tail = nullptr; int size = 0; };
DoublyLinkedList* createDList();
void deleteDList(DoublyLinkedList* list);
void LPUSH_HEAD(DoublyLinkedList* list, const string& key);
void LPUSH_TAIL(DoublyLinkedList* list, const string& key);
string LPOP_HEAD(DoublyLinkedList* list);
string LPOP_TAIL(DoublyLinkedList* list);
bool LGET(DoublyLinkedList* list, const string& key);
void LDEL(DoublyLinkedList* list, const string& key);
