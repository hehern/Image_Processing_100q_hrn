#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

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
    Mat resImg = Grayscale(srcImg);
    imwrite("../pictures_results/q2.jpg",resImg);
    imshow("Grayscale", resImg);
    waitKey(0);
    destroyAllWindows();
}