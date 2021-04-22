// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"

std::int priority(std::char ch_inf)
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
std::int calculator(std::int num1, std::int num2 , std::char ch_pst) {
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
  TStack<std::char> stack1;
    std::string str = "";
    for (std::int i = 0; i < inf.size(); i++)
    {
        std::char ch_inf = inf[i];
        std::int check = priority(ch_inf);

        if (check == -1)
            str.append(string(1, ch_inf));
        else
        {
            if (stack1.isEmpty() || check == 0 || check > priority(stack1.get()))
                stack1.push(ch_inf);
            else
            {
                if (check == 1)
                {
                    while (true)
                    {
                        std::char symbol = stack1.get();
                        stack1.pop();
                        if (symbol != '(')
                            str.append(string(1, symbol));
                    }
                }
                else
                {
                    while (!stack1.isEmpty())
                    {
                        std::char last_element = stack1.get();
                        stack1.pop();

                        if (priority(last_element) >= check)
                            str.append(string(1, last_element));
                    }
                    stack1.push(ch_inf);
                }
            }
        }
    }
    while (!stack1.isEmpty())
    {
        std::char last_element = stack1.get();
        stack1.pop();
        str.append(string(1, last_element));
    }
    return str;
}

std::int eval(std::string pst) 
{
  TStack<std::int> stack2;

    for (std::int i = 0; i < pst.size(); i++)
    {
        std::char ch_pst = pst[i];

        std::int prior = priority(ch_pst);

        if (prior == -1)
            stack2.push(ch_pst - 48);
        else
        {
            std::int num1 = stack2.get();
            stack2.pop();

            std::int num2 = stack2.get();
            stack2.pop();

            std::int res = calculator(num1, num2, ch_pst);
            stack2.push(res);
        }
    }

    return stack2.get();
}
