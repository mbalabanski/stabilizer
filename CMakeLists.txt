cmake_minimum_required(VERSION 3.10)

set(PROJECT_N sable)
project(${PROJECT_N} VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SRCS ${PROJECT_SOURCE_DIR}/src/*.cpp)

# a macro that gets all of the header containing directories. 
MACRO(header_directories return_list includes_base_folder extention )
    FILE(GLOB_RECURSE new_list ${includes_base_folder}/*.${extention})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# using said macro.
header_directories(INCLUDES ${PROJECT_SOURCE_DIR}/include/ hpp)

message("src files:")
foreach(file ${SRCS})
        message(STATUS ${file})
endforeach()

message("include directories:")
foreach(dir ${INCLUDES})
        message(STATUS ${dir})
endforeach()


add_library(${PROJECT_N} SHARED ${SRCS})
target_include_directories(${PROJECT_N} PUBLIC include)


find_package(Boost REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
    target_link_libraries(${PROJECT_N} ${Boost_LIBRARIES})
endif()

find_package(Threads REQUIRED)
if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(${PROJECT_N} PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(${PROJECT_N} "${CMAKE_THREAD_LIBS_INIT}")
endif()

# Tests

MACRO(build_example name_ file_)
  add_executable(${name_} ${file_})
  target_link_libraries(${name_} ${PROJECT_N})
  add_test(NAME ${name_} COMMAND ${name_})
ENDMACRO()

build_example(Wait examples/wait.cpp)
build_example(Calc examples/calc.cpp)
build_example(Watch examples/watch.cpp)
build_example(ConfusionMatrix examples/confusion_matrix.cpp)
build_example(Flag examples/flag.cpp)
build_example(MultiThreaded examples/multi_threaded.cpp)