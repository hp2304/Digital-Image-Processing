clc;close all, clear;
sample_img = imresize(imread('yalefaces/subject1.gif'), 0.4);
nrows = size(sample_img, 1);
ncols = size(sample_img, 2);
cnt = 1;
%for k = 1 : 12
me = zeros(nrows*ncols,1);
me = double(me);
files = dir('yalefaces/');
for file = files'
    if ~(strcmp(file.name, '.') || strcmp(file.name, '..'))
        img = imread(strcat('yalefaces/', file.name));
        img = imresize(img, 0.4);
        A(:, cnt) = img(:);
        me = me + double(img(:));
        cnt = cnt + 1;
    end
end

me = me./(cnt-1);
A = double(A);
me_A = A - repmat(me, [1,(cnt-1)]);
C = (me_A'*me_A);
[v,s] = eig(C);
s=diag(flipud(diag(s)));
v=fliplr(v);
k = 30;
basis_eigenfaces = A*v(:,1:k);
    
for i=1:k
    eigenface = reshape(basis_eigenfaces(:,i),[nrows,ncols]);
    subplot(5,6,i);
    imshow(uint8(eigenface));
end
%waitforbuttonpress;
%close(gcf);
weights = zeros(size(basis_eigenfaces, 2), (cnt-1));


for i=1:(cnt-1)
    weights(:,i) = mldivide(basis_eigenfaces, A(:,i));
    reconstructed_img = reshape(basis_eigenfaces*weights(:,i),[nrows,ncols]);
    %subplot(5,3,i);
    %imshow(uint8(reconstructed_img));
end

x = input('Enter image name (Enter 0 to exit) : ', 's');
while ~strcmp(x,'0')
    %testname = strcat('yalefaces/', x);
    test_img = imread(x);
    test_img = imresize(test_img, 0.4);
    test_img = test_img(:);
    test_img = double(test_img);
    test_weights = mldivide(basis_eigenfaces, test_img);
    
    for j = 1:size(weights, 2)
        sim(j) = norm(weights(:, j) - test_weights);
    end
    [min_val, ind] = min(sim);
    min_val
    figure;
    subplot(1,2,1)
    subimage(uint8(reshape(test_img, [nrows,ncols])))
    title('Entered Image');
    subplot(1,2,2)
    subimage(uint8(reshape(A(:, ind), [nrows,ncols])))
    title('Matched with this Image');
    waitforbuttonpress;
    close all;
    
    x = input('Enter image name (Enter 0 to exit) : ', 's');
end

