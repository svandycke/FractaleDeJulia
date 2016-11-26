
//  to compile : 
//  g++ window.cpp -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core
//  with threads:  -DWITH_THREAD
//  with n thread: -DNB_THREAD=n

#include <stdio.h>
#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <complex>
#include <thread>

using namespace cv;
using namespace std;

#ifndef NB_THREAD
#define NB_THREAD thread::hardware_concurrency() //to get nof cores
#endif

#define _W 1430
#define _H 780

Mat img(_H, _W, CV_8UC3);//img(cols, rows, flags)
complex<long double> c;

long double update(long double& number){
  return (( (number += 0.00005) < 1. )? number : (number -= 2.));
} 

Vec3b julia(long double i, long double j){
  complex<long double> z(i, j);
  int val(0);
  while((val < 255) && (norm(z) < 4)){
    z = z * z + c;
    val++;
  }
  return Vec3b(val, 255, 255);
}

void thread_func(int k){
#ifdef WITH_THREAD
  int i = k * img.rows/NB_THREAD, n = i + (img.rows/NB_THREAD);
#else
  int i = 0, n = img.rows;
#endif
  for(; i < n; i++)
    for(int j(0); j < img.cols; j++){
      img.at<Vec3b>(Point(j, i)) = julia(((long double)i/img.rows) * 2. - 1., ((long double)j/img.cols) * 2. - 1.);
    }
}

int main(int argc, char ** argv) { 
  Mat rgb(_H, _W, CV_8UC3);//img(cols, rows, flags)
  long double reel(0.285), imaginaire(0.013);
  int cnt(0), round_max = ((argc >= 2)? atoi(argv[1]):10);
  int64 t0 , t = 0;
  ofstream log (argc == 3? argv[2]:"Test/Default.txt");
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  moveWindow("Fractale de julia", 0, 0);
  log << "nombre de threads : " << NB_THREAD << endl;
  while(1) {
    c = complex<long double> (update(reel), update(imaginaire));
    t0 = getTickCount()/1000000;
#ifdef WITH_THREAD
    thread * th = new thread[NB_THREAD];
    for(int k(0); k < NB_THREAD; k++) th[k] = thread(thread_func, k);
    for(int k(0); k < NB_THREAD; k++) th[k].join();    
#else
    thread_func(0);
#endif
    t += ((getTickCount()/1000000) - t0);
    cnt++;
    log << "traitement n° " << cnt << endl;
    cvtColor(img, rgb, CV_HSV2RGB);
    imshow("Fractale de julia", rgb);
    if((waitKey(10) & 0xFF) == 'q' || (waitKey(10) & 0xFF) == 27 || cnt >= round_max){
      log << "\ntemps passe = " << (long double)(t/1000.) << " s\n" << endl;
      log << "\ntemps moyen = " << (t/cnt) << " ms\n" << endl;
      log.close();
      return 0;
    }
  }
  log.close();
  return 0;
}
