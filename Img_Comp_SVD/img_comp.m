clc;close all;

img = imread('autumn.tif');
img = rgb2gray(img);
img_d = double(img);
%img_d = gpuArray(img_d);
[u,s,v] = svd(img_d);
%[u,s,v] = my_svd(img_d);
rank(double(img))
x = input('Enter number : ');

while x~=0
    new = zeros(size(img));
    for i=1:x
        new = new + s(i,i).*(u(:,i)*(v(:,i))');
    end
    new_u = uint8(new);
    error = sum(sum(abs(new-img_d).^2, 2))
    saved = (numel(img))-(8*x*(size(v,1)+size(u,1)+1))
    figure;
    subplot(1,2,1);
    imshow(new_u);
    title('compressed')
    subplot(1,2,2);
    imshow(img)
    title('original')
    waitforbuttonpress;
    close all;
    x = input('Enter number (0 to exit): ');
end
