/********************************************************************************
 * Author: 黃煜展
 * Date: 2026-10-17
 * Purpose: Template definitions for Node and UnorderedList classes.
 ********************************************************************************/

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>

using namespace std;

// --- Template for Node class ---
template <typename T>
class Node {
private:
    T data;
    Node<T> *next;

public:
    Node(T initdata) {
        data = initdata;
        next = NULL;
    }

    T getData() const { return data; }
    Node<T> *getNext() const { return next; }
    void setData(T newData) { data = newData; }
    void setNext(Node<T> *newnext) { next = newnext; }
};

// --- Template for UnorderedList class ---
template <typename T>
class UnorderedList {
private:
    Node<T> *head;

public:
    UnorderedList() { head = NULL; }

    Node<T>* getHead() const { return head; }
    void setHead(Node<T>* newHead) { head = newHead; }

    bool isEmpty() const { return head == NULL; }

    void add(T item) {
        Node<T> *temp = new Node<T>(item);
        temp->setNext(head);
        head = temp;
    }

    int size() const {
        Node<T> *current = head;
        int count = 0;
        while (current != NULL) {
            count++;
            current = current->getNext();
        }
        return count;
    }

    bool search(T item) const {
        Node<T> *current = head;
        while (current != NULL) {
            if (current->getData() == item) return true;
            current = current->getNext();
        }
        return false;
    }

    void remove(T item) {
        Node<T> *current = head;
        Node<T> *previous = NULL;
        bool found = false;
        while (!found && current != NULL) {
            if (current->getData() == item) {
                found = true;
            } else {
                previous = current;
                current = current->getNext();
            }
        }
        if (found) {
            if (previous == NULL) {
                head = current->getNext();
            } else {
                previous->setNext(current->getNext());
            }
            delete current;
        }
    }
};

#endif