# Problem Statement
Do histogram equalization on input image.

## Requirements
* Read about histogram equalization in **imageEnh.pdf**.

## Basic Idea
* Image might be dark or overly bright. Input image may have histogram concentrated over very small region. Look at **baby_hist1.pdf**. Goal is to do some processing to make the histogram look like **baby_hist2.pdf** (More variation). I think this technique must be used in **HDR** mode we see in our mobile phones, to improve contrast.

## Usage
```bash
foo@bar:~$ gcc enh.c -o enh
foo@bar:~ ./enh
```
* **Personal recommendation** : Give *babyincradle_blue.raw* as input. See it's dimensions in *babyincradle_blue.jpg*. As output *babyincradle_blue.raw_out* will be created. Open both in ImageJ or you can use their jpeg versions *babyincradle_blue.jpg* and *babyincradle_blue_raw_histeq.jpg* for visulization. And Voila !!
* **baby_hist1.pdf** corresponds to the histogram of **babyincradle_blue.jpg** and **baby_hist2.pdf** corresponds to the histogram of **babyincradle_blue_raw_histeq.jpg**.
