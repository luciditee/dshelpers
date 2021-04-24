# Data Structure Helpers
A simple C library containing fairly unremarkable, canoncial implementations of commonly used data structures, such as hashtables and linked lists. Written to C89 spec for maximum portability, and (with the exception of the `.vscode` directory, which is more for my own help) all files respect 8.3 file naming conventions for use on older or embedded systems which may require it.

Everyone who did CS has done this. Many, many commonly used C libraries implement some or all of these. Likewise, there's really no reason for anyone to use this library. It's more for my own personal educational reasons that I'm posting this to help me further internalize core compsci fundamentals that I never really got to grapple with since my degree wasn't originally in CS.

All files are commented to explain how each data structure works, the **time complexity** of data retrieval for each data structure in big-O notation, and use cases for when those time complexities may be encountered.

# Usage
Again, you really have no reason to use this, almost any other C library out there will contain stuff like this. But if you must--each `.c` file has an accompanying `.h` header file in the `includes` directory, which is required to interface with and use the data structures handled by the `.c` code.

Just copy the `.c` file wherever you keep your `.c` source files, and plonk the `.h` file wherever your headers typically go.

Header files are kept neat and tidy in case you want to read them to learn the API of each data structure. This is done because the C world has, for some reason, settled on this mal-adaptive idea of reading header files for documentation, so I figured it would be polite to at least make it readable.

# License
Licensed under the 2-clause BSD license (see enclosed LICENSE file for details).