# Problem Statement
Perform Discrete Fourier Transform on Image

## Requirements
* Go through **FT_matlab** first.
* Read slide 23 of **DIP_FT.pdf**.

## Procedure
* Just use formulae shown in slide 23 of **DIP_FT.pdf** to find DFT of image.
* **Time complexity: O(n^4)** :(

## Usage
```bash
foo@bar:~$ gcc dft.c -o dft
foo@bar:~$ ./dft
```
Basically it will create raw_out file as output. Which contains magnitude spectrum of image. Same as shown in *FT_matlab* exercise.

---
### Note
* Here I have taken images of size 128x128 and 64x64, reason being this method has **O(n^4)** time complexity. So, for image of size 1024x1024, it will take ages. Also note that *complex multiplications* are involved too.
* Last exercise's method (*FT_matlab*) has **O(n^3)** time complexity.
* Hence none of these approachs are feasible, to find DFT of images.
---
