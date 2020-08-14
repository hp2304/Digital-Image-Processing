clc;clear;
img = im2double(imread('office_2.jpg'));
if size(img, 3) == 3
    img = rgb2gray(img);
end
img_copy = img;
img = log(1 + img);
nb_rows = size(img,1);
nb_cols = size(img,2);
img_ft = fft2(img);

while 1
    sigma = input('Enter sigma: ');
    if sigma == 0
        break
    end

    [X, Y] = meshgrid(1:nb_cols,1:nb_rows);
    c_x = ceil(nb_cols/2);
    c_y = ceil(nb_rows/2);
    highpass_fr = exp(-((X - c_x).^2 + (Y - c_y).^2)./(2*sigma.^2));
    highpass_fr = 1 - highpass_fr;
    highpass_fr = fftshift(highpass_fr);
    highpass_fr = repmat(highpass_fr, 1, 1, size(img, 3));

    out = real(ifft2(highpass_fr.*img_ft));
    out = exp(out) - 1;

    imshowpair(img_copy, out, 'montage')
end
close all;
