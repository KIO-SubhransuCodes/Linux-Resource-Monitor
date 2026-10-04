# Linux Resource Monitor

A lightweight C++ command-line tool for monitoring basic system resources on Linux. The program collects system-level information directly from Linux interfaces and displays it in a simple, readable format in the terminal.

## Features

* Displays CPU model and processor information
* Shows the number of available CPU processors
* Displays total disk/storage capacity
* Shows available and used storage
* Reads CPU information directly from the Linux `/proc` filesystem
* Uses filesystem statistics to retrieve storage information
* Lightweight and runs directly from the terminal
* Uses standard C++ libraries for file handling and system interaction

## Tech Stack

* **C++**
* **Linux**
* **`/proc` filesystem**
* **`statvfs`**
* **C++ Standard Library**

## How It Works

The program collects system information from Linux's virtual filesystem and filesystem APIs.

For CPU information, it reads `/proc/cpuinfo` using C++ file handling and extracts details such as the CPU model and processor count.

For storage information, the program uses `statvfs()` to retrieve filesystem statistics. These values are used to determine the total, available, and used storage of the system.

The collected information is then processed and displayed directly in the terminal.

## Requirements

* Linux-based operating system
* C++ compiler such as `g++`

## Example Output

```text
===== Linux Resource Monitor =====

CPU Information
CPU Model: Intel(R) Core(TM) ...
Processors: 12

Storage Information
Total Storage: ...
Available Storage: ...
Used Storage: ...
```
