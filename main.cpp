#include <iostream>
#include<stack>

#include <sstream>
#include<stdlib.h>
using namespace std;

double CalSuffix(string suffix)
{
    double result;
    stack<double> number;
    int i = 0,j;
    int n=0;//判断是否为数字
    string current;
    while(suffix[i]!='#')
    {
        isNum=0;
        if(suffix[i]=='|')
        {
            for(j=i+1;; j++)
            {
                if(suffix[j]=='|')
                    break;
                if(suffix[j]=='#')
                    break;
            }

            //获取|A|之间元素
            for(int k=i+1; k<j; k++)
            {
                current+=suffix[k];
            }

            //判断是否为数值
            for(int k=0; k<current.size(); k++)
            {
                if(current[k]>=48 && current[k]<=57)//数字
                {
                    //strinf转double
                    istringstream iss(current);
                    double num;
                    iss >> num;
                    number.push(num);
                    isNum = 1;
                    break;
                }
            }
            if(isNum!=1){
                double n2 = number.top();
                number.pop();
                double n1 = number.top();
                number.pop();
                if(current=="+"){
                    number.push(n1+n2);
                }
                else if(current=="-"){
                    number.push(n1-n2);
                }
                else if(current=="*"){
                    number.push(n1*n2);
                }
                else if(current=="/"){
                    number.push(n1/n2);
                }
            }
            current="";//清空当前字符串;
        }

        i++;
    }
    if(number.size()!=1)
        cout<<"输入有误"<<endl;
    else
        return number.top();

}


int Priority(char operate)//栈中优先级
{
    switch(operate)
    {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '(':
    case ')':
        return 1;
    default:
        return 0;
    }
}

string Infix2Suffix(string Infix)
{
    stack<char> operate;
    string Suffix = "                               ";//初始化后缀表达式
    char currentOp;
    int negative;
    int i = 0,j = 0;//i为中缀当前指向 j为后缀当前指向
    while(Infix[i]!='\0')
    {
        if(i+1!='\0')
            negative = 0;
        if(Infix[i]>=48 && Infix[i]<=57) //判断数字
        {
            Suffix[j++] = '|';//j是后缀表达索引
            Suffix[j++] =Infix[i];//存储当前数字并指向下一个
            while(Infix[++i]>=48 && Infix[i]<=57) //整数部分
            {
                Suffix[j++] =Infix[i];
            }
            if(Infix[i]=='.') //是小数
            {
                Suffix[j++]='.';
                i+=1;//中缀索引 往后移
                while(Infix[i]>=48 && Infix[i]<=57) //小数部分
                {
                    Suffix[j++] =Infix[i];
                    i+=1;
                }
            }
        }
        else if(Infix[i]=='(')//如果读入(，因为左括号优先级最高，因此放入栈中，但是注意，当左括号放入栈中后，则优先级最低。
        {
            operate.push(Infix[i++]);
        }
        else if(Infix[i]==')')//如果读入），则将栈中运算符取出放入输出字符串，直到取出（为止，注意：（）不输出到输出字符串。
        {

            if(operate.empty())//没有左括号
                cout<<"表达式错误"<<endl;
            else
            {
                currentOp = operate.top();
                while(currentOp!='(')
                {
                    cout<<currentOp<<endl;
                    Suffix[j++]='|';
                    Suffix[j++]=currentOp;
                    operate.pop();
                    if(operate.empty())
                    {
                        cout<<"表达式错误"<<endl;
                        break;
                    }
                    currentOp = operate.top();
                }
                operate.pop();//删除栈中(
                i++;
            }
        }

        else if(Infix[i]=='+'||Infix[i]=='-'||Infix[i]=='/'||Infix[i]=='*')
        {
            //判断负数
            if(Infix[i]=='-')
            {

                if(i==0)//第一个为‘-’时为负号
                    negative = 1;
                else if(Infix[i-1]=='+'||Infix[i-1]=='-'||Infix[i-1]=='/'||Infix[i-1]=='*')//如果前面有操作符则为负号
                    negative = 1;
                if(negative==1)
                {
                    Suffix[j++] = '|';//负号
                    Suffix[j++] = '-';
                    i+=1;
                    if(Infix[i]>=48 && Infix[i]<=57) //判断数字
                    {
                        Suffix[j++] =Infix[i];
                        while(Infix[++i]>=48 && Infix[i]<=57) //整数部分
                        {
                            Suffix[j++] =Infix[i];
                        }
                        if(Infix[i]=='.') //是小数
                        {
                            Suffix[j++]='.';
                            i+=1;
                            while(Infix[i]>=48 && Infix[i]<=57) //小数部分
                            {
                                Suffix[j++] =Infix[i];
                                i+=1;
                            }
                        }
                    }
                    continue;
                }
            }

            //如果读入一般运算符如+-*/，则放入堆栈，但是放入堆栈之前必须要检查栈顶
            if(operate.empty())
            {
                operate.push(Infix[i++]);
            }
            else
            {
                char top = operate.top();//栈顶
                if(Priority(top)<Priority(Infix[i])) //放入的符号优先级低于栈顶
                {
                    operate.push(Infix[i++]);//放入栈顶并指向下一个
                }
                else//如果放入的优先级较低，则需要将栈顶的运算符放入输出字符串。
                {
                    while(Priority(top)>=Priority(Infix[i]))
                    {
                        Suffix[j++]='|';
                        Suffix[j++]=top;
                        operate.pop();
                        if(!operate.empty())
                        {
                            top = operate.top();
                        }
                        else
                            break;
                    }
                    operate.push(Infix[i++]);//放入栈顶并指向下一个
                }
            }

        }
        else
        {
            cout<<"符号错误"<<endl;
            i+=1;
        }
    }

    //顺序读完表达式，如果栈中还有操作符，则弹出，并放入输出字符串。
    while(!operate.empty())
    {
        char to = operate.top();
        Suffix[j++]='|';
        Suffix[j++]=to;
        operate.pop();
    }
    Suffix[j] = '#';//结束符
    cout<<Suffix<<endl;
    return Suffix;
}

int main()
{
    string a;
    cin>>a;
    istringstream iss(a);
    double num;
    iss >> num;
    cout<<num;
    cout<<"后缀为："<<Infix2Suffix(a)<<endl;
    cout<<CalSuffix(Infix2Suffix(a));
    return 0;
}
