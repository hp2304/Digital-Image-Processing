
fin=fopen('cam2_128_128.raw_out','r');
I=fread(fin,128*128,'uint8=>uint8'); 
ft_Z=reshape(I,128,128);
ft_Z=ft_Z';
subplot(1,2,1);
imshow(ft_Z);



fin=fopen('cam2_128_128.raw','r');
I=fread(fin,128*128,'uint8=>uint8'); 
Z=reshape(I,128,128);
Z=Z';
%subplot(1,2,1);

hmm = uint8(255*mat2gray(log(1+fftshift(abs(fft2(double(Z)))))));

subplot(1,2,2);
imshow(hmm);

%{
img = imread('cameraman.tif');
img = img(1:2:end, 1:2:end);
imshow(img)
imwrite(img, 'cam2.png');
%}

%{
a=[1 2 3 4; 5 6 7 8; 9 10 11 12; 13 14 15 16];
uint8(abs(fftshift(fft2(a))))
%}