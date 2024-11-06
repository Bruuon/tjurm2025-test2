#include "impls.h"


cv::Mat my_resize(const cv::Mat &input, float scale)
{
  /**
   * 要求：
   *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
   * 用cv::resize。resize算法的内容自行查找学习，不是很难。
   *
   * 提示：
   * 无。
   *
   * 通过条件：
   * 运行测试点，你的结果跟答案长的差不多就行。
   */
  const int new_rows = input.rows * scale, new_cols = input.cols * scale;
  // IMPLEMENT YOUR CODE HERE
  int h = input.rows, w = input.cols, c = input.channels();

  float x0, y0, dx, dy;
  int x1, x2, x3, x4, y1, y2, y3, y4;
  cv::Mat_<cv::Vec3f> output(new_cols, new_rows, input.type());
  // float *Q, *P1, *P2, *P3, *P4;
  typedef cv::Vec<float, 3> PIXEL;
  input.type()
    for (int y = 0; y < new_rows; ++y) {
      for (int x = 0; x < new_cols; ++x) {
        // center point
        x0 = x / scale; y0 = y / scale;
        // top-left
        x1 = static_cast<int>(x0) % w; y1 = static_cast<int>(y0) % h;
        // top-right
        x2 = (x1 + 1) % w; y2 = y1;
        // bottom-left
        x3 = x1; y3 = (y1 + 1) % h;
        // bottom-right
        x4 = (x1 + 1) % w; y4 = (y1 + 1) % h;

        dx = x0 - x1; dy = y0 - y1;

        // Q = (*pOut)[y][x];
        cv::Vec3f Q = output.at<cv::Vec3f>(y, x);
        // P1 = (*pIn)[y1][x1]; P2 = (*pIn)[y2][x2];
        // P3 = (*pIn)[y3][x3]; P4 = (*pIn)[y4][x4];
        cv::Vec3f P1 = input.at<input.type()>(y1, x1);
        // x0 %= w; y0 %= h;
        for (int i = 0; i < c; ++i) {
          // (*outMat)[y][x][i] = (*inMat)[y0][x0][i];
          Q[i] = P1[i] * (1 - dx) * (1 - dy) + P2[i] * dx * (1 - dy) + P3[i] * (1 - dx) * dy + P4[i] * dx * dy;
        }
      }
    }


  return output;
}