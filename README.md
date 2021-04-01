# Josemi's Memory Cleaner
## About this:
This software have an easy way to free memory in Windows systems.

It works allocating all non-used memory in the system to occupy all "pending" memory, after that it frees all the allocated memory to let it completely free, not "half-free, half-pending-to-free" as Windows usually handle it.

The last version of the program check your physical free memory on your computer to do the cleaning automatically without any stability issue.

## UPDATE 1
* Some bugs found in the code are solved.
* Changed the default percentage of used memory from 90% to 80% to resolve stability issues.
* Changes in the arguments. Now you set a percentage to clean instead a fixed value of kilobytes.
* Added a check to 32-bit version users to advise them to use the 64-bit version when there are more than 2 GB of RAM to clean.
* Refactored the code and the "Read Me" file.

## Using the software:
There are compiled binaries to use Windows machines in addition to the single C source file. If you have less than 4 GB of RAM you could use both, but if you use the 32-bit version in a 64-bit machine it will not work properly.

Here are binaries and code downloads:

* Download source code: [MemCleaner.c](https://github.com/josemirm/MemoryCleaner/raw/master/MemCleaner.c)
* Download 64-bit binary (Recommended): [MemCleaner64.exe](https://github.com/josemirm/MemoryCleaner/raw/master/MemCleaner64.exe)
* Download 32-bit binary: [MemCleaner32.exe](https://github.com/josemirm/MemoryCleaner/raw/master/MemCleaner32.exe)

Do not use the versions in the "OldVersions" folder: It will try to get all your system memory and make it unstable. Use it at your own risk.

## What happens on non-Windows machines:
This program is completely targeted to Windows machines, in other OS the memory management works different and have diffent problems and solutions. Also, it uses non-portable Windows functions unavailable in other OS.

## License:

MIT License

Copyright (c) 2017 José Miguel (josemirm) Rodríguez

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
