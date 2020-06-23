fin=fopen('cam2_128_128.raw','r');
I=fread(fin,128*128,'uint8=>uint8'); 
Z=reshape(I,128,128);
Z=Z';
unique_vals = 0:255;
total_pix = 128*128;


for i=unique_vals
    len = find(i==Z(:));
    prob(i+1) = length(len);
end
prob = prob./total_pix;
[dict, avglen] = huffmandict(unique_vals,prob);