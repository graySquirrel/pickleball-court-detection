#include <opencv2/opencv.hpp>

#include "TimeMeasurement.h"
#include "Line.h"
#include "CourtLinePixelDetector.h"
#include "CourtLineCandidateDetector.h"
#include "TennisCourtFitter.h"
#include "DebugHelpers.h"

using namespace cv;

int main(int argc, char **argv)
{
  //  std::cout << cv::getBuildInformation() << std::endl;

  TimeMeasurement::debug = true;
  CourtLinePixelDetector::debug = false;
  CourtLineCandidateDetector::debug = false;
  TennisCourtFitter::debug = false;

  if (argc != 3)
  {
    std::cout << "Usage: ./detect image_path output_path" << std::endl;
    std::cout << "       image_path:  path to an input image file." << std::endl;
    std::cout << "       output_path: path to where to write the output files" << std::endl;
    std::cout << "            		testframe.png, testframeWithLines.png, and court.txt" << std::endl;
    return -1;
  }
  std::string filename(argv[1]);
  std::string outpath(argv[2]);

  std::cout << "Reading file " << filename << std::endl;
  //VideoCapture vc(filename);
  //if (!vc.isOpened())
  //{
  //  std::cerr << "Cannot open file " << filename << std::endl;
  //  return 1;
  //}
  //printVideoInfo(vc);
  Mat frame = imread(filename, IMREAD_COLOR);
  //int fps = int(vc.get(CAP_PROP_FPS));
  //int inputSeconds = 20;
  //if (argc == 4)
  //{
  //  long arg = strtol(argv[3], NULL, 10);
  //  inputSeconds = int(arg);
  //}
  // int frameIndex = int(vc.get(CAP_PROP_FRAME_COUNT)) / 2;
  //int frameIndex = int(inputSeconds * fps);
  //vc.set(CAP_PROP_POS_FRAMES, frameIndex);
  //if (!vc.read(frame))
  if (frame.empty())
  {
    std::cerr << "Failed to read image " << filename << std::endl;
    return 2;
  }
  //std::cout << "Reading frame with index " << frameIndex << std::endl;

  CourtLinePixelDetector courtLinePixelDetector;
  CourtLineCandidateDetector courtLineCandidateDetector;
  TennisCourtFitter tennisCourtFitter;

  std::cout << "Starting court line detection algorithm..." << std::endl;
  try
  {
    TimeMeasurement::start("LineDetection");
    Mat binaryImage = courtLinePixelDetector.run(frame);
    std::vector<Line> candidateLines = courtLineCandidateDetector.run(binaryImage, frame);
    TennisCourtModel model = tennisCourtFitter.run(candidateLines, binaryImage, frame);
    int elapsed_seconds = TimeMeasurement::stop("LineDetection");
    std::cout << "Elapsed time: " << elapsed_seconds << "s." << std::endl;
    std::string outFilename;
    outFilename = outpath + "/testframe.png";
    imwrite(outFilename, frame); // write out the frame before marking
    //imwrite("testframe.png", frame); // write out the frame before marking

    model.drawModel(frame);
    //displayImage("Result - press key to exit", frame);
    outFilename = outpath + "/testframeWithLines.png";
    imwrite(outFilename, frame); // write out the frame before marking
    //imwrite("testframeWithLines.png", frame); // write out the frame before marking

    outFilename = outpath + "/court.txt";
    model.writeToFile(outFilename);
    std::cout << "Result written to " << outFilename << std::endl;
  }
  catch (std::runtime_error &e)
  {
    std::cout << "Processing error: " << e.what() << std::endl;
    return 3;
  }

  return 0;
}
