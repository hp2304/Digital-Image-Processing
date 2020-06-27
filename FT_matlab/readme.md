# Visulization of FT
Perform Discrete Fourier Transform using matrix multiplication

## Requirements
* Go through **haar_transform** folder first.
* Good knowledge of fourier transform.
* Read sildes 2 to 12 of **DIP_FT.pdf**.
* Matlab

## Procedure
* Transformation matrix *U* (or so called fourier basis matrix) is created, to apply it on the image I (shape nxn) (Method is shown in pdf as stated in requirements). U is unitary matrix, meaning *inverse(U) = conjugate(transpose(U))* (entris of U are complex numbers). Note, U is a square matrix.
* Transformed Image *B = U x I x U*.
* To visulize magnitude spectrum, take absolute value of B (since entries of B are complex) and center the low frequency components.
* There will be a bright dot at the center, which shows presence of low frequency components.
* **Time complexity: O(n^3)**.

## Usage
* Run dft.m in matlab. It will show 2 figures, first figure corresponds to result of our approach shown above, and second is result of matlab's inbuilt function. Both looks the same, so implementation is correct. You can change the image and visulize.