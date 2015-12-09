/*
 * File: Calculator.cpp
 * ---------------------------
 * This program simulates an electronic calculator.
 * Using only IOStream.
 * Operations: addition, subtraction, multiplication, division, operations in brackets.
 *
 */

#include <iostream>
#include "console.h"

using namespace std;

/* Function prototypes */

double number(); // Realizes a number, from input stream
double expression(); // Realizes operations of addition and subtraction
double brackets(); // Realizes brackets
double term(); // Realizes the operations of multiplication and division
void help(); // Displays the HELP

/* Main program */

int main() {

    help();

    do {
        double result = expression();

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
* Function: expression()
* Usage: expression();
* ---------------------------------------
* Realizes operations of addition and subtraction.
*/
double expression() {
    double x = term();
    while (true) {
        char c = cin.get();
        switch (c) {
        case '+':
            x += term();
            break;
        case '-':
            x -= term();
            break;
        default:
            cin.putback(c);
            return x;
        }
    }
}

/*
* Function: brackets()
* Usage: brackets();
* ---------------------------------------
* Realizes brackets.
*/
double brackets() {
    char c = cin.get();
    if (c == '(') {
        double x = expression();
        cin.get();
        return x;
    }
    else{
        cin.putback(c);
        return number();
    }
}
/*
* Function: brackets()
* Usage: brackets();
* ---------------------------------------
* Realizes the operations of multiplication and division.
*/
double term() {
    double x = brackets();
    while (true) {
        char c = cin.get();
        switch (c) {
        case '*':
            x *= brackets();
            break;
        case '/':
            x /= brackets();
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
