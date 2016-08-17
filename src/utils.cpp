#include <utils.hpp>

using namespace std;
using namespace cv;

ImageDirectory::ImageDirectory(string directory_path, string img_extension, Mat &output_mat)
  : dir_path(directory_path)
  , extension(img_extension)
  , out_mat(output_mat)
{
  cout << "constructing ImageDirectory" << endl;
  // check that directory exists
  namespace fs = boost::filesystem;
  fs::path dir_boost_path {dir_path};
  if(fs::is_directory(dir_boost_path)){

    // iterate through all files in directory
    fs::directory_iterator dir_end;  // default ctor --> past-the-end
    for(fs:: directory_iterator dir_itr(dir_boost_path); dir_itr != dir_end; ++dir_itr){

      string path_str {dir_itr->path().filename().string()};
      // collect all files that match img extension
      if(path_str.compare(path_str.size() - extension.size(), extension.size(), extension) == 0){
        img_path_vec.push(dir_itr->path().string());  // automatically sorted by priority queue
      }
    }
  }
  else {
    cerr << "Error: " << directory_path << " is not a valid directory." << endl;
    fail_bit = true;
  }
}

void ImageDirectory::get_next_frame(){
  // can be on if there are no more available frames
  if(fail_bit){
    cerr << "Fail bit indicates that an operation has compromised the integrity"
      << "of this(" << this << ") ImageSource object. remember to call the"
      << "ok() method before requesting a new frame." << endl;
      return;
  }
  if(!img_path_vec.empty()){  // check there are more images to read
    Mat temp_mat {};
    temp_mat = imread(img_path_vec.top(), CV_LOAD_IMAGE_GRAYSCALE);

    if(!temp_mat.empty()){  // check img file was read was successfully
      out_mat = temp_mat;   // update output cv::Mat's image data
      img_path_vec.pop();   // remove loaded img path
    }
    else{
      cerr << "Failed to read image from" << img_path_vec.top() << "." << endl;
      fail_bit = true;
    }
  }
  else{
    cout << "Finished iterating through images in " << dir_path << "." << endl;
    fail_bit = true;
  }
}
