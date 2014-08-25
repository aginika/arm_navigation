# Catkin User Guide: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/user_guide.html
# Catkin CMake Standard: http://www.ros.org/doc/groovy/api/catkin/html/user_guide/standards.html
cmake_minimum_required(VERSION 2.8.3)
project(collision_space)
# Load catkin and all dependencies required for this package
# TODO: remove all from COMPONENTS that are not catkin packages.
find_package(catkin REQUIRED COMPONENTS rosconsole planning_models geometric_shapes)
find_package(Boost REQUIRED COMPONENTS thread)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
add_definitions(-DdDOUBLE)
find_package(Bullet REQUIRED)
find_package(ODE REQUIRED)
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

include_directories(include ${Boost_INCLUDE_DIR} ${catkin_INCLUDE_DIRS} ${Bullet_INCLUDE_DIRS} ${ODE_INCLUDE_DIRS})

catkin_package(
    DEPENDS pkg-config bullet libode-dev ode
    CATKIN_DEPENDS rosconsole planning_models geometric_shapes
    INCLUDE_DIRS include
    LIBRARIES collision_space
)

add_library(collision_space src/environment_objects.cpp
				    src/environment.cpp
				    src/environmentODE.cpp
)
target_link_libraries(collision_space ${catkin_LIBRARIES} ${Boost_LIBRARIES} ${Bullet_LIBRARIES} ${ODE_LIBRARIES} /usr/lib/libode.so)

catkin_add_gtest(test_collision_space test/test_collision_space.cpp)
target_link_libraries(test_collision_space collision_space ${catkin_LIBRARIES} ${ODE_LIBRARIES})