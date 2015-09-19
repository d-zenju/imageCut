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
cv::Mat toGray(cv::Mat image);

#endif /* cv_method_hpp */
