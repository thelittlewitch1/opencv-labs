#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>

using namespace cv;
using std::vector;

uchar calculateNewPixel(const Mat& image, const vector<vector<double>>& kernel,
                        int ii, int jj){
    int newPixel = 0;

    for (unsigned i = 0; i < kernel.size(); ++i) {
        for (unsigned j = 0; j < kernel.size(); ++j) {
            newPixel += image.at<uchar>(ii + static_cast<int>(i),
                                        jj + static_cast<int>(j)) * kernel[i][j];
        }
    }
    return saturate_cast<uchar>(newPixel);
}

uchar Convolution(const Mat& image, Mat& result,
                  const vector<vector<double> >& kernel){
    int border = static_cast<int>(kernel.size() / 2);

    if (image.type() == 0) {
        for (uint i = 0; i < image.cols - border + 1; ++i) {
            for (uint j = 0; j < image.rows - border + 1; ++j) {
                result.at<uchar>(i, j) = calculateNewPixel(image, kernel, i, j);
            }
        }
    }else {
        vector<Mat> channels;
        split(image, channels);
        vector<Mat> results = channels;

        for (int i = border; i < image.cols - border + 1; ++i) {
            for (int j = border; j < image.rows - border + 1; ++j) {
                results[0].at<uchar>(i, j) = calculateNewPixel(channels[0], kernel, i, j);
                results[1].at<uchar>(i, j) = calculateNewPixel(channels[1], kernel, i, j);
                results[2].at<uchar>(i, j) = calculateNewPixel(channels[2], kernel, i, j);
            }
        }
        merge(results, result);
    }

}

void Smoothing(const Mat &image, Mat &result, unsigned size) {
    image.copyTo(result);

    vector<vector<double> > kernel(size, vector<double>(size, 1. / (size * size)));
    Convolution(image, result, kernel);
}

void Gradient(const Mat &image, Mat &result) {
    image.copyTo(result);
    vector<vector<double> > kernel = {{-3, -10, -3}, {0, 0, 0}, {3, 10, 3}};
    Convolution(image, result, kernel);
}

int main(int argc, char* argv[]) {
    cv::Mat image = cv::imread("/home/nadezhda/Документы/labss/lab2/ak.jpg");;
    cv::Mat res;
    if (image.empty()) {
        std::cout << "Error\n";
        return -1;
    }

    Smoothing(image, res, 6);
    namedWindow("Smoothing", WINDOW_AUTOSIZE);
    imshow("Smoothing", res);

    Gradient(image, res);
    namedWindow("Gradient", WINDOW_AUTOSIZE);
    imshow("Gradient", res);

    waitKey(0);

    return 0;
}
