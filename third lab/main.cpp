#include <iostream>
#include <fstream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

using namespace std;
using namespace cv;

vector<Mat> imgs;
string result_name = "result.jpg";

int main(int argc, char* argv[])
{
    for (int i = 1; i < argc; ++i)
    {

        Mat img = imread(argv[i]);
        if (img.empty())
        {
            // Exit if image is not present
            cout << "Can't read image '" << argv[i] << "'\n";
            return -1;
        }
        imgs.push_back(img);
    }

    Mat pano;
    Ptr<Stitcher> stitcher = Stitcher::create(Stitcher::PANORAMA);
    Stitcher::Status status = stitcher->stitch(imgs, pano);

    if (status != Stitcher::OK)
    {
        cout << "Can't stitch images, error code = " << status << endl;
        return -1;
    }

    imwrite("result.jpg", pano);

    // Show the result
    imshow("Result", pano);
    waitKey(0);
    return 0;
}