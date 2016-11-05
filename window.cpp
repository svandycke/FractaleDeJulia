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


long double update(long double& number){
  return (( (number += 0.00005) < 1. )? number : (number -= 2.));
} 

Vec3b julia(long double i, long double j, complex<long double> c){
  complex<long double> z(i, j);
  int val = 0;
  do{
    z = z * z + c;
    val++;
  }while((val < 255) && (norm(z) < 2));
  return Vec3b(val/2, val/3, val);
}

int main(int argc, char ** argv) {
  Mat img(600, 600, CV_8UC3);//img(cols, rows, flags)
  long double reel(-0.0986), imaginaire(-0.65186);
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  moveWindow("Fractale de julia", 0, 0);
  while(1) {
    complex<long double> c(update(reel), update(imaginaire));
    for(int i = 0; i < img.rows; i++)
      for(int j = 0; j < img.cols; j++)
	img.at<Vec3b>(Point(j, i)) = julia(((long double)i/img.rows) * 2. - 1., ((long double)j/img.cols) * 2. - 1. , c);
    imshow("Fractale de julia", img);
    if((waitKey(10) & 0xFF) == 'q' || (waitKey(10) & 0xFF) == 27){
      exit(-1);
    }
  }
  return 0;
}
