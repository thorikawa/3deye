#include "glcv.hpp"

void screenshot (const int width, const int height, const char* filename, const int buffer) {
  glReadBuffer(buffer);
  cv::Mat img(height, width, CV_8UC3);
  cv::Mat flipped(height, width, CV_8UC3);
  glPixelStorei(GL_PACK_ALIGNMENT, (img.step & 3) ? 1 : 4);
  glPixelStorei(GL_PACK_ROW_LENGTH, img.step/img.elemSize());
  glReadPixels(0, 0, img.cols, img.rows, GL_BGR, GL_UNSIGNED_BYTE, img.data);
  cv::flip(img, flipped, 0);
  imwrite(filename, flipped);
  return;
}
