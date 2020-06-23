
fin=fopen('cam1_64_64.raw_out','r');
I=fread(fin,128*128,'uint8=>uint8'); 
ft_Z=reshape(I,128,128);
ft_Z=ft_Z';
subplot(1,2,1);
imshow(ft_Z);

%{
for i=1:128
    some(i,:) = fft(Z(i,:));
end
some = transpose(some);
a=fft(some(3,:));
%}


fin=fopen('boat_512_512.raw','r');
I=fread(fin,512*512,'uint8=>uint8'); 
Z=reshape(I,512,512);
Z=Z';
a=dct2(double(Z));
Z_new = padarray(Z, [512-300, 512-255], 0, 'post');
%subplot(1,2,1);
a=ifft2(fft2(double(Z)));
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