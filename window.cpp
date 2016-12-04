/*!\file windows.c
 *
 * \brief Programmation Temps Réel : Fractales de Julia
 *
 * \author Abdellatif BENNANI & Steve VANDYCKE
 * \date December 04 2016
 */

/*!\
 * Pour compiler sans thread
 * g++ window.cpp -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core

 * Pour compiler avec threads 
 * g++ window.cpp -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -DWITH_THREAD

 * Pour compiler avec N threads 
 * g++ window.cpp -std=c++11 -lopencv_highgui -lopencv_imgproc -lopencv_core -DWITH_THREAD -DNB_THREAD=n

 * Il est possible de préciser la taille en largeur et hauteur de la fenêtre avec les options :
 * -D_H et -D_W (Exemple : -D_H=1000 -D_W=1000)
 */

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

#ifndef _W
#define _W 400
#endif
#ifndef _H
#define _H 400
#endif

/*!\brief Définition des variables */
Mat img(_H, _W, CV_8UC3);//img(cols, rows, flags)
complex<long double> c;
float coef = 1.;
bool clicked = false;
Point _offset = Point(0, 0);

/*!\brief Fonction qui permet d'incrémenter l nombre complexe
 * \param number Nombre complexe à incrémenter
*/
long double update(long double& number){
  return (( (number += 0.00005) < 1. )? number : (number -= 2.));
} 

/*!\brief Fonction qui calcul la valeur de chaque pixel à afficher avec l'utilisation de la suite de Julia
 * \param i La partie réelle qui dépend de la largeur de l'écran
 * \param j La partie imaginaire qui dépend de la hauteur de l'écran
*/
Vec3b julia(long double i, long double j){
  complex<long double> z(i, j);
  int val(0);
  while((val < 255) && (norm(z) < 4)){
    z = z * z + c;
    val++;
  }
  return Vec3b(255 - val, 255, 255);
}

/*!\brief Fonction threads
 * \param k Rang du thread
*/
void thread_func(int k){
#ifdef WITH_THREAD
  int i = ceil(k * (float)img.rows/NB_THREAD), n = ceil(k * (float)img.rows/NB_THREAD + (float)img.rows/NB_THREAD);
#else
  int i = 0, n = img.rows;
#endif
  for(; i < n; i++)
    for(int j(0); j < img.cols; j++){
      img.at<Vec3b>(Point(j, i)) = julia(((long double)(i + _offset.x)/(coef * img.rows)) * 2. - 1., ((long double)(j + _offset.y)/(coef * img.cols)) * 2. - 1.);
    }
}

/*!\brief Fonction qui gère l'évenement de la souris
 * \param evt Evenement
 * \param x Position x
 * \param y Position y
 * \param flags Non utilisé
 * \param param C'est le point qui reçoit les coordonnées du clique
*/
void mouseEvent(int evt, int x, int y, int flags, void* param) {
  Point* pix = (Point*) param;
  if(evt == CV_EVENT_LBUTTONUP)
    {
      *pix = Point(x, y);
      clicked = true;
    }
}

/*!\brief Fonction principale (Main)
 * \param argc Nombre de paramètres 
 * \param argv Tableau de paramètres (1er paramètre : Nombre d'itération, par défaut : 10 / 2ème paramètre : Nom du fichier de sauvegarde des logs, par défaut : Test/Defaut.txt)
*/
int main(int argc, char ** argv) { 
  Mat rgb(_H, _W, CV_8UC3);//img(cols, rows, flags)
  Point pt;
  long double reel(0.285), imaginaire(0.013);
  int cnt(0), round_max = ((argc >= 2)? atoi(argv[1]):10);
  int64 t0 , t = 0;
  ofstream log (argc == 3? argv[2]:"Test/Default.txt", ios_base::app);
  cvNamedWindow("Fractale de julia", CV_WINDOW_AUTOSIZE);
  moveWindow("Fractale de julia", 0, 0);
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
    //t += ((getTickCount()/1000000) - t0);
    cnt++;
    cvtColor(img, rgb, CV_HSV2RGB);
    setMouseCallback("Fractale de julia", mouseEvent, &pt);
    if(clicked) {
      _offset += Point((pt.y - _H/2), (pt.x - _W/2)); 
      coef += 0.6;
      circle(rgb, pt, 5, Scalar(0, 0, 100), 1, CV_AA);
      circle(rgb, pt, 10, Scalar(0, 0, 150), 1, CV_AA);
      circle(rgb, pt, 15, Scalar(0, 0, 200), 1, CV_AA);
      circle(rgb, pt, 20, Scalar(0, 0, 255), 1, CV_AA);
      clicked = false;
    }
    imshow("Fractale de julia", rgb);
    t += ((getTickCount()/1000000) - t0);
    if((waitKey(10) & 0xFF) == 'd') coef -= 0.6;
    if((waitKey(10) & 0xFF) == 'r') {coef = 1.0; _offset = Point(0, 0);}
    if((waitKey(10) & 0xFF) == 'q' || (waitKey(10) & 0xFF) == 27 || cnt >= round_max){

    #ifdef WITH_THREAD
      log << NB_THREAD;   
    #else
      log << "Sans thread"; 
    #endif

   log << ";" << (long double)(t/1000.) << ";" << (t/cnt) << "\n";
   log.close();
    
    return 0;
    }
  }
  log.close();
  return 0;
}
