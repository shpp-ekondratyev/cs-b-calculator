/*
 * File: CalculatorColl.cpp
 * ---------------------------------------------------------------------------
 * This program simulates an electronic calculator.
 * Operations: addition, subtraction, multiplication,
 * division, involution and operations in brackets.
 */

#include <iostream>
#include <string>
#include <cmath>

#include "console.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"

#include "myqueue.h"
#include "mystack.h"

using namespace std;

/* Function prototypes */
void intro();
bool checkParenthesis(string expression);
bool isOperator(string ch);
MyQueue<string> toPostfix(string expression);
double calculate(MyQueue<string> &postfixExpr);
int getPriority(char chOperator);
double counting(double  firstOperand, double secondOperand, string sOperator);

/* Main programm */
int main() {
    intro();
    while (true) {
        string expression = toLowerCase(getLine("Type the expression: "));
        if (expression == "q" || expression == "quit") break;
        else if (checkParenthesis(expression)){
            MyQueue<string> postfixExpr = toPostfix(expression);
            double result = calculate(postfixExpr);
            cout << "Result: " << result << endl << endl;
        } else {
            cout << "You have entered the incorrect expression," << endl;
            cout << "check the parenthesis." << endl << endl;
        }
    }
    return 0;
}

/**
 * Function:  intro
 * Usage: intro();
 * ---------------------------------------------------------------------------
 * This feature displays a message about the functionality of the program.
 */
void intro(){
    cout << "This program simulates an electronic calculator." << endl;
    cout << "Operations: addition, subtraction, multiplication," << endl;
    cout << "division, involution and operations in brackets." << endl << endl;
}

/**
 * Function:  checkParenthesis
 * Usage: checkParenthesis(expression);
 * ---------------------------------------------------------------------------
 * This function checks correspondence between the opening and closing brackets,
 * but also returns the error in case of premature closing parentheses.
 */
bool checkParenthesis(string expression){
    bool result = true;
    MyStack<char> parenthesis;
    for(char ch: expression){
        if(ch == '('){
            parenthesis.push(ch);
        }
        if (ch == ')' && !parenthesis.isEmpty()){
            parenthesis.pop();
        } else if (ch == ')' && parenthesis.isEmpty()) {
            result = false;
        }
    }
    if (!parenthesis.isEmpty()){
        result = false;
    }
    return result;
}

/**
 * Function: toPostfix
 * Usage: toPostfix(string expression);
 * ---------------------------------------------------------------------------
 * This function transforms the original expression from infix notation to postfix.
 */
MyQueue<string> toPostfix(string expression){
    MyQueue<string> postfixExpr;
    MyStack<string> operators;
    TokenScanner scanner(expression);
    scanner.addOperator("+");
    scanner.addOperator("-");
    scanner.addOperator("*");
    scanner.addOperator("/");
    scanner.addOperator("^");
    scanner.scanNumbers();
    scanner.ignoreWhitespace();
    bool unaryMinus = false;
    string prevToken = "";
    while(scanner.hasMoreTokens()){
        string token = scanner.nextToken();
        if (isdigit(token[0]) && unaryMinus){
            string sTemp = "-" + token;
            postfixExpr.enqueue(sTemp);
            unaryMinus = false;
        } else if (isdigit(token[0])){
            postfixExpr.enqueue(token);
        } else if ((token == "-" && prevToken == "") || (token == "-" && prevToken == "(")){
            unaryMinus = true;
        } else if (token == "("){
            operators.push(token);
        } else if (token == ")"){
            while (operators.top() != "(" ){
                postfixExpr.enqueue(operators.pop());
            }
            operators.pop();
        } else if (isOperator(token)){
            while (operators.size() > 0 && getPriority(operators.top()[0]) >= getPriority(token[0])){
                postfixExpr.enqueue(operators.pop());
            }
            operators.push(token);
        }
        prevToken = token;
    }
    while (!operators.isEmpty()){
        postfixExpr.enqueue(operators.pop());
    }
    return postfixExpr;
}

/**
 * Function:  calculate
 * Usage: calculate(MyQueue<string> &postfixExpr);
 * ---------------------------------------------------------------------------
 * This function receives the expression in the postfix notation and calculates it's value.
 */
double calculate(MyQueue<string> &postfixExpr){
    MyStack<double> numbers;
    while (!postfixExpr.isEmpty()) {
        string sTemp = postfixExpr.dequeue(); // remove and return first element from queue
        if (sTemp.length() > 1 && sTemp[0] == '-'){
            numbers.push(-stod(sTemp.substr(1))); // convert to double and save unary minus
        } else if (sTemp.length() > 1 && isdigit(sTemp[0])){
            numbers.push(stod(sTemp)); // convert to double
        } else if (isdigit(sTemp[0])){
            numbers.push(stod(sTemp));
        } else { // this mean that sTemp is operator
            double secondOperand = numbers.pop();
            double firstOperand = numbers.pop();
            numbers.push(counting(firstOperand, secondOperand, sTemp));
        }
    }
    return numbers.pop();
}

/**
 * Function: isOperator
 * Usage: isOperator(string ch);
 * ---------------------------------------------------------------------------
 * Checks whether the incoming character is operator.
 */
bool isOperator(string ch) {
    return (ch == "+" || ch == "-" || ch == "/" || ch == "*" || ch == "^");
}

/**
 * Function: getPriority
 * Usage: getPriority(char chOperator);
 * ---------------------------------------------------------------------------
 * This function returns the priority of the operator.
 */
int getPriority(char chOperator){
    switch (chOperator) {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return 0;
}

/**
 * Function: counting
 * Usage: counting(firstOperand, secondOperand, sOperator);
 * ---------------------------------------------------------------------------
 * This function executes the recived operation between two received operands.
 */
double counting(double firstOperand, double secondOperand, string sOperator){
    double result = 0;

    if (sOperator == "+"){
        result = firstOperand + secondOperand;
    } else if (sOperator == "-") {
        result = firstOperand - secondOperand;
    } else if (sOperator == "*") {
        result = firstOperand * secondOperand;
    } else if (sOperator == "/") {
        result = firstOperand / secondOperand;
    } else if (sOperator == "^") {
        result = pow(firstOperand, secondOperand);
    }
    return result;
}
