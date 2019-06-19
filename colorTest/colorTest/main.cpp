//
//  main.cpp
//  colorTest
//
//  Created by 柳澤昂輝 on 2019/06/16.
//  Copyright © 2019年 柳澤昂輝. All rights reserved.
//

#include <opencv2/opencv.hpp>

int valR = 128;
void changeRColor(int position, void* userdata); //trackbarコールバック関数（Rの変更）
int valG = 128;
void changeGColor(int position, void* userdata); //trackbarコールバック関数（Gの変更）
int valB = 128;
void changeBColor(int position, void* userdata); //trackbarコールバック関数（Bの変更）

cv::Mat src(300, 300, CV_8UC3, cv::Scalar::all(127));
cv::Mat colorTest(1500, 1000, CV_8UC3, cv::Scalar::all(255));

int main()
{
    cv::namedWindow("Color Image");
    //トラックバーの設置
    cv::createTrackbar("Red", "Color Image", &valR, 255, changeRColor);
    cv::createTrackbar("Green", "Color Image", &valG, 255, changeGColor);
    cv::createTrackbar("Blue", "Color Image", &valB, 255, changeBColor);
    imshow("Color Image", src);
    
    cv::putText(colorTest, "Input Color", cv::Point(400,30), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(1,1,1));
    
    cv::Mat tmp = colorTest.clone();
    cv::rectangle(tmp, cv::Point(450,50),cv::Point(550,150), cv::Scalar(valB, valG, valR),-1);
    
    cv::putText(tmp, "(" + std::to_string(valR) + ", " + std::to_string(valG)+ ", " + std::to_string(valB) + ")", cv::Point(340,200), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    imshow("colorTest", tmp);
    cv::waitKey(0);
    return 0;
}

void changedColor(void){
    src.setTo(cv::Scalar(valB, valG, valR));
    imshow("Color Image", src);
    
    cv::Mat tmp = colorTest.clone();
    cv::rectangle(tmp, cv::Point(450,50),cv::Point(550,150), cv::Scalar(valB, valG, valR), -1);
    
    cv::putText(tmp, "(" + std::to_string(valR) + ", " + std::to_string(valG)+ ", " + std::to_string(valB) + ")", cv::Point(50,200), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    imshow("colorTest", tmp);
}

//trackbarコールバック関数（Rの変更）
void changeRColor(int position, void* userdata){
    valR = position; //トラックバーの位置によってRの値を更新
    changedColor();
}
// trackbarコールバック関数（Gの変更）
void changeGColor(int position, void* userdata)
{
    valG = position; //トラックバーの位置によってGの値を更新
    changedColor();
}
// trackbarコールバック関数（Bの変更）
void changeBColor(int position, void* userdata)
{
    valB = position; //トラックバーの位置によってBの値を更新
    changedColor();
}

