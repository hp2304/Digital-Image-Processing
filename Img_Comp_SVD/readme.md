# Fun experiment

## Image compression using Singular value Decomposition

### Requirements
* Matlab
* Good knowledge of Singular value Decomposition.

Check out *__svd_info.pdf__* to read about SVD and some intersting results of this excercise.

### Procedure
* Read Image in matrix A (*mxn*).
* Find U (*mxm*), S (*mxn*) and V (*nxn*) matrices by doing SVD of A.
* Generate comressed image. (see eq. on slide *16* of *__DIP_ImageTransforms.pdf__* to know how to do that). In that slide r is tunable parameter, u_i and v_i is i-th column of matrix U and V respectively.

 So basically **compressed image is just weighted sum of outer product of columns of matrix U and V**. Increase r to get good quality. Summing up, there will be total r matrices, created from outer product of u_i and v_i. Each of them will be weighed by sigma_i (S[i,i] called singular value) and then added together to get compressed image.

 ### Compression ratio
 * So actually while storing compressed image. One will store U, S and V values. And from them compressed image will be generated.
 * Compressd image size is *8x(mxr)x(r)x(nxr)*. 8 because double takes 8 bytes in matlab, (mxr) is for first r columns of U, r is for first r singular values and (nxr) is for first r columns of V.

**Compression ratio = original image size / compressed image size**

 So when r increases compression ratio decreases.

 Run *__img_comp.m__* in matlab. Change image file in the code to experiment with other images. Input r value when asked "Enter Number: ". Larger value of r will result in good quality of compressed image. Change input image and r value and experiment :)
