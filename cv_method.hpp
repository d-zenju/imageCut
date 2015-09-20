//
//  cv_method.hpp
//  CVGL_test
//
//  Created by ZENJU Daisuke on 2015/09/19.
//  Copyright © 2015年 ZENJU Daisuke. All rights reserved.
//

#ifndef cv_method_hpp
#define cv_method_hpp

#include "init.hpp"

void cutImage(cv::Mat image, _mousePoint mPoint[2], int frames);
cv::Mat toHSV(cv::Mat image);
cv::Mat toRGB(cv::Mat image);
_hsvChannels splitHSV(cv::Mat image);
cv::Mat hsvPoint(cv::Mat hsvImage, int height, int width, int H_low, int H_hi, int S_low, int S_hi, int V_low, int V_hi);
cv::Mat toGray(cv::Mat image);
cv::Mat threshAdaptive(cv::Mat grayImage, int blockSize, int c);
cv::Mat threshOtu(cv::Mat grayImage);
cv::Mat thresh(cv::Mat grayImage, int th);
cv::Mat bilateral(cv::Mat image, int d, double sigmaColor, double sigmaSpace);
cv::Mat kmeansColor(cv::Mat image, int K);

#endif /* cv_method_hpp */
