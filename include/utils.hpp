#pragma once

#include <queue>
#include <functional>

#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>


// Common interface for all ImageSources
class ImageSource{
public:
ImageSource(){};
~ImageSource(){};
virtual void get_next_frame() = 0;
virtual bool ok(){ return !fail_bit; }

protected:
bool fail_bit {false};
};

class ImageDirectory : public ImageSource {
public:
    ImageDirectory(std::string directory_path, std::string img_extension, cv::Mat &output_mat);
    ~ImageDirectory(){};
    void get_next_frame();

private:
std::string dir_path;
std::string extension;
cv::Mat &out_mat;
size_t curent_path_iter;
std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string>> img_path_vec {};
};


class VideoSource : public ImageSource{
public:
    VideoSource(){};
    ~VideoSource(){};
private:
    std::string file_path;
};


class WebcamSource : public ImageSource{
public:
    WebcamSource(){};
    ~WebcamSource(){};
private:
    int v4l_camera_idx;
};
