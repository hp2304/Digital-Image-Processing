clc;close all, clear;
sample_img = imresize(imread('yalefaces/subject1.gif'), 0.4);
nrows = size(sample_img, 1);
ncols = size(sample_img, 2);
%{
for k = 1 : 15
    %filename = strcat(strcat('dataset/img', num2str(k)), '.jpg');
    filename = strcat(strcat('yalefaces/subject', num2str(k)), '.gif');
    img = imread(filename);
    %img = rgb2gray(img);
    img = imresize(img, 0.4);
    A(:, k) = img(:);
    %cnt = cnt+1;
end
%}
files = dir('yalefaces/');
cnt=1;
for file = files'
    if ~(strcmp(file.name, '.') || strcmp(file.name, '..'))
        img = imread(strcat('yalefaces/', file.name));
        img = imresize(img, 0.4);
        A(:, cnt) = img(:);
        cnt = cnt + 1;
    end
end

A = double(A);
A_copy = A;
%data_mean = mean(A);
%data_dev = std(A);
% A = (A-data_mean)/data_dev;
rank_A = rank(A);
%[u,s,v] = my_svd(A);
[u,s,v] = svd(A);
k=rank_A;
co_ords = transpose(A)*u(:, 1:k);

x = input('Enter image name (Enter 0 to exit) : ', 's');
while ~strcmp(x,'0')
    %testname = strcat('dataset/', x);
    test_img = imread(x);
    %test_img = rgb2gray(test_img);
    test_img = imresize(test_img, 0.4);
    test_img = test_img(:);
    test_img_copy = test_img;
    test_img = double(test_img);
    %test_img = (test_img - mean(test_img))/std(test_img);
    test_coords = transpose(test_img)*u(:,1:k);
    %{
    mean_coords = sum(co_ords, 1);
    q = zeros(size(co_ords, 2), size(co_ords, 2));
    for i = 1:size(co_ords, 1)
        q = q + (transpose(co_ords(1, :)-mean_coords)*(co_ords(1, :)-mean_coords));
    end
    q = q.*(1/(size(co_ords, 1)-1));
    for j = 1:size(co_ords, 1)
        sim(j) = ((co_ords(j, :)-test_coords)*(q)*(transpose(co_ords(j, :) - test_coords))).^(0.5);
    end
    %}
    for j = 1:size(co_ords, 1)
        sim(j) = norm(co_ords(j, :) - test_coords);
    end
    [min_val, ind] = min(sim);
    min_val
    %if min_val < 5000
    figure;
    subplot(1,2,1)
    subimage(uint8(reshape(test_img_copy, [nrows,ncols])))
    title('Entered Image');
    subplot(1,2,2)
    pred = uint8(reshape(A_copy(:, ind), [nrows,ncols]));
    subimage(pred)
    title('Matched with this Image');
    waitforbuttonpress;
    close all;
    %else
     %   'Didnt find any match ...'
    %end
    x = input('Enter image name (Enter 0 to exit) : ', 's');
end