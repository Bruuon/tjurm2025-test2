#include "impls.h"
#include <unordered_map>


std::unordered_map<int, cv::Rect> roi_color(const cv::Mat &input)
{
  /**
   * INPUT: 一张彩色图片, 路径: opencv/assets/roi_color/input.png
   * OUTPUT: 一个 unordered_map, key 为颜色(Blue: 0, Green: 1, Red: 2), value 为对应颜色的矩形区域(cv::Rect)
   * TODO:
   *  1. 找到图片中三个颜色的轮廓
   *  2. 计算出三处矩形的颜色
   *  3. 返回一个 unordered_map, key 为颜色, value 为cv::Rect (表示矩形的位置)
   * HINT:
   *  1. 预处理
   *    1. 在学习 findContours 时，我们提供的输入图片已经是一个二值图像了，
   *       但是在这里，input 是一个彩色图形。
   *       而 findContours 的 input 最好是一个二值图像。
   *    2. findContours 处理时，一般是在一个黑色背景上，找白色的轮廓
   *       (因此在二值化时，你可能需要考虑一下 cv::THRESH_BINARY_INV 选项
   *       同时，建议了解一下 cv::THRESH_OTSU 选项以及他们如何配合使用)
   *    3. 因此，预处理流程如下:
   *      1. 将 input 转换成灰度图像
   *      2. 对灰度图像进行二值化，得到黑底的二值化图
   *   2. 找到三个矩形 (findContours)
   *   3. 对找到的三个矩形，分别进行如下计算:
   *      1. 使用 cv::boundingRect 将轮廓转换成矩形 cv::Rect
   *      2. 使用该 cv::Rect 得到 input 中的 ROI区域 (写法: roi = input(rect))
   *      3. 使用统计的方法，得到该 ROI 区域的颜色
   *      4. 将颜色 和 矩形位置 存入 map 中
   */
  std::unordered_map<int, cv::Rect> res;
  // IMPLEMENT YOUR CODE HERE
  CV_Assert(input.channels() == 3 && input.depth() == CV_8U);

  cv::Mat img;
  cv::cvtColor(input, img, cv::COLOR_RGB2GRAY);
  // Use Otsu algorithm to choose the optimal threshold value. Currently, the
  // Otsu's and Triangle methods are implemented only for 8-bit single-channel
  // images.
  cv::threshold(img, img, 50, 255, cv::THRESH_BINARY_INV | cv::THRESH_OTSU);

  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(img, contours, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);
  cv::Mat roi;
  int idxB = 0, idxG = 1, idxR = 2;
  std::vector<double> chAvg(3);
  cv::Vec3b  P;
  for (int k = 0; k < contours.size(); ++k) {
    std::cout << "contour " << k << ": " << std::endl;
    cv::Rect rect = cv::boundingRect(contours[k]);
    roi = cv::Mat(input, rect);
    // cv::imshow("roi", roi);
    // cv::waitKey(0);
    for (int i = 0; i < roi.rows; ++i) {
      for (int j = 0; j < roi.cols; ++j) {
        P = roi.at<cv::Vec3b>(i, j);
        double n = (i + 1) * (j + 1);
        for (int c = 0; c < roi.channels(); ++c) {
          chAvg[c] = n > 1 ? ((n - 1) / n * chAvg[c] + P[c] / n) : P[c];
        }
      }
    }
    int idxBGR = std::max_element(chAvg.begin(), chAvg.end()) - chAvg.begin();
    std::cout << chAvg[0] << ' ' << chAvg[1] << ' ' << chAvg[2] << " color: " << idxBGR << std::endl;
    res.insert({ idxBGR, rect });
  }

  return res;
}
