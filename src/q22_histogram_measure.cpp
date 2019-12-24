#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <algorithm>
#include <iostream>

using namespace cv;
using namespace std;
Mat histogram_measure(Mat img, float mean, float std)
{
    int row = img.rows;
    int col = img.cols;
    Mat returnImg = Mat::zeros(row,col,CV_8UC3);
    int channel = img.channels();;
    float pixel = 0;
    float mean_count = 0;
    float std_count = .0;
    //get mean and std
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int c=0; c<channel; c++)
            {
                pixel += img.at<Vec3b>(i,j)[c];
            }
        }
    }
    mean_count = pixel/(row*col*channel);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int c=0; c<channel; c++)
            {
                std_count += pow(img.at<Vec3b>(i,j)[c]-mean_count,2);
            }
        }
    }
    std_count = sqrt(std_count/(row*col*channel));

    //change the mean and std of the histogram
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int c=0; c<channel; c++)
            {
                int pixel = img.at<Vec3b>(i,j)[c];
                returnImg.at<Vec3b>(i,j)[c] = std/std_count*(pixel-mean_count)+mean;
            }
        }
    }
    return returnImg;

}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori_dark.jpg");
    Mat resultImg = histogram_measure(srcImg, 128, 52);

    imwrite("../pictures_results/q22.jpg", resultImg);
    imshow("histogram", resultImg);
    waitKey(0);
    destroyAllWindows();
}