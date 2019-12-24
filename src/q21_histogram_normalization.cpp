#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
Mat histogram_normalization(Mat img, int min_p, int max_p)
{
    int row = img.rows;
    int col = img.cols;
    Mat return_img = Mat::zeros(row, col, CV_8UC3);
    int channel = img.channels();

    int min_pixel = 999;
    int max_pixel = 0;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int c=0; c<channel; c++)
            {
                if(img.at<Vec3b>(i,j)[c] > max_pixel) max_pixel = img.at<Vec3b>(i,j)[c];
                if(img.at<Vec3b>(i,j)[c] < min_pixel) min_pixel = img.at<Vec3b>(i,j)[c];
            }
        }
    }

    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int c=0; c<channel; c++)
            {
                return_img.at<Vec3b>(i,j)[c] = (float)((max_p-min_p)/(max_pixel-min_pixel))*(img.at<Vec3b>(i,j)[c]-min_pixel)+min_p;
            }
        }
    }

    return return_img;
    

}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori_dark.jpg");
    Mat resultImg = histogram_normalization(srcImg, 0, 255);

    imwrite("../pictures_results/q21.jpg", resultImg);
    imshow("hist_nor", resultImg);
    waitKey(0);
    destroyAllWindows();

}