#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>

typedef int Data;

struct List
{
    struct Node 
    {
        Data val;
        Node* next;
    };

    Node* head;
    size_t size;

    void init()
    {
        head = NULL;
        size = 0;
    }

    void push_front(Data x)
    {
        // Выделяем новый элемент и задаём его значения
        Node* p_new_node = new Node;
        p_new_node->val = x;
        p_new_node->next = head;

        // Изменяем head
        head = p_new_node;
        size++;
    }

    Data pop_front()
    {
        if (head == NULL)
        {
            printf("Error! Can't remove an element. List is empty!\n");
            exit(1);
        }
        // Запоминаем result, чтобы вернуть это значение и temp, чтобы освободить эту память в конце функции
        Node* temp = head;
        Data result = temp->val;

        // head должен указывать на 2-й элемент
        head = head->next;
        delete temp;

        size--;
        return result;
    }


    void insert_after(Node* p_node, Data x)
    {
        Node* p_new_node = new Node;
        p_new_node->val = x;
        p_new_node->next = p_node->next;

        p_node->next = p_new_node;
        size++;
    }

    Data erase_after(Node* p_node)
    {
        if (p_node == NULL || p_node->next == NULL)
            printf("Error! Can't erase element from list\n");

        Node* temp = p_node->next;
        Data temp_value = p_node->next->val;

        p_node->next = p_node->next->next;
        delete temp;
        size--;
        return temp_value;
    }


    void print()
    {
        std::cout << "List: size = " << size << ", elements = { ";
        Node* ptr = head;
        while (ptr)
        {
            std::cout << ptr->val << ", ";
            ptr = ptr->next;
        }
        std::cout << "\b\b }" << std::endl;
    }

    size_t get_size()
    {
        return size;
    }

    void destroy()
    {
        Node* ptr = head;
        Node* ptr_next;
        while (ptr != NULL)
        {
            ptr_next = ptr->next;
            delete ptr;
            ptr = ptr_next;
        }
        head = NULL;
    }
};


int main()
{
    List a;
    List b;
    a.init();
    b.init();

    for (int i = 0; i < 10; ++i)
        a.push_front(i * i);

    a.print();

    b.head = a.head->next->next;
    a.insert_after(b.head, 123);
    a.insert_after(b.head, 654);

    a.print();

    b.head = b.head->next->next->next;
    a.erase_after(b.head);
    a.erase_after(b.head);

    a.print();

    a.destroy();
}