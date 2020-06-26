# Problem Statement
Read a .raw image file and flip it horizontally/vertically.

## Usage
```bash
foo@bar:~$ gcc horizontal_reverse.c -o hr
foo@bar:~$ ./hr
foo@bar:~$ gcc vertical_reverse.c -o vr
foo@bar:~$ ./vr
```

* Enter .raw filename when asked, also enter width and height of the image. For boat image height and width is 512 (encoded in filename). Also ImageJ can create .raw file from jpg, png, etc. So one can experiment it with their own input files. Output image will be flipped horizontally/vertically and will have different file extension (still raw images), these files can be visulized in ImageJ.