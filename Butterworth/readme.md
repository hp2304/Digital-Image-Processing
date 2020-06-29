# Problem Statement
Apply Butterworth Filter on image.

## Requirements
* Go through **A6_FFT** first.
* Introductory level knowledge of butterworth filters.

## Procedure and Usage
* As in in procedure of **A6_FFT** get FFT of image. Replace each entry by equation given at slide 71 of **FreqDomFil.pdf** (Butterworth low pass filter).
* Do Inverse DFT to get filtered image back.

```bash
foo@bar:~$ gcc main.c -lm -lpthread -o main
foo@bar:~$ ./main
```

Cut off frequency and order of butterworth filter will be taken as inputs. Here I have Implemented low pass butterworth filter.

To implement high pass butterworth filter, in equation linked above, term in denominator should be inversed, meaning replace *D(u,v)/D_0* by *D_0/D(u,v)* (Take a look at slide 72 of **FreqDomFil.pdf**).

*Try different images, cut off frequencies and order of filter. Experiment !!*