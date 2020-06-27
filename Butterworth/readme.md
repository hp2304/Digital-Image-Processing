# Problem Statement
Apply Butterworth Filter on image.

## Requirements
* Go through **A6_FFT** first.
* Introductory level knowledge of butterworth filters.

## Procedure and Usage
* As in in procedure of **A6_FFT** get FFT of image. Replace each entry by equation given at [this link](https://www.geeksforgeeks.org/matlab-butterworth-lowpass-filter-in-image-processing/).
* Do Inverse DFT to get filtered image back.

```bash
foo@bar:~$ gcc main.c -lm -lpthread -o main
foo@bar:~$ ./main
```

Cut off frequency and order of butterworth filter will be taken as inputs. Here I have Implemented low pass butterworth filter.

To implement high pass butterworth filter, in equation linked above, term in denominator should be inversed, see [this](https://www.geeksforgeeks.org/matlab-butterworth-highpass-filter-in-image-processing/).

*Try different images, cut off frequencies and order of filter. Experiment !!*