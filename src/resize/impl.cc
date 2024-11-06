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
  int h = input.rows, w = input.cols, c = input.channels();

  float x0, y0, dx, dy;
  int x1, x2, x3, x4, y1, y2, y3, y4;
  new_rows=input.rows;new_cols=input.cols;
  cv::Mat_<cv::Vec3d> output=cv::Mat(1000, 1000, input.type());
  std::cout << input.rows << ' ' << input.cols << std::endl;
  std::cout << new_rows << ' ' << new_cols << ' ' << c << std::endl;
  for (int row = 0; row < new_rows; ++row) {
    for (int col = 0; col < new_cols; ++col) {
      // for (int row = 0; row < std::min(input.rows, output.rows); ++row) {
      //   for (int col = 0; col < std::min(input.cols, output.cols); ++col) {

      // // center point
      // x0 = col / scale; y0 = row / scale;
      // // top-left
      // x1 = static_cast<int>(x0) % w; y1 = static_cast<int>(y0) % h;
      // // top-right
      // x2 = (x1 + 1) % w; y2 = y1;
      // // bottom-left
      // x3 = x1; y3 = (y1 + 1) % h;
      // // bottom-right
      // x4 = (x1 + 1) % w; y4 = (y1 + 1) % h;

      // dx = x0 - x1; dy = y0 - y1;

      // const cv::Vec3d &P1 = input.at<cv::Vec3d>(y1, x1);
      // const cv::Vec3d &P2 = input.at<cv::Vec3d>(y2, x2);
      // const cv::Vec3d &P3 = input.at<cv::Vec3d>(y3, x3);
      // const cv::Vec3d &P4 = input.at<cv::Vec3d>(y4, x4);

      cv::Vec3d &Q = output.at<cv::Vec3d>(row, col);
      for (int i = 0; i < c; ++i) {
        // Q[i] = P1[i] * (1 - dx) * (1 - dy) + P2[i] * dx * (1 - dy) + P3[i] * (1 - dx) * dy + P4[i] * dx * dy;
        Q[i] = input.at<cv::Vec3d>(row , col) [i];
      }
    }
  }


  return output;
}