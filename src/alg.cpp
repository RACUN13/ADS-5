// Copyright 2021 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

int priorGet(char symbol) {
  switch (symbol) {
  case '(':
    return 0;
  case ')':
    return 1;
  case '+':
    return 2;
  case '-':
    return 2;
  case '*':
    return 3;
  case '/':
    return 3;
  case ' ':
    return -100;
  }
  return -1;
}

std::string infx2pstfx(std::string inf) {
  TStack<char, 100> stack;
  std::string output = "";
  int prior = 0;
  int gratPrior = -1;
  for (auto& op : inf) {
    prior = priorGet(op);
    gratPrior = priorGet(stack.get());
    if (op == '\n') {
      while (priorGet(stack.get()) > 1) {
        output += stack.pop();
        output += " ";
      }
      stack.pop();
    }
    if (prior == -1) {
      output += op;
      output += " ";
    } else if (prior == 0) {
      stack.push(op);
    } else if (prior == 1) {
      while (priorGet(stack.get()) > 0) {
        output += stack.pop();
        output += " ";
      }
      stack.pop();
    } else if (prior > gratPrior || stack.isEmpty()) {
      stack.push(op);
    } else if (prior <= gratPrior && prior > 1) {
      while (priorGet(stack.get()) > 1) {
        output += stack.pop();
        output += " ";
      }
      stack.push(op);
    }
  }
  while (priorGet(stack.get()) > 1) {
    output += stack.pop();
    output += " ";
  }
  std::string out = "";
  for (int i = 0; i < output.length() - 1; ++i) {
    out += output[i];
  }
  return out;
}
int opreoretat(int a, int b, char op) {
  switch (op) {
  case '+':
    return a + b;
  case '-':
    return a - b;
  case '*':
    return a * b;
  case '/':
    return a / b;
  }
  return 0;
}
int eval(std::string pref) {
  TStack<int, 100> stack1;
  int preoret = 0;
  int prior = 0;
  for (auto& op : pref) {
    prior = priorGet(op);
    if (prior == -100) {
      continue;
    }
    if (prior == -1) {
      stack1.push(op - 48);
    } else {
      int peremen = 0;
      while (!(peremen + stack1.isEmpty())) {
        peremen += 1;
        int a = stack1.pop();
        int b = stack1.pop();
        preoret = opreoretat(b, a, op);
        stack1.push(preoret);
      }
    }
  }
  return stack1.pop();
}
