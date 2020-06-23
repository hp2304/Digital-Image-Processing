clc;clear;close all;
%{
num_samples = input('Enter number of samples per second : ');
func = @(k) 5 + (2*cos(((2*pi*k)/(num_samples))-(pi/2))) + (3*cos(4*pi*(k/num_samples)));

x_vals = 0:num_samples-1;

y_vals = func(x_vals);
%}
img = imread('cameraman.tif');
img = double(img);
basis_mat = create_basis(size(img,1));
out = basis_mat*img*basis_mat;
imshow(uint8(real(out)));


%frq = basis_mat*y_vals';
%{
close all; clear all;

img   = imread('cameraman.tif');
imshow(img)
%img   = fftshift(img);
F     = fft2(img);

F = real(F); % Get the magnitude
%F = log(F+1); % Use log, for perceptual scaling, and +1 since log(0) is undefined
%F = mat2gray(F); % Use mat2gray to scale the image between 0 and 1

imshow(F,[]); % Display the result
%}