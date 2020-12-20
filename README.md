# Josemi's Memory Cleaner
## About this:
This software have an easy way to free memory in Windows systems.
This memory cleaner works allocating all non-used memory in the system to occupy all "pending" memory, after that, it frees all the allocated memory to let it completely free, not "half-free, half-pending-to-free". The last version of the program check your physical free memory on your computer to do the cleaning automatically without any 
* TO THE OLD VERSION (NOT RECOMMENDED): If you haven't any virtual memory assigned to your system, you can use the infinite memory allocation (t wouldn't allocate more memory than you have), otherwise with a virtual memory file/partition, it will fill both physical and virtual memory making your computer totally unstable.

## Using the software:
There are compiled binaries to use in 32-bit and 64-bit Windows machines in addition to the single ~~C++~~ C source file. If you have less than 4 GB of RAM you could use both, but if you use the 32-bit version in a 64-bit machine it will NOT work properly.
It's ~~about 100~~ exactly 50 lines of code, it's simple but powerful.
Here are binaries and code downloads:

* Download source code: [MemCleaner.c](https://github.com/josemirm/MemoryCleaner/raw/master/MemCleaner.c)
* Download 64-bit binary: [MemCleaner64.exe](https://github.com/josemirm/MemoryCleaner/raw/master/MemCleaner64.exe)
* Download 32-bit binary: [MemCleaner32.exe](https://github.com/josemirm/MemoryCleaner/raw/master/MemCleaner32.exe)

## What happens on non-Windows machines:
This program is completely targeted to Windows machines, in other OS the memory management works different and have diffent problems and solutions to the shown here.
At first, the source code will only compile in Windows with Microsoft C/C++ Compiler, or other compiler with full windows headers and libraries support, that exclude for example GCC, that uses MINGW or MSYS Unix emulation to work (and doesn't have full libraries support). That's let the new code without any non-Windows support, but in Windows is totally needed the Windows exclusive "GlobalMemoryStatusEx" function in order to know different system memory stats (physica, free, used, etc.).
To use on non-Windows machines you could use the older version at your own risk. It does the same but in a more manual way, having to write in the arguments how many MB you want to clean (e.g., "MemCleaner32.exe 1024").

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
