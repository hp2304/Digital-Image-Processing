clc;close all, clear;

height = 150;
width = 150;

img_cnt = 0;
for k_indices = 1 : 15
    dir_path = sprintf("train/%d", k_indices);
    for file_details = dir(dir_path)'
        if file_details.isdir == 0
            filepath = sprintf("train/%d/%s", k_indices, file_details.name);
            img = imread(filepath);
            img = imresize(img, [height, width]);

            img_cnt = img_cnt + 1;
            data(:, img_cnt) = img(:);
        end
    end
end

data = double(data);

data_norm = normalize(data, 2);
C = (data_norm'*data_norm);
[V,S] = eig(C);
S = diag(flipud(diag(S)));
V = fliplr(V);
r = 50;
eigen_faces = data*V(:,1:r);
eigen_faces_norm = data_norm*V(:,1:r);
    
f = figure();
f.WindowState = 'maximized';
for i=1:r
    eigen_face = reshape(eigen_faces(:,i),[height,width]);
    subplot(5,10,i);
    imshow(uint8(eigen_face));
end
plot_fp = "results/eigenfaces.jpg";
saveas(f, plot_fp);
waitforbuttonpress;
close(f);

plot_img = imread(plot_fp);
imwrite(plot_img(100: 1420, 360:2750), plot_fp);

train_embeddings = zeros(r, img_cnt);


for i=1:img_cnt
    train_embeddings(:,i) = mldivide(eigen_faces_norm, data_norm(:,i));
end

k = 5;

cnt = 0;
for testfile_details = dir("test")'
    if testfile_details.isdir == 1
        continue;
    end
    cnt = cnt + 1;
    test_fp = sprintf("test/%s", testfile_details.name);
    test_img = imread(test_fp);
    test_img = imresize(test_img, [height, width]);
    test_img_v = double(test_img(:));

    test_img_v_norm = (test_img_v - mean(data, 2)) ./ std(data, 0, 2);
    test_embeddings = mldivide(eigen_faces_norm, test_img_v_norm);
    
    dists = sqrt(sum((train_embeddings-test_embeddings).^2, 1));
    [k_min_dists, k_indices] = mink(dists, k);
    
    f=figure();
    f.WindowState = 'maximized';
    subplot(1, k + 1, 1)
    imshow(uint8(test_img));
    title('Query Image');
    for idx=1:k
        subplot(1, k + 1, idx + 1)
        imshow(uint8(reshape(data(:, k_indices(idx)), [height, width])));
        title(sprintf('distance: %f', k_min_dists(idx)));
    end
    plot_fp = sprintf("results/%d.jpg", cnt);
    saveas(f, plot_fp);
    waitforbuttonpress;
    close all;

    plot_img = imread(plot_fp);
    imwrite(plot_img(540: 940, 350:2750), plot_fp);
end

