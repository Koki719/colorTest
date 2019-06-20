//
//  main.cpp
//  colorTest
//
//  Created by 柳澤昂輝 on 2019/06/16.
//  Copyright © 2019年 柳澤昂輝. All rights reserved.
//

#include <opencv2/opencv.hpp>

int numofcolors = 24;

int valR = 128;
void changeRColor(int position, void* userdata); //trackbarコールバック関数（Rの変更）
int valG = 128;
void changeGColor(int position, void* userdata); //trackbarコールバック関数（Gの変更）
int valB = 128;
void changeBColor(int position, void* userdata); //trackbarコールバック関数（Bの変更）

cv::Mat src(300, 300, CV_8UC3, cv::Scalar::all(127));
cv::Mat colorTest(1300, 1000, CV_8UC3, cv::Scalar::all(255));
cv::Mat projector(1920,1080, CV_8UC3);

int main()
{
    cv::namedWindow("Color Image");
    cv::namedWindow("projector");
    //トラックバーの設置
    cv::createTrackbar("Red", "Color Image", &valR, 255, changeRColor);
    cv::createTrackbar("Green", "Color Image", &valG, 255, changeGColor);
    cv::createTrackbar("Blue", "Color Image", &valB, 255, changeBColor);
    imshow("Color Image", src);
    
    cv::putText(colorTest, "Input Color", cv::Point(400,30), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(1,1,1));
    for(int i = 0; i < numofcolors; i++){
        cv::rectangle(colorTest, cv::Point(100 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(150 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
        cv::putText(colorTest, "+", cv::Point(200 + (i / 12) * 450, 285 + (i % 12) * 75), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
        cv::rectangle(colorTest, cv::Point(270 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(320 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
        cv::putText(colorTest, "=", cv::Point(370 + (i / 12) * 450, 285 + (i % 12) * 75), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
        cv::rectangle(colorTest, cv::Point(440 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(490 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
    }
    
    cv::Mat tmp = colorTest.clone();
    cv::rectangle(tmp, cv::Point(450,50),cv::Point(550,150), cv::Scalar(valB, valG, valR),-1);
    cv::putText(tmp, "(" + std::to_string(valR) + ", " + std::to_string(valG)+ ", " + std::to_string(valB) + ")", cv::Point(340,200), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    imshow("colorTest", tmp);
    projector.setTo(cv::Scalar(valB, valG, valR));
    cv::moveWindow("projector", 2560, 0);
    cv::setWindowProperty("projector", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    imshow("projector", projector);
    cv::waitKey(0);
    return 0;
}

void changedColor(void){
    src.setTo(cv::Scalar(valB, valG, valR));
    projector.setTo(cv::Scalar(valB, valG, valR));
    imshow("Color Image", src);
    imshow("projector", projector);
    cv::Mat tmp = colorTest.clone();
    cv::rectangle(tmp, cv::Point(450,50),cv::Point(550,150), cv::Scalar(valB, valG, valR), -1);
    
    cv::putText(tmp, "(" + std::to_string(valR) + ", " + std::to_string(valG)+ ", " + std::to_string(valB) + ")", cv::Point(50,200), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    imshow("colorTest", tmp);
}

void dispColor(void){
    cv::Mat tmp = colorTest.clone();
    for(int i = 0; i < numofcolors; i++){
        cv::rectangle(colorTest, cv::Point(270 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(320 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
        cv::rectangle(colorTest, cv::Point(440 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(490 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
    }
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

