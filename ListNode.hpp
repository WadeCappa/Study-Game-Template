#include "LinuxData.hpp"

#include <iostream>
#include <fstream>
#include <string>

#pragma once


template <typename T>
class ListNode
{
    public:
        ListNode( T *newData);
        ListNode(ListNode<T>* inNode);
        ~ListNode();

        T* getData(void);
        void setData( T *inData);

        ListNode<T>* getNext(void);
        void setNext(ListNode<T>* &newListNode);

        T* data;
        ListNode<T>* next;

    private:
        
};



template <typename T>
ListNode<T>::ListNode( T *newData)
{
    // std::cout << "ListNode Constructor" << std::endl;
    this->data = newData;
    this->next = nullptr;
    // std::cout << "Exited ListNode Constructor" << std::endl;
}


template <typename T>
ListNode<T>::ListNode(ListNode<T>* inNode)
{
    data = new LinuxData(inNode->getData());
    next = nullptr;
}


template <typename T>
ListNode<T>::~ListNode(void)
{
    delete data;
}

template <typename T>
T* ListNode<T>::getData(void) 
{
    return data;
}


template <typename T>
void ListNode<T>::setData( T* inData)
{
    data = inData;
}

template <typename T>
ListNode<T>* ListNode<T>::getNext(void) 
{
    return next;
}

template <typename T>
void ListNode<T>::setNext(ListNode<T>* &newListNode)
{
    next = newListNode;
}

