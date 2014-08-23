# Catkin User Guide: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/user_guide.html
# Catkin CMake Standard: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/standards.html
cmake_minimum_required(VERSION 2.8.3)
project(robot_self_filter)
# Load catkin and all dependencies required for this package
# TODO: remove all from COMPONENTS that are not catkin packages.
find_package(catkin REQUIRED COMPONENTS roscpp tf tf_conversions filters sensor_msgs visualization_msgs geometric_shapes urdf resource_retriever pcl_conversions shape_msgs)

find_package(Eigen REQUIRED)
find_package(PCL REQUIRED)
find_package(Boost REQUIRED COMPONENTS signals)
find_package(OpenMP REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${EIGEN_INCLUDE_DIRS} ${PCL_INCLUDE_DIRS} ${OpenMP_INCLUDE_DIRS})

#generate_messages(
#    #TODO DEPENDENCIES geometry_msgs std_msgs
#)

find_package(PkgConfig REQUIRED)
find_package(ASSIMP QUIET)
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


# catkin_package parameters: http://ros.org/doc/groovy/api/catkin/html/dev_guide/generated_cmake_api.html#catkin-package
# TODO: fill in what other packages will need to use this package
catkin_package(
    DEPENDS pcl assimp pkg-config
    CATKIN_DEPENDS roscpp tf tf_conversions filters sensor_msgs visualization_msgs geometric_shapes urdf resource_retriever pcl_conversions shape_msgs
    INCLUDE_DIRS include
    LIBRARIES robot_self_filter
)


add_library(robot_self_filter src/self_mask.cpp)
#add_openmp_flags(robot_self_filter)
target_link_libraries(robot_self_filter assimp
                                        ${PCL_LIBRARIES}
                                        ${catkin_LIBRARIES}
                                        ${Boost_LIBRARIES}
                                        ${OpenMP_LIBRARIES}
)

add_executable (test_filter src/test_filter.cpp)
#add_openmp_flags (test_filter)
target_link_libraries (test_filter robot_self_filter
  assimp
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${OpenMP_LIBRARIES}
)

add_executable(self_filter src/self_filter.cpp)
#add_openmp_flags(self_filter)
target_link_libraries(self_filter assimp
                                  robot_self_filter
				  BulletCollision BulletDynamics BulletSoftBody BulletMultiThreaded
 ${catkin_LIBRARIES}
 ${Boost_LIBRARIES}
                                        ${OpenMP_LIBRARIES}
)