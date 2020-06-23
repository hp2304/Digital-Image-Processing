clc;clear;close all;

fin=fopen('boat_512_512.raw','r');
I=fread(fin,512*512,'uint8=>uint8'); 
ft_Z=reshape(I,512,512);
ft_Z=ft_Z';
imshow(ft_Z)

noisy = imnoise(ft_Z,'gaussian',0,.1);

figure;
imshow(noisy)

%imwrite(noisy, 'noisy_var_0.01.png');