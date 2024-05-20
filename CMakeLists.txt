cmake_minimum_required(VERSION 3.10)

set(PROJECT_N sable_lib)
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

add_executable(WaitTest test/wait.cpp)
target_link_libraries(WaitTest ${PROJECT_N})
add_test(NAME WaitTest COMMAND WaitTest)


add_executable(CalcTest test/calc_test.cpp)
target_link_libraries(CalcTest ${PROJECT_N})
add_test(NAME CalcTest COMMAND CalcTest)

add_executable(WatchTest test/watch.cpp)
target_link_libraries(WatchTest ${PROJECT_N})
add_test(NAME WatchTest COMMAND WatchTest)

add_executable(ConfusionMatrix test/confusion_matrix.cpp)
target_link_libraries(ConfusionMatrix ${PROJECT_N})
add_test(NAME ConfusionMatrix COMMAND ConfusionMatrix)

add_executable(FlagTest test/flag_test.cpp)
target_link_libraries(FlagTest ${PROJECT_N})
add_test(NAME FlagTest COMMAND FlagTest)