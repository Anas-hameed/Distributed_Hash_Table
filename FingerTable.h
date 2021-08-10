#pragma once
#ifndef FINGERTABLE_H_
#define FINGERTABLE_H_
#include<iostream>
#include<string>
#include"FunctionUtil.h"
using namespace std;

// Prototype for the Dht class to use it pointer in Finger Table Single list Class
template <typename T>
struct dhtNode;

// This is Class Implemented for the Routing Table
template<typename T>
struct SinglyListNode
{
    dhtNode<T>* Pointer;
    SinglyListNode* next;
    SinglyListNode()
    {
        Pointer = NULL;
        next = NULL;
    }
    SinglyListNode(dhtNode<T>* n)
    {
        Pointer = n;
        next = NULL;
    }
};
// This class contain a refrence of next machine in the DDH 
template<typename T>
struct RoutingTable
{
    SinglyListNode<T>* head, * tail;
    RoutingTable()
    {
        head = tail = NULL;
    }
    void insert(dhtNode<T>* ptr)
    {
        SinglyListNode<T>* new_node = new SinglyListNode<T>(ptr);
        if (head == NULL)
            head = tail = new_node;
        else
        {
            tail->next = new_node;
            tail = new_node;
        }
    }
    void clear() {
        SinglyListNode<T>* temp = head;

        SinglyListNode<T>* current;

        while (temp != NULL) {
            current = temp;

            temp = temp->next;

            delete current;
        }

        head = NULL;
    }

    void display()
    {
        SinglyListNode<T>* temp = head;
        if (head == NULL)
        {
            cout << "List is Empty..." << endl;
            return;
        }
        while (temp != NULL)
        {
            cout << To_Integer(temp->Pointer->id) << "  ";
            temp = temp->next;
        }
        cout << endl;
        return;
    }
};
#endif