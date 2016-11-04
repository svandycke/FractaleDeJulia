#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <complex>
using namespace cv;
using namespace std;


Vec3b julia(long double i, long double j, complex<long double> c){
  complex<long double> z(i, j);
  int val = 0;
  do{
    z = z * z + c;
    val++;
  }while((val < 255) && (norm(z) < 2));
  return Vec3b(0, val, 0);
}

int main(int argc, char ** argv) {
  Mat img(600, 600, CV_8UC3);
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  moveWindow("Fractale de julia", 0, 0);
  complex<long double> c(-0.0986, -0.65186);
  for(int i = 0; i < img.rows; i++)
    for(int j = 0; j < img.cols; j++)
      img.at<cv::Vec3b>(cv::Point(i, j)) = julia(((long double)i/img.rows) * 2. - 1., ((long double)j/img.cols) * 2. - 1. , c);
  while(1) {
    imshow("Fractale de julia", img);
    if((waitKey(10) & 0xFF) == 'q' || (waitKey(10) & 0xFF) == 27){
      exit(-1);
    }
  }
  return 0;
}
