# Fun experiment

## Frequency domain filtering using Haar Transform

### Requirements
* Read slides 31 to 41 in **DIP_ImageTransforms.pdf**.
* Matlab

### Usage
* Run haar.m first section and then second section.
* First section calculates haar transformation matrix H using haar function (written in *haar_func.m**). Remember H is *orthonormal* matrix.
* Transformed image **G = H x I x H'**. Where I is input image. Transformed image will be displayed when second section is ran.


### Intuition
* In transformed image, you will observe that top left corner of the image is mostly bright and as we move to bottom right corner, pixels are becoming darker. This shows that image contains mostly low frequency components (sky, clothes of the cameraman, etc.) and very small amount of high frequency components (edges and stuff) are present in image. As we move to right and downward from top left, frequncy in x direction and y direction increases respectively. Here I am talking about cameraman image in matlab.

* Let's move to the reconstruction of original Image, uncomment this code in **haar.m**
```matlab
% Updating transformed matrix and then reconstruct original image
transformed(100:256,100:256) = 0;
    
H_tran = H';
reg = H_tran*transformed*H;
subplot(1,2,1);
imshow(uint8(img));
subplot(1,2,2);
imshow(uint8(reg));
```
* Reconstructed image **I' = H' x G x H** *(Just some matrix manipulation)*, since H is *orthonormal*. Where G is transformed image.

* So where's the *filtering* part? In the above code, actually we applied **low pass filter** by zeroing out high frequency in x and y direction. And still reconstructed and original image looks same, because like image contains mostly low frequency components. Hence zeroing out high frequency components won't matter much.
```matlab
transformed(100:256,100:256) = 0;
```
(here **transformed** in code is our transformed image **G**.)
```matlab
transformed(1:20,1:20) = 0;
```
* Above line will apply **high pass filter** to image. Now the reconstructed image will look significantly different than original image, even though we zero out only 400 values in G. Intuition is same as above.

```matlab
transformed(20:150,20:150) = 0;
```
* Above line will apply **band pass filter** to image. Now the reconstructed image will look somewhat different. Part with edges will be messed up. And parts like sky, coat of cameraman in the image will look same as the original image.

* And like that, if we don't make any changes in G, we will get same image back. Means reconstructed and original image will be same.

* Change input image and cut off frequencies and observe the differences. Have fun :)