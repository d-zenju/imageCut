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
_hsvChannels splitHSV(cv::Mat hsvImage) {
    _hsvChannels hsv;
    cv::Mat channels[3];
    cv::split(hsvImage, channels);
    hsv.H = channels[0];
    hsv.S = channels[1];
    hsv.V = channels[2];
    return hsv;
}


// 指定したHSVの色のみ出力
cv::Mat hsvPoint(cv::Mat hsvImage, int height, int width, int H_low, int H_hi, int S_low, int S_hi, int V_low, int V_hi) {
    cv::Mat hsvOut = cv::Mat::zeros(height, width, CV_8UC3);
    
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int a = hsvImage.step * y + (x * 3);
            if (hsvImage.data[a] >= H_low && hsvImage.data[a] <= H_hi && hsvImage.data[a + 1] >= S_low && hsvImage.data[a + 1] <= S_hi && hsvImage.data[a + 2] >= V_low && hsvImage.data[a + 2] <= V_hi)
                hsvOut.data[a] = 255;
        }
    }
    
    return hsvOut;
}


// RGB to Gray
cv::Mat toGray(cv::Mat image) {
    cv::Mat grayImage;
    cv::cvtColor(image, grayImage, CV_BGR2GRAY);
    return grayImage;
}


// Adaptive Thresh (MEAN or GAUSSIAN)
cv::Mat threshAdaptive(cv::Mat grayImage, int blockSize, int c) {
    cv::Mat binaryImage;
    //cv::adaptiveThreshold(grayImage, binaryImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, blockSize, c);
    cv::adaptiveThreshold(grayImage, binaryImage, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, blockSize, c);
    return binaryImage;
}


// Otu Thresh
cv::Mat threshOtu(cv::Mat grayImage) {
    cv::Mat binaryImage;
    cv::threshold(grayImage, binaryImage, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    return binaryImage;
}


// Normal Thresh
cv::Mat thresh(cv::Mat grayImage, int th) {
    cv::Mat binaryImage;
    cv::threshold(grayImage, binaryImage, th, 255, CV_THRESH_BINARY);
    return binaryImage;
}


// bilateralFilter Smooth
cv::Mat bilateral(cv::Mat image, int d, double sigmaColor, double sigmaSpace) {
    cv::Mat smoothImage;
    cv::bilateralFilter(image, smoothImage, d, sigmaColor, sigmaSpace);
    return smoothImage;
}


// K-means subtractive color
cv::Mat kmeansColor(cv::Mat image, int K) {
    cv::Mat points;
    image.convertTo(points, CV_32FC3);
    points = points.reshape(3, image.rows * image.cols);
    
    cv::Mat_<int> clusters(points.size(), CV_32SC1);
    cv::Mat centers;
    cv::kmeans(points, K, clusters, cvTermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 10, 10), 1, cv::KMEANS_PP_CENTERS, centers);
    
    cv::Mat dstImage(image.size(), image.type());
    cv::MatIterator_<cv::Vec3b> itd = dstImage.begin<cv::Vec3b>(), itd_end = dstImage.end<cv::Vec3b>();
    for (int i = 0; itd != itd_end; ++itd, ++i) {
        cv::Vec3f &color = centers.at<cv::Vec3f>(clusters(i), 0);
        (*itd)[0] = cv::saturate_cast<uchar>(color[0]);
        (*itd)[1] = cv::saturate_cast<uchar>(color[1]);
        (*itd)[2] = cv::saturate_cast<uchar>(color[2]);
    }
    
    return dstImage;
}