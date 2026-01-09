#include "src/kernel/stdio/stdint.h"
#include "src/kernel/stdio/stdio.h"

int operation(int op1,int op2,char sy){
    int ans;
    if(sy=='+'){
        ans=op1+op2;
    }
    else if(sy=='-'){
        ans=op1-op2;
    }
    else if(sy=='*'){
        ans=op1*op2;
    }
    else{
        ans=op1/op2;
    }
    return ans;
}

int infix_to_postfix(char *expression){
    int operand[100];
    char operators[100];

    int operand_iterator=-1;
    int operator_iterator=-1;

    int open_braces=0;
    char *expr=expression;

    while(*expr){
        int temp=0;
        int flag=0;

        while(*expr>='0' && *expr<='9'){
            temp=temp*10+(*expr-'0');
            expr++;
            flag=1;
        }

        if(flag){
            operand[++operand_iterator]=temp;
            continue;
        }

        if(*expr=='('){
            operators[++operator_iterator]=*expr;
            open_braces++;
        }
        else if(*expr==')'){
            if(open_braces==0){
                printf("Expression is wrong...\n");
                return 0;
            }
            while(operator_iterator!=-1 && operators[operator_iterator]!='('){
                int op2=operand[operand_iterator--];
                int op1=operand[operand_iterator--];
                char sy=operators[operator_iterator--];
                operand[++operand_iterator]=operation(op1,op2,sy);
            }
            operator_iterator--;
            open_braces--;
        }
        else if(*expr=='+' || *expr=='-'){
            while(operator_iterator!=-1 &&
                 (operators[operator_iterator]=='+' ||
                  operators[operator_iterator]=='-' ||
                  operators[operator_iterator]=='*' ||
                  operators[operator_iterator]=='/')){
                int op2=operand[operand_iterator--];
                int op1=operand[operand_iterator--];
                char sy=operators[operator_iterator--];
                operand[++operand_iterator]=operation(op1,op2,sy);
            }
            operators[++operator_iterator]=*expr;
        }
        else if(*expr=='*' || *expr=='/'){
            while(operator_iterator!=-1 &&
                 (operators[operator_iterator]=='*' ||
                  operators[operator_iterator]=='/')){
                int op2=operand[operand_iterator--];
                int op1=operand[operand_iterator--];
                char sy=operators[operator_iterator--];
                operand[++operand_iterator]=operation(op1,op2,sy);
            }
            operators[++operator_iterator]=*expr;
        }

        expr++;
    }

    while(operator_iterator!=-1){
        char sy=operators[operator_iterator--];
        if(sy=='(') continue;
        int op2=operand[operand_iterator--];
        int op1=operand[operand_iterator--];
        operand[++operand_iterator]=operation(op1,op2,sy);
    }

    return operand[0];
}

int main(){
    char expression[100];
    scanf("%s",expression);
    int ans=infix_to_postfix(expression);
    printf("%d",ans);
}