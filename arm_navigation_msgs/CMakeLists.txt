# Catkin User Guide: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/user_guide.html
# Catkin CMake Standard: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/standards.html
cmake_minimum_required(VERSION 2.8.3)
project(arm_navigation_msgs)
# Load catkin and all dependencies required for this package
# TODO: remove all from COMPONENTS that are not catkin packages.
find_package(catkin REQUIRED COMPONENTS std_msgs actionlib_msgs sensor_msgs geometry_msgs trajectory_msgs tf message_generation)


add_message_files(
  FILES
  AllowedCollisionEntry.msg
  AllowedCollisionMatrix.msg
  AllowedContactSpecification.msg
  ArmNavigationErrorCodes.msg
  AttachedCollisionObject.msg
  CollisionMap.msg
  CollisionObject.msg
  CollisionObjectOperation.msg
  CollisionOperation.msg
  Constraints.msg
  ContactInformation.msg
  DisplayTrajectory.msg
  JointConstraint.msg
  JointLimits.msg
  JointTrajectoryWithLimits.msg
  LinkPadding.msg
  MotionPlanRequest.msg
  MoveArmStatistics.msg
  MultiDOFJointState.msg
  MultiDOFJointTrajectory.msg
  MultiDOFJointTrajectoryPoint.msg
  OrderedCollisionOperations.msg
  OrientationConstraint.msg
  OrientedBoundingBox.msg
  PlanningScene.msg
  PositionConstraint.msg
  RobotState.msg
  RobotTrajectory.msg
  Shape.msg
  SimplePoseConstraint.msg
  VisibilityConstraint.msg
  WorkspaceParameters.msg
)

add_service_files(
  FILES
  FilterJointTrajectory.srv
  FilterJointTrajectoryWithConstraints.srv
  GetCollisionObjects.srv
  GetJointTrajectoryValidity.srv
  GetMotionPlan.srv
  GetPlanningScene.srv
  GetRobotState.srv
  GetRobotTrajectoryValidity.srv
  GetStateValidity.srv
  SetPlanningSceneDiff.srv
)

add_action_files(
  FILES
  MakeStaticCollisionMap.action
  MoveArm.action
  SyncPlanningScene.action
)

generate_messages(
  DEPENDENCIES geometry_msgs std_msgs actionlib_msgs sensor_msgs trajectory_msgs
)

# catkin_package parameters: http://ros.org/doc/groovy/api/catkin/html/dev_guide/generated_cmake_api.html#catkin-package
# TODO: fill in what other packages will need to use this package
catkin_package(
    DEPENDS
    CATKIN_DEPENDS std_msgs actionlib_msgs sensor_msgs geometry_msgs trajectory_msgs tf message_runtime
    INCLUDE_DIRS # TODO include
    LIBRARIES # TODO
)
