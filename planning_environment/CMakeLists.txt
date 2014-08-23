cmake_minimum_required(VERSION 2.8.3)
project(planning_environment)
find_package(catkin REQUIRED COMPONENTS roscpp rosconsole rosbag actionlib_msgs actionlib tf std_srvs message_filters angles geometric_shapes sensor_msgs arm_navigation_msgs visualization_msgs planning_models collision_space pcl_ros robot_self_filter rviz)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
find_package(Eigen REQUIRED)
find_package(OpenMP REQUIRED)
find_package(PCL)
find_package(PkgConfig REQUIRED)
find_package(ASSIMP QUIET)
find_package(Boost REQUIRED COMPONENTS thread signals)
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
set( headers
        include/planning_environment/tools/planning_description_configuration_wizard.h
)
qt4_wrap_cpp(moc_sources ${headers})


if (NOT ASSIMP_FOUND)
  pkg_check_modules(ASSIMP assimp)
endif()
if (ASSIMP_FOUND)
  if( ${ASSIMP_VERSION} STRGREATER "2.0.0" )
    set(IS_ASSIMP3 1)
    add_definitions(-DIS_ASSIMP3)
    message(STATUS "Found assimp v3")
  else()
    message(STATUS "Found assimp v2")
  endif()
  include_directories(${ASSIMP_INCLUDE_DIRS})
  link_directories(${ASSIMP_LIBRARY_DIRS})
else()
  message(STATUS "could not find assimp (perhaps available thorugh ROS package?), so assimping assimp v2")
  set(ASSIMP_LIBRARIES assimp)
  set(ASSIMP_LIBRARY_DIRS)
  set(ASSIMP_CXX_FLAGS)
  set(ASSIMP_CFLAGS_OTHER)
  set(ASSIMP_LINK_FLAGS)
  set(ASSIMP_INCLUDE_DIRS)
  set(IS_ASSIMP3 0) # most likely not
endif()


include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} ${QT_INCLUDE_DIR} ${OpenMP_INCLUDE_DIRS})


catkin_package(
    DEPENDS libqt4-dev tinyxml pkg-config yaml-cpp
    CATKIN_DEPENDS roscpp rosconsole rosbag actionlib_msgs actionlib tf std_srvs message_filters angles geometric_shapes sensor_msgs arm_navigation_msgs visualization_msgs planning_models collision_space pcl_ros robot_self_filter rviz
    INCLUDE_DIRS include
    LIBRARIES planning_environment
)

add_library(planning_environment src/models/robot_models.cpp
					 src/models/collision_models.cpp
					 src/models/collision_models_interface.cpp
					 src/monitors/kinematic_model_state_monitor.cpp
					 src/monitors/collision_space_monitor.cpp
					 src/monitors/planning_monitor.cpp
					 src/util/kinematic_state_constraint_evaluator.cpp
					 src/util/construct_object.cpp
					 src/util/collision_operations_generator.cpp
					 src/models/model_utils.cpp
					 src/monitors/monitor_utils.cpp
				         src/monitors/joint_state_monitor.cpp)

target_link_libraries(planning_environment yaml-cpp ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${OpenMP_LIBRARIES})
add_executable(environment_server src/monitors/environment_server.cpp)
target_link_libraries(environment_server planning_environment)

add_executable(planning_scene_validity_server src/monitors/planning_scene_validity_server.cpp)
target_link_libraries(planning_scene_validity_server planning_environment)

add_executable(visualize_all_collisions test/visualize_all_collisions.cpp)
target_link_libraries(visualize_all_collisions planning_environment ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(visualize_collision_models test/visualize_collision_models.cpp)
target_link_libraries(visualize_collision_models planning_environment)

add_executable(visualize_planning_scene test/visualize_planning_scene.cpp)
target_link_libraries(visualize_planning_scene planning_environment ${catkin_LIBRARIES} ${Boost_LIBRARIES})

add_executable(filter_attached_objects src/tools/filter_attached_objects.cpp) 
target_link_libraries(filter_attached_objects planning_environment ${catkin_LIBRARIES} ${Boost_LIBRARIES})

set( sources
	src/tools/planning_description_configuration_wizard.cpp
)

add_executable(planning_description_configuration_wizard ${sources} ${headers} ${moc_sources})
target_link_libraries(planning_description_configuration_wizard planning_environment ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${QT_LIBRARIES} tinyxml)

add_executable(default_joint_state_publisher test/default_joint_state_publisher.cpp)
target_link_libraries(default_joint_state_publisher planning_environment ${catkin_LIBRARIES})

# add_executable(test_robot_models test/test_robot_models.cpp) 
# add_dependencies(tests test_robot_models)
# add_gtest_build_flags(test_robot_models)
# target_link_libraries(test_robot_models planning_environment ${catkin_LIBRARIES})

# add_executable(test_collision_models test/test_collision_models.cpp) 
# add_dependencies(tests test_collision_models)
# add_gtest_build_flags(test_collision_models)
# target_link_libraries(test_collision_models planning_environment ${catkin_LIBRARIES})
# add_rostest(test/test_models.launch)

# add_executable(test_planning_monitor test/test_planning_monitor.cpp) 
# add_dependencies(tests test_planning_monitor)
# add_gtest_build_flags(test_planning_monitor)
# target_link_libraries(test_planning_monitor planning_environment ${catkin_LIBRARIES} gtest)
# add_rostest(test/test_monitors.launch)
