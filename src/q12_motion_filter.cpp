#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace cv;
using namespace std;
Mat motion_filter(Mat img, vector<vector<float>> ker)
{
    int row = img.rows;
    int col = img.cols;
    int channel = img.channels();
    int R = floor(ker.size()/2);
    Mat retrunImg = Mat::zeros(row, col, CV_8UC3);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int t=0; t<channel; t++)
            {
                float pixel = .0;
                if(i>=R && i<row-R && j>=R && j<col-R)
                {
                    for(int m=-R; m<=R; m++)
                    {
                        pixel += img.at<Vec3b>(i+m,j+m)[t]*ker[m+R][m+R];
                    }

                }
                retrunImg.at<Vec3b>(i,j)[t] = pixel;
            }
        }
    }
    return retrunImg;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    vector<vector<float>> kernel={
        {1.0/3,0,0},
        {0,1.0/3,0},
        {0,0,1.0/3}
    };
    Mat resultImg = motion_filter(srcImg, kernel);

    imwrite("../pictures_results/q12.jpg", resultImg);
    imshow("median_filter", resultImg);
    waitKey(0);
    destroyAllWindows();

}