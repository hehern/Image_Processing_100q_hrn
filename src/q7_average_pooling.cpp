#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
Mat average_pooling(Mat img, int R)
{
    int row = img.rows;
    int col = img.cols;
    Mat returnImg(row,col,CV_8UC3);

    for(int i=0; i<row; i+=R)
    {
        for(int j=0; j<col; j+=R)
        {
            int pixel_R, pixel_G, pixel_B;
            for(int k=i; k<i+R; k++)
            {
                for(int m=j; m<j+R; m++)
                {
                    pixel_B += img.at<Vec3b>(k,m)[0];
                    pixel_G += img.at<Vec3b>(k,m)[1];
                    pixel_R += img.at<Vec3b>(k,m)[2];
                }
            }
            pixel_B/=(R*R);
            pixel_G/=(R*R);
            pixel_R/=(R*R);
            for(int k=i; k<i+R; k++)
            {
                for(int m=j; m<j+R; m++)
                {
                    returnImg.at<Vec3b>(k,m)[0] = pixel_B;
                    returnImg.at<Vec3b>(k,m)[1] = pixel_G;
                    returnImg.at<Vec3b>(k,m)[2] = pixel_R;
                }
            }
        }
    }
    return returnImg;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    Mat resultImg = average_pooling(srcImg,8);

    imwrite("../pictures_results/q7.jpg", resultImg);
    imshow("average_pooling", resultImg);
    waitKey(0);
    destroyAllWindows();
}