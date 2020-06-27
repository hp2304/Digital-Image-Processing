# Problem Statement
Implement FFT (Fast Fourier Transform) algorithm to perform Discrete Fourier Transform on Image. Also do filtering.

## Requirements
* Go through **DFT_C** first.
* Read slides 25 to 29 of **DIP_FT.pdf**.
* Must know how to do FFT of 1D sequence.

## Procedure and Usage
* Read image (shape *nxn*).
* Multiply each entry (i, j) by pow (-1, i + j ) (*0 indexing*), will explain later *why?*
* Do 1D FFT of rows of image. Store them in variable *fft* (2d array of type struct complex).
* Transpose 2d array *fft*.
* Again do 1D FFT of rows of *fft*. Store it in variable *fft*.
* Again transpose *fft*. And we got it :). No need to center the low frequencies, it's already done, reason is second step. How it happened I don't know, sorry.

```bash
foo@bar:~$ gcc main.c -o main
foo@bar:~$ ./main
```
It will print the whole thing (hopefully it would be correct. Check in matlab or python, **Don't forget fftshift**).
* Now to do the IDFT (Inverse DFT to get the image back), take conjugate of fft.
**(Need to uncomment lines 63 to 97 in main.c)**
* Do transpose, 1D FFT of rows, transpose, 1D FFT of rows and conjugate of *fft*. And we will get back same array as in step 2.
* Multiply by pow(-1, i+j) to get original image back.
* **Time Complexity: O(n^2 lg(n))** (DFT and/or IDFT). Becasue 1D FFT of length n has *O(nlogn)* time complexity. And we are just doing that, for all n rows repeatedly (constant times, 4 to be accurate, DFT and IDFT).
---
## Make it more faster
* Use implementation provided in *./FFT/Threaded*
```bash
foo@bar:~$ gcc main.c -lm -lpthread
foo@bar:~$ ./main
```
* What I did? **Multithreading**, as one would guess.
* One thing to note here is, 1D FFT of 1st row and 2nd row is independent, and this is true b.w. all pairs of rows. So now we can create a thread which will do just 1D FFT of one row, we can create such multiple threads to make it faster, where each thread will do FFT of different row.
* But we need to synchronize these threads before we do transpose and conjugate operations. Remember all threads are operating on different rows *fft*(2D array) variable. So we need to wait till all the threads have done it's work. And then only we should proceed to perform transpose or conjugate operation, otherwise it will create chaos.
* And this is like crazy fast. It took around just **<2** seconds on a **1024x1024 image (DFT and IDFT)** (My laptop has i7-7500U and 16GB RAM). This is signficantly faster than *naive* method shown in **DFT_C** assignment and that matrix multiplication method in **FT_matlab**.
* Well you can use any implementation either with multithreading or without multithreading. I have used multithreaded version in filtering part. 
---
*Now let's move to filtering part.* So when we get FFT of image at 6th step, (Remember *low frequencies are at center and high frequencies are at corners of our fft matrix*)
* **Low pass:** *It lets the low frequency components pass and filters out high frequency component.* Imagine a circle with radius r, centered at center of our fft matrix. Make entries zero, which are outside the circle (Chopping off high frequency components). And now do IDFT to get filtered image back.
```bash
foo@bar:~$ cd FFT/low_pass_filter
foo@bar:~$ gcc main.c -o main
foo@bar:~$ ./main
```
* **High pass:** *It lets the high frequency components pass and filters out low frequency component.* Imagine a circle with radius r, centered at center of our fft matrix. Make entries zero, which are inside the circle (Chopping off low frequency components). And now do IDFT to get filtered image back.
```bash
foo@bar:~$ cd FFT/high_pass_filter
foo@bar:~$ gcc main.c -o main
foo@bar:~$ ./main
```
*In both of the above filters r is taken as input from user.* Note in high pass filter choose small value of r, since most images have large values of low frequency components.
* **Band pass:** *Not implemented but you get the logic*. *It lets a range of frequencies pass and blocks other freqeuncies.* Imagine 2 circles with radius r1 and r2, both centered at center of our fft matrix. Make entries zero, which are outside the ring (letting in only range of frequencies, and chopping off other frequencies). And now do IDFT to get filtered image back.

* Try different images, various values of *r* and experiment :)


---
### Note
* Here 1D FFT that I have implemented, takes sequences which have length of integer powers of 2. Hence image with below property is preferred.
* *width = height = 2^k, where k is positive integer*
* To do FFT of arbitrary sized image, you need pad the image such that it follows above property (*pad with zeros*). And after performing IDFT trim the padded part to get filtered image.
---