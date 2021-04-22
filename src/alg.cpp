// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

int priority(char ch_inf)
{

    switch (ch_inf)
    {
    case '(':return 0;
    case ')':return 1;
    case '+':return 2;
    case '-':return 2;
    case '*':return 3;
    case '/':return 3;
    default:return -1;
    }
}

int calculator(int num1, int num2 , char ch_pst) {
    switch (ch_pst)
    {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case'*': return num1 * num2;
    case '/': return num1 / num2;
    }
}

std::string infx2pstfx(std::string inf)
{
    char top = 0;
    TStack <char> stack1;
    std::string out;

    for (int i = 0; i < inf.length(); i++) {

        char ch = inf[i];
        int prior;
        prior = priority(ch);

        if (prior > -1) {
            if ((prior == 0 || prior > priority(top) ||
                stack1.isEmpty()) && ch != ')') {
                if (stack1.isEmpty())
                    top = ch;
                stack1.push(ch);
            }
            else if (ch == ')') {
                while (stack1.get() != '(') {
                    out.push_back(stack1.get());
                    out.push_back(' ');
                    stack1.pop();
                }
                stack1.pop();
                if (stack1.isEmpty())
                    top = 0;
            }
            else {
                while (!stack1.isEmpty() &&
                    priority(stack1.get()) >= prior) {
                    out.push_back(stack1.get());
                    out.push_back(' ');
                    stack1.pop();
                }
                if (stack1.isEmpty())
                    top = inf[i];
                stack1.push(inf[i]);
            }
        }
        else {
            out.push_back(ch);
            out.push_back(' ');
        }
    }
    while (!stack1.isEmpty()) {
        out.push_back(stack1.get());
        out.push_back(' ');
        stack1.pop();
    }
    out.erase(out.end() - 1, out.end());
    return out;
}


int eval(std::string pst)
{
    TStack <int> stack2;

    for (int i = 0; i < pst.size(); i++)
    {
        char ch = pst[i];
        int prior = priority(ch);

        if (prior == -1)
            stack2.push(ch - 48);
        else
        {
            int num1 = stack2.get();
            stack2.pop();

            int num2 = stack2.get();
            stack2.pop();


            int res = calculator(num2, num1, ch);
            stack2.push(res);
        }

    }
    return stack2.get();
}
