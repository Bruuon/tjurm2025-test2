#include "impls.h"
#include <vector>


std::vector<std::vector<cv::Point>> find_contours(const cv::Mat &input)
{
  /**
   * 要求：
   * 使用cv::findContours函数，从输入图像（3个通道）中找出所有的最内层轮廓。
   * 将它们保存起来作为函数返回值就行。contours的中文意思就是轮廓。
   *
   * 提示：
   * 1. 使用cv::imshow来查看输入图像。
   * 2. 使用cv::drawContours来在一张图上绘制轮廓。
   * 3. 直接使用原图一般而言不利于轮廓的寻找，可以做一些简单的处理。
   * 4. findContours函数可以返回轮廓的层次结构，理解层次结构的保存方式并使用它（重点）。
   *
   * 通过条件：
   * 运行测试点，你找到的轮廓与答案的轮廓一样就行。
   */
  std::vector<std::vector<cv::Point>> res;
  // IMPLEMENT YOUR CODE HERE
  cv::Mat grayImg;
  cv::cvtColor(input, grayImg, cv::COLOR_BGR2GRAY);
  cv::threshold(grayImg, grayImg, 50, 255, cv::THRESH_BINARY);

  // THe idea is simple, just consider the contour which doesn't have child.
  cv::Mat contourOutput = grayImg.clone();
  std::vector<std::vector<cv::Point>> contours;
  // hierarchy – Optional output vector (e.g. std::vector<cv::Vec4i>),
  // containing information about the image topology. It has as many elements as
  // the number of contours. For each i-th contour contours[i], the elements
  // hierarchy[i][0] , hierarchy[i][1] , hierarchy[i][2] , and hierarchy[i][3]
  // are set to 0-based indices in contours of the next and previous contours at
  // the same hierarchical level, the first child contour and the parent
  // contour, respectively. If for the contour i there are no next, previous,
  // parent, or nested contours, the corresponding elements of hierarchy[i] will
  // be negative.
  std::vector<cv::Vec4i> hierarchy;
  cv::findContours(contourOutput, contours, hierarchy, cv::RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);

  // iterate through each contour
  for (size_t i = 0; i < contours.size(); i = hierarchy[i][0]) {
    // if there are no nested contours, then the current contour is an innermost
    // contour
    if (hierarchy[i][2] < 0) {
      res.push_back(contours[i]);
    }
  }

  cv::Mat contourImage(input.size(), CV_8UC3, cv::Scalar(0, 0, 0));
  cv::Scalar colors[3];
  colors[0] = cv::Scalar(255, 0, 0);
  colors[1] = cv::Scalar(0, 255, 0);
  colors[2] = cv::Scalar(0, 0, 255);
  for (size_t i = 0; i < res.size(); ++i) {
    cv::drawContours(contourImage, res, i, colors[i % 3]);
  }

  cv::imshow("Input Image: ", input);
  cv::moveWindow("Input Image", 0, 0);
  cv::imshow("Contours", contourImage);
  cv::waitKey(0);

  return res;
}