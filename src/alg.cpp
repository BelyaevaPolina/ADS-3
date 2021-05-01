// Copyright 2021 NNTU-CS
#include <string>
#include "tstack.h"
int priority(char ch_inf) {
    switch (ch_inf) {
    case '(': return 0;
    case ')': return 1;
    case '+': return 2;
    case '-': return 2;
    case '*': return 3;
    case '/': return 3;
    default: return -1;
    }
}
int calculator(int num1, int num2 , char ch_pst) {
    switch (ch_pst) {
    case '+': return num1 + num2;
    case '-': return num1 - num2;
    case'*': return num1 * num2;
    case '/': return num1 / num2;
    }
}
std::string infx2pstfx(std::string inf) {
    char top = 0;
    TStack <char> stack1;
    std::string str_pst;

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
            } else if (ch == ')') {
                while (stack1.get() != '(') {
                    str_pst.push_back(stack1.get());
                    str_pst.push_back(' ');
                    stack1.pop();
                }
                stack1.pop();
                if (stack1.isEmpty())
                    top = 0;
            } else {
                while (!stack1.isEmpty() &&
                    priority(stack1.get()) >= prior) {
                    str_pst.push_back(stack1.get());
                    str_pst.push_back(' ');
                    stack1.pop();
                }
                if (stack1.isEmpty())
                    top = inf[i];
                stack1.push(inf[i]);
            }
        } else {
            str_pst.push_back(ch);
            str_pst.push_back(' ');
        }
    }
    while (!stack1.isEmpty()) {
        str_pst.push_back(stack1.get());
        str_pst.push_back(' ');
        stack1.pop();
    }
    str_pst.erase(str_pst.end() - 1, str_pst.end());
    return str_pst;
}
int eval(std::string pst) {
    TStack <int> stack2;
    int i = 0, res = 0;
    char ch = pst[i];
    while (ch) {
        if (ch >= '0' && ch <= '9') {
            int num = 0;
            int dec = 1;
            while (ch != ' ') {
                num += (ch - 48) * dec;
                dec *= 10;
                ch = pst[++i];
            }
            stack2.push(num);
        } else {
            char ch_pst = ch;
            i++;
            int num2 = stack2.get();
            stack2.pop();
            int num1 = stack2.get();
            stack2.pop();
            int result = calculator(num1, num2, ch_pst);
            stack2.push(res);
        }
        if (i < pst.size())
            ch = pst[++i];
        else
            ch = 0;
    }
    res = stack2.get();
    stack2.pop();
    return res;
}
