# tennis-court-detection
[![Build
Status](https://travis-ci.com/gchlebus/tennis-court-detection.svg?branch=master)](https://travis-ci.com/gchlebus/tennis-court-detection)
[![License](https://img.shields.io/badge/License-BSD%203--Clause-blue.svg)](https://opensource.org/licenses/BSD-3-Clause)

Fully automatic algorithm for tennis court line detection. Implementation based on Farin
D. et al. "Robust Camera Calibration for Sports Videos using Court Models", *Storage and
Retrieval Methods and Applications for Multimedia 2004*, 2003.

![AlgorithmResult](tennis-court-detection.png)
![AlgorithmResult2](pickleball-court-detection.png)

# Installation instructions

```
git clone https://github.com/gchlebus/tennis-court-detection.git
cd tennis-court-detection
mkdir build && cd build
conan install .. --build missing
cmake ..
cmake --build .
```

# Usage

The detection algorithm is started for the middle frame of the input video file (in avi
format).

```
Usage: ./detect video_path output_path seconds
       video_path:  path to an input avi file.
       output_path: path to an output file where the xy court point coordinates will be written.
       seconds: time at which the test frame will be taken.  
This will take in a video, find the one frame at 'seconds' seconds, and run the algo on it.
Typical time is around one minute on a MacBook Pro.
Does not run in real time on all frames... i guess we are assuming that the camera is still for the duration of the video.
Will fail sometimes when there is alot of other white stuff in the scene, like big text.

```

## Output file

The output file contains 2 parts: image domain points and orthogonal domain points.  There are 14 points in each part that describe the pickleball court, one point per line. The XY coordinates are separated by a comma.  The points are in the following order:

```
1.  Intersection of the upper base line with the left side line
2.  Intersection of the lower base line with the left side line
3.  Intersection of the lower base line with the right side line
4.  Intersection of the upper base line with the right side line
5.  Intersection of the upper service line with the left side line
6.  Intersection of the lower service line with the left side line
7.  Intersection of the lower service line with the right side line
8.  Intersection of the upper service line with the right side line
9.  Intersection of the upper base line with center service line
10. Intersection of the lower base line with the center service line
11. Intersection of the upper service line with the center service line
12. Intersection of the lower service line with the center service line
13. Intersection of the left side line with the net line
14. Intersection of the right side with the net line
```
The analyzed frame is put out on the current directory called testframe.png
