# Fun experiment

## Face matching using Principal Component Analysis

### Requirements
* Go through *__img_comp_svd__* and *__A4_face_recog_svd__* first.
* Matlab
* Good knowledge of Eigen Value Decomposition and Principal Component Analysis.

Here I am using [yalefaces dataset](http://cvc.cs.yale.edu/cvc/projects/yalefaces/yalefaces.html). It contains 165 grayscale images in GIF format of 15 individuals. There are 11 images per subject, one per different facial expression or configuration.

After downloading dataset move some files to parent directory as I have done. These files will be used for evaluation (Test set). And remaining of them will be used as training set.

### Basic Idea
* Read all training images and make matrix **A** of shape *mxn*. Where m is total number of pixels in input image and n is total number images in training set.
* Do feature Normalization on A. (Subtract mean and divide by std. deviation)
* Find *C = A'xA*. C is called covariance matrix. Hence C is of shape *nxn*. 
* Do Eigen Value Decomposition of matrix C to get **S and V** matrix. Columns of V(shape *nxn*) contains eigenvectors. And S contains eigenvalues corresponding to eigenvectors.
* Select first *k* (tunable parameter) columns of matrix V to create our transformation matrix **T** (shape *nxk*). And apply this matrix to A (before the normalization step) to get eigen faces. These eigen faces act as basis of our dataset. We can represent any face as linear combination of these eigen faces. These weights can be found using **Ax = b** where x is weights we want to find, A is eigen faces and b is the image from our dataset. Now onwards now we represent every example in our dataset as some set (k) of  weights.
* Read test image find weights for that image as shown in above step.
* Display image for which euclidean distance is minimum b.w. weights of test image and weights of train image (among many images).

## Usage
* Run **my_pca.m**. First, all 15 eigenfaces will be displayed (I am taking **k=15**, you can change it in the code. Also you have to change code for displaying the eigenfaces if you change k). After that try any test image and it will display closest matched face.