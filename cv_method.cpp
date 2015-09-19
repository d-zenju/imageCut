//
//  cv_method.cpp
//  CVGL_test
//
//  Created by ZENJU Daisuke on 2015/09/19.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#include "cv_method.hpp"

// Cut Image
void cutImage(cv::Mat image, _mousePoint mPoint[2], int frames) {
    int x0, x1, y0, y1;
    
    // クリックポイントの大小判定
    if (mPoint[0].x < mPoint[1].x) {
        x0 = mPoint[0].x;
        x1 = mPoint[1].x;
    } else {
        x0 = mPoint[1].x;
        x1 = mPoint[0].x;
    }
    
    if (mPoint[0].y < mPoint[1].y) {
        y0 = mPoint[0].y;
        y1 = mPoint[1].y;
    } else {
        y0 = mPoint[1].y;
        y1 = mPoint[0].y;
    }
    
    // クリックポイントの座標差
    int xsub = x1 - x0;
    int ysub = y1 - y0;
    
    std::cout << "cut: (" << x0 << ", " << y0 << "), (" << x1 << ", " << y1 << ")" << std::endl;
    
    // 画像切り取り, 保存
    cv::Mat cutimg(image(cv::Rect(x0, y0, xsub, ysub)));
    std::string filename = "/Users/zenju/Desktop/test/";
    filename = filename + std::to_string(frames) + ".jpg";
    cv::imwrite(filename, cutimg);
}


// RGB to HSV
cv::Mat toHSV(cv::Mat image) {
    cv::Mat hsvImage;
    cv::cvtColor(image, hsvImage, CV_BGR2HSV);
    return hsvImage;
}


// HSV to RGB
cv::Mat toRGB(cv::Mat image) {
    cv::Mat rgbImage;
    cv::cvtColor(image, rgbImage, CV_HSV2BGR_FULL);
    return rgbImage;
}


// split HSV
_hsvChannels splitHSV(cv::Mat image) {
    _hsvChannels hsv;
    cv::Mat channels[3];
    cv::split(image, channels);
    hsv.H = channels[0];
    hsv.S = channels[1];
    hsv.V = channels[2];
    return hsv;
}


// RGB to Gray
cv::Mat toGray(cv::Mat image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, CV_RGB2GRAY);
    return grayImage;
}