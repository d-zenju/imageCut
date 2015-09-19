//
//  init.hpp
//  CVGL_test
//
//  Created by ZENJU Daisuke on 2015/09/19.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#ifndef init_hpp
#define init_hpp

#include <iostream>
#include <GLUT/GLUT.h>
#include <opencv2/opencv.hpp>

// Mouse Point
typedef struct {
    int x;
    int y;
} _mousePoint;


// HSV struct
typedef struct {
    cv::Mat H;
    cv::Mat S;
    cv::Mat V;
} _hsvChannels;

#endif /* init_hpp */
