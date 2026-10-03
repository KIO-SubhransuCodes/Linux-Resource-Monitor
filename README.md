# Linux Resource Monitor

A simple C++ program that displays basic Linux system resource information directly in the terminal.

## Features

* Displays CPU model information
* Shows the number of processors
* Displays disk/storage information
* Reads system information from Linux system files

## Tech Stack

* C++
* Linux `/proc` filesystem
* `statvfs`

## How It Works

The program reads CPU information from `/proc/cpuinfo` and uses Linux filesystem statistics through `statvfs()` to retrieve storage details. The collected information is then processed and displayed in the terminal.
