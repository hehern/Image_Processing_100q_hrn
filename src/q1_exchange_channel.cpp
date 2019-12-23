//需求：将BGR图像替换成RGB图像
//先验知识：
//1.cv.imread()的intflag参数。默认为1
//                      >0返回三通道彩色图片,顺序为BGR
//                      =0返回灰度图片
//                      <0返回包含Alhpa通道的图像
//2.多通道Mat元素的访问：at(rows,cols)
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

void swap(Mat& srcImg)
{
    for(int i=0; i<srcImg.rows; i++)
    {
        for(int j=0; j<srcImg.cols; j++)
        {
            int temp = srcImg.at<Vec3b>(i,j)[0];//B->temp
            srcImg.at<Vec3b>(i,j)[0] = srcImg.at<Vec3b>(i,j)[2];//R->B
            srcImg.at<Vec3b>(i,j)[2] = temp;//temp->R
        }
    }
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    swap(srcImg);
    imwrite("../pictures_results/q1.jpg", srcImg);
    imshow("exchange_channel", srcImg);
    waitKey(0);
    destroyAllWindows();
    
    return 0;
}