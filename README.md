# LZS compression algorithm

LZS (Lempel Ziv Stac Eletronics) is a lossless compression algorithm developed in C standard ISO/IEC 9899:1999. Instead of using a history buffer of 2048 bytes this implementation use a 256 bytes window size with the hash table support for pattern search.

# Features

  - Command Line Interface available
  - Multilayer architecture
  - Compress and decompress all kind of data

# Usage

LZS require MinGW or any other compiler for C. Static distributions are available for linux and windows in the *dist/* folder, while the necessary libraries are available in the *lib/* dir. 

To run the algorithm go to the dist/<your so> then run the following command and specify the option '-c' to compress or '-d' to decompress followed by an input and an ouput file:

```sh
$ ./static_LZS_1.0.0 <option> <input_file> <output_file>
```

License
----

MIT © Mohamed Boutaleb
