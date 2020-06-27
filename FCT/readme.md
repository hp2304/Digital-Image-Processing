# Problem Statement
Implement FCT (Fast Cosine Transform) algorithm to perform Discrete Cosine Transform on Image.

## Requirements
* Go through **A6_FFT** first.
* Read slides 30 to 40 of **DIP_FT.pdf**.
* Must know how to do FCT of 1D sequence.

## Procedure and Usage
* Read image (shape *nxn*).
* Do 1D FCT of rows of image. Store them in variable *fct* (2d array of type struct complex).
* Transpose 2d array *fct*.
* Again do 1D fct of rows of *fct*. Store it in variable *fct*.
* Again transpose *fct*. And we got it :)

```bash
foo@bar:~$ gcc main.c -lm -lpthread -o main
foo@bar:~$ ./main
```
It will print the whole thing (hopefully it would be correct. Check in matlab).
* **Time Complexity: O(n^2lg(n))**. same as *FFT*.
* I am using multithreaded version here.

---
### Note
* Function for 1D FCT is derived from function 1D FFT used in **A6_FFT**. If curious, check out function *find_1d_fct* in **fct_dp.h** file.
---