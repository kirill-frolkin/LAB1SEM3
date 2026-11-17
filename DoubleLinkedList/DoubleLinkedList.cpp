#include "DoubleLinkedList.h"
using namespace std;
DoublyLinkedList* createDList() { return new DoublyLinkedList; }
void deleteDList(DoublyLinkedList* list) {
    if (!list) return;
    LNode* curr = list->head;
    while(curr) { LNode* next = curr->next; delete curr; curr = next; }
    delete list;
}
void LPUSH_HEAD(DoublyLinkedList* list, const string& key) {
    LNode* newNode = new LNode{key, nullptr, list->head};
    if (list->head) list->head->prev = newNode;
    else list->tail = newNode;
    list->head = newNode;
    list->size++;
}
void LPUSH_TAIL(DoublyLinkedList* list, const string& key) {
    LNode* newNode = new LNode{key, list->tail, nullptr};
    if (list->tail) list->tail->next = newNode;
    else list->head = newNode;
    list->tail = newNode;
    list->size++;
}
string LPOP_HEAD(DoublyLinkedList* list) {
    if (!list || !list->head) return "";
    LNode* temp = list->head;
    string val = temp->key;
    list->head = list->head->next;
    if (list->head) list->head->prev = nullptr;
    else list->tail = nullptr;
    delete temp;
    list->size--;
    return val;
}
string LPOP_TAIL(DoublyLinkedList* list) {
    if (!list || !list->tail) return "";
    LNode* temp = list->tail;
    string val = temp->key;
    list->tail = list->tail->prev;
    if (list->tail) list->tail->next = nullptr;
    else list->head = nullptr;
    delete temp;
    list->size--;
    return val;
}
bool LGET(DoublyLinkedList* list, const string& key) {
    LNode* curr = list->head;
    while(curr) { if (curr->key == key) return true; curr = curr->next; }
    return false;
}
void LDEL(DoublyLinkedList* list, const string& key) {
    LNode* curr = list->head;
    while(curr) {
        if (curr->key == key) {
            if (curr->prev) curr->prev->next = curr->next;
            else list->head = curr->next;
            if (curr->next) curr->next->prev = curr->prev;
            else list->tail = curr->prev;
            delete curr;
            list->size--;
            return;
        }
        curr = curr->next;
    }
}
