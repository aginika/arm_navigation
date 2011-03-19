/*********************************************************************
* Software License Agreement (BSD License)
* 
*  Copyright (c) 2010, Willow Garage, Inc.
*  All rights reserved.
* 
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
* 
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
* 
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

/** \author E. Gil Jones */

#ifndef _MODEL_UTILS_H_
#define _MODEL_UTILS_H_

#include <tf/tf.h>
#include <planning_models/kinematic_state.h>
#include <motion_planning_msgs/RobotState.h>
#include <motion_planning_msgs/Constraints.h>
#include <motion_planning_msgs/OrderedCollisionOperations.h>

#include <planning_environment/util/kinematic_state_constraint_evaluator.h>
#include <geometric_shapes_msgs/Shape.h>
#include <visualization_msgs/Marker.h>
#include <motion_planning_msgs/LinkPadding.h>
#include <collision_space/environment.h>
#include <planning_environment_msgs/AllowedCollisionMatrix.h>

namespace planning_environment {

//returns true if the joint_state_map sets all the joints in the state, 
bool setRobotStateAndComputeTransforms(const motion_planning_msgs::RobotState &robot_state,
                                       planning_models::KinematicState& state);

void convertKinematicStateToRobotState(const planning_models::KinematicState& kinematic_state,
                                       const ros::Time& timestamp,
                                       const std::string& header_frame,
                                       motion_planning_msgs::RobotState &robot_state);

void applyOrderedCollisionOperationsToMatrix(const motion_planning_msgs::OrderedCollisionOperations &ord,
                                             collision_space::EnvironmentModel::AllowedCollisionMatrix& acm);

void convertFromACMToACMMsg(const collision_space::EnvironmentModel::AllowedCollisionMatrix& acm,
                            planning_environment_msgs::AllowedCollisionMatrix& matrix);

collision_space::EnvironmentModel::AllowedCollisionMatrix convertFromACMMsgToACM(const planning_environment_msgs::AllowedCollisionMatrix& matrix);

bool applyOrderedCollisionOperationsListToACM(const motion_planning_msgs::OrderedCollisionOperations& ordered_coll,
                                              const std::vector<std::string>& object_names,
                                              const std::vector<std::string>& att_names,
                                              const planning_models::KinematicModel* model,
                                              collision_space::EnvironmentModel::AllowedCollisionMatrix& matrix);
       
/*
void printAllowedCollisionMatrix(const std::vector<std::vector<bool> > &curAllowed,
                                 const std::map<std::string, unsigned int> &vecIndices) {
  size_t all_size = curAllowed.size();
  for(unsigned int i = 0; i < vecIndices.size(); i++) {
    std::string n;
    for(std::map<std::string, unsigned int>::const_iterator it = vecIndices.begin();
        it != vecIndices.end();
        it++) {
      if(it->second == i) {
        n = it->first; 
      }
    }
    if(n.empty()) {
      ROS_WARN_STREAM("Can't find index " << i << " in vecIndex");
      return;
    }
    std::cout << std::setw(40) << n;
    std::cout << " | ";
    for(size_t j = 0; j < all_size; j++) {
      std::cout << std::setw(3) << curAllowed[i][j];
    }
    std::cout << std::endl;
  }
}
*/
bool doesKinematicStateObeyConstraints(const planning_models::KinematicState& state,
                                       const motion_planning_msgs::Constraints& constraints,
                                       bool verbose = false);

void setMarkerShapeFromShape(const geometric_shapes_msgs::Shape &obj, visualization_msgs::Marker &mk);

void setMarkerShapeFromShape(const shapes::Shape *obj, visualization_msgs::Marker &mk);

void convertFromLinkPaddingMapToLinkPaddingVector(const std::map<std::string, double>& link_padding_map,
                                                  std::vector<motion_planning_msgs::LinkPadding>& link_padding_vector);
}
#endif
