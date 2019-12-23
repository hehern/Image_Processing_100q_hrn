#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace cv;
using namespace std;
Mat Thresholding(Mat& img, int thre_pixel)
{
    int row = img.rows;
    int col = img.cols;
    Mat grayimg(row, col, CV_8UC1);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            int gray = img.at<uchar>(i,j);
            gray>thre_pixel ? grayimg.at<uchar>(i,j)=255 : grayimg.at<uchar>(i,j)=0;
        }
    }
    return grayimg;
}
float count_g(vector<float> his, int thre)
{
    float w0 = .0;
    float u0 = .0;
    for(int i=0; i<thre+1; i++)
    {
        w0 += his[i];
        u0 += his[i]*i;
    }
    if(w0!=0) u0 /= w0;
    else u0 = .0;
    float w1 = 1 - w0;
    float u1 = .0;
    for(int j=thre+1; j<256; j++)
    {
        u1 += his[j]*j;
    }
    if(w1!=0) u1 /= w1;
    else u1 = .0;
    float g = w0*w1*(u0-u1)*(u0-u1);
    return g;

}
void compute_histogram(Mat img, vector<int>& histogram)
{
    int row = img.rows;
    int col = img.cols;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            histogram[img.at<uchar>(i,j)]++;
        }
    }
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
Mat otsu_thresholding(Mat img)
{
    //灰度化
    Mat grayimg = Grayscale(img);
    //计算直方图
    vector<int> hist(256,0);
    compute_histogram(grayimg, hist);
    //归一化
    vector<float> normal_his(256,0.0);
    int pixel_size = grayimg.total();
    for(int i=0; i<hist.size(); i++)
    {
        normal_his[i] = (float)hist[i]/pixel_size;
    }
    //计算类间方差
    vector<float> g_vector;
    for(int j=0; j<256; j++)
    {
        float g = count_g(normal_his, j);
        g_vector.push_back(g);
    }
    //找最大类间方差的像素分界点
    vector<float>::iterator biggest = max_element(begin(g_vector), end(g_vector));
    int thre_pixel = distance(begin(g_vector), biggest);
    //二值化
    Mat resultImg = Thresholding(grayimg, thre_pixel);

    return resultImg;

}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    Mat resImg = otsu_thresholding(srcImg);

    imwrite("../pictures_results/q4.jpg", resImg);
    imshow("otsu_thresholding", resImg);
    waitKey(0);
    destroyAllWindows();


}