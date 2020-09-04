# LZS compression algorithm

LZS (Lempel Ziv Stac Eletronics) is a lossless compression algorithm developed in C standard ISO/IEC 9899:1999. Instead of using a history buffer of 2048 bytes use 256 bytes with the hash table support for pattern search.

# Features

  - Command Lind Interface available
  - Multilayer architecture
  - Compress and decompress all kind of data

# Installation

LZS require MinGW or any other compiler for C.

Compile and create all the object files and the libraries with the following command:

```sh
$ make static_LZS_1.0.0
```

To run the algorithm specify the option '-c' to compress or '-d' to decompress followed by an input and an ouput file:

```sh
$ ./static_LZS_1.0.0 <option> <input_file> <output_file>
```

License
----

MIT © Mohamed Boutaleb
