# Problem Statement
Implement Adaptive Filtering to Remove Noise from image.

## Procedure
* Here input is noisy image and we want filtered image (noise removal) back.
* Take a 4x4 window (You can change this size in code), put it on top left portion of image. Find mean and variance of those 16 values call it *mu* and *var* respectively.
* Take a parameter *noise_var* (input parameter), meant as *variance of noise*. 
* Replace each entry using below equation,

*new_value = old_value - ( ( ( noise_var / var ) x ( old_value - mu ) )*.

* Slide the window over the whole image (with stride of 1), to get the filtered image back.
* Tune *noise_var* parameter. For some value of *noise_var*, we will get best filtered image, meaning noise will be removed significantly.


## Usage
```bash
foo@bar:~$ gcc main.c -o main
foo@bar:~$ ./main
```
* Enter image details, then *noise_var* as input. Go with *noisy_var_250.raw* (width and height is 512), enter 250 as *noise_var*. Visulize *noisy_var_250.raw_out*. Now try different values of *noise_var* (other than 250) and visulize *noisy_var_250.raw_out*.