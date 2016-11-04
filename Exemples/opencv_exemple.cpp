/* http://docs.opencv.org/
 
 SOUS MAC :
 port install opencv
 
 g++ -Wall opencv_exempleCPP.cpp -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -I/opt/local/include -L/opt/local/lib -std=c++11
 
 SOUS LINUX :
 sudo apt-get install libopencv-core-dev
 sudo apt-get install libopencv-photo-dev
 sudo apt-get install libopencv-contrib-dev
 sudo apt-get install libhighgui-dev
 
 g++ -Wall opencv_exempleCPP.cpp -lopencv_core -lopencv_highgui -lopencv_imgproc -std=c++11
 */
#include <opencv2/opencv.hpp>
#define IMG_W 800
#define IMG_H 600

int main(int argc, char * argv[]) {
	// un nouvel objet image (ordre des couleurs : bleu/vert/rouge)
    cv::Mat newImg(IMG_W, IMG_H, CV_8UC3);
    // déclaration d'une couleur
    cv::Vec3b white(255, 255, 255);
    // coordonnées du point
    int x = 50;
    int y = 100;
    // dessine d'un pixel
    newImg.at<cv::Vec3b>(cv::Point(x, y)) = white;
    // interaction avec l'utilisateur
    // on attend 30 seconde une touche, au bout de 30 secondes on exécute
    // quand même la boule
    // key = -1 indique qu'aucune touche n'a été enfoncée
    while(int key = cvWaitKey(30)) {
    	switch (key) {
    		case 'r':
    			y--;
    			break;
    		case 'c':
    			y++;
    			break;
    		case 'd':
    			x--;
    			break;
    		case 'f':
    			x++;
    			break;
    		default:
    			break;
    	}
    	if (key == 'q')
    		break;
    	newImg.at<cv::Vec3b>(cv::Point(x, y)) = white;
    	imshow("image", newImg); // affiche l'image
    }
    imwrite("image.jpg", newImg); // sauve une copie de l'image
	cvDestroyWindow("image"); // ferme la fenêtre

    return 0;
}
