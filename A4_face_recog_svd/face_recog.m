%% Sec 1 : Run this section to create .mat files
clc;close all, clear;
sample_img = imresize(imread('yalefaces/subject1.gif'), 0.4);
nrows = size(sample_img, 1);
ncols = size(sample_img, 2);
%cnt = 1;
%for k = 1 : 12
for k = 1 : 15
    %filename = strcat(strcat('dataset/img', num2str(k)), '.jpg');
    filename = strcat(strcat('yalefaces/subject', num2str(k)), '.gif');
    img = imread(filename);
    %img = rgb2gray(img);
    img = imresize(img, 0.4);
    A(:, k) = img(:);
    %cnt = cnt+1;
end

A = double(A);
rank_A = rank(A);
[u,s,v] = my_svd(A);
co_ords = transpose(A)*u(:, 1:rank_A);


%{
imp_vars = [nrows, ncols, rank_A];
save('face_co_ordinates.mat','co_ords');
save('u_matrix.mat','u');
save('imp_vars.mat', 'imp_vars');
save('a.mat','A');
%}
%% Sec 2 : Always run this when above .mat are present in PWD
%clc;close all, clear;
%{
mat1 = matfile('face_co_ordinates.mat');
co_ords = mat1.co_ords;
%mat2 = matfile('u_matrix.mat');
%u = mat2.u;
val = matfile('imp_vars.mat');
imp_vars = val.imp_vars;
nrows = imp_vars(1);
ncols = imp_vars(2);
rank_A = imp_vars(3);
mat = matfile('a.mat');
A = mat.A;
%}
x = input('Enter image name (Enter 0 to exit) : ', 's');
while ~strcmp(x,'0')
    %testname = strcat('dataset/', x);
    %testname = strcat('yalefaces/', x);
    testname = x;
    test_img = imread(testname);
    %test_img = rgb2gray(test_img);
    test_img = imresize(test_img, 0.4);
    test_img = test_img(:);
    test_img = double(test_img);
    test_coords = transpose(test_img)*u(:,1:rank_A);
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
    subimage(uint8(reshape(test_img, [nrows,ncols])))
    title('Entered Image');
    subplot(1,2,2)
    subimage(uint8(reshape(A(:, ind), [nrows,ncols])))
    title('Matched with this Image');
    waitforbuttonpress;
    close all;
    %else
     %   'Didnt find any match ...'
    %end
    x = input('Enter image name (Enter 0 to exit) : ', 's');
end
%% 
