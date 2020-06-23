fin=fopen('boat_512_512.raw','r');
I=fread(fin,512*512,'uint8=>uint8'); 
Z=reshape(I,512,512);
Z=Z';
k=imshow(Z)
[pixelCountsG, grayLevelsG] = imhist(Z);
plot(grayLevelsG, pixelCountsG, 'LineWidth', 2);