//  Created by jimmy on 2017-01-21.
//  Copyright (c) 2017 Nowhere Planet. All rights reserved.
//

#ifndef __btrf_forest_builder__
#define __btrf_forest_builder__

#include <stdio.h>
#include "btrf_forest.hpp"
#include "btrf_util.hpp"

/*
Train a random forest
Example:
 BTRFForestBuilder builder;
 Forest model; // this the training result
 builder.setTreeParameter(...);
 builder.setDatasetParameter(...);
 builder.buildModel(model, ...);
 model.saveModel('model.txt'); // save the training result 
*/

class BTRFForestBuilder
{
    typedef BTRFForest Forest;
    typedef SCRFRandomSample Feature;
    typedef BTRFTreeParameter TreeParameter;
private:
    TreeParameter tree_param_;
    DatasetParameter dataset_param_;
    
    typedef SCRFRandomSample FeatureType;
    typedef BTRFTree TreeType;
    
public:
    
    // before training: set tree and dataset parameters
    void setTreeParameter(const TreeParameter & param);
    void setDatasetParameter(const DatasetParameter & param);

    
    // builder a model from features
    // model: output, trained model
    // features: random pixel location and local patch descriptors
    // label: 3D location
    // rgb_images: training images
    // max_check: back tracking parameter, for validation purpose
    //            not influence the model
    // model_file_name: optional,
    
    bool buildModel(Forest & model,
                    const vector<Feature> & features,
                    const vector<VectorXf> & labels,
                    const vector<cv::Mat> & rgb_images,
                    const int max_check,
                    const char * model_file_name = NULL) const;
    
    // builder a model from sequence of RGB image, depth image and pose files
    // trees are sequential trained,
    // model: output, trained model
    // rgb_img_files: file names of RGB images,  8bit unsigned char
    // depth_img_files: file names of depth images, 16bit, unsigned short int
    // pose_files: camera pose file, format as pose file in
    // https://www.microsoft.com/en-us/research/project/rgb-d-dataset-7-scenes/#
    // 4x4 camera to world coordinate transformation matrix
    // save_memory: save memory in training, set it as true when the tree is very large
    // model_file_name: model file name, .txt file
    bool buildModel(Forest& model,
                    const vector<string> & rgb_img_files,
                    const vector<string> & depth_img_files,
                    const vector<string> & pose_files,
                    const int max_check,
                    const char *model_file_name) const;
    
private:
    // out of bag validation
    bool estimateValidataionError(const TreeType & tree,
                                  const vector<string> & rgb_img_files,
                                  const vector<string> & depth_img_files,
                                  const vector<string> & pose_files,
                                  const int sample_frame_num,
                                  const int max_check,
                                  const double error_threshold) const;
    
};


#endif /* defined(__btrf_forest_builder__) */
