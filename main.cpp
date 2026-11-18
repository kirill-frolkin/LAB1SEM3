#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <queue>

// Подключаем заголовочные файлы
#include "Array/Array.h"
#include "LinkedList/SinglyLinkedList.h"
#include "DoubleLinkedList/DoubleLinkedList.h"
#include "Stack/Stack.h"
#include "Queue/Queue.h"
#include "CompleteBinaryTree/CompleteBinaryTree.h"

using namespace std;

// Вспомогательная функция для стандартизации вывода TRUE/FALSE
string boolToStr(bool val) { return val ? "TRUE" : "FALSE"; }

int main(int argc, char *argv[])
{
    string filename = "";
    string query = "";

    // 1. Парсинг CLI аргументов
    for (int i = 1; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc)
            filename = argv[++i];
        else if (arg == "--query" && i + 1 < argc)
            query = argv[++i];
    }

    if (filename.empty() || query.empty())
    {
        cerr << "Usage: ./dbms --file <file.data> --query '<COMMAND> <STRUCT_NAME> [ARGS...]'" << endl;
        return 1;
    }

    // Словари для хранения структур
    unordered_map<string, DynamicArray *> arrays;
    unordered_map<string, SinglyLinkedList *> slists;
    unordered_map<string, DoublyLinkedList *> dlists;
    unordered_map<string, Stack *> stacks;
    unordered_map<string, Queue *> queues;
    unordered_map<string, CompleteBinaryTree *> trees;

    // 2. ДЕСЕРИАЛИЗАЦИЯ (Чтение из файла)

    ifstream infile(filename);
    if (infile.is_open())
    {
        string line;
        while (getline(infile, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            string type, name, val;
            ss >> type >> name;

            if (type == "ARRAY")
            {
                arrays[name] = createArray();
                while (ss >> val)
                    pushBack(arrays[name], val);
            }
            else if (type == "SLIST")
            {
                slists[name] = createSList();
                while (ss >> val)
                    FPUSH_TAIL(slists[name], val);
            }
            else if (type == "DLIST")
            {
                dlists[name] = createDList();
                while (ss >> val)
                    LPUSH_TAIL(dlists[name], val);
            }
            else if (type == "STACK")
            {
                stacks[name] = createStack();
                while (ss >> val)
                    push(stacks[name], val);
            }
            else if (type == "QUEUE")
            {
                queues[name] = createQueue();
                while (ss >> val)
                    enqueue(queues[name], val);
            }
            else if (type == "TREE")
            {
                trees[name] = createCBT();
                while (ss >> val)
                    insertCBT(trees[name], val);
            }
        }
        infile.close();
    }

    // 3. ВЫПОЛНЕНИЕ ЗАПРОСА
    stringstream qs(query);
    string cmd, structName, value;
    qs >> cmd;

    // МАССИВЫ (M)
    if (cmd == "MPUSH")
    {
        string dir;
        qs >> dir >> structName >> value;
        if (arrays.find(structName) == arrays.end())
            arrays[structName] = createArray();
        if (dir == "F")
            pushFront(arrays[structName], value);
        else
            pushBack(arrays[structName], value);
        cout << "-> " << value << endl;
    }
    else if (cmd == "MPOP")
    {
        string dir;
        qs >> dir >> structName;
        if (arrays.find(structName) != arrays.end())
        {
            if (dir == "F")
                popFront(arrays[structName]);
            else
                popBack(arrays[structName]);
            // По заданию MPOP ничего не возвращает
        }
        else
        {
            cout << "-> ошибка откуда удалить F или B" << endl;
        }
    }
    else if (cmd == "MGET")
    {
        int idx;
        qs >> structName >> idx;
        if (arrays.find(structName) != arrays.end())
            cout << "-> " << getAt(arrays[structName], idx) << endl;
    }
    else if (cmd == "MDEL")
    {
        int idx;
        qs >> structName >> idx;
        if (arrays.find(structName) != arrays.end())
            removeAt(arrays[structName], idx);
    }

    // ОДНОСВЯЗНЫЙ СПИСОК (F)
    else if (cmd == "FPUSH")
    {
        string dir;
        qs >> dir >> structName >> value;
        if (slists.find(structName) == slists.end())
            slists[structName] = createSList();
        if (dir == "F")
            FPUSH_HEAD(slists[structName], value);
        else
            FPUSH_TAIL(slists[structName], value);
        cout << "-> " << value << endl;
    }
    else if (cmd == "FPOP")
    {
        string dir;
        qs >> dir >> structName;
        if (slists.find(structName) != slists.end())
        {
            if (dir == "F")
                cout << "-> " << FPOP_HEAD(slists[structName]) << endl;
            else
                cout << "-> " << FPOP_TAIL(slists[structName]) << endl;
        }
    }
    else if (cmd == "FGET")
    {
        qs >> structName >> value;
        if (slists.find(structName) != slists.end())
        {
            cout << "-> " << boolToStr(FGET(slists[structName], value)) << endl;
        }
    }
    else if (cmd == "FDEL")
    {
        qs >> structName >> value;
        if (slists.find(structName) != slists.end())
            FDEL(slists[structName], value);
    }

    // ДВУСВЯЗНЫЙ СПИСОК (L)
    else if (cmd == "LPUSH")
    {
        string dir;
        qs >> dir >> structName >> value;
        if (dlists.find(structName) == dlists.end())
            dlists[structName] = createDList();
        if (dir == "F")
            LPUSH_HEAD(dlists[structName], value);
        else
            LPUSH_TAIL(dlists[structName], value);
        cout << "-> " << value << endl;
    }
    else if (cmd == "LPOP")
    {
        string dir;
        qs >> dir >> structName;
        if (dlists.find(structName) != dlists.end())
        {
            if (dir == "F")
                cout << "-> " << LPOP_HEAD(dlists[structName]) << endl;
            else
                cout << "-> " << LPOP_TAIL(dlists[structName]) << endl;
        }
    }
    else if (cmd == "LGET")
    {
        qs >> structName >> value;
        if (dlists.find(structName) != dlists.end())
        {
            cout << "-> " << boolToStr(LGET(dlists[structName], value)) << endl;
        }
    }
    else if (cmd == "LDEL")
    {
        qs >> structName >> value;
        if (dlists.find(structName) != dlists.end())
            LDEL(dlists[structName], value);
    }

    // СТЕК (S)
    else if (cmd == "SPUSH")
    {
        qs >> structName >> value;
        if (stacks.find(structName) == stacks.end())
            stacks[structName] = createStack();
        push(stacks[structName], value);
        cout << "-> " << value << endl;
    }
    else if (cmd == "SPOP")
    {
        qs >> structName;
        if (stacks.find(structName) != stacks.end())
            cout << "-> " << pop(stacks[structName]) << endl;
    }
    else if (cmd == "SPEEK")
    {
        qs >> structName;
        if (stacks.find(structName) != stacks.end())
            cout << "-> " << peek(stacks[structName]) << endl;
    }

    // ОЧЕРЕДЬ (Q)
    else if (cmd == "QPUSH")
    {
        qs >> structName >> value;
        if (queues.find(structName) == queues.end())
            queues[structName] = createQueue();
        enqueue(queues[structName], value);
        cout << "-> " << value << endl;
    }
    else if (cmd == "QPOP")
    {
        qs >> structName;
        if (queues.find(structName) != queues.end())
            cout << "-> " << dequeue(queues[structName]) << endl;
    }
    else if (cmd == "QFRONT")
    {
        qs >> structName;
        if (queues.find(structName) != queues.end())
            cout << "-> " << peekFront(queues[structName]) << endl;
    }

    // ДЕРЕВО (T)
    else if (cmd == "TINSERT")
    {
        qs >> structName >> value;
        if (trees.find(structName) == trees.end())
            trees[structName] = createCBT();
        insertCBT(trees[structName], value);
        cout << "-> " << value << endl;
    }
    else if (cmd == "TFIND" || cmd == "ISMEMBER")
    {
        qs >> structName >> value;
        if (trees.find(structName) != trees.end())
        {
            cout << "-> " << boolToStr(findCBT(trees[structName], value)) << endl;
        }
        else
        {
            cout << "-> FALSE" << endl;
        }
    }
    else if (cmd == "TCOMPLETE")
    {
        qs >> structName;
        if (trees.find(structName) != trees.end())
        {
            cout << "-> " << boolToStr(isCompleteCBT(trees[structName])) << endl;
        }
        else
        {
            cout << "-> TRUE" << endl; // Пустое дерево считается полным
        }
    }

    // =========================================================
    // 4. СЕРИАЛИЗАЦИЯ (Запись в файл)
    // =========================================================
    ofstream outfile(filename, ios::trunc);

    for (auto const &pair : arrays)
    {
        outfile << "ARRAY " << pair.first;
        for (int i = 0; i < pair.second->size; i++)
            outfile << " " << pair.second->data[i];
        outfile << "\n";
    }

    for (auto const &pair : slists)
    {
        outfile << "SLIST " << pair.first;
        FNode *curr = pair.second->head;
        while (curr)
        {
            outfile << " " << curr->key;
            curr = curr->next;
        }
        outfile << "\n";
    }

    for (auto const &pair : dlists)
    {
        outfile << "DLIST " << pair.first;
        LNode *curr = pair.second->head;
        while (curr)
        {
            outfile << " " << curr->key;
            curr = curr->next;
        }
        outfile << "\n";
    }

    for (auto const &pair : stacks)
    {
        outfile << "STACK " << pair.first;
        for (int i = 0; i <= pair.second->top; i++)
            outfile << " " << pair.second->data[i];
        outfile << "\n";
    }

    for (auto const &pair : queues)
    {
        outfile << "QUEUE " << pair.first;
        Queue *q = pair.second;
        for (int i = 0; i < q->size; i++)
            outfile << " " << q->data[(q->front + i) % q->capacity];
        outfile << "\n";
    }

    // Сохранение дерева обходом в ширину
    for (auto const &pair : trees)
    {
        outfile << "TREE " << pair.first;
        if (pair.second->root)
        {
            std::queue<TreeNode *> q;
            q.push(pair.second->root);
            while (!q.empty())
            {
                TreeNode *curr = q.front();
                q.pop();
                outfile << " " << curr->data;
                if (curr->left)
                    q.push(curr->left);
                if (curr->right)
                    q.push(curr->right);
            }
        }
        outfile << "\n";
    }

    outfile.close();

    // Очистка памяти
    for (auto &p : arrays)
        deleteArray(p.second);
    for (auto &p : slists)
        deleteSList(p.second);
    for (auto &p : dlists)
        deleteDList(p.second);
    for (auto &p : stacks)
        deleteStack(p.second);
    for (auto &p : queues)
        deleteQueue(p.second);
    for (auto &p : trees)
        deleteCBT(p.second);

    return 0;
}
