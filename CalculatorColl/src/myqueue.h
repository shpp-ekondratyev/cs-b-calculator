/* File: myqueue.h
 * -----------------------------------------------------
 * This file exports a simple version of the Queue class
 * based on the linked list.
 */

#ifndef MYQUEUE_H
#define MYQUEUE_H

#include <iostream>

/* Class: MyQueue<T>
 * -------------------------------------------------------
 * This clas implements queue of a specified ValueType (T)
 * elements
 */
template <typename T>
class MyQueue{
private:
    /* Structure for saving elements of the queue */
    struct Node{
        T value;
        Node* link;
    };
    /* Links for the linked list */
    Node* top;
    Node* down;
    int count; // Current number of the elements in the queue
public:
    MyQueue();
    virtual ~MyQueue();
    T dequeue(); // Removes the first elements of the queue and returns it's value
    void enqueue (T); // Adds new element to the end of the queue
    void clear(); // Removes all elements of the queue
    int size() const; // Return current number of the elements of the queue
    bool isEmpty() const; // Returns true if current number of the elements is 0
    T peek() const; // Return value of the first element without removing it.
};

/* Constructor */
template <typename T>
MyQueue<T> :: MyQueue(){
    count = 0;
    top = down = NULL;
}

/* Method: enqueue
 * Usage: queue.enqueue(value);
 * -----------------------------------------------
 * Adds new element to the end of the queue
 */
template<typename T>
void MyQueue<T> :: enqueue(T newValue){
    Node *newNode = new Node;
    newNode->value = newValue;
    newNode->link = NULL;
    if(top == NULL) { //if queue is empty
        top = down = newNode;
    } else {
        down->link = newNode;
        down  = newNode;
    }
    count++;
}

/* Method: dequeue
 * Usage: value = queue.dequeue();
 * ---------------------------------------------
 * Removes the first elements of the queue and returns it's value
 */
template<typename T>
T MyQueue<T> :: dequeue(){
    if (count == 0){
        std:: cout << "Error: queue is empty!!!" << std:: endl;
        exit(1);
    }
    Node *tmpNode = top;
    top = top->link;
    T tmpValue = tmpNode->value;
    count--;
    delete tmpNode; //prevent memory leaks
    return tmpValue;
}

/* Method: clear
 * Usage: queue.clear();
 * ---------------------------------------------
 * Removes all elements of the queue
 */
template<typename T>
void MyQueue<T> :: clear(){
    for(int i = 0; i < count; i++){
        Node *tmpNode = top;
        top = top->link;
        delete tmpNode; //prevent memory leaks
    }
    count = 0;
}

/* Method: size
 * Usage: int size = queue.size();
 * --------------------------------------------
 * Return current number of the elements of the
 * queue
 */
template<typename T>
int MyQueue<T> :: size() const{
    return count;
}

/* Method: isEmpty
 * Usage: if(queue.isEmpty)...
 * --------------------------------------------
 * Returns true if current number of the elements
 * is 0.
 */
template<typename T>
bool MyQueue<T> :: isEmpty() const{
    return count == 0;
}

/* Method: peek
 * Usage: value = queue.peek();
 * ---------------------------------------------
 * Return value of the first element without removing it.
 */
template<typename T>
T MyQueue<T> :: peek() const{
    return top->value;
}

/* Destructor */
template <typename T>
MyQueue<T> :: ~MyQueue(){
    for(int i = 0; i < count; i++){
        Node *tmpNode = top;
        top = top->link;
        delete tmpNode;
    }
}

#endif // MYQUEUE_H
