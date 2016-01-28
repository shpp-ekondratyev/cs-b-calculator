/* File: mystack.h
 * -----------------------------------
 * This file exports a simple implementation
 * of Stack class based on the dynamic array.
 */

#ifndef MYSTACK_H
#define MYSTACK_H

#include <iostream>

/* Class MyStack<T>
 * --------------------------------
 * This class implements a stack of a specified value type.
 */
template <typename T>
class MyStack {
private:
    static const int START_SIZE = 10;
    T *array; //  Dynamic array for storing elements
    int currentSize; //  Current size of the dynamic array
    int count; // Current number of the element in array
    void extendArray(); // Increases dynamyc arra in two times
public:
    MyStack(); // Initializes a new empty stack
    virtual ~MyStack(); // Frees memory allocated for array in the heap.
    void push(T value); // Pushes the specified value on the stack
    T pop(); // Removes top element of the stack and returns it's value
    void clear(); // Removes all elements of the stack.
    bool isEmpty() const; // Returns true if stack is empty
    T top() const; // Returns value of the top element of the stack without removing it.
    int size() const; // Returns current number of the element in the stack
};

/* Constructor */
template <typename T>
MyStack<T>::MyStack(){
    array = new T[START_SIZE];
    currentSize = START_SIZE;
    count = 0;
}

/* Destructor */
template <typename T>
MyStack<T>::~MyStack(){
    delete[] array;
}

/* Method: push
 * Usage: stack.push(value);
 * -----------------------------------------------------
 * Pushes the specified value on the stack
 */
template <typename T>
void MyStack<T>::push(T value){
    if (count == currentSize){ //check for a free space for new element
        extendArray();
    }
    array[count] = value;
    count++;
}

/* Method: pop
 * Usage: stack.pop();
 * ----------------------------------------------------
 * Removes top element of the stack and returns it's value
 */
template <typename T>
T MyStack<T>::pop(){
    if (isEmpty()){
        std:: cout << "Error: Stack is empty!!!" << std::endl;
        exit(1);
    }
    count--;
    return array[count];

}

/* Method: clear
 * Usage: stack.clear();
 * -----------------------------------------------------
 * Removes all elements of the stack.
 */
template <typename T>
void MyStack<T>::clear(){
    count = 0;
}

/* Method: isEmpty
 * Usage: stack.isEmpty();
 * -----------------------------------------------------
 * Returns true if stack is empty
 */
template <typename T>
bool MyStack<T>::isEmpty() const {
    return count == 0;
}

/* Method: top
 * Usage: stack.top();
 * -----------------------------------------------------
 * Returns value of the top element of the stack
 * without removing it.
 */
template <typename T>
T MyStack<T>::top() const {
    if (isEmpty()){
        std:: cout << "Error: Stack is empty!!!" << std::endl;
        exit(1);
    }
    return array[count-1];
}

/* Method: size
 * Usage: stack.size();
 * -----------------------------------------------------
 * Returns current number of the element in the stack
 */
template <typename T>
int MyStack<T>::size() const{
    return count;
}

/* Method: extendArray
 * Usage: extendArray();
 * ------------------------------------------------
 * Increases dynamyc arra in two times
 */
template <typename T>
void MyStack<T>::extendArray(){
    T *oldArray = array;
    currentSize *= 2;
    array = new T[currentSize];

    for (int i = 0; i < count; i++){
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}

#endif // MYSTACK_H
