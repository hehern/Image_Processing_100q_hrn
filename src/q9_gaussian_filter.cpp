#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;
Mat gaussian_filter(Mat img, vector<vector<int>> ker)
{
    int row = img.rows;
    int col = img.cols;
    int channel = img.channels();
    int length = ker.size();
    int R = floor(length/2);
    Mat returnImg = Mat::zeros(row,col,CV_8UC3);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int t=0; t<channel; t++)
            {
                int pixel = 0;
                if(i>=R && i<row-R && j>=R && j<col-R)//边缘不处理
                {
                    for(int m=-R; m<=R; m++)
                    {
                        for(int n=-R; n<=R; n++)
                        {
                            pixel += img.at<Vec3b>(i+m,j+n)[t];
                        }
                    }
                }
                returnImg.at<Vec3b>(i,j)[t] =  pixel/(length*length);     
            }
        }
    }
    return returnImg;
}
vector<vector<int>> get_gauss_kernel(int dimen, float sigma)
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
            kernel[i][j] = 1/(2*M_PI*sigma*sigma)*exp(-(x*x+y*y)/(2*sigma*sigma));
            sum_kernel += kernel[i][j];
        }
    }
    vector<vector<int>> kernel_int(dimen, vector<int>(dimen, 0));
    for(int i=0; i<dimen; i++)
    {
        for(int j=0; j<dimen; j++)
        {
            kernel_int[i][j] = kernel[i][j]/sum_kernel;
        }
    }
    return kernel_int;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori_noise.jpg");
    // vector<vector<int>> kernel = {{1,2,1},
    //                               {2,4,2},
    //                               {1,2,1}};
    float sigma = 1.3;
    vector<vector<int>> kernel = get_gauss_kernel(3, sigma);
    Mat resultImg = gaussian_filter(srcImg, kernel);

    imwrite("../pictures_results/q9.jpg", resultImg);
    imshow("gaussian_filter", resultImg);
    waitKey(0);
    destroyAllWindows();
}