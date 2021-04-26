# Data Structure Helpers
A simple C library containing fairly unremarkable, canoncial implementations of commonly used data structures, such as hashtables and queues. Written to C89 spec for maximum portability, and (with the exception of the `.vscode` directory, which is more for my own help) all files respect 8.3 file naming conventions for use on older or embedded systems which may require it.

All files are commented to explain how each data structure works, the **time complexity** of data retrieval for each data structure in big-O notation, and use cases for when those time complexities may be encountered.

# What's the point?
There isn't one, really, other than educational purposes.

You may fit into one of the niches that I fit into, though:

## Legacy systems support
I have some DOS game development musings I'd like to entertain one day, beyond silly test code. You can't reasonably expect to have `vector` or `sys/queue.h` under DOS unless you go out of your way to use certain compilers, or cross-compile it and statically link those libraries into the code. To me, dealing with cross-compiler hell sounds worse than just writing it myself, and you'll see from most of the `.c` files the implementations are really lean/simple--perfect for DOS.

## Embedded systems
C89 or ISO C, being the earliest standardized versions, are one of those things you can reasonably expect to be supported on just about any hardware that has a C compiler. If you're targeting an 8080/8085, or a very old Atmel chip, or some other microcontroller; or maybe you're dealing with some old MIPS code--expecting C99 or C11 support is probably not the best idea.

I tinker with hardware development on the side, too, so this seems like a good idea.

## Any application where `<sys/queue.h>` isn't available
The `sys/` family of headers is not standard outside of Linux and some flavors of BSD. If you plan to run your code on Windows, Linux, BSD, macOS, and what-have-you, relying on the `sys` family is ill-advised.

Most of these are simple enough that if you're smart enough to have thought "Hey, I can't use `sys` when I port this to Windows," and you know what data structure you need and why you need it, you could probably implement it yourself.

# Usage
Again, unless you're learning compsci fundamentals, or you fit into one of the above niches, you don't need to use code in this repo.

But if you must--each `.c` file has an accompanying `.h` header file in the `includes` directory, which is required to interface with and use the data structures handled by the `.c` code.

Just copy the `.c` file wherever you keep your `.c` source files, and plonk the `.h` file wherever your headers typically go.

Header files are kept neat and tidy in case you want to read them to learn the API of each data structure. This is done because the C world has, for some reason, settled on this mal-adaptive idea of reading header files for documentation, so I figured it would be polite to at least make it readable.

# License
Licensed under the 2-clause BSD license (see enclosed LICENSE file for details).