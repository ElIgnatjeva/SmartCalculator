#include "calc.h"

int is_unary_plus_or_minus(char* str, int i) {
  int result = ERROR;
  if (str[i] == '-' || str[i] == '+') {
    if (i != 0) {
      if (is_number(str[i + 1]) == OK &&
          (str[i - 1] == '(' || str[i - 1] == '^')) {
        result = OK;
      }
    } else {
      if (is_number(str[i + 1]) == OK) {
        result = OK;
      }
    }
  }
  return result;
}

int is_sign(char c) {
  int res = ERROR;
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
    res = OK;
  }
  return res;
}

int is_number(char c) {
  int res = ERROR;
  int num = custom_atoi(c);
  if (num >= 0 && num <= 9) {
    res = OK;
  }
  return res;
}

double custom_atoi(char c) {
  double res = 0;
  res = res * 10 + c - '0';
  return res;
}

void omit_spaces(const char* str, char* str2, int length, const char* x_value) {
  int i = 0;
  for (int j = 0; j < length; j++) {
    if (str[j] == ' ') {
      continue;
    } else if (str[j] == 'x') {
      int x_value_length = strlen(x_value);
      for (int k = 0; k < x_value_length; k++) {
        str2[i] = x_value[k];
        i++;
      }
    } else {
      str2[i] = str[j];
      i++;
    }
  }
  str2[i] = '\0';
}

int is_function(char* str, int i) {
  int res = ERROR;
  if (((str[i] == 's' || str[i] == 'c' || str[i] == 't') &&
       str[i + 3] == '(') ||
      ((str[i] == 'a' || str[i] == 's') && str[i + 4] == '(') ||
      (str[i] == 'l' && (str[i + 2] == '(' || str[i + 3] == '(')) ||
      (str[i]) == 'm') {
    res = OK;
  }
  return res;
}

int is_mod(char* str, int start) {
  int res = ERROR;
  if (is_number(str[start - 1]) == OK || str[start - 1] == ')') {
    if (str[start + 1] == 'o' && str[start + 2] == 'd' &&
        (is_number(str[start + 3]) == OK || str[start + 3] == '(')) {
      res = OK;
    }
  }
  return res;
}

int is_sin(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 'i' && str[start + 2] == 'n' &&
       str[start + 3] == '(')) {
    res = OK;
  }
  return res;
}

int is_cos(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 'o' && str[start + 2] == 's' &&
       str[start + 3] == '(')) {
    res = OK;
  }
  return res;
}

int is_tan(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 'a' && str[start + 2] == 'n' &&
       str[start + 3] == '(')) {
    res = OK;
  }
  return res;
}

int is_asin(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 's' && str[start + 2] == 'i' &&
       str[start + 3] == 'n' && str[start + 4] == '(')) {
    res = OK;
  }
  return res;
}

int is_acos(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 'c' && str[start + 2] == 'o' &&
       str[start + 3] == 's' && str[start + 4] == '(')) {
    res = OK;
  }
  return res;
}

int is_atan(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 't' && str[start + 2] == 'a' &&
       str[start + 3] == 'n' && str[start + 4] == '(')) {
    res = OK;
  }
  return res;
}

int is_sqrt(char* str, int start) {
  int res = ERROR;
  if (is_sign(str[start - 1]) == OK ||
      (str[start + 1] == 'q' && str[start + 2] == 'r' &&
       str[start + 3] == 't' && str[start + 4] == '(' &&
       is_number(str[start + 5])) == OK) {
    res = OK;
  }
  return res;
}

int is_ln(char* str, int start) {
  int res = ERROR;
  if ((str[start + 1] == 'n' && str[start + 2] == '(') ||
      is_sign(str[start - 1]) == OK) {
    res = OK;
  }
  return res;
}

int is_log(char* str, int start) {
  int res = ERROR;
  if ((str[start + 1] == 'o' && str[start + 2] == 'g' &&
       str[start + 3] == '(') ||
      is_sign(str[start - 1]) == OK) {
    res = OK;
  }
  return res;
}
