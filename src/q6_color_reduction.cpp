#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

void ColorReduction(Mat &img)
{
    int row = img.rows;
    int col = img.cols;
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int channel=0; channel<3; channel++)
            {
                int pixel = img.at<Vec3b>(i,j)[channel];
                if(pixel>=0 && pixel<64) pixel = 32;
                else if(pixel>=64 && pixel<128) pixel = 96;
                else if(pixel>=128 && pixel<192) pixel = 160;
                else if(pixel>=192 && pixel<256) pixel = 224;
                img.at<Vec3b>(i,j)[channel] = pixel;
            }
        }
    }

}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori.jpg");
    ColorReduction(srcImg);

    imwrite("../pictures_results/q6.jpg", srcImg);
    imshow("color_reduction", srcImg);
    waitKey(0);
    destroyAllWindows();
}