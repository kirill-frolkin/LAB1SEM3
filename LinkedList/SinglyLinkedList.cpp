#include "SinglyLinkedList.h"
using namespace std;
SinglyLinkedList* createSList() { return new SinglyLinkedList; }
void deleteSList(SinglyLinkedList* list) {
    if (!list) return;
    FNode* curr = list->head;
    while(curr) { FNode* next = curr->next; delete curr; curr = next; }
    delete list;
}
void FPUSH_HEAD(SinglyLinkedList* list, const string& key) {
    FNode* newNode = new FNode{key, list->head};
    list->head = newNode;
    if (!list->tail) list->tail = newNode;
    list->size++;
}
void FPUSH_TAIL(SinglyLinkedList* list, const string& key) {
    FNode* newNode = new FNode{key, nullptr};
    if (!list->tail) { list->head = list->tail = newNode; }
    else { list->tail->next = newNode; list->tail = newNode; }
    list->size++;
}
string FPOP_HEAD(SinglyLinkedList* list) {
    if (!list || !list->head) return "";
    FNode* temp = list->head;
    string val = temp->key;
    list->head = list->head->next;
    if (!list->head) list->tail = nullptr;
    delete temp;
    list->size--;
    return val;
}
string FPOP_TAIL(SinglyLinkedList* list) {
    if (!list || !list->head) return "";
    if (list->head == list->tail) return FPOP_HEAD(list);
    FNode* curr = list->head;
    while (curr->next != list->tail) curr = curr->next;
    string val = list->tail->key;
    delete list->tail;
    list->tail = curr;
    list->tail->next = nullptr;
    list->size--;
    return val;
}
bool FGET(SinglyLinkedList* list, const string& key) {
    FNode* curr = list->head;
    while(curr) { if (curr->key == key) return true; curr = curr->next; }
    return false;
}
void FDEL(SinglyLinkedList* list, const string& key) {
    if (!list || !list->head) return;
    if (list->head->key == key) { FPOP_HEAD(list); return; }
    FNode* curr = list->head;
    while(curr->next && curr->next->key != key) curr = curr->next;
    if (curr->next) {
        FNode* temp = curr->next;
        curr->next = temp->next;
        if (temp == list->tail) list->tail = curr;
        delete temp;
        list->size--;
    }
}
