

#include <iostream>
#include <fstream>
#include <string>

#include "ListNode.hpp"

#pragma once

template <typename T>
class LinkedList
{
    public:
        LinkedList();
        LinkedList(LinkedList<T>*);
        ~LinkedList();

        ListNode<T>* getHead(void) ;
        int getLength(void);

        void pushNode(ListNode<T> *inNode);
        ListNode<T>* getNode(int n);
        void removeNode(int n);
        void removeNode(T* data);



        bool checkDuplicate(T* data);

        void DEBUG_PRINTLIST(void);

    private:
        ListNode<T>* headNode;
        int length;
};




template <typename T>
LinkedList<T>::LinkedList()
{
    headNode = nullptr;
    length = 0;
}


template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>* inList)
{
    headNode = nullptr;
    length = 0;

    ListNode<T>* trav = inList->getHead();

    while (trav != nullptr)
    {
        pushNode(new ListNode<T>(trav));
        trav = trav->next;
    }
}



template <typename T>
LinkedList<T>::~LinkedList()
{
    ListNode<T>* trav = headNode;
    ListNode<T>* laggedTrav = headNode;
    while (trav != nullptr)
    {
        trav = laggedTrav->next;
        delete laggedTrav;
        laggedTrav = trav;
    }
    delete trav;
}


template <typename T>
ListNode<T>* LinkedList<T>::getHead(void)
{
    return headNode;
}


template <typename T>
int LinkedList<T>::getLength(void)
{
    return length;
}


template <typename T>
void LinkedList<T>::pushNode(ListNode<T>* inNode)
{
    if (headNode == nullptr)
    {
        headNode = inNode;
    }
    else 
    {
        inNode->setNext(headNode);
        headNode = inNode;
    }
    length++;
}


template <typename T>
ListNode<T>* LinkedList<T>::getNode(int n)
{
    int count = 0;
    ListNode<T> *trav = headNode;

    while (count != n)
    {
        trav = trav->next;
        count++;
    }
    return trav;
}


template <typename T>
void LinkedList<T>::removeNode(int n)
{
    int count = 0;
    ListNode<T> *trav = headNode;

    while (count != n - 1)
    {
        trav = trav->next;
        count++;
    }

    ListNode<T> *temp = trav->next;
    trav->setNext(trav->next->next);
    delete temp;

    length--;   
}


template <typename T>
void LinkedList<T>::removeNode(T* data)
{
    ListNode<T> *trav = headNode;

    if (*data == *headNode->getData())
    {
        headNode = headNode->next;
        delete trav;
    }
    else
    {
        while (!(*trav->next->getData() == *data))
        {
            trav = trav->next;
        }
        ListNode<T> *temp = trav->next;
        trav->setNext(trav->next->next);
        delete temp;
    }
    length--;  
}


template <typename T>
bool LinkedList<T>::checkDuplicate(T* data)
{
    ListNode<T>* trav = headNode;
    while (trav != nullptr)
    {
        if (*trav->getData() == *data)
        {
            return true;
        }
        trav = trav->next;
    }
    return false;
}



template <typename T>
void LinkedList<T>::DEBUG_PRINTLIST(void)
{
    ListNode<T> *trav = headNode;
    int count = 0;

    while (trav)
    {
        std::cout << count++ << ") " << *trav->data << std::endl;
        trav = trav->next;
    }
}







template <typename T>
std::ofstream & operator << (std::ofstream &stream, LinkedList<T> &inputList)
{
    ListNode<T> *trav = inputList.getHead();
    while (trav != nullptr)
    {
        stream << *trav->data;
        trav = trav->next;
    }
    return stream;
}