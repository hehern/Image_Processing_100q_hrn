#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;
Mat gaussian_filter(Mat img, vector<vector<float>> ker)
{
    int row = img.rows;
    int col = img.cols;
    int channel = img.channels();
    int length = ker.size();
    int R = floor(length/2);
    Mat returnImg = Mat::zeros(row,col,CV_8UC1);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {

            float pixel = 0;
            if(i>=R && i<row-R && j>=R && j<col-R)//边缘不处理
            {
                for(int m=-R; m<=R; m++)
                {
                    for(int n=-R; n<=R; n++)
                    {
                        pixel += img.at<uchar>(i+m,j+n)*ker[m+R][n+R];
                    }
                }
            }
            returnImg.at<uchar>(i,j) =  pixel;
        }
    }
    return returnImg;
}
vector<vector<float>> get_LoG_kernel(int dimen, float sigma)
{
    vector<vector<float>> kernel(dimen, vector<float>(dimen, .0));
    float sum_kernel = .0;
    int R = floor(dimen/2);
    for(int i=0; i<dimen; i++)
    {
        for(int j=0; j<dimen; j++)
        {
            int x = i - R;
            int y = j - R;
            kernel[i][j] = (x*x+y*y-sigma*sigma)/(2*M_PI*pow(sigma,6))*exp(-(x*x+y*y)/(2*sigma*sigma));
            sum_kernel += kernel[i][j];
        }
    }
    for(int i=0; i<dimen; i++)
    {
        for(int j=0; j<dimen; j++)
        {
            kernel[i][j] /= sum_kernel;
        }
    }
    return kernel;
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
    Mat srcImg = imread("../pictures_origin/imori_noise.jpg");
    Mat grayImg = Grayscale(srcImg);

    float sigma = 3.0;
    vector<vector<float>> kernel = get_LoG_kernel(5, sigma);
    Mat resultImg = gaussian_filter(grayImg, kernel);

    imwrite("../pictures_results/q19.jpg", resultImg);
    imshow("LoG_filter", resultImg);
    waitKey(0);
    destroyAllWindows();
}