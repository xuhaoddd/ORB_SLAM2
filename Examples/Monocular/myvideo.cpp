// 该文件将打开给定的视频文件，并将图像传递给ORB-SLAM2进行定位
 
// 需要opencv
#include <opencv2/opencv.hpp>
#include <cstdio>
// ORB-SLAM的系统接口
#include "System.h"
 
#include <string>
#include <chrono>   // for time stamp
#include <iostream>
 
using namespace std;
 
// 参数文件与字典文件
// 如果你系统上的路径不同，请修改它
string parameterFile = "./Examples/Monocular/myvideo.yaml";
string vocFile = "./Vocabulary/ORBvoc.txt";
 
// 视频文件
string videoFile = "./experiment/myvideo_0506.avi";
 
int main(int argc, char **argv) {
 
    // 声明 ORB-SLAM2 系统
    ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);
 
    // 获取视频图像
    cv::VideoCapture cap(videoFile);    // change to 1 if you want to use USB camera.
 
    // 记录系统时间
    auto start = chrono::system_clock::now();
 
    while (1) {
	int key=cv::waitKey(100);
        if(key==113){
	    break;	
	}
        cv::Mat frame;
        cap >> frame;   // 读取相机数据
        if ( frame.data == nullptr )
            break;
 
        // rescale because image is too large
        cv::Mat frame_resized;
        cv::resize(frame, frame_resized, cv::Size(640,360));
 
        auto now = chrono::system_clock::now();
        auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
	//float image_name=timestamp.count()/1000.0;
        double image_name=timestamp.count()/1000.0;
	char file_name[100];
	//sprintf(file_name,"/home/jyokou/dataset/orb2_datast/20200506/%f.png",image_name);
        sprintf(file_name,"/home/jyokou/dataset/orb2_datast/20200508/%lf.png",image_name);
	cv::imwrite(file_name,frame_resized);
        //SLAM.TrackMonocular(frame_resized, double(timestamp.count())/1000.0);
        SLAM.TrackMonocular(frame_resized, image_name);
        cv::waitKey(30);
    }
 
    SLAM.Shutdown();
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory_myvideo.txt");
    return 0;
}
