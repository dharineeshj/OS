#include "src/kernel/stdio/stdint.h"
#include "src/kernel/stdio/stdio.h"

int operation(int op1, int op2, char sy) {
    switch (sy) {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;  // assume op2 != 0
    }
    return 0;
}

int infix_to_postfix(char *expression) {
    int operand[100];
    char operators[100];

    int operand_iterator = -1;
    int operator_iterator = -1;

    int open_braces = 0;
    char *expr = expression;

    int temp = 0;
    int flag = 0;

    int op1, op2;
    char sy;

    while (*expr) {

        /* Parse multi-digit numbers */
        if (*expr >= '0' && *expr <= '9') {
            temp = 0;
            while (*expr >= '0' && *expr <= '9') {
                temp = temp * 10 + (*expr - '0');
                expr++;
            }
            operand[++operand_iterator] = temp;
            continue;  // important
        }

        if (*expr == '(') {
            operators[++operator_iterator] = *expr;
            open_braces++;
        }
        else if (*expr == ')') {
            if (open_braces == 0) {
                printf("Expression is wrong...\n");
                return 0;
            }
            while (operator_iterator != -1 && operators[operator_iterator] != '(') {
                op2 = operand[operand_iterator--];
                op1 = operand[operand_iterator--];
                sy = operators[operator_iterator--];
                operand[++operand_iterator] = operation(op1, op2, sy);
            }
            operator_iterator--;  // pop '('
            open_braces--;
        }
        else if (*expr == '+' || *expr == '-') {
            while (operator_iterator != -1 &&
                   (operators[operator_iterator] == '+' ||
                    operators[operator_iterator] == '-' ||
                    operators[operator_iterator] == '*' ||
                    operators[operator_iterator] == '/')) {

                op2 = operand[operand_iterator--];
                op1 = operand[operand_iterator--];
                sy = operators[operator_iterator--];
                operand[++operand_iterator] = operation(op1, op2, sy);
            }
            operators[++operator_iterator] = *expr;
        }
        else if (*expr == '*' || *expr == '/') {
            while (operator_iterator != -1 &&
                   (operators[operator_iterator] == '*' ||
                    operators[operator_iterator] == '/')) {

                op2 = operand[operand_iterator--];
                op1 = operand[operand_iterator--];
                sy = operators[operator_iterator--];
                operand[++operand_iterator] = operation(op1, op2, sy);
            }
            operators[++operator_iterator] = *expr;
        }

        expr++;
    }

    /* Final evaluation */
    while (operator_iterator != -1) {
        sy = operators[operator_iterator--];
        if (sy == '(') continue;
        op2 = operand[operand_iterator--];
        op1 = operand[operand_iterator--];
        operand[++operand_iterator] = operation(op1, op2, sy);
    }

    return operand[0];
}

void cals() {
    char expression[100];
    int ans;
    scanf("%s",expression);
    ans=infix_to_postfix(expression);
    printf("%d",ans);
}