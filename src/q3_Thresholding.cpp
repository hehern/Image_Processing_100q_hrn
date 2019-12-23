#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

Mat Thresholding(Mat& img)
{
    int row = img.rows;
    int col = img.cols;
    Mat grayimg(row, col, CV_8UC1);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            int gray = 0.2126*img.at<Vec3b>(i,j)[2] + 0.7152*img.at<Vec3b>(i,j)[1] + 0.0722*img.at<Vec3b>(i,j)[0];
            gray>128 ? grayimg.at<uchar>(i,j)=255 : grayimg.at<uchar>(i,j)=0;
        }
    }
    return grayimg;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    Mat resImg = Thresholding(srcImg);

    imwrite("../pictures_results/p3.jpg", resImg);
    imshow("Thresholding", resImg);
    waitKey(0);
    destroyAllWindows();
}