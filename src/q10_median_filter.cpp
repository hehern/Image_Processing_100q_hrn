#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;
Mat median_filter(Mat img, int dimen)
{
    int row = img.rows;
    int col = img.cols;
    int channel = img.channels();
    int R = floor(dimen/2);
    Mat retrunImg = Mat::zeros(row, col, CV_8UC3);
    for(int i=0; i<row; i++)
    {
        for(int j=0; j<col; j++)
        {
            for(int t=0; t<channel; t++)
            {
                int pixel = 0;
                if(i>=R && i<row-R && j>=R && j<col-R)
                {
                    vector<int> pixels;
                    for(int m=-R; m<=R; m++)
                    {
                        for(int n=-R; n<=R; n++)
                        {
                            pixels.push_back(img.at<Vec3b>(i+m,j+n)[t]);
                        }
                    }
                    sort(pixels.begin(), pixels.end());
                    pixels.size()%2==0 ? pixel = (pixels[pixels.size()/2-1] + pixels[pixels.size()/2])/2 : pixel = pixels[pixels.size()/2];

                }
                retrunImg.at<Vec3b>(i,j)[t] = pixel;
            }
        }
    }
    return retrunImg;
}
int main(int argc, char *argv[])
{
    Mat srcImg = imread("../pictures_origin/imori_noise.jpg");
    Mat resultImg = median_filter(srcImg, 3);

    imwrite("../pictures_results/q10.jpg", resultImg);
    imshow("median_filter", resultImg);
    waitKey(0);
    destroyAllWindows();

}