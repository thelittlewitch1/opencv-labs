#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

int main(int argc, char** argv)
{
    cv::Mat im_rgb = cv::imread(argv[1]);
    if (im_rgb.empty()) {
        cout << "Error" << endl;
        return -1;
    }

    cv::moveWindow("original", 200, 0);
    cv::imshow("original",im_rgb);

    cv::Mat im_gr;
    cvtColor(im_rgb,im_gr,cv::COLOR_RGB2GRAY);
    cv::moveWindow("Gray", 200, 0);
    imshow("Gray", im_gr);

    cv::Mat im_canny;
    cv::Canny(im_rgb,im_canny,100,200);
    cv::moveWindow("Canny", 200, 0);
    imshow("Canny", im_canny);

    cv::Mat im_gauss;
    GaussianBlur(im_rgb,im_gauss, cv::Size(9, 9), 0);
    cv::moveWindow("Gaussian", 200, 0);
    imshow("Gaussian", im_gauss);

    cv::Mat im_hsv;
    cvtColor(im_rgb,im_hsv, cv::COLOR_BGR2HSV);
    cv::moveWindow("HSV", 200, 0);
    imshow("HSV", im_hsv);

    cv::Mat im_clr;
    cvtColor(im_rgb,im_clr, cv::COLOR_BGR2Lab);

    cv::moveWindow("Lab", 200, 0);
    imshow("Lab", im_clr);
    cv::waitKey(0);
    return 0;
}