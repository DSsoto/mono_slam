/*
 Program: demos uses of the momo_slam library
 Author: David Soto
 Created: 8/15/2016
 Last Modified: 8/17/2016
*/

#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <utils.hpp>

 // Main using images from directory
int main_directory(std::string img_dir, std::string img_extension);

// Main using v4l webcam via OpenCV video capture
int main_v4l(int cam_idx);

// Main using video file via OpenCV VideoCapture
int main_video(std::string vid_path);

using namespace std;
using namespace cv;

int main(int argc, char** argv){
    stringstream usage;
  {
    string pad {"      "};
    int opt_w {10};
    usage << left << "usage: " << "mono_slam " << "[OPTION]" << endl
      << pad << setw(opt_w) << "-W=<IDX>" << pad 
        << "use v4l camera at index IDX" << endl
      << pad << setw(opt_w) << "-V=<PATH>" << pad
        << "use video at PATH" << endl
      << pad << setw(opt_w) << "-D=<DIR>" << pad 
        << "use images at directory DIR" << endl
      << pad << setw(opt_w) << "-E=<EXT>" << pad 
        << "set image extension to EXT (only for use with -D)" << endl; 
  }
    if(argc < 2){   // at least two arguments required
        cerr << usage.str() << endl;
        return -1;
    }
  
  bool cam_flag = false;
  bool vid_flag = false;
  bool dir_flag = false;
  bool ext_flag = false;
  char opt = 0;
  int camera_idx = -1;
  string video_path;
  string img_dir;
  string img_extension;
  while((opt = getopt(argc, argv, "W:V:D:E:")) != -1){
    static int i = 0;
    cout << "parse" << i++ << ": opt=" << opt << " arg=" << optarg << endl;

    switch (opt){
      case 'W':
        cam_flag = true;
        camera_idx = atoi(optarg);
        break;
      case 'V':
        vid_flag = true;
        video_path = optarg;
        break;
      case 'D':
        dir_flag = true;
        img_dir = optarg;
        break;
      case 'E':
        ext_flag = true;
        img_extension = optarg;
        break;
      case '?':
        cout << "exiting" << endl;
        opt = -1; // exit loop
        break;
    }
    // cout << "optopt: " << opt << "\t optarg: " << optarg << endl;
  }

  cout << "camera_idx: " << camera_idx << endl;
  cout << "video_path: " << video_path << endl;
  cout << "img_dir: " << img_dir << endl;
  cout << "img_extension: " << img_extension << endl;
  
  // check for directory mode
  if(dir_flag){
    if(!ext_flag){
      cout << "size: " << img_extension.size() << endl;
      cerr << "Error: Option -E, along with the image extension(w/o period),"
        << " must be supplied when using directory mode(option -D)." << endl
        << endl << usage.str() << endl;
    }
    main_directory(img_dir, img_extension); 
  }
  else if (cam_flag){
    main_v4l(camera_idx);
  }
  else if (vid_flag){
    main_video(video_path);
  }
  else{
    cerr << "Unable to parse arguments." << endl << usage.str() << endl;
  }
}

int main_directory(string img_dir, string img_extension){
  static int i = 0;
  cout << "Directory mode!" << endl;
  Mat most_current_frame {};
  ImageDirectory frame_src {img_dir, img_extension, most_current_frame};

  // iterate through frames from frame_src
  while(frame_src.ok()){

    if(frame_src.ok()) frame_src.get_next_frame();
    imshow("current_frame", most_current_frame);
    waitKey(1);
    cout << "ok=" << frame_src.ok() << " i=" << ++i << endl;
  }

  return EXIT_SUCCESS;
}


int main_v4l(int cam_idx){
  return 0;
}


int main_video(string vid_path){
  return 0;
}
