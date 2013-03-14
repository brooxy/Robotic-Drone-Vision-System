#include <QCoreApplication>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
#include <time.h>
#include <stdio.h>
#include <QDebug>

using namespace cv;

//Set up matrix for storing frame
//Mat frame;
//Mat frame1;
//Mat frame2;

CvCapture *capture = 0;
CvCapture *capture1 = 0;
CvCapture *capture2 = 0;
CvCapture *capture3 = 0;
IplImage *frame1 = 0;
IplImage *frame2 = 0;
IplImage *frame3 = 0;
IplImage *frame4 = 0;

//void colorDetect(Mat &frame);

int main()
{
    time_t start, end;
    //Sets up new video capture from default webcam
    capture = cvCaptureFromCAM(0);
    capture1 = cvCaptureFromCAM(1);
    capture2 = cvCaptureFromCAM(2);
    capture3 = cvCaptureFromCAM(3);

    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, 320);
    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);

    cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_WIDTH, 320);
    cvSetCaptureProperty(capture1, CV_CAP_PROP_FRAME_HEIGHT, 240);

    cvSetCaptureProperty(capture2, CV_CAP_PROP_FRAME_WIDTH, 320);
    cvSetCaptureProperty(capture2, CV_CAP_PROP_FRAME_HEIGHT, 240);

    cvSetCaptureProperty(capture3, CV_CAP_PROP_FRAME_WIDTH, 320);
    cvSetCaptureProperty(capture3, CV_CAP_PROP_FRAME_HEIGHT, 240);

    //Error handling statement
   /* if ( !capture.isOpened() ) {
        fprintf( stderr, "ERROR: capture is NULL \n" );
        getchar();
        return -1;
    }*/

    //Create a window in which the captured images will be presented
    cvNamedWindow("camera1", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("camera2", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("camera3", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("camera4", CV_WINDOW_AUTOSIZE);

    time(&start);
    int counter = 0;

    //Show the image captured from the camera in the window and repeat
    while ( 1 ) {

        //Capture the matrix frame
        //capture.read(frame);
        //capture1.read(frame1);
        //capture2.read(frame2);

        frame1 = cvQueryFrame(capture);
        frame2 = cvQueryFrame(capture1);
        frame3 = cvQueryFrame(capture2);
        frame4 = cvQueryFrame(capture3);

        //Run submethod for color detection
        //colorDetect(frame);

        //Output image to screen
        //imshow("camera1", frame);
        //imshow("camera2", frame1);
        //imshow("camera3", frame2);

        cvShowImage("camera1", frame1);
        cvShowImage("camera2", frame2);
        cvShowImage("camera3", frame3);
        cvShowImage("camera4", frame4);

        time(&end);
        ++counter;
        double sec = difftime(end,start);
        double fps = counter/sec;
        qDebug() << fps;

        //Do not release the frame!
        //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
        //remove higher bits using AND operator
        if ((cvWaitKey(143) & 255) == 27) {
            cvDestroyWindow("camera1");
            cvReleaseCapture(&capture);
            cvDestroyWindow("camera2");
            cvReleaseCapture(&capture1);
            cvDestroyWindow("Camera3");
            cvReleaseCapture(&capture2);
            cvDestroyWindow("camera4");
            cvReleaseCapture(&capture3);
            break;
        }
    }

    cvReleaseCapture(&capture);
    cvReleaseCapture(&capture1);
    cvReleaseCapture(&capture2);
    cvReleaseCapture(&capture3);

    return 0;
}

//Red detection non-dependant on the lighting conditions
/*void colorDetect(Mat &frame)
{
    //Store values of rows and columns width and height of frame
    int nl = frame.rows;
    int nc = frame.cols;

    //Sets up array for storing
    int e = nl*nc;
    bool color[e];

    //total number of elements per line
    for(int j=0; j < nl; j++)
    {

        for(int i=0; i < nc; i++)
        {
            //To get seperate values of red/green/blue channels
            float b = frame.at<cv::Vec3b>(j,i)[0];
            float g = frame.at<cv::Vec3b>(j,i)[1];
            float r = frame.at<cv::Vec3b>(j,i)[2];

            //Subtractive method **This seems to identify red better but still not great**
            float ratio1 = r-b;
            float ratio2 = r-g;

            //Division method
            //float ratio1 = r/b;
            //float ratio2 = r/g;

            if(ratio1 > 2 && ratio2 > 2)
            {
                color[e] = 1;
                frame.at<cv::Vec3b>(j,i)[0] = 0;
                frame.at<cv::Vec3b>(j,i)[1] = 0;
                frame.at<cv::Vec3b>(j,i)[2] = 0;
            } else {
                color[e] = 0;
                frame.at<cv::Vec3b>(j,i)[0] = 255;
                frame.at<cv::Vec3b>(j,i)[1] = 255;
                frame.at<cv::Vec3b>(j,i)[2] = 255;
            }
        }
    }
}

/*Multithreaded input from 4 cameras over restricted usb space
 *using*/



