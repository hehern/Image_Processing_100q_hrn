#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace cv;
using namespace std;
Mat max_min_filter(Mat img, int dimen)
{
    int row = img.rows;
    int col = img.cols;
    int R = floor(dimen/2);
    Mat retrunImg = Mat::zeros(row, col, CV_8UC1);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {

            vector<int> pixel;
            int diff = .0;
            if(i>=R && i<row-R && j>=R && j<col-R)
            {
                for(int m=-R; m<=R; m++)
                {
                    for(int n=-R; n<=R; n++)
                    {
                        pixel.push_back(img.at<uchar>(i+m,j+n));
                    }
                }
                sort(pixel.begin(), pixel.end());//从小到大
                diff = *(pixel.end()-1) - *pixel.begin();
            }
            retrunImg.at<uchar>(i,j) = diff;
        }
    }
    return retrunImg;
}
Mat Grayscale(Mat img)
{
    int row = img.rows;
    int col = img.cols;
    Mat gray_img(row, col, CV_8UC1);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            gray_img.at<uchar>(i,j) = 0.2126*img.at<Vec3b>(i,j)[2] + 0.7152*img.at<Vec3b>(i,j)[1] + 0.0722*img.at<Vec3b>(i,j)[0];
        }
    }
    return gray_img;

}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    Mat grayImg = Grayscale(srcImg);
    Mat resultImg = max_min_filter(grayImg, 3);

    imwrite("../pictures_results/q13.jpg", resultImg);
    imshow("median_filter", resultImg);
    waitKey(0);
    destroyAllWindows();

}