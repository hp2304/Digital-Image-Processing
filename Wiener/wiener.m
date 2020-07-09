clc;clear;close all;
I = im2double(imread('cameraman.tif'));
imshow(I);
title('Original Image');

LEN = 21;
THETA = 0;
PSF = fspecial('motion', LEN, THETA);
blurred = imfilter(I, PSF, 'conv', 'replicate');
figure, imshow(blurred);

noise_mean = 0;
noise_var = 0.001;
blurred_noisy = imnoise(blurred, 'gaussian', noise_mean, noise_var);
figure, imshow(blurred_noisy)
imwrite(blurred_noisy, 'degraded.png')
title('Simulate Blur and Noise')


estimated_nsr = 0;
wnr2 = deconvwnr(blurred_noisy, PSF, estimated_nsr);
figure, imshow(wnr2)
title('Restoration of Blurred, Noisy Image Using NSR = 0')


estimated_nsr = noise_var / var(I(:));
wnr3 = deconvwnr(blurred_noisy, PSF, estimated_nsr);
figure, imshow(wnr3)
title('Restoration of Blurred, Noisy Image Using Estimated NSR');
