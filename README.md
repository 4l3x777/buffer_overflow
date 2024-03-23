# Buffer Overflow Vulnerability

+ Explore Buffer Overflow Vulnerability
+ простой эксплоит для понимания концепта уязвимости переполнения буфера

## compiler's params

+ ASLR отключен для определения const return address'a
+ DEP отключен для возможности исполнения кода на стэке (addition E - execute privilege)

## buffer_overflow x86

+ проект содержит уязвимую программу с возможностью эксплуатации переполнения буфера
+ проект собран с учетом `compiler's params`
+ уязвимая функция

```C++
  void buffer_overflow_vuln(char *buf)
  {
    LPVOID data;
    DWORD size;
    char localBuf[0x100000];
    size = *(DWORD*)buf;
    data = buf + 4;
    printf("size: %d\n",size);
    memcpy(localBuf, data, size);
  }
```

+ размер полезной нагрузки ограничен размером `localBuf`

## bin

+ содержит PoC эксплоита `bof_exploit.py`
+ уязвимую программу `buffer_overflow.exe`
+ пример текстового шеллкода `shell.bin` - получен из примера `hello_msb_asm_x86.exe` проекта [shell_maker](https://github.com/4l3x777/shell_maker)

## Пример работы

![alt text](/img/bof.gif)

## Ссылки

+ https://github.com/4l3x777/shell_maker
