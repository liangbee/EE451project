#include <iostream>
#include <bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <chrono>
#include <math.h>
#include <omp.h> 

using namespace std;
using namespace std::chrono;
using namespace cv;

int main( int argc, char** argv ) {

  VideoCapture cap("dat/test_video.mp4");
  // Mat cap;
  // cap = cv::imread("dat/image_0002_1024.jpg" ,cv::IMREAD_COLOR);

  // if(!cap.data){
  //   cout << "Error opening " << endl;
  //   return -1;
  // }

  namedWindow("frameCanny", CV_WINDOW_AUTOSIZE);
  namedWindow("frameBlurred", CV_WINDOW_AUTOSIZE);
  namedWindow("frame", CV_WINDOW_AUTOSIZE);

  // int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
  // int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
  // int ex = static_cast<int>(cap.get(CAP_PROP_FOURCC));
  // int fps = cap.get(CAP_PROP_FPS);
  // Size size = Size(frame_width, frame_height);
  // cout << frame_width << ", "<< frame_height << ", fps:" << fps << endl;

  // VideoWriter video("dat/temp.mp4", ex, cap.get(CAP_PROP_FPS),size,false);

  auto start = high_resolution_clock::now();
  
  // while(1){
    Mat frame;
    Mat frameGrey;
    Mat frameBlurred;
    Mat frameCanny;

    cap >> frame;

    cvtColor(frame, frameGrey, CV_RGB2GRAY);
    GaussianBlur(frameGrey, frameBlurred, Size(5, 5), 0);
    Canny(frameBlurred, frameCanny, 25,100);

    //video.write(frameCanny);
    // char c=(char) waitKey(1);
    // if(c==27)
    //   break;
  //}
  auto stop = high_resolution_clock::now(); 

  imshow("frameCanny", frameCanny);
  imshow("frameBlurred", frameBlurred);
  imshow("frame", frame);

  imwrite("dat/out/lane_canny.bmp", frameCanny);
  imwrite("dat/out/lane_blurred.bmp", frameBlurred);
  imwrite("dat/out/lane.bmp", frame);


  auto duration = duration_cast<microseconds>(stop - start); 
  cout << "Serial time: " << duration.count() << "us " << endl;

  cap.release();
  //video.release();
  destroyAllWindows();

  // cv::Mat image;
  // image = cv::imread("test.png" ,cv::IMREAD_COLOR);
  
  // if(! image.data ) {
  //     std::cout <<  "Image not found or unable to open" << std::endl ;
  //     return -1;
  //   }
  
  // cv::namedWindow( "Techawarey:OpenCV Test Program", cv::WINDOW_AUTOSIZE );
  // cv::imshow( "Techawarey:OpenCV Test Program", image );
  
  // cv::waitKey(0);
  return 0;
}
