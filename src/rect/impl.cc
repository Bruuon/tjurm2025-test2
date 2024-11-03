#include "impls.h"

std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat &input)
{
  /**
   * 要求：
   * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
   * 最小面积外接矩形。所需要的函数自行查找。
   *
   * 通过条件：
   * 运行测试点，你找到的矩形跟答案一样就行。
  */
  std::pair<cv::Rect, cv::RotatedRect> res;
  // IMPLEMENT YOUR CODE HERE
  cv::Mat grayImg;
  cv::cvtColor(input, grayImg, cv::COLOR_BGR2GRAY);
  cv::threshold(grayImg, grayImg, 127, 255, cv::THRESH_BINARY);

  // THe idea is simple, just consider the contour which doesn't have parent.
  cv::Mat contourOutput = grayImg.clone();
  std::vector<std::vector<cv::Point>> contours, outer;
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
    // if there are no parent contours, then the current contour is an outermost
    // contour
    if (hierarchy[i][3] < 0) {
      res.first = cv::boundingRect(contours[i]);
      res.second = cv::minAreaRect(contours[i]);
      break;
    }
  }

  return res;
}