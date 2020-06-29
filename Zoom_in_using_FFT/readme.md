# Problem Statement
Upsample images using fourier transform.

## Requirements
* Go through **A6_FFT** first.

## Procedure
* Get discrete fourier transform of image I_nxn (First 6 steps of **A6_FFT**).
* Now pad this transformed image with zeros on the border, also padded image should have height and width in form of powers of 2 (Read *Note* in *A6_FFT*).
* Do inverse DFT of this padded transformed image to get upsampled image.

## Usage
```bash
foo@bar:~$ gcc main.c -lm -lpthread -o main
foo@bar:~$ ./main
```
* Enter image details, then pad amount. You can enter any postive pad amount and program will pad it such that dimensions of final padded array are nearest power of 2.
