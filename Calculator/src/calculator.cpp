/*
 * File: Calculator.cpp
 * ---------------------------
 * This program simulates an electronic calculator.
 */

#include <iostream>
#include "console.h"

using namespace std;

/* Function prototypes */

double number(); // Realizes a number, from input stream
double expr(); // Realizes operations of addition and subtraction
double skobki(); // Realizes brackets
double factor(); // Realizes the operations of multiplication and division
void help(); // Displays the HELP

/* Main program */

int main() {

    help();

    do {
        double result = expr();

        cout << " Result : " << result << endl << endl;
        if (result != 0) cout << " Enter expression: ";
    } while (cin.get() != 'Q');

    return 0;
}

/*
* Function: number
* Usage: number();
* ---------------------------------------
* Realizes a number, from input stream.
*/
double number() {
    double res = 0;
    while(true){
        char c = cin.get();
        if (c >= '0' && c <= '9')
            res = res * 10 + c - '0';
        else{
            cin.putback(c);
            return res;
        }
    }
}

/*
* Function: expr()
* Usage: expr();
* ---------------------------------------
* Realizes operations of addition and subtraction.
*/
double expr() {
    double x = factor();
    while (true) {
        char c = cin.get();
        switch (c) {
        case '+':
            x += factor();
            break;
        case '-':
            x -= factor();
            break;
        default:
            cin.putback(c);
            return x;
        }
    }
}

/*
* Function: skobki()
* Usage: skobki();
* ---------------------------------------
* Realizes brackets.
*/
double skobki() {
    char c = cin.get();
    if (c == '(') {
        double x = expr();
        cin.get();
        return x;
    }
    else{
        cin.putback(c);
        return number();
    }
}
/*
* Function: skobki()
* Usage: skobki();
* ---------------------------------------
* Realizes the operations of multiplication and division.
*/
double factor() {
    double x = skobki();
    while (true) {
        char c = cin.get();
        switch (c) {
        case '*':
            x *= skobki();
            break;
        case '/':
            x /= skobki();
            break;
        default:
            cin.putback(c);
            return x;
        }
    }
}

void help() {
    cout << " This is a simple calculator that performs operations"<< endl;
    cout << " of addition, subtraction, multiplication and division."<< endl;
    cout << " As well as operations in brackets."<< endl;
    cout << " To quit the program use command 'Q'."<< endl << endl;
    cout << " Enter expression: ";
}
