/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * AS IS BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */

/*
 * Copyright (c) 2018, Open AI Lab
 * Author: chunyinglv@openailab.com
 */

/* modified for using OpenCV DNN
   jia.wu@opencv.org.cn */

#ifndef __MTCNN_HPP__
#define __MTCNN_HPP__

#include "opencv2/opencv.hpp"
#include "mtcnn_utils.hpp"


class mtcnn
{
public:
    int minsize_;

    float conf_p_threshold_;
    float conf_r_threshold_;
    float conf_o_threshold_;

    float nms_p_threshold_;
    float nms_r_threshold_;
    float nms_o_threshold_;

    mtcnn(int minsize = 60, float conf_p = 0.6, float conf_r = 0.7, float conf_o = 0.8, float nms_p = 0.5,
          float nms_r = 0.7, float nms_o = 0.7);
    ~mtcnn()
    {
    };

    int load_3model(const std::string& model_dir);

    void detect(cv::Mat img, std::vector<face_box>& face_list);

protected:
    cv::dnn::Net PNet;
    cv::dnn::Net RNet;
    cv::dnn::Net ONet;

    int run_PNet(const cv::Mat& img, scale_window& win, std::vector<face_box>& box_list);
    int run_RNet(const cv::Mat& img, std::vector<face_box>& pnet_boxes, std::vector<face_box>& output_boxes);
    int run_ONet(const cv::Mat& img, std::vector<face_box>& rnet_boxes, std::vector<face_box>& output_boxes);
};

#endif
