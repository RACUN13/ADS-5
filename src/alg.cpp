// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int prior(char ch) {
    if (ch == ')' || ch == '(')
        return 0;
    if (ch == '+' || ch == '-')
        return 1;
    if (ch == '*' || ch == '/')
        return 2;
    else
        return 0;
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack1;
  std::string s = "";
  for (int i = 0; i < inf.length(); i++) {
    if ((inf[i] >= '0') && (inf[i] <= '9')) {
      s += inf[i];
      s += " ";
    } else if (inf[i] == '(') {
      stack1.push(inf[i]);
    } else if (isOperand(inf[i])) {
        while (!stack1.isEmpty() &&
               getPrior(inf[i]) <= getPrior(stack1.getValue())) {
            s += stack1.getValue();
            s += " ";
            stack1.pop();
        }
        stack1.push(inf[i]);
    } else if (inf[i] == ')') {
        while (!stack1.isEmpty() && stack1.getValue() != '(') {
        s += stack1.getValue();
        s += " ";
        stack1.pop();
      }
      stack1.pop();
    }
  }
  while (!stack1.isEmpty()) {
    s += stack1.getValue();
    s += " ";
    stack1.pop();
  }
  s.pop_back();
  return s;
}

int eval(std::string pref) {
  TStack<int, 100> stack2;
  int k, l, g;
  for (int i = 0; i < pref.length(); i++) {
    if (pref[i] == ' ') {
      continue;
    } else if (pref[i] >= '0' && pref[i] <= '9') {
      k = pref[i] - '0';
      stack2.push(k);
    } else if (pref[i] == '+' || pref[i] == '-' ||
          pref[i] == '*' || pref[i] == '/') {
      l = stack2.getValue();
      stack2.pop();
      g = stack2.getValue();
      stack2.pop();
      if (pref[i] == '+') stack2.push(g + l);
      else if (pref[i] == '-')
        stack2.push(g - l);
      else if (pref[i] == '*')
        stack2.push(g * l);
      else if (pref[i] == '/')
        stack2.push(g / l);
    }
  }
  return stack2.getValue();
}
