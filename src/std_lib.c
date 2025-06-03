#include "std_lib.h"

int div(int a, int b)
{
  int sign = 1;
  int result = 0;
  if (a < 0) {
    a = -a;
    sign *= -1;
  }
  if (b < 0) {
    b = -b;
    sign *= -1;
  }
  while (a >= b) {
    a -= b;
    result++;
  }
  return result * sign;
}

int mod(int a, int b)
{
  int sign = 1;
  if (a < 0) {
    a = -a;
    sign = -1;
  }
  if (b < 0) {
    b = -b;
  }
  while (a >= b) {
    a -= b;
  }
  return a * sign;
}


bool strcmp(char *str1, char *str2) {
  int i = 0;
  while (str1[i] != '\0' && str2[i] != '\0') {
    if (str1[i] != str2[i]) return false;
    i++;
  }
  return str1[i] == '\0' && str2[i] == '\0';
}

void strcpy(char *dst, char *src)
{
  int i = 0;
  while (src[i] != '\0') {
    dst[i] = src[i];
    i++;
  }
  dst[i] = '\0'; // Akhiri string
}

void clear(char *buf, unsigned int length) {
  int i;
  for (i = 0; i < length; i++) {
    buf[i] = '\0';
  }
}


void atoi(char *str, int *num)
{
  int i = 0;
  int sign = 1;
  *num = 0;

  // Cek tanda negatif
  if (str[i] == '-') {
    sign = -1;
    i++;
  }

  while (str[i] != '\0') {
    *num = (*num * 10) + (str[i] - '0');
    i++;
  }

  *num *= sign;
}


void itoa(int num, char *str)
{
  int i = 0, sign = 0;
  char temp[64];
  int isNegative = 0;
   int j;

  if (num == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }

  if (num < 0) {
    isNegative = 1;
    num = -num;
  }

  while (num != 0) {
    temp[i++] = mod(num, 10) + '0';
    num = div(num, 10);
  }

  if (isNegative) {
    temp[i++] = '-';
  }

  temp[i] = '\0';
 
  for (j = 0; j < i; j++) {
    str[j] = temp[i - j - 1];
  }
  str[i] = '\0';
}




