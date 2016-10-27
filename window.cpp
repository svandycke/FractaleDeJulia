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

  Mat img;
  cvNamedWindow("Fractale de julia", CV_WINDOW_NORMAL);
  setWindowProperty("Fractale de julia", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
  while(1) {
    imshow("Fractale de julia", img);
    if((waitKey(10) & 0xFF) == 'q'){
      exit(-1);
    }
  }
  return 0;
}
