# Sisop-5-2025-IT02

## Kelompok

Nama | NRP
--- | ---
Evan Christian Nainggolan | 5027241026
Dimas Muhammad Putra | 5027241076
Binar Najmuddin Mahya | 5027241101

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

2. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```
  
7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan

### Penjelasan Nomor 1
"The Echo"
Deskripsi soal: Semua yang diketik user (selain valid command) di-echo kembali.
Implementasi di kode:
- Di loop shell(), setelah parseCommand() kita cek apakah cmd cocok dengan salah satu command yang dikenali.
- Jika tidak cocok semua (masuk ke else paling bawah), maka kode:
```c
else {
  printString(buf);
  printString("\r\n");
}
```
ini akan mencetak kembali isi buf apa pun yang user ketik.
- Jadi jika user mengetik “Hello!” atau “I have the Echo”, itu akan langsung dicetak ulang apa adanya.

### Penjelasan Nomor 2
`gurt`: yo <-> gurt
Deskripsi soal:
* Ketik `yo`-> tampilkan `gurt`
* Ketik `gurt` -> tampilkan `yo`
Implementasi di kode:
- Di blok if `(strcmp(cmd, "yogurt"))` sampai else if `(strcmp(cmd, "gurt") && …)`:
```c
else if (strcmp(cmd, "yo") && arg[0][0] == '\0') {
  printString("gurt\r\n");
} else if (strcmp(cmd, "gurt") && arg[0][0] == '\0') {
  printString("yo\r\n");
}
```
* `strcmp(cmd, "yo")` mengembalikan `true` jika `cmd` sama `"yo"`. Karena argumen harus kosong `(arg[0][0]=='\0')`, maka hanya kata tunggal saja.

### Penjelasan Nomor 3
`user` → ubah username
Deskripsi soal:
* user <nama> → ganti nama prompt menjadi <nama>
* user tanpa arg → reset ke "user"
Implementasi di kode:
* Blok:
```c
else if (strcmp(cmd, "user")) {
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
}
```
* Fungsi `updateUsername()` menggabungkan `user` dan `hostname` jadi string prompt lengkap di `username`.

### Penjelasan Nomor 4
`grandcompany` → `clear`
Deskripsi soal:
* `grandcompany maelstrom|twinadder|immortalflames` → clear screen + ubah warna & tambahkan `@Storm|@Serpent|@Flame` di prompt
* `grandcompany` tanpa argumen atau invalid → error message
* `clear` → reset warna, prompt kembali normal, clear screen
Implementasi di kode:
* Di `shell()` ada blok:
```c
else if (strcmp(cmd, "grandcompany")) {
  if (strcmp(arg[0], "maelstrom")) {
    interrupt(0x10, 0x0200, 0, 0, 0);
    setColorRed();
    clearScreen(currentColor);
    strcpy(hostname, "@Storm");
    updateUsername();
  }
  else if (strcmp(arg[0], "twinadder")) { … }
  else if (strcmp(arg[0], "immortalflames")) { … }
  else {
    printString("Error: Invalid grandcompany name\r\n");
  }
}
else if (strcmp(cmd, "clear")) {
  interrupt(0x10, 0x0200, 0, 0, 0);
  resetColor();
  hostname[0] = '\0';
  clearScreen(currentColor);
  updateUsername();
}
```
* Panggilan `interrupt(0x10,0x0200,…)` berfungsi clear screen via BIOS, lalu `setColorX()` + `clearScreen(attribute)` me-repaint layar sesuai warna baru.

### Penjelasan Nomor 5
Kalkulator sederhana
Deskripsi soal:
* `add x y`, `sub x y`, `mul x y`, `div x y` → operasi matematika integer
Implementasi di kode:
* Masing-masing command punya blok sendiri:
```c
else if (strcmp(cmd, "add")) { … }
else if (strcmp(cmd, "sub")) { … }
else if (strcmp(cmd, "mul")) { … }
else if (strcmp(cmd, "div")) { … }
```
* Parsing argumen dengan `atoi(arg[0], &x)` dan `atoi(arg[1], &y)`.
* Operasi `mul` dan `div` menggunakan loop atau fungsi `div()`/`mod()` yang kamu definisikan di `std_lib.c`.

### Penjelasan Nomor 6
`yogurt` → random answer
Deskripsi soal:
* Panggil `randomAnswer()` yang memilih salah satu dari tiga teks secara acak.
Implementasi di kode:
* Command `"yogurt"`:
```c
if (strcmp(cmd, "yogurt")) {
  randomAnswer();
}
```
* `randomAnswer()` memanggil `getBiosTick()`, lalu `mod(...,3)` untuk membuat `r` di [0..2], kemudian `printString()` salah satu dari:
* "ts unami gng </3\r\n"
* "yo\r\n"
* "sygau ini soal baru\r\n"

### Penjelasan Nomor 7
Makefile → build OS image
Deskripsi soal:
*  Lengkapi `Makefile` agar bisa compile & link bootloader, kernel, stdlib, shell, lalu inject ke `floppy.img`.
Implementasi di makefile:
* Command `"yogurt"`:
```
prepare:
    dd if=/dev/zero of=bin/floppy.img bs=512 count=2880

bootloader:
    nasm -f bin src/bootloader.asm -o bin/bootloader.bin
    dd if=bin/bootloader.bin of=bin/floppy.img bs=512 count=1 conv=notrunc

stdlib:
    bcc -ansi -Iinclude -c src/std_lib.c -o bin/std_lib.o

shell:
    bcc -ansi -Iinclude -c src/shell.c -o bin/shell.o

kernel:
    nasm -f as86 src/kernel.asm -o bin/kernel-asm.o
    bcc -ansi -Iinclude -c src/kernel.c -o bin/kernel.o

link:
    ld86 -o bin/kernel.bin -d bin/kernel.o bin/kernel-asm.o bin/std_lib.o bin/shell.o
    dd if=bin/kernel.bin of=bin/floppy.img bs=512 seek=1 conv=notrunc

build: prepare bootloader stdlib shell kernel link
```
* Dengan `make build` semua step ini akan otomatis dijalankan, menghasilkan `bin/floppy.img` yang siap dijalankan di emulator.
