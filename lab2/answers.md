**1.**

```
main.o  :
section                size   addr
.text                    30      0
.data                     0      0
.bss                      0      0
.comment                 39      0
.note.GNU-stack           0      0
.note.gnu.property       32      0
.eh_frame                56      0
Total                   157


hotfix.o  :
section                size   addr
.text                    39      0
.data                     0      0
.bss                      0      0
.comment                 39      0
.note.GNU-stack           0      0
.note.gnu.property       32      0
.eh_frame                56      0
Total                   166


core.o  :
section                 size   addr
.text                     70      0
.data                   4032      0
.bss                   50000      0
.rodata                   76      0
.data.rel.local            8      0
.comment                  39      0
.note.GNU-stack            0      0
.note.gnu.property        32      0
.eh_frame                 88      0
Total                  54345


legacy.o  :
section                size   addr
.text                    52      0
.data                     0      0
.bss                      4      0
.comment                 39      0
.note.GNU-stack           0      0
.note.gnu.property       32      0
.eh_frame                88      0
Total                   215
```

---

**2.**

в `core.o` `.bss` занимает аж 50000 байт, что очень много по сравнению с другими объектными файлами.
почему так? для этого нужно разобраться, а что вообще хранит `.bss` именно в бинаре.
в объектном файле секция `.bss` не занимает место, она является лишь его "заполнителем".
во время исполнения программы выделяется статическая память под переменные из .bss

---

**3.**

```
core.o: file format elf64-x86-64

Sections:
Idx Name                 Size     VMA              Type
  0                      00000000 0000000000000000 
  1 .text                00000046 0000000000000000 TEXT
  2 .rela.text           00000078 0000000000000000 
  3 .data                00000fc0 0000000000000000 DATA
  4 .bss                 0000c350 0000000000000000 BSS
  5 .rodata              0000004c 0000000000000000 DATA
  6 .data.rel.local      00000008 0000000000000000 DATA
  7 .rela.data.rel.local 00000018 0000000000000000 
  8 .comment             00000027 0000000000000000 
  9 .note.GNU-stack      00000000 0000000000000000 
 10 .note.gnu.property   00000020 0000000000000000 DATA
 11 .eh_frame            00000058 0000000000000000 DATA
 12 .rela.eh_frame       00000030 0000000000000000 
 13 .symtab              00000138 0000000000000000 
 14 .strtab              0000006c 0000000000000000 
 15 .shstrtab            00000089 0000000000000000 

legacy.o:       file format elf64-x86-64

Sections:
Idx Name               Size     VMA              Type
  0                    00000000 0000000000000000 
  1 .text              00000034 0000000000000000 TEXT
  2 .rela.text         00000048 0000000000000000 
  3 .data              00000000 0000000000000000 DATA
  4 .bss               00000004 0000000000000000 BSS
  5 .comment           00000027 0000000000000000 
  6 .note.GNU-stack    00000000 0000000000000000 
  7 .note.gnu.property 00000020 0000000000000000 DATA
  8 .eh_frame          00000058 0000000000000000 DATA
  9 .rela.eh_frame     00000030 0000000000000000 
 10 .symtab            000000c0 0000000000000000 
 11 .strtab            00000046 0000000000000000 
 12 .shstrtab          0000006c 0000000000000000 

hotfix.o:       file format elf64-x86-64

Sections:
Idx Name               Size     VMA              Type
  0                    00000000 0000000000000000 
  1 .text              00000027 0000000000000000 TEXT
  2 .rela.text         00000060 0000000000000000 
  3 .data              00000000 0000000000000000 DATA
  4 .bss               00000000 0000000000000000 BSS
  5 .comment           00000027 0000000000000000 
  6 .note.GNU-stack    00000000 0000000000000000 
  7 .note.gnu.property 00000020 0000000000000000 DATA
  8 .eh_frame          00000038 0000000000000000 DATA
  9 .rela.eh_frame     00000018 0000000000000000 
 10 .symtab            00000078 0000000000000000 
 11 .strtab            00000023 0000000000000000 
 12 .shstrtab          0000006c 0000000000000000
```

поля, которые есть в core.o, но которых нету в hotfix.o и legacy.o
```
5 .rodata              0000004c 0000000000000000 DATA
6 .data.rel.local      00000008 0000000000000000 DATA
7 .rela.data.rel.local 00000018 0000000000000000 
```

`.rodata` - секция, которая хранит readonly данные

---

**4.**

```
System Initialized v1.0
FLAG{b1nary_4rch4eology_2026} <-- SECRET TOKEN
%s, Mode: %d
GCC: (Ubuntu 15.2.0-16ubuntu1) 15.2.0
core.c
large_buffer
internal_cleanup
system_mode
config_table
welcome_msg
secret_token
print_status
printf
.symtab
.strtab
.shstrtab
.rela.text
.data
.bss
.rodata
.rela.data.rel.local
.comment
.note.GNU-stack
.note.gnu.property
.rela.eh_frame
```

FLAG{b1nary_4rch4eology_2026} - секретный токен

---

**5.**

```
core.o:
0000000000000020 D config_table
0000000000000000 t internal_cleanup
0000000000000000 b large_buffer
0000000000000012 T print_status
                 U printf
0000000000000020 R secret_token
0000000000000000 D system_mode
0000000000000000 D welcome_msg

hotfix.o:
0000000000000000 T apply_hotfix
0000000000000004 C system_mode

legacy.o:
000000000000001a T apply_legacy_patch
0000000000000000 b legacy_counter
0000000000000000 t legacy_helper
0000000000000004 C system_mode

main.o:
                 U apply_hotfix
0000000000000000 T main
                 U print_status
```

список имен, которые встречаются в нескольких файлах;
формат: имя - список файлов
print_status - core.o main.o
system_mode - core.o hotfix.o legacy.o main.o

---

**6.**

```
0000000000000000 g     O .data  0000000000000004 system_mode
0000000000000004       O *COM*  0000000000000001 system_mode
0000000000000004       O *COM*  0000000000000004 system_mode

0000000000000012 g     F .text  0000000000000034 print_status
0000000000000000         *UND*  0000000000000000 print_status
```

в `hotfix.o` у system_mode выравнивание 1, в остальных 4.

---

**7.**

с `-fcommon` линкер использует определение D из core.o, так как оно сильнее, ошибки нет, все три файла будут изменять кусок в 4 байта. я пробовал поиграться и сделал синтетический пример, где в одном объектнике переменная в .rodata, а в других также common. с -fcommon можно спокойно перетирать .rodata, правда после этого программа падает с SIGSEGV из за попытки изменить readonly область памяти (защита ОС).

---

**8.**

```
$ gcc -fcommon core.o legacy.o hotfix.o main.o -o app
$ echo $?
0
$ ./app
System Initialized v1.0, Mode: 1
System Initialized v1.0, Mode: 4407873
```

```
$ gcc -fcommon core.o legacy.o hotfix.o main.o -o app -Wl,--warn-common
/usr/bin/ld: legacy.o: warning: common of `system_mode' overridden by definition from core.o
/usr/bin/ld: hotfix.o: warning: common of `system_mode' overridden by definition from core.o
```

---

**9.**

```
$ nm app | grep system_mode
0000000000404040 D system_mode

$ readelf -s app | grep system_mode
    32: 0000000000404040     4 OBJECT  GLOBAL DEFAULT   23 system_mode

$ readelf -S app | grep -E "\.data|\.bss"
  [23] .data             PROGBITS         0000000000404020  00003020
  [24] .bss              NOBITS           0000000000405020  00004008
```

---

**10.**

```
$ gcc -fno-common main.o hotfix.o legacy.o core.o -o app_better
$ echo $?
0
```

```
$ gcc -fno-common -c hotfix.c && nm hotfix.o
0000000000000000 T apply_hotfix
0000000000000000 B system_mode

$ gcc -fno-common main.o hotfix.o legacy.o core.o -o app_better
/usr/bin/ld: warning: alignment 1 of normal symbol `system_mode' in hotfix.o is smaller than 4 used by the common definition in legacy.o
/usr/bin/ld: warning: NOTE: alignment discrepancies can cause real problems.  Investigation is advised.
/usr/bin/ld: core.o:(.data+0x0): multiple definition of `system_mode'; hotfix.o:(.bss+0x0): first defined here
collect2: error: ld returned 1 exit status
```

```
$ # hotfix.c: extern char system_mode[4];
$ gcc -fno-common -c hotfix.c && nm hotfix.o
0000000000000000 T apply_hotfix
                 U system_mode

$ gcc -fno-common main.o hotfix.o legacy.o core.o -o app_better
$ echo $?
0
$ nm app_better | grep system_mode
0000000000404040 D system_mode
```

с `-fno-common` каждая неинициализированная переменная станет B в .bss. Получится 3 определения 1 глобального символа и линтер упадет из за multiple definition

в hotfix.c лучше всего сделать extern char system_mode, тогда это будет объявление, но не определение - флаг U (undefined) - не определено. тогда ссылка будет на core.o и все будет ок.
