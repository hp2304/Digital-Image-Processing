clc;clear;close all
img = uint8(10.*rand(5,4));
img = double(img);
%img = [1 -1; -2 2; 2 -2];
%img = [4 11 14; 8 7 -2];

[u,s,v] = my_svd(img);
u*s*v'
img
