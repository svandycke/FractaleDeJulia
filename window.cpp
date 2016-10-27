#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>
#include <X11/Xlib.h>

int main(int argc, char ** argv) {

  Display* disp = XOpenDisplay(NULL);
  Screen*  scrn = DefaultScreenOfDisplay(disp);
  int height = scrn->height;
  int width  = scrn->width;
  IplImage* img = NULL;
  //CvCapture * capture = NULL;
  CvSize s;
  /* si pas de webcam IplImage* img = cvLoadImage("image.png", CV_LOAD_IMAGE_COLOR); */
  //capture = cvCaptureFromCAM(CV_CAP_ANY);
  s.width = width;
  s.height = height;
  fprintf(stderr, "dimensions du flux %dx%d\n", s.width, s.height);
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  img = cvCreateImage(s, IPL_DEPTH_8U, 1);
  while(1) {
    //cvCvtColor(img, imgG, CV_RGB2GRAY);
    //cvSmooth(imgG, imgG, CV_GAUSSIAN, 15, 15, 0, 0);
    cvShowImage("Fractale de julia", img);
    if((cvWaitKey(10) & 0xFF) == 27)
      break;
  }
  //if(capture)
  //cvReleaseCapture(&capture);
  return 0;
}
