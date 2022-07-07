# Run Length Encoding

## Problem Statement
Do run length encoding of input image and also decode the encoding to get the input image back. Run length encoding is a compression technique which is used heavily in storing segmentation masks.


## Usage
```bash
foo@bar:~$ gcc encode.c -o encode
foo@bar:~$ ./encode
```
After running encode executable, a **encodings.txt** file will be generated.

```bash
foo@bar:~$ gcc decode.c -o decode
foo@bar:~$ ./decode
```
Decode will require filename of encodings, image height and image width as inputs to decode. **out.raw** (Decoded image) will be created. 
