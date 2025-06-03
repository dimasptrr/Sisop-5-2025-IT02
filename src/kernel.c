#include "shell.h"
#include "kernel.h"

int main() {
  interrupt(0x10, 0x0200, 0, 0, 0);
  clearScreen(0x07);
  shell();
}

void printString(char *str)
{
  while (*str != '\0') {
    // AH = 0x0E, teletype output
    // AL = karakter yang dicetak
    // INT 0x10 mencetak karakter ke layar
    interrupt(0x10, 0x0E00 + *str, 0, 0, 0);
    str++;
  }
}

void readString(char *buf)
{
  int i = 0;
  char c = 0;
  char temp[2];

  while (1) {
    c = interrupt(0x16, 0x0000, 0, 0, 0); // BIOS keyboard input

    // Enter key (ASCII 13)
    if (c == 13) {
      buf[i++] = '\r'; // carriage return
      buf[i++] = '\n'; // newline
      buf[i] = '\0';
      printString("\r\n"); // tampilkan baris baru di layar
      break;
    }
    // Backspace
    else if (c == 0x08) {
      if (i > 0) {
        i--;
        printString("\b \b"); // hapus karakter dari layar
      }
    }
    // Normal character
    else {
      buf[i++] = c;
       temp[0] = c;
       temp[1] = '\0';
      printString(temp); // tampilkan karakter ke layar
    }
  }
}

void clearScreen(int warna)
{
  int i;
  for (i = 0; i < 25 * 80; i++) {
    putInMemory(0xB800, i * 2, ' ');     // karakter spasi
    putInMemory(0xB800, i * 2 + 1, warna); // atribut warna default (abu-abu terang di hitam)
  }
}