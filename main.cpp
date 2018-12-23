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
    int n=0;//�ж��Ƿ�Ϊ����
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

            //��ȡ|A|֮��Ԫ��
            for(int k=i+1; k<j; k++)
            {
                current+=suffix[k];
            }

            //�ж��Ƿ�Ϊ��ֵ
            for(int k=0; k<current.size(); k++)
            {
                if(current[k]>=48 && current[k]<=57)//����
                {
                    //strinfתdouble
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
            current="";//��յ�ǰ�ַ���;
        }

        i++;
    }
    if(number.size()!=1)
        cout<<"��������"<<endl;
    else
        return number.top();

}


int Priority(char operate)//ջ�����ȼ�
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
    string Suffix = "                               ";//��ʼ����׺���ʽ
    char currentOp;
    int negative;
    int i = 0,j = 0;//iΪ��׺��ǰָ�� jΪ��׺��ǰָ��
    while(Infix[i]!='\0')
    {
        if(i+1!='\0')
            negative = 0;
        if(Infix[i]>=48 && Infix[i]<=57) //�ж�����
        {
            Suffix[j++] = '|';//j�Ǻ�׺�������
            Suffix[j++] =Infix[i];//�洢��ǰ���ֲ�ָ����һ��
            while(Infix[++i]>=48 && Infix[i]<=57) //��������
            {
                Suffix[j++] =Infix[i];
            }
            if(Infix[i]=='.') //��С��
            {
                Suffix[j++]='.';
                i+=1;//��׺���� ������
                while(Infix[i]>=48 && Infix[i]<=57) //С������
                {
                    Suffix[j++] =Infix[i];
                    i+=1;
                }
            }
        }
        else if(Infix[i]=='(')//�������(����Ϊ���������ȼ���ߣ���˷���ջ�У�����ע�⣬�������ŷ���ջ�к������ȼ���͡�
        {
            operate.push(Infix[i++]);
        }
        else if(Infix[i]==')')//������룩����ջ�������ȡ����������ַ�����ֱ��ȡ����Ϊֹ��ע�⣺���������������ַ�����
        {

            if(operate.empty())//û��������
                cout<<"���ʽ����"<<endl;
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
                        cout<<"���ʽ����"<<endl;
                        break;
                    }
                    currentOp = operate.top();
                }
                operate.pop();//ɾ��ջ��(
                i++;
            }
        }

        else if(Infix[i]=='+'||Infix[i]=='-'||Infix[i]=='/'||Infix[i]=='*')
        {
            //�жϸ���
            if(Infix[i]=='-')
            {

                if(i==0)//��һ��Ϊ��-��ʱΪ����
                    negative = 1;
                else if(Infix[i-1]=='+'||Infix[i-1]=='-'||Infix[i-1]=='/'||Infix[i-1]=='*')//���ǰ���в�������Ϊ����
                    negative = 1;
                if(negative==1)
                {
                    Suffix[j++] = '|';//����
                    Suffix[j++] = '-';
                    i+=1;
                    if(Infix[i]>=48 && Infix[i]<=57) //�ж�����
                    {
                        Suffix[j++] =Infix[i];
                        while(Infix[++i]>=48 && Infix[i]<=57) //��������
                        {
                            Suffix[j++] =Infix[i];
                        }
                        if(Infix[i]=='.') //��С��
                        {
                            Suffix[j++]='.';
                            i+=1;
                            while(Infix[i]>=48 && Infix[i]<=57) //С������
                            {
                                Suffix[j++] =Infix[i];
                                i+=1;
                            }
                        }
                    }
                    continue;
                }
            }

            //�������һ���������+-*/��������ջ�����Ƿ����ջ֮ǰ����Ҫ���ջ��
            if(operate.empty())
            {
                operate.push(Infix[i++]);
            }
            else
            {
                char top = operate.top();//ջ��
                if(Priority(top)<Priority(Infix[i])) //����ķ������ȼ�����ջ��
                {
                    operate.push(Infix[i++]);//����ջ����ָ����һ��
                }
                else//�����������ȼ��ϵͣ�����Ҫ��ջ�����������������ַ�����
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
                    operate.push(Infix[i++]);//����ջ����ָ����һ��
                }
            }

        }
        else
        {
            cout<<"���Ŵ���"<<endl;
            i+=1;
        }
    }

    //˳�������ʽ�����ջ�л��в��������򵯳�������������ַ�����
    while(!operate.empty())
    {
        char to = operate.top();
        Suffix[j++]='|';
        Suffix[j++]=to;
        operate.pop();
    }
    Suffix[j] = '#';//������
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
    cout<<"��׺Ϊ��"<<Infix2Suffix(a)<<endl;
    cout<<CalSuffix(Infix2Suffix(a));
    return 0;
}
