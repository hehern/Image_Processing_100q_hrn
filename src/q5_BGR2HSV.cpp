#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace cv;
using namespace std;

Mat BGR2HSV(Mat img)
{
    int row = img.rows;
    int col = img.cols;
    Mat hsvImg(row, col, CV_32FC3);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            float B = (float)img.at<Vec3b>(i,j)[0]/255;
            float G = (float)img.at<Vec3b>(i,j)[1]/255;
            float R = (float)img.at<Vec3b>(i,j)[2]/255;
            float Max, Min;
            Max = max(B, max(G,R));
            Min = min(B, min(G,R));
            float H,S,V;

            if(Min == Max) H = .0;
            else if(Min == B) H = 60*(G-R)/(Max-Min)+60;
            else if(Min == R) H = 60*(B-G)/(Max-Min)+180;
            else if(Min == G) H = 60*(R-B)/(Max-Min)+300;

            V = Max;
            S = Max - Min;
            hsvImg.at<Vec3f>(i,j)[0] = H;
            hsvImg.at<Vec3f>(i,j)[1] = S;
            hsvImg.at<Vec3f>(i,j)[2] = V;

        }
    }
    return hsvImg;
}
void inverse_H(Mat &img)
{
    int row = img.rows;
    int col = img.cols;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            img.at<Vec3f>(i,j)[0] += 180;
            if(img.at<Vec3f>(i,j)[0] > 360) img.at<Vec3f>(i,j)[0] -= 360;
        }
    }
}
Mat HSV2BGR(Mat img)
{
   float R,G,B;
   int row = img.rows;
   int col = img.cols;
   Mat returnImg(row,col,CV_8UC3);
   for(int i=0; i<row; i++)
   {
       for(int j=0; j<col; j++)
       {
           float C = img.at<Vec3f>(i,j)[1]; //S
           float H_ = img.at<Vec3f>(i,j)[0]/60; //H
           float V = img.at<Vec3f>(i,j)[2];//V
           float X = C*(1-fabs(fmod(H_,2)-1));
           if(H_>=0 && H_<1)
           {
               R = V-C+C;
               G = V-C+X;
               B = V-C;
           }else if(H_>=1 && H_<2)
           {
               R = V-C+X;
               G = V-C+C;
               B = V-C; 
           }else if(H_>=2 && H_<3)
           {
               R = V-C;
               G = V-C+C;
               B = V-C+X; 
           }else if(H_>=3 && H_<4)
           {
               R = V-C;
               G = V-C+X;
               B = V-C+C; 
           }else if(H_>=4 && H_<5)
           {
               R = V-C+X;
               G = V-C;
               B = V-C+C; 
           }else if(H_>=5 && H_<6)
           {
               R = V-C+C;
               G = V-C;
               B = V-C+X; 
           }else
           {
               R = V-C;
               G = V-C;
               B = V-C;
           }

           returnImg.at<Vec3b>(i,j)[0] = B*255;
           returnImg.at<Vec3b>(i,j)[1] = G*255;
           returnImg.at<Vec3b>(i,j)[2] = R*255;
           
       }
   }
   return returnImg;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    Mat hsv_img = BGR2HSV(srcImg);
    inverse_H(hsv_img);
    Mat result_img = HSV2BGR(hsv_img);

    imwrite("../pictures_results/q5.jpg", result_img);
    imshow("BGR2HSV", result_img);
    waitKey(0);
    destroyAllWindows();
}