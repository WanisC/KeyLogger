# KeyLogger

## Overview

The aim of this project is to develop a keylogger that can be used on one's own Windows machine (versions adapted for Linux/macOS will come in the future).  
Captured keys will be stored inside a text file.  
A CLI version using nodeJS will also be implemented, but is not yet operational.

## Notice of non-professional use

It is essential to emphasize that the use of KeyLogger on any machine without explicit consent is strictly prohibited. Employing such tools without proper authorization is not only unethical but also illegal in many jurisdictions. KeyLogger is intended for legitimate and lawful purposes, such as personal use or with the explicit permission of the owner of the target system.

I want to make it explicitly clear that I do not endorse or support any unauthorized, unethical, or malicious use of the KeyLogger program. If the program is used by individuals with malicious intent, I hereby declare that I bear no responsibility for any damage, loss of data, or other harm caused by such usage.

I strongly advise against using KeyLogger for any unauthorized or unethical purposes, and I urge you to respect privacy and adhere to legal and ethical standards when employing this tool.

If you have any questions or concerns regarding the appropriate use of KeyLogger, please feel free to reach out. Your understanding and responsible use of this program are greatly appreciated.

## How to run it

To download and set up the project, follow these steps:

1. Using the Makefile targets (2 ways):

```bash
make
make run
```

2. Using gcc:

```bash
gcc -o main os.c
./main
```

## How to stop it

```bash
taskkill /IM main.exe /F
```

You'll need to be in the same path as the executable.  
After using the taskill command, you can now open the text file and read what the keylogger has captured.

For any inquiries, please contact me on discord : 2diff1cult

## Version/Language

- Current version: v2023-2024
- Language: C
