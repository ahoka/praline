cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(PRALINE)

set(PRALINE_SRC HttpSubsystem.cc main.cc Praline.cc RequestHandler.cc RequestHandlerFactory.cc Topic.cc TopicList.cc TopicWriter.cc)
add_executable(praline ${PRALINE_SRC})

set_property(TARGET praline PROPERTY CXX_STANDARD 11)
set_property(TARGET praline PROPERTY CXX_STANDARD_REQUIRED ON)

find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_NET PocoNet)
target_link_libraries(praline ${POCO_FOUNDATION} ${POCO_NET} ${POCO_UTIL})

find_package(Threads REQUIRED)
target_link_libraries(praline ${CMAKE_THREAD_LIBS_INIT})
