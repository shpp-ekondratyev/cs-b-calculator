 * This program implements a basic expression calculator.
 * Input from cin; output to cout.
 * This program is my realization of the concepts presented in the book
 * of "Programming - Principles and Practice Using C++" by Bjarne Stroustrup.

    The grammar for input is:

    Calculation:
        Statement
        Print
        Quit
        Calculation Statement

    Statement:
        Declaration
        Expression

    Declaration:
        "let" Name "=" Expression

    Print:
        ;

    Quit:
        q

    Expression:
        Term
        Expression + Term
        Expression - Term
    Term:
        Primary
        Term * Primary
        Term / Primary
        Term % Primary
    Primary:
        Number
        Name
        ( Expression )
        - Primary
        + Primary
    Number:
        floating-point-literal
