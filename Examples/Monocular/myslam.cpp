#include <opencv2/opencv.hpp>
// ORB-SLAM的系统接口
#include "System.h"
#include <string>
#include <chrono>   // for time stamp
#include <iostream>
 
using namespace std;
 
// 参数文件与字典文件
// 如果你系统上的路径不同，请修改它
string parameterFile = "./Examples/Monocular/myslam.yaml";
string vocFile = "./Vocabulary/ORBvoc.txt";
 
int main(int argc, char **argv) {
 
    // 声明 ORB-SLAM2 系统
    ORB_SLAM2::System SLAM(vocFile, parameterFile, ORB_SLAM2::System::MONOCULAR, true);
 
    // 获取相机图像代码
    cv::VideoCapture cap(1);    // change to 1 if you want to use USB camera.
 
    // 分辨率设为640x480
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
 
    // 记录系统时间
    auto start = chrono::system_clock::now();
 
    while (1) {
        int key=cv::waitKey(100);
        if(key==113){
	    break;	
	}
        cv::Mat frame;
        cap >> frame;   // 读取相机数据
        auto now = chrono::system_clock::now();
        auto timestamp = chrono::duration_cast<chrono::milliseconds>(now - start);
        SLAM.TrackMonocular(frame, double(timestamp.count())/1000.0);
    }
    SLAM.Shutdown();
    SLAM.SaveKeyFrameTrajectoryTUM("KeyFrameTrajectory_myslam.txt");
    return 0;
}
