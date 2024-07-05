// Evaluation of arithmetic expressions and assignment statement.
// date: 2022/12/12

#include <iostream>
#include <cmath>
using namespace std;

class Stack
{
private:
    double num[100];
public:
    int top = -1;
    void push(double x){
        num[++top] = x;
    }
    double pop(){
        return (num[top--]);
    }
};

double calculate(Stack stack){
    double sum = 0;
    for (int x = stack.top; x > -1; x--)
        sum += stack.pop();
    return sum;
}

double input(char x,double value){
    Stack stack;
    double num = 0;
    char opt = '+';
    bool decimal = false;
    int point = 0;
    while (cin.peek()){

        if (cin.peek()==' '){
            cin.get();
            continue;
        }

        char c = cin.get();

        if (isdigit(c)){
            num = 10 * num + (c - '0');
            if (decimal)
                point++;
        }
        else{
            num *= pow(0.1, point);
            decimal = false;
            point = 0;
        }

        if (c == '(')
            num = num? num*input(x,value) :input(x,value);

        else if(c==x)
                num = num? num*value :value;

        else if (c == '.'){
            decimal = true;
        }

        else if ((!isdigit(c) || c == '\n' || c == ')')){
            switch (opt){
            case '+':
                stack.push(num);
                break;
            case '-':
                stack.push(-num);
                break;
            case '*':
                stack.push(stack.pop() * num);
                break;
            case '/':
                stack.push(stack.pop() / num);
                break;
            }
            
            opt = c;
            num = 0;
            if (c == '\n' || c == ')')
                break;
        }
    }
    return (calculate(stack));
}

int main(){
    if(!isalpha(cin.peek()))
        cout << "ans = " << input(' ',0) << endl;
    else{
        char x = cin.get();
        while (cin.peek()==' '|| cin.peek()=='=')
            cin.get();
        double value = input(' ',0);

        char y = cin.get();
        while (cin.peek()==' '|| cin.peek()=='=')
            cin.get();
        cout <<endl<< x <<" = "<<value<<endl
             << y <<" = "<<input(x,value)<<endl;
     }
}