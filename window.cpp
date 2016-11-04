#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

int main(int argc, char ** argv) {

  Mat img(600, 600, CV_8UC3);
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  moveWindow("Fractale de julia", 0, 0);
  //setWindowProperty("Fractale de julia", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  while(1) {
    for(int i = 0; i < img.rows; i++)
      for(int j = 0; j < img.cols; j++)
        img.at<cv::Vec3b>(cv::Point(i, j)) = Vec3b(125, 125, 125);
    imshow("Fractale de julia", img);
    if((waitKey(10) & 0xFF) == 'q'){
      exit(-1);
    }
  }
  return 0;
}
