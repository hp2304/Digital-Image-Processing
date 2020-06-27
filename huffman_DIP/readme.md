# Problem Statement
Apply Huffman Encoding and Decoding on image.

## Requirements
* Go through **Run_length_Encoding** assignment first.
* Good knowledge of huffman encoding and decoding.

## Core Idea
* Basically this method assigns some pattern (sequence of 0s and 1s) to different symbols in data (pixel values in our case).  
* This algorithm does this such that most occuring symbol gets pattern with lesser length compared to least occuring symbols.
* Let's take an example, take image with low brightness. Most pixel values will be 0 in this image. So this algo will assign let's say, pattern "0" and let's say pixel value 200 is least occuring, then it will assign pattern "000101001101" to it. This mapping (pixel values to patterns) is stored in *table.txt* file.
* Encoding file will contain assigned patterns for each pixel values of our image.
* At the decoding time we read the table, and then start reading encoding file to decode the pixel values.
* This technique is also used in *JPEG compression*.

## Usage
```bash
foo@bar:~$ gcc encode.c -o encode
foo@bar:~$ ./encode
```
After running encode executable, **encodings.txt** and **table.txt** (kinda lookup table, required while decoding) files will be generated.

```bash
foo@bar:~$ gcc decode.c -o decode
foo@bar:~$ ./decode
```
Decode will require filename of encodings, image height and image width and lookup table filename as inputs to decode. It also takes output filename as input. After that {output filename}.raw will be created.

---
### Note
* Here, we do need image dimensions at decoding time, unlike run length encoding. But I have not encoded image dimensions in encodings.txt, you can implement it if you like.
---