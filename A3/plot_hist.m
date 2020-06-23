clc;clear;close all

T = readtable('img_hist.txt','Delimiter',' ','ReadVariableNames',false);
T = table2array(T);
graylevels = T(:, 1);
pixelCount = T(:, 2);
plot(graylevels, pixelCount, 'LineWidth', 1);
saveas(gcf,'histogram.png');