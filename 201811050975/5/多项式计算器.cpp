#include <iostream>
#define MAX  100
using namespace std;
int level(char p)  //规定运算符优先级
{
    int temp;
    switch (p)
    {
    case '*':
    case '/':temp = 3; break;
    case '+':
    case '-':temp = 2; break;
    case '(':temp = 1; break;
    case '@':temp = -1; break;
    }
    return temp;
}

void  cal(int number[], int* numberTop, char Symbol[], int* SymbolTop) //从字符栈中取出一个字符，从数值栈中取出两个数值进行运算
{
    char operation = Symbol[(*SymbolTop)]; //出符号
    (*SymbolTop)--;
    int value1 = number[(*numberTop)];
    (*numberTop)--;
    int value2 = number[(*numberTop)];
    (*numberTop)--;
    int temp;
    switch (operation)
    {
    case '+':temp = value2 + value1; break;
    case '-':temp = value2 - value1; break;
    case '*':temp = value2 * value1; break;
    case '/':temp = value2 / value1; break;
    }
    (*numberTop)++;     //易错点！！！！！必须加括号！！！！！！
    number[*numberTop] = temp;
}
int fun(char str[])
{
    char  Symbol[MAX];
    int SymbolTop = -1;  //运算符栈
    int numberTop = -1;  //数值栈
    int  number[MAX];
    int  y = 0; //用来计算多位数 
    int i = 0;
    Symbol[++SymbolTop] = '@'; //先把 @ 入到符号栈中,就不用判断栈是否空了！！！这是一个比较聪明的想法
    while (str[i]) {  //先遍历该字符串
        y = 0;
        if (str[i] <= '9' && str[i] >= '0') { //是数字
            while (str[i] <= '9' && str[i] >= '0') {
                y = y * 10 + str[i] - '0';
                i++;
            }
            number[++numberTop] = y; //入栈数值
        }
        else if ((str[i] > '9' || str[i] < '0') && str[i] != '(' && str[i] != ')') {   //不是数字,排除左,右括号的情况
            while (level(str[i]) <= level(Symbol[SymbolTop]))  //让栈中比它大的和等于它的都出栈！！！中缀表达式转后缀表达式的核心
                                                            //从符号栈中出一个符号，从数值栈中出两个数字，计算后压入数值栈
                cal(number, &numberTop, Symbol, &SymbolTop);
            Symbol[++SymbolTop] = str[i];
            i++;
        }
        else if (str[i] == '(') {   //遇见左括号直接入栈
            Symbol[++SymbolTop] = '(';
            i++;
        }
        else if (str[i] == ')') {   //进行运算直到遇到左括号
            while (Symbol[SymbolTop] != '(') {
                cal(number, &numberTop, Symbol, &SymbolTop);
            }
            SymbolTop--; //将左括号覆盖掉
            i++;
        }
        // 将Symbol 栈检查一下，返回number 的栈顶，结束
    }
    while (Symbol[SymbolTop] != '@') {
        cal(number, &numberTop, Symbol, &SymbolTop);
    }
    return number[numberTop];
}
int main(void)
{
    char str[MAX];
    int result;
    gets(str);
    result = fun(str);
    cout<<result<<endl;
    return 0;
}