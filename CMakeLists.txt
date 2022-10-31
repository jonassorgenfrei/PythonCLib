cmake_minimum_required(VERSION 3.15)

# Raytracer
PROJECT(CppPythonLib VERSION 1.0)

# Cpp settings
##############

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(
    -fPIC
)

# INCLUDE
#########

# boost
set(Boost_NO_SYSTEM_PATHS true)
set (Boost_USE_STATIC_LIBS OFF CACHE BOOL "use static libraries from Boost")
set (Boost_USE_MULTITHREADED ON)
set (BUILD_SHARED_LIBS ON)
find_package(Boost REQUIRED COMPONENTS python REQUIRED)

# python
if(DEFINED USER_PYTHON_VERSION)
	find_package(Python ${USER_PYTHON_VERSION} EXACT REQUIRED COMPONENTS Interpreter Development)
else()
	find_package(Python REQUIRED COMPONENTS Interpreter Development)
endif()

# include
include_directories(${Boost_INCLUDE_DIRS} ${Python_INCLUDE_DIRS})

# main programm
###############
if(Boost_USE_STATIC_LIBS)
    add_definitions(-DBOOST_PYTHON_STATIC_LIB)
endif()

file(GLOB SRC_FILES src/*.cpp)

add_library(pyClass SHARED ${SRC_FILES})

SET_TARGET_PROPERTIES(pyClass PROPERTIES PREFIX "")
if (WIN32)
	# for windows add .pyd
	set_target_properties(pyClass PROPERTIES SUFFIX ".pyd")
endif()

# linking
#########
target_link_libraries(pyClass Boost::python ${Python_LIBRARIES})

if (WIN32)
  # disable autolinking in boost
  add_definitions( -DBOOST_ALL_NO_LIB )

  # force all boost libraries to dynamic link (we already disabled
  # autolinking, so I don't know why we need this, but we do!)
  add_definitions( -DBOOST_ALL_DYN_LINK )
endif()

# install
#########
set(PYTHON_PACKAGE_RELATIVE_PATH lib/python/pyClass)
set(INSTALL_PYTHONPACKAGE_DIR ${CMAKE_INSTALL_PREFIX}/${PYTHON_PACKAGE_RELATIVE_PATH})

install(TARGETS pyClass DESTINATION ${INSTALL_PYTHONPACKAGE_DIR})

# test 
######

enable_testing()
	
set(TEST_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/testenv)
if (WIN32)
	set(_testPYTHONPATH "PYTHONPATH=${INSTALL_PYTHONPACKAGE_DIR};$ENV{PYTHONPATH}")
else()
	set(_testPYTHONPATH "PYTHONPATH=${INSTALL_PYTHONPACKAGE_DIR}:$ENV{PYTHONPATH}")
endif()
add_test(
  NAME myClassTest
  COMMAND ${Python_EXECUTABLE} -m unittest discover -s ${TEST_SOURCE_DIR}/myClass -p "*.py"
)

set_tests_properties(myClassTest
    PROPERTIES ENVIRONMENT ${_testPYTHONPATH})


