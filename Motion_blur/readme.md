# Problem Statement
Try to recover motion blurred image using inverse filtering.

## Requirements
* Go through **A6_FFT** assignment first.

## Procedure and Usage
* Applying motion blurring on image is just convolving the image with some filter. Just like we do it for edges, we apply filters like sobel, robert, prewitt filters to image to detect edges. Hence motion blurring is just some filter, which can be convolved with image to make it look like motion blurred, sometimes we do observe such cases while we try to capture a photo of moving object with our mobile phone camera.
* So how to get original image back. After we have applied some filter on an image, *given information about the filter apriori*. Well we can do [transposed convolution](https://github.com/naokishibuya/deep-learning/blob/master/python/transposed_convolution.ipynb) or we can utilize a **property of fourier transform**. We will go with second approach. Convolution of two signals is same as multiplying them in frequency domain (*their fourier transformed versions obviously*). 
* Take **blurry_256_256.raw** as input. Which I have generated in matlab by appying a average filter of size 1x21 on cameraman image. Our filter is [1/21, 1/21, ..., 1/21], a 21 dimensional row vector.
* So general idea is to take fourier transform of input image, call it *img_ft*. Then take fourier transform of average filter (zero pad the filter to to have size of input image, where actual values will be on top left), call it *filter_ft*.
* Element-wise divide *img_ft* and *filter_ft*, call it *recovered_ft*. Do **Inverse fourier transform** of *recovered_ft* to get the recovered image back. Visulize *{input image name}.raw_out*.

```bash
foo@bar:~$ gcc main.c -lm -lpthread -o main
foo@bar:~$ ./main
```
Give **blurry_256_256.raw** as input (256 height and width). Then visulize **blurry_256_256.raw_out**, recovered image. Which should look same as original image (*theoretically*), but it's **not**. I don't know why? I did same experimentations in matlab too, resulting image looks same as our C program result. Try to findout what's wrong !!