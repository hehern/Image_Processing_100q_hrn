#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
Mat max_pooling(Mat img, int R)
{
    int row = img.rows;
    int col = img.cols;
    Mat returnImg(row,col,CV_8UC3);

    for(int i=0; i<row; i+=R)
    {
        for(int j=0; j<col; j+=R)
        {
            int chanel = img.channels();
            for(int t=0; t<chanel; t++)
            {
                int max_pixel = 0;
                for(int k=i; k<i+R; k++)
                {
                    for(int m=j; m<j+R; m++)
                    {
                        if(img.at<Vec3b>(k,m)[t] > max_pixel)
                        max_pixel = img.at<Vec3b>(k,m)[t];
                    }
                }
                for(int k=i; k<i+R; k++)
                {
                    for(int m=j; m<j+R; m++)
                    {
                        returnImg.at<Vec3b>(k,m)[t] = max_pixel;
                    }
                }
            }

        }
    }
    return returnImg;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    Mat resultImg = max_pooling(srcImg,8);

    imwrite("../pictures_results/q8.jpg", resultImg);
    imshow("average_pooling", resultImg);
    waitKey(0);
    destroyAllWindows();
}