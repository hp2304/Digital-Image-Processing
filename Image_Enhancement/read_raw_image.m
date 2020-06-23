fin=fopen('boat_512_512.raw','r');
I=fread(fin,512*512,'uint8=>uint8'); 
Z=reshape(I,512,512);
Z=Z';
imshow(Z);