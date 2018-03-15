# CameraCalibration

### Computer Vision Project 1
- Calibrates camera based on a given set of 3D and 2D coordinates of the calibration rig image.

### Issues
- Need to normalize the projection matrix by the normal of the third row of the rotation matrix
- Need to divide the homogeneous reprojected points by the scale factor to get the 2D image coordinates of the reprojected points

### Dependencies
- Matrix.cpp (https://github.com/akalicki/matrix/blob/master/dist/matrix.cpp)
- Matrix.h (https://github.com/akalicki/matrix/blob/master/dist/matrix.h)

### Disclaimer
- Matrix class by Github user "akalicki"
