
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


fin=fopen('cam1_64_64.raw','r');
I=fread(fin,64*64,'uint8=>uint8'); 
Z=reshape(I,64,64);
Z=Z';
ft = fftshift(fft2(double(Z)));
ft = padarray(ft, [32,32]);
img = abs(ifft2(ifftshift(ft)));
subplot(1,2,1);
imshow(Z);
subplot(1,2,2);
x=1;
%img = img(x:x+128, x:x+128);
imshow(uint8(img).*3);
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