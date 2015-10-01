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
    Mat img = imdecode(jpg, CV_LOAD_IMAGE_COLOR);
    if ( img.data == NULL) {
        cerr << "Image loading error." << endl;
        return faceLocations;
    }

    CascadeClassifier cascade;
    if( !cascade.load( cascadeName ) )
    {
        cerr << "ERROR: Could not load classifier cascade" << endl;
        return faceLocations;
    }

    int i = 0;
    double t = 0;
    vector<Rect> faces;
    Mat gray, smallImg( cvRound (img.rows/scale), cvRound(img.cols/scale), CV_8UC1 );
    
    cvtColor( img, gray, CV_BGR2GRAY );
    resize( gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR );
    equalizeHist( smallImg, smallImg );

    cascade.detectMultiScale( smallImg, faces,
        1.1, 2, 0
        //|CV_HAAR_FIND_BIGGEST_OBJECT
        //|CV_HAAR_DO_ROUGH_SEARCH
        |CV_HAAR_SCALE_IMAGE
        ,
        Size(30, 30) );
    faceLocations.resize(faces.size());
    for( int i = 0; i < faces.size(); i++)
    {
        faceLocations[i].x = faces[i].x;
        faceLocations[i].y = faces[i].y;
        faceLocations[i].width = faces[i].width;
        faceLocations[i].height = faces[i].height;
    }
    return faceLocations;
}
