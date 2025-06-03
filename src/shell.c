#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char user[64] = "user";
char hostname[64] = "";
char username[128]; 
int currentColor = 0x07;

void updateUsername() {
  int i = 0, j = 0;
  clear(username, 128);

  while (user[i] != '\0') {
    username[i] = user[i];
    i++;
  }

  while (hostname[j] != '\0') {
    username[i] = hostname[j];
    i++;
    j++;
  }

  username[i] = '\0';
}


// Fungsi ini ambil hasil acak sederhana pakai getBiosTick
void randomAnswer() {
  int r = mod(getBiosTick(), 3);
  if (r == 0) {
    printString("ts unami gng </3\r\n");
  } else if (r == 1) {
    printString("yo\r\n");
  } else {
    printString("sygau ini soal baru\r\n");
  }
}

void shell() {
  char buf[128];
  char cmd[64];
  char arg[2][64];
  int i;

  printString("Welcome to EorzeOS!\r\n");
  updateUsername();

  while (true) {
    printString(username);
    printString("> ");

    readString(buf);

    // Hilangkan newline
    i = 0;
    while (buf[i] != '\0') {
      if (buf[i] == '\r' || buf[i] == '\n') {
        buf[i] = '\0';
        break;
      }
      i++;
    }

    parseCommand(buf, cmd, arg);

    // Tambah perintah yogurt yang random jawabannya dari fungsi randomAnswer()
    if (strcmp(cmd, "yogurt")) {
      randomAnswer();

    } else if (strcmp(cmd, "yo")) {
      printString("gurt\r\n");

    } else if (strcmp(cmd, "gurt")) {
      printString("yo\r\n");

    } else if (strcmp(cmd, "user")) {
      if (arg[0][0] != '\0') {
        strcpy(user, arg[0]);
        printString("Username changed to ");
        printString(arg[0]);
        printString("\r\n");
      } else {
        strcpy(user, "user");
        printString("Username changed to user\r\n");
      }
      updateUsername();

    } else if (strcmp(cmd, "grandcompany")) {
      if (strcmp(arg[0], "maelstrom")) {
        interrupt(0x10, 0x0200, 0, 0, 0);
        setColorRed();
        clearScreen(currentColor);
        strcpy(hostname, "@Storm");
        updateUsername();
      } else if (strcmp(arg[0], "twinadder")) {
        interrupt(0x10, 0x0200, 0, 0, 0);
        setColorYellow();
        clearScreen(currentColor);
        strcpy(hostname, "@Serpent");
        updateUsername();
      } else if (strcmp(arg[0], "immortalflames")) {
        interrupt(0x10, 0x0200, 0, 0, 0);
        setColorBlue();
        clearScreen(currentColor);
        strcpy(hostname, "@Flame");
        updateUsername();
      } else {
        printString("Error: Invalid grandcompany name\r\n");
      }

    } else if (strcmp(cmd, "clear")) {
      interrupt(0x10, 0x0200, 0, 0, 0);
      resetColor();
      hostname[0] = '\0';
      clearScreen(currentColor);
      updateUsername();

    } else if (strcmp(cmd, "add")) {
      int x, y, result;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      result = x + y;
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");

    } else if (strcmp(cmd, "sub")) {
      int x, y, result;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      result = x - y;
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");

    } else if (strcmp(cmd, "mul")) {
      int x, y, result = 0;
      int positive = 1;
      int i;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);

      if (x < 0) {
        x = -x;
        positive *= -1;
      }
      if (y < 0) {
        y = -y;
        positive *= -1;
      }

      for (i = 0; i < y; i++) {
        result += x;
      }

      result *= positive;
      itoa(result, resultStr);
      printString(resultStr);
      printString("\r\n");

    } else if (strcmp(cmd, "div")) {
      int x, y, result;
      char resultStr[64];
      atoi(arg[0], &x);
      atoi(arg[1], &y);
      if (y == 0) {
        printString("Error: Division by zero\r\n");
      } else {
        result = div(x, y);
        itoa(result, resultStr);
        printString(resultStr);
        printString("\r\n");
      }

    } else {
      printString(buf);
      printString("\r\n");
    }
  }
}

// Warna
void setColorRed()    { currentColor = 0x04; }
void setColorYellow() { currentColor = 0x0E; }
void setColorBlue()   { currentColor = 0x01; }
void resetColor()     { currentColor = 0x07; }

// Parsing command dan argumen
void parseCommand(char *buf, char *cmd, char arg[2][64]) {
  int i = 0, j = 0, argIndex = 0;

  clear(cmd, 64);
  clear(arg[0], 64);
  clear(arg[1], 64);

  while (buf[i] != ' ' && buf[i] != '\0') {
    cmd[i] = buf[i];
    i++;
  }
  cmd[i] = '\0';

  if (buf[i] == ' ') i++;

  while (buf[i] != '\0' && argIndex < 2) {
    j = 0;
    while (buf[i] != ' ' && buf[i] != '\0') {
      arg[argIndex][j++] = buf[i++];
    }
    arg[argIndex][j] = '\0';
    argIndex++;
    if (buf[i] == ' ') i++;
  }
}
