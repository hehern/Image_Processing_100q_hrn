#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;
Mat differential_filter(Mat img, vector<vector<int>> k)
{
    int row = img.rows;
    int col = img.cols;
    int dimen = k.size();
    int R = floor(dimen/2);
    Mat retrunImg = Mat::zeros(row, col, CV_8UC1);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {

            int pixel = 0;
            if(i>=R && i<row-R && j>=R && j<col-R)
            {
                for(int m=-R; m<=R; m++)
                {
                    for(int n=-R; n<=R; n++)
                    {
                        pixel += img.at<uchar>(i+m,j+n)*k[m+R][n+R];
                    }
                }
            }
            pixel = max(0, pixel);
            pixel = min(255, pixel);
            retrunImg.at<uchar>(i,j) = abs(pixel);
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
    //与微分滤波器相比，仅仅是算子不同而已
    vector<vector<int>> K_emboss={
        {-2,-1,0},
        {-1,1,1},
        {0,1,2}
    };

    Mat Img = differential_filter(grayImg,K_emboss);

    imwrite("../pictures_results/q18.jpg", Img);

    imshow("emboss", Img);
    waitKey(0);
    destroyAllWindows();

}