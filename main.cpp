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

// Set Window Size
int imageWidth = capture.get(CV_CAP_PROP_FRAME_WIDTH);
int imageHeight = capture.get(CV_CAP_PROP_FRAME_HEIGHT);

// Magnification Ratio
double widthMagnification;
double heightMagnification;

// mouse point
_mousePoint mPoint[2];
_mousePosition mPosition;

// Status
int write_flag = 0;

// movie sec
double sec = 0.0;


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


// Draw String
void drawString(double x, double y, const std::string str){
    void *font = GLUT_BITMAP_HELVETICA_10;
    glRasterPos2f(x, y);
    for (int i = 0; i < str.size(); i++) {
        glutBitmapCharacter(font, str[i]);
    }
}



// Play Movie
void display()
{
    glRasterPos3f(0, 0, 0);
    
    // capture to Mat:image
    cv::Mat image;
    capture.set(CV_CAP_PROP_POS_MSEC, sec);
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
    cv::Mat hsv_img = toHSV(image);
    _hsvChannels hsv = splitHSV(hsv_img);
    cv::imshow("HSV", hsv_img);
    cv::imshow("HSV H", hsv.H);
    cv::imshow("HSV S", hsv.S);
    cv::imshow("HSV V", hsv.V);
    cv::imshow("HSV to RGB", toRGB(image));    
    */
    
    //cv::imshow("K-means", kmeansColor(image, 10));
    
    // RGB -> Gray
    //cv::imshow("Gray", toGray(image));
    
    // Thresh
    //cv::imshow("Adaptive Thresh", threshAdaptive(toGray(bilateral(image, 20, 90, 40)), 21, 3));
    //cv::imshow("Otu Thresh", threshOtu(toGray(bilateral(image, 20, 90, 40))));
    //cv::imshow("Normal Thresh", thresh(toGray(bilateral(image, 20, 90, 40)), 100));
    
    // Smooth
    //cv::imshow("Smooth", bilateral(image, 20, 90, 40));
    
    
    // draw Stinrg
    std::string printSec = "time : " + std::to_string(sec) + " [msec]";
    drawString(10, 670, printSec);
    
    std::string printMousePosition = "mouse : " + std::to_string(mPosition.x) + ", " + std::to_string((mPosition.y));
    drawString(10, 650, printMousePosition);
    
    // Draw Image
    glFlush();
    glutPostRedisplay();
    
    sec += 1000;
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


void passive_motion(int x, int y) {
    mPosition.x = (int)(x / widthMagnification);
    mPosition.y = (int)(y / heightMagnification);
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
    glutPassiveMotionFunc(passive_motion);
    glutMainLoop();
    
    return 0;
}