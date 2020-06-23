%% If H_mat.mat doesn't exist then run this section
clc;close all; clear;

img = imread('cameraman.tif');

%t = linspace(0,1,size(img,1)+1);
t = linspace(0,1,size(img,1)+1);
t(end) = [];
H = zeros(size(img, 1), size(img, 2));
H = double(H);
img = double(img);
H(1,:) = 1;
for i = t
    for p = 0:7
        for val = 2^p:(2^(p+1))-1
            H(val+1, :) = haar_func(p, val-(2^p), t);
        end
    end
end

H = (1/norm(H(:, 1))).*H;

save('H_mat.mat','H');
%% If H_mat.mat exist then run this section
clc;close all; clear;

img = imread('cameraman.tif');
img = double(img);
mat = matfile('H_mat.mat');
H = mat.H;
H_tran = H';
transformed = H*img*transpose(H);
imshow(uint8(transformed));

%{
Basis images

val = (H(3,:))'*(H(3,:));
val = ((255/(max(max(val))-min(min(val)))).*val);
imshow(uint8(val));

%}

%{
Updating transformed matrix and then reconstruct original image

for i=100:256
    for j=100:256
        transformed(i,j) = 0;
    end
end

H_tran = H';
reg = H_tran*transformed*H;
subplot(1,2,1);
imshow(uint8(img));
subplot(1,2,2);
imshow(uint8(reg));
%}

