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
    TStack<char> stack1;

    std::string str = "";

    for (int i = 0; i < inf.size(); i++)
    {
        char ch_inf = inf[i];
        int check = priority(ch_inf);

        if (check == -1)
            str.append(std::string(1, ch_inf));
        else
        {
            if (stack1.isEmpty() || check == 0 || check > priority(stack1.get()))
                stack1.push(ch_inf);
            else
            {
                if (check == 1)
                {
                    while (true) {
                        char symbol = stack1.get();
                        stack1.pop();
                        if (symbol != '(')
                            str.append(std::string(1, symbol));
                    }
                }
                else
                {
                    while (!stack1.isEmpty())
                    {
                        char last_element = stack1.get();
                        stack1.pop();

                        if (priority(last_element) >= check)
                            str.append(std::string(1, last_element));
                    }
                    stack1.push(ch_inf);
                }
            }
        }
    }
    while (!stack1.isEmpty())
    {
        char last_element = stack1.get();
        stack1.pop();
        str.append(std::string(1, last_element));
    }
    return str;
}

int eval(std::string pst) {
    TStack<int> stack2;

    for (int i = 0; i < pst.size(); i++) {

        char ch_pst = pst[i];

        int prior = priority(ch_pst);

        if (prior == -1)
            stack2.push(ch_pst - 48);
        else
        {
            int num1 = stack2.get();
            stack2.pop();

            int num2 = stack2.get();
            stack2.pop();

            int res = calculator(num1, num2, ch_pst);
            stack2.push(res);
        }
    }

    return stack2.get();
}
