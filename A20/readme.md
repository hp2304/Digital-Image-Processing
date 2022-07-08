# Fun experiment

## Face image matching using Singular value Decomposition

### Requirements
* Matlab
* Good knowledge of Singular value Decomposition.
* Checkout *__img_comp_svd__* folder first.

Here I am using [yalefaces dataset](http://cvc.cs.yale.edu/cvc/projects/yalefaces/yalefaces.html). It contains 165 grayscale images in GIF format of 15 individuals. There are 11 images per subject, one per different facial expression or configuration.

After downloading dataset move some files to parent directory as I have done. These files will be used for evaluation (Test set). And remaining of them will be used as training set.

### Procedure
* Read all training images and make matrix **A** of shape *mxn*. Where m is total number of pixels in input image and n is total number images in training set.
* Do Singular Value Decomposition of matrix A  to get **U** matrix. Google about SVD if you don't know.
* Select first *k* (tunable parameter) columns of matrix U to create our transformation matrix **T** (shape *mxk*).
* Transform all train images to k-dimensional space from n-dimensional space and store it.
* Read test image and apply matrix T to transform out image to k-dimensional vector from n-dimensional vector. 
* Display image for which euclidean distance is minimum b.w. transformed test image vector and transformed train image vector.(**find distance using transformed vectors**).

### Usage
Run *face_recog.m* in matlab. In code you can change k to see results of our face matching program. Basically increasing k (upto n) will give good result.

---
### *Note:*

* I also have implemented function to find SVD (*__my_svd.m__* file) but it's somewhat slow compared to in-built function. You can check it out for knowledge.
---