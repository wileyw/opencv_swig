#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include "test_function.hpp"

using namespace std;
using namespace cv;

string cascadeName = "haarcascade_frontalface_alt.xml";

vector<FaceLocation> detectFaces(vector<char>& jpg, double scale)
{
    vector<FaceLocation> faceLocations;
    //Mat img = imdecode(jpg, CV_LOAD_IMAGE_COLOR);
    Mat img;
    img = imread("face.jpg", CV_LOAD_IMAGE_COLOR);
    if ( img.data = NULL) {
        cerr << "Image loading error." << endl;
        return faceLocations;
    }
    cout << img.rows << endl;
    cout << img.cols << endl;
    cout << img.total() << endl;

    cv::imwrite("test.jpg", img);
    cout << "**************write here" << endl;

    CascadeClassifier cascade;
    cout << "**************here" << endl;
    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return faceLocations;
    }
    cout << "**************loaded here" << endl;


    int i = 0;
    double t = 0;
    vector<Rect> faces, faces2;
    const static Scalar colors[] =  { CV_RGB(0,0,255),
        CV_RGB(0,128,255),
        CV_RGB(0,255,255),
        CV_RGB(0,255,0),
        CV_RGB(255,128,0),
        CV_RGB(255,255,0),
        CV_RGB(255,0,0),
        CV_RGB(255,0,255)} ;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
    cout << "**************here" << endl;
    
    cvtColor( img, gray, CV_BGR2GRAY );
    cout << "here" << endl;
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );
    cout << "here" << endl;

    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(30, 30) );
    cout << "here" << endl;
    for( vector<Rect>::const_iterator r = faces.begin(); r != faces.end(); r++, i++ )
    {
        cout << (*r) << endl;
        Mat smallImgROI;
        Point center;
        Scalar color = colors[i%8];
        int radius;

        double aspect_ratio = (double)r->width/r->height;
        if( 0.75 < aspect_ratio && aspect_ratio < 1.3 )
        {
            center.x = cvRound((r->x + r->width*0.5)*scale);
            center.y = cvRound((r->y + r->height*0.5)*scale);
            radius = cvRound((r->width + r->height)*0.25*scale);
            circle( img, center, radius, color, 3, 8, 0 );
        }
        else
            rectangle( img, cvPoint(cvRound(r->x*scale), cvRound(r->y*scale)),
                       cvPoint(cvRound((r->x + r->width-1)*scale), cvRound((r->y + r->height-1)*scale)),
                       color, 3, 8, 0);

    }
    return faceLocations;
}
