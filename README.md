# Dev OS

This is a little project I have been working on for a while now. It's a basic operating system built from scratch, written mostly in C++ and Assembly. 
---

### Running
To start this operating system, you must first have some dependencies installed. 
    - qemu
    - bochs (optional)
    - g++
    - doxygen (for documentation generation)

Once installed, you can run with `make run`. This should compile, then start a qemu instance of the operating system. If you want to debug, you can use `make bochs` which should start the operating system with bochs, however when bochs launces you will have to select option 6 to start the bootloader, then when it breaks, you must type 'c' and then press enter. 


The documentation for the code can be seen at https://wa6cr.com/osdev/

PULL REQUESTS ARE ACCEPTED AND WELCOME! I would be very happy to have others contribute to this project of mine. 