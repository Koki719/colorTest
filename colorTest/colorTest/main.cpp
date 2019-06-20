//
//  main.cpp
//  colorTest
//
//  Created by 柳澤昂輝 on 2019/06/16.
//  Copyright © 2019年 柳澤昂輝. All rights reserved.
//

#include <opencv2/opencv.hpp>

int numofcolors = 24;

// カラーチェッカーの各カラーを格納
std::vector<cv::Scalar> colorset{cv::Scalar(68,82,115),cv::Scalar(130,150,194),cv::Scalar(157,122,98),cv::Scalar(67,108,87),cv::Scalar(177,128,133),cv::Scalar(170,189,103),cv::Scalar(44,126,214),cv::Scalar(166,91,80),cv::Scalar(99,90,193),cv::Scalar(108,60,94),cv::Scalar(64,188,157),cv::Scalar(46,163,224),cv::Scalar(150,61,56),cv::Scalar(73,148,70),cv::Scalar(60,54,175),cv::Scalar(31,199,231),cv::Scalar(149,86,187),cv::Scalar(161,133,8),cv::Scalar(242,243,243),cv::Scalar(200,200,200),cv::Scalar(160,160,160),cv::Scalar(121,122,122),cv::Scalar(85,85,85),cv::Scalar(52,52,52)};

// トラックバーの初期値、コールバック関数のプロトタイプ宣言
int valR = 128;
void changeRColor(int position, void* userdata); //trackbarコールバック関数（Rの変更）
int valG = 128;
void changeGColor(int position, void* userdata); //trackbarコールバック関数（Gの変更）
int valB = 128;
void changeBColor(int position, void* userdata); //trackbarコールバック関数（Bの変更）

// ウィンドウ用Matクラス宣言
cv::Mat src(300, 300, CV_8UC3, cv::Scalar::all(127));
cv::Mat colorTest(1300, 1000, CV_8UC3, cv::Scalar::all(255));
cv::Mat projector(1920,1080, CV_8UC3);

int main()
{
    std::cout << colorset[0] + colorset[1];
    cv::namedWindow("Color Image");
    cv::namedWindow("projector");
    //トラックバーの設置
    cv::createTrackbar("Red", "Color Image", &valR, 255, changeRColor);
    cv::createTrackbar("Green", "Color Image", &valG, 255, changeGColor);
    cv::createTrackbar("Blue", "Color Image", &valB, 255, changeBColor);
    cv::imshow("Color Image", src);
    
    // UI用ディスプレイの設定
    cv::putText(colorTest, "Input Color", cv::Point(400,30), cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(1,1,1));
    for(int i = 0; i < numofcolors; i++){
        cv::rectangle(colorTest, cv::Point(100 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(150 + (i / 12) * 450, 300 + (i % 12) * 75), colorset[i], -1);
        cv::putText(colorTest, "+", cv::Point(200 + (i / 12) * 450, 285 + (i % 12) * 75), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
        cv::putText(colorTest, "=", cv::Point(370 + (i / 12) * 450, 285 + (i % 12) * 75), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    }
    
    cv::Mat tmp = colorTest.clone();
    cv::rectangle(tmp, cv::Point(450,50),cv::Point(550,150), cv::Scalar(valB, valG, valR),-1);
    cv::putText(tmp, "(" + std::to_string(valR) + ", " + std::to_string(valG)+ ", " + std::to_string(valB) + ")", cv::Point(340,200), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    for(int i = 0; i < numofcolors; i++){
        cv::rectangle(tmp, cv::Point(270 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(320 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB,valG,valR), -1);
        cv::rectangle(tmp, cv::Point(440 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(490 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB,valG,valR) + colorset[i], -1);
    }
    cv::imshow("colorTest", tmp);
    projector.setTo(cv::Scalar(valB, valG, valR));
    cv::moveWindow("projector", 2560, 0);
    cv::setWindowProperty("projector", cv::WND_PROP_FULLSCREEN, cv::WINDOW_FULLSCREEN);
    cv::imshow("projector", projector);
    cv::waitKey(0);
    return 0;
}

// コールバック関数にて色が変えられた時, 表示を変える関数
void changedColor(void){
    src.setTo(cv::Scalar(valB, valG, valR));
    projector.setTo(cv::Scalar(valB, valG, valR));
    cv::imshow("Color Image", src);
    cv::imshow("projector", projector);
    cv::Mat tmp = colorTest.clone();
    cv::rectangle(tmp, cv::Point(450,50),cv::Point(550,150), cv::Scalar(valB, valG, valR), -1);
    cv::putText(tmp, "(" + std::to_string(valR) + ", " + std::to_string(valG)+ ", " + std::to_string(valB) + ")", cv::Point(340,200), cv::FONT_HERSHEY_DUPLEX, 1.2, cv::Scalar(1,1,1));
    for(int i = 0; i < numofcolors; i++){
        cv::rectangle(tmp, cv::Point(270 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(320 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB,valG,valR), -1);
        cv::rectangle(tmp, cv::Point(440 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(490 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB,valG,valR) + colorset[i], -1);
    }
    cv::imshow("colorTest", tmp);
}

// UI表示用関数
void dispColor(void){
    cv::Mat tmp = colorTest.clone();
    for(int i = 0; i < numofcolors; i++){
        cv::rectangle(tmp, cv::Point(270 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(320 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
        cv::rectangle(tmp, cv::Point(440 + (i / 12) * 450, 250 + (i % 12) * 75), cv::Point(490 + (i / 12) * 450, 300 + (i % 12) * 75), cv::Scalar(valB, valG,valR), -1);
    }
    cv::imshow("colorTest", tmp);
}

// trackbarコールバック関数（Rの変更）
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

