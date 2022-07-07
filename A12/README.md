# Fast Cosine Transform: Algorithm to Compute DCT

## Problem Statement
- Implement FCT (Fast Cosine Transform) algorithm to calculate Discrete Cosine Transform of input image. DCT is used heavily in **Image Compression**.

- Text regarding this topic is in slides 30 to 40 of [DIP_FT.pdf](../A10/DIP_FT.pdf).


## Algorithm and Usage
* Read input image (shape *nxn*).
* Do 1D DCT of rows of image. Store it in variable *fct* (2D array of type struct complex).
* Transpose 2D array *fct*.
* Do 1D DCT of rows of *fct*. Store it in variable *fct*.
* Transpose *fct*. 

```bash
foo@bar:~$ gcc main.c -lm -lpthread -o main
foo@bar:~$ ./main
```
- Executing the same prints the first column of transformed (real part) of the inputted image.
* **Time Complexity: O(n^2lg(n))**. same as *FFT*.
* I am using multithreaded version here.

---
### Note
* Function to calculate 1D DCT is derived from function to calculate 1D FFT used in [A10](../A10/).
---