# Catkin User Guide: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/user_guide.html
# Catkin CMake Standard: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/standards.html
cmake_minimum_required(VERSION 2.8.3)
project(planning_models)
# Load catkin and all dependencies required for this package
# TODO: remove all from COMPONENTS that are not catkin packages.
find_package(catkin REQUIRED COMPONENTS urdf rosconsole geometric_shapes angles roslib)
find_package(ASSIMP QUIET)
find_package(Eigen REQUIRED)
find_package(PkgConfig REQUIRED)

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

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${Eigen_INCLUDE_DIRS})
catkin_package(
    DEPENDS pkg-config
    CATKIN_DEPENDS urdf rosconsole geometric_shapes angles roslib
    INCLUDE_DIRS include
    LIBRARIES planning_models
)

add_library(planning_models src/kinematic_model.cpp src/kinematic_state.cpp)
target_link_libraries(planning_models planning_models ${catkin_LIBRARIES} ${Eigen_LIBRARIES}
)

# Unit tests
catkin_add_gtest(test_kinematic test/test_kinematic.cpp)
target_link_libraries(test_kinematic planning_models ${catkin_LIBRARIES}
)

add_executable(test_kinematic_complicated test/test_kinematic_complicated.cpp)
target_link_libraries(test_kinematic_complicated planning_models BulletCollision gtest ${catkin_LIBRARIES})

