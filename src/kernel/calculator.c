#include "stdio.h"
#include "stdint.h"

// globals
int  operation(int op1,int op2,char sy){
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
    int operators[100];
    
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
        if(flag) operand[++operand_iterator]=temp;
        if(*expr=='(') open_braces++;
        else if (*expr==')'){
            if(open_braces==0){
                printf("Expression is wrong...\n");
                break;
            }
            while(operators[operator_iterator]!='('){
                int op1=operand[operand_iterator--];
                int op2=operand[operand_iterator--];
                char sy=operators[operator_iterator--];

                int ans=operation(op2,op1,sy);

                operand[++operand_iterator]=ans;
            }
            operator_iterator--;
            open_braces--;
            expr++;
            continue;
        }
        else if(*expr=='+' || *expr == '-'){
            while(operator_iterator!=-1 && (operators[operator_iterator]=='*' || operators[operator_iterator]=='/')){
                int op1=operand[operand_iterator--];
                int op2=operand[operand_iterator--];
                char sy=operators[operator_iterator--];

                int ans=operation(op1,op2,sy);

                operand[++operand_iterator]=ans;
            }
        }
        else if(*expr=='*'){
            while(operator_iterator!=-1 && (operators[operator_iterator]=='*' || operators[operator_iterator]=='/')){
                int op1=operand[operand_iterator--];
                int op2=operand[operand_iterator--];
                char sy=operators[operator_iterator--];

                int ans=operation(op2,op1,sy);

                operand[++operand_iterator]=ans;
            }
        }

        operators[++operator_iterator]=*expr;
        expr++;
    }
    
    operator_iterator--;
    while(operator_iterator!=-1){
        
        int op1=operand[operand_iterator--];
        int op2=operand[operand_iterator--];
        char sy=operators[operator_iterator--];

        if(sy=='(') continue;
        
        int ans=operation(op2,op1,sy);
        printf("%d %c %d\n",op1,sy,op2);
        operand[++operand_iterator]=ans;
    }

    return operand[0];

}

int main(){
    char expression[100];
    scanf("%s",expression);
    int ans=infix_to_postfix(expression);
    printf("%d",ans);
}