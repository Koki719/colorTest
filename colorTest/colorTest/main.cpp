//
//  main.cpp
//  colorTest
//
//  Created by 柳澤昂輝 on 2019/06/16.
//  Copyright © 2019年 柳澤昂輝. All rights reserved.
//

#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int valR = 128;
void changeRColor(int position, void* userdata); //trackbarコールバック関数（Rの変更）
int valG = 128;
void changeGColor(int position, void* userdata); //trackbarコールバック関数（Gの変更）
int valB = 128;
void changeBColor(int position, void* userdata); //trackbarコールバック関数（Bの変更）
int main()
{
    Mat src(128, 384, CV_8UC3, Scalar::all(127));
    namedWindow("Color Image");
    //トラックバーの設置
    createTrackbar("Red", "Color Image", &valR, 255, changeRColor);
    createTrackbar("Green", "Color Image", &valG, 255, changeGColor);
    createTrackbar("Blue", "Color Image", &valB, 255, changeBColor);
    while (1) {
        src.setTo(Scalar(valB, valG, valR)); //RGBのすべての値更新
        imshow("Color Image", src);
        if(waitKey(30) == 27) break;
    }
    return 0;
}
//trackbarコールバック関数（Rの変更）
void changeRColor(int position, void* userdata){
    valR = position; //トラックバーの位置によってRの値を更新
}
// trackbarコールバック関数（Gの変更）
void changeGColor(int position, void* userdata)
{
    valG = position; //トラックバーの位置によってGの値を更新
}
// trackbarコールバック関数（Bの変更）
void changeBColor(int position, void* userdata)
{
    valB = position; //トラックバーの位置によってBの値を更新
}
