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
  int new_rows = input.rows * scale, new_cols = input.cols * scale;
  // IMPLEMENT YOUR CODE HERE
  int input_rows = input.rows, input_cols = input.cols, channels = input.channels();

  float x0, y0, dx, dy;
  int x1, x2, x3, x4, y1, y2, y3, y4;
  
  CV_Assert(input.depth() == CV_8U);
  cv::Mat output = cv::Mat::zeros(new_rows, new_cols, input.type());

  cv::Vec3b P1, P2, P3, P4, *Q;
  
  for (int i = 0; i < new_rows; ++i) {
    for (int j = 0; j < new_cols; ++j) {
      // center point
      x0 = j / scale; y0 = i / scale;
      // top-left
      x1 = static_cast<int>(x0) % input_cols; y1 = static_cast<int>(y0) % input_rows;
      // top-right
      x2 = (x1 + 1) % input_cols; y2 = y1;
      // bottom-left
      x3 = x1; y3 = (y1 + 1) % input_rows;
      // bottom-right
      x4 = (x1 + 1) % input_cols; y4 = (y1 + 1) % input_rows;

      dx = x0 - x1; dy = y0 - y1;

      P1 = input.at<cv::Vec3b>(y1, x1);
      P2 = input.at<cv::Vec3b>(y2, x2);
      P3 = input.at<cv::Vec3b>(y3, x3);
      P4 = input.at<cv::Vec3b>(y4, x4);

      Q = &output.at<cv::Vec3b>(i, j);
      for (int i = 0; i < channels; ++i) {
        (*Q)[i] = P1[i] * (1 - dx) * (1 - dy) + P2[i] * dx * (1 - dy) + P3[i] * (1 - dx) * dy + P4[i] * dx * dy;
        // Q[i] = input.at<cv::Vec3b>(i%input_rows, j%input_cols)[i];
      }
    }
  }


  return output;
}