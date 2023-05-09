// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"
int prior(char sim) {
    switch (sim) {
    case '(':
        return 0;
        break;
    case ')':
        return 1;
        break;
    case '+':
        return 2;
        break;
    case '-':
        return 2;
        break;
    case '*':
        return 3;
        break;
    case '/':
        return 3;
        break;
    default:
        return 0;
        break;
    }
}
std::string infx2pstfx(std::string inf) {
TStack<char, 100> opStack;
    std::string result = "";
    for (int i = 0; i < inf.size(); i++) {
        if (isdigit(inf[i]) != 0) {
            result += inf[i];
        } else if (prior(inf[i]) == 2 || prior(inf[i]) == 3) {
            result += " ";
            if (opStack.isEmpty() || prior(opStack.get()) == 0 ||
                prior(inf[i]) > prior(opStack.get())) {
                opStack.push(inf[i]);
            } else if (prior(inf[i]) <= prior(opStack.get())) {
                while (prior(inf[i]) <= prior(opStack.get())) {
                    result += opStack.pop();
                    result += " ";
                }
                opStack.push(inf[i]);
            }
        } else if (prior(inf[i]) == 0) {
            opStack.push(inf[i]);
        } else if (prior(inf[i]) == 1) {
            while (prior(opStack.get()) != 0) {
                result += " ";
                result += opStack.pop();
            }
            opStack.pop();
        }
    }
    while (!opStack.isEmpty()) {
        result += " ";
        result += opStack.pop();
    }
    return std::string(result);
}
int calculate(const int a, const int b, const char oper) {
    switch (oper) {
        case '+':
            return b + a;
        case '-':
            return b - a;
        case '*':
            return a * b;
        case '/':
            return b / a;
        default:
            break;
    }
    return 0;
}

int eval(std::string pref) {
TStack<int, 100> opStack2;
    for (int i = 0; i < pref.size(); i++) {
        if (isdigit(pref[i]) != 0) {
            int num = pref[i] - '0';
            opStack2.push(num);
        } else if (prior(pref[i]) == 2 || prior(pref[i]) == 3) {
            int a = opStack2.pop();
            int b = opStack2.pop();
            opStack2.push(calculate(a, b, pref[i]));
        }
    }
    return opStack2.pop();
}
