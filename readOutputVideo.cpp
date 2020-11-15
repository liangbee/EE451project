#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/objdetect/objdetect.hpp>
#include <math.h>
#include <omp.h> 

using namespace std;
using namespace cv;

int main( int argc, char** argv ) {

  VideoCapture cap("out_canny.mp4");

  if(!cap.isOpened()){
    cout << "Error opening video" << endl;
    return -1;
  }

  while(1){
    Mat frame;
    Mat frameGrey;
    Mat frameBlurred;
    Mat frameCanny;

    cap >> frame;

    if(frame.empty()) 
      break;
    namedWindow("frame", CV_WINDOW_AUTOSIZE);
    imshow("frame", frame);

    char c=(char) waitKey(25);
    if(c==27)
      break;
  }
  
  cap.release();
  destroyAllWindows();
  return 0;
}
