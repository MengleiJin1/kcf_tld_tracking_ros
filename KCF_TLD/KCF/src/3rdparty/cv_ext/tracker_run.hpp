/*M///////////////////////////////////////////////////////////////////////////////////////
//
// IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
// By downloading, copying, installing or using the software you agree to this license.
// If you do not agree to this license, do not download, install,
// copy or use the software.
//
// License Agreement
// For Open Source Computer Vision Library
// (3-clause BSD License)
//
// Copyright (C) 2000-2015, Intel Corporation, all rights reserved.
// Copyright (C) 2009-2011, Willow Garage Inc., all rights reserved.
// Copyright (C) 2009-2015, NVIDIA Corporation, all rights reserved.
// Copyright (C) 2010-2013, Advanced Micro Devices, Inc., all rights reserved.
// Copyright (C) 2015, OpenCV Foundation, all rights reserved.
// Copyright (C) 2015, Itseez Inc., all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the names of the copyright holders nor the names of the contributors
//   may be used to endorse or promote products derived from this software
//   without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall copyright holders or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//M*/

/*
// Original file: https://github.com/Itseez/opencv_contrib/blob/292b8fa6aa403fb7ad6d2afadf4484e39d8ca2f1/modules/tracking/samples/tracker.cpp
// + Author: Klaus Haag
// * Refactor file: Move target selection to separate class/file
// * Replace command line argumnets
// * Change tracker calling code
// * Add a variety of additional features
*/

#ifndef TRACKER_RUN_HPP_
#define TRACKER_RUN_HPP_

#include <tclap/CmdLine.h>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include "cf_tracker.hpp"
#include "tracker_debug.hpp"
#include "dsst_tracker.hpp"
#include "image_acquisition.hpp"

struct Parameters{
    std::string sequencePath;
    std::string outputFilePath;
    std::string imgExportPath;
    std::string expansion;
    cv::Rect initBb;
    int device = 0;
    int startFrame = 1;
    bool showOutput = true;
    bool paused;
    bool repeat;
    bool isMockSequence;
};

class TrackerRun
{
public:
    TrackerRun(std::string windowTitle);
    virtual ~TrackerRun();
  //  bool start(int argc, const char** argv);
    void setTrackerDebug(cf_tracking::TrackerDebug* debug);
    
    cv::Rect_<double> _boundingBox;
    Parameters _paras;
   // bool _isTrackerInitialzed = false;
    bool _targetOnFrame = false;
//private:
    Parameters parseCmdArgs(int argc,  char** argv);
    bool init(cv::Mat image_run);
   // bool run();
    bool update(cv::Mat image_run);
    void printResults(const cv::Rect_<double>& boundingBox, bool isConfident, double fps);

protected:
    virtual cf_tracking::CfTracker* parseTrackerParas(TCLAP::CmdLine& cmd, int argc,  char** argv) = 0;
private:
    cv::Mat _image;
    cf_tracking::CfTracker* _tracker;
    std::string _windowTitle;
   // Parameters _paras;
   // cv::Rect_<double> _boundingBox;
    ImageAcquisition _cap;
    std::ofstream _resultsFile;
    TCLAP::CmdLine _cmd;
    cf_tracking::TrackerDebug* _debug;
    int _frameIdx = 0;
    bool _isPaused = false;
    bool _isStep = false;
    bool _exit = false;
    bool _hasInitBox = false;
    bool _isTrackerInitialzed = false;
   // bool _targetOnFrame = false;
    bool _updateAtPos = false;
};

#endif
