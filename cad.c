#define SIZE 50           
#include <ctype.h>
#include<stdio.h>
#include<string.h>
char s[SIZE];
int top=-1;        
char stack[SIZE];

char type(char elem)
{
  if (elem =='*'||elem=='+'||elem=='!')
    return(operator);
  else if(elem =='('||elem==')')
    return(bracket);
  else 
    return(operand);
 
}

 void push(char elem)
{                        
    s[++top]=elem;
}
 
char pop()
{                       
    return(s[top--]);
}
 
int pr(char elem)
{                  
    switch(elem)
    {
        case '#': return 0;
        case '(': return 1;
        case '+': return 2;
        case '*': return 3;
        case '!': return 4;
    }
}
 
int main(void)
{                          
    char infx[50],pofx[50],ch,elem;
    int i=0,k=0;
    printf(" Read the Infix Expression \n ");
    scanf("%s",infx);
    push('#');
    while( (ch=infx[i++]) != '\0')
    {
        if( ch == '(') push(ch);
        else if(isalnum(ch)) pofx[k++]=ch;
            else if( ch == ')')
                {
                    while( s[top] != '(')
                        pofx[k++]=pop();
                    elem=pop();  
                }
                else
                {       
                    while( pr(s[top]) >= pr(ch) )
                        pofx[k++]=pop();
                    push(ch);
                }
    }
    while( s[top] != '#')      
        pofx[k++]=pop();
    pofx[k]='\0';          
    printf("\n\nGiven Infix Expn: %s  Postfix Expn: %s\n",infx,pofx);

    for(int i=0;i<strenl(pofx);i++)
   {
      
     if(type(pofx[i]== operand)
        push(pofx[i]);

     else if(posstfix[i]=='*')
        pop();
      
   }

   







}
