//
//  main.cpp
//  CVGL_test
//
//  Created by ZENJU Daisuke on 2015/08/11.
//  Copyright (c) 2015年 ZENJU Daisuke. All rights reserved.
//


#include "cv_method.hpp"


// Read Movie
//cv::VideoCapture capture(0);
cv::VideoCapture capture("/Users/zenju/Documents/seminar/AIS_GPS_Movie_20141113/Movie_originalData/001.mov");
double fps = capture.get(CV_CAP_PROP_FPS);

// Set Window Size
int imageWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
int imageHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

// Magnification Ratio
double widthMagnification;
double heightMagnification;

// mouse point
_mousePoint mPoint[2];

// Status
int write_flag = 0;


// Quit by Keyboard
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
        case 'q':
        case 'Q':
        case '\033':
            exit(0);
            break;
            
        default:
            break;
    }
}



// Play Movie
void display()
{
    // capture to Mat:image
    cv::Mat image;
    capture >> image;
    int frames = capture.get(CV_CAP_PROP_POS_FRAMES);
    
    // Cut Image(Status:2 --> cut image)
    if(write_flag == 2) {
        write_flag = 0;
        cutImage(image, mPoint, frames);
    }
    
    // openCV -> openGL Image
    cv::flip(image, image, 0);
    cv::cvtColor(image, image, CV_BGR2RGB);
    
    glDrawPixels(image.cols, image.rows, GL_RGB, GL_UNSIGNED_BYTE, image.data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    cv::flip(image, image, 0);
    
    /*
    // RGB -> HSV
    _hsvChannels hsv = splitHSV(toHSV(image));
    cv::imshow("HSV H", hsv.H);
    cv::imshow("HSV S", hsv.S);
    cv::imshow("HSV V", hsv.V);
    */
    
    // RGB -> Gray
    //cv::imshow("Gray", toGray(image));
    
    // Thresh
    cv::imshow("Adaptive Thresh", threshAdaptive(toGray(bilateral(image, 20, 90, 40)), 7, 6));
    cv::imshow("Otu Thresh", threshOtu(toGray(bilateral(image, 20, 90, 40))));
    cv::imshow("Normal Thresh", thresh(toGray(bilateral(image, 20, 90, 40)), 100));
    
    // Smooth
    cv::imshow("Smooth", bilateral(image, 20, 90, 40));
    
    // Draw Image
    glFlush();
    glutPostRedisplay();
}



// Image Resize
void resize(int w, int h) {
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    
    // Calc Magnification
    widthMagnification = (double)w / (double)imageWidth;
    heightMagnification = (double)h / (double)imageHeight;
    glPixelZoom(widthMagnification, heightMagnification);
}



// Get Mouse Point
void mouse(int button, int state, int x, int y)
{
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_UP) {
                // Calc click Point
                int xx = (int)(x / widthMagnification);
                int yy = (int)(y / heightMagnification);
                std::cout << xx << ", " << yy << std::endl;
                
                // save click point
                mPoint[write_flag].x = xx;
                mPoint[write_flag].y = yy;
                write_flag++;
            }
            break;
            
        case GLUT_MIDDLE_BUTTON:
            break;
        case GLUT_RIGHT_BUTTON:
            break;
        default:
            break;
    }
}


// Main Program
int main(int argc, char * argv[]) {
    if (!capture.isOpened()) {
        return -1;
    }
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(imageWidth, imageHeight);
    glutCreateWindow("Ship Movie");
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    
    return 0;
}