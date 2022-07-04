# Image Histograms

## Problem Statement
Read RAW image file and store it's histogram in .txt file

## Usage
```bash
foo@bar:~$ gcc a4.c -o a4
foo@bar:~$ ./a4
```

Basically this program just stores the **histogram** of input image in *img_hist.txt* file. It can be visualized with **gnuplot** and can be exported as an image.

```bash
gnuplot> plot 'img_hist.txt' with linespoints linewidth 2
```

## Results

| **Input Image** | ![](../A3/boat_512_512.jpg) |
| ----------- | --------------------- |
| **Histogram** | ![](boat_hist.png)|
