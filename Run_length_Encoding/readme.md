# Problem Statement
Do run length encoding of input image and also decode the encoding to get the input image back.

## Requirements
* Read about run length encoding.

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

---
### Note
* Though we don't need to provide image dimensions in decode (intuitive), but the way I am writing raw images in C, I need to specify it's dimensions. But there's always a workaround, you can change it, if you like (being lazy). 
---