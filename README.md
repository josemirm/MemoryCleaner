# MemoryCleaner
## About this:
This software have an easy way to free memory in Windows systems.
It works allocating all non-used memory in the system to occupy all "pending" memory, after that, it frees all the allocated memory to let it completely free, not "half-free, half-pending-to-free". If you haven't any virtual memory assigned to your system, you can use the infinite memory allocation; It wouldn't allocate more memory than you have. Otherwise, with a virtual memory file/partition, it will fill both physical and virtual memory making your computer totally unstable.

## Using the software:
There are compiled binaries to use in 32-bit and 64-bit Windows machines in addition to the single ~~C++~~ C source file.
It's about 100 lines of real code, it's simple but powerful.
Here are binaries and code downloads:

* Download source code: [MemCleaner.c](https://github.com/josemicoronil/MemoryCleaner/raw/master/MemCleaner.c)
* Download 64-bit binary: [MemCleaner64.exe](https://github.com/josemicoronil/MemoryCleaner/raw/master/MemCleaner64.exe)
* Download 32-bit binary: [MemCleaner32.exe](https://github.com/josemicoronil/MemoryCleaner/raw/master/MemCleaner32.exe)

## What happens on non-Windows machines:
Their memory management works in a different way, so I don't think this software would be useful for you, but hey, you are free to try it out, it wouldn't do anything bad. I promise.

## License:

MIT License

Copyright (c) 2017 José Miguel (Josemi) Rodríguez

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
