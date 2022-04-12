#include <opencv2/imgcodecs.hpp>

#include "smoke.hh"

int main(int argc, char** argv) {
    cv::Mat kitti_img = cv::imread("../kitti_000008.png");
    cv::Mat intrinsic = (cv::Mat_<float>(3, 3) << 
        721.5377, 0.0, 609.5593, 0.0, 721.5377, 172.854, 0.0, 0.0, 1.0);
    SMOKE smoke("../smoke.trt8", intrinsic);
    smoke.Detect(kitti_img);
    return 0;
}
