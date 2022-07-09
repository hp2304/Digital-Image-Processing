clc;close all;

img_gray = imread('batman.jpg');
img_gray_d = double(img_gray);
[u,s,v] = svd(img_gray_d);
%[u,s,v] = my_svd(img_gray_d);
rank(double(img_gray_d))
u = single(u);
s = single(s);
v = single(v);
k = input('Enter number : ');

while k~=0
    compressed_img = zeros(size(img_gray_d));
    for i=1:k
        compressed_img = compressed_img + s(i,i).*(u(:,i)*(v(:,i))');
    end
    compressed_img_uint8 = uint8(compressed_img);
    mse = mean((compressed_img-img_gray_d).^2, 'all');
    cr = numel(img_gray) / (k*(size(v,1)+size(u,1)+1));
    figure;
    subplot(1,2,1);
    imshow(compressed_img_uint8);
    title('compressed')
    subplot(1,2,2);
    imshow(img_gray)
    title('original')
    fn = sprintf('batman_k_%d_cr_%.1f_mse_%.0f.png', k, cr, mse);
    imwrite(compressed_img_uint8, fn);
    waitforbuttonpress;
    close all;
    k = input('Enter number (0 to exit): ');
end
