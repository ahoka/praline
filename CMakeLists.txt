cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)
project(PRALINE)

find_package(Threads REQUIRED)

set(PRALINE_SRC HttpSubsystem.cc Praline.cc RequestHandler.cc RequestHandlerFactory.cc Topic.cc TopicList.cc TopicWriter.cc)
add_executable(praline ${PRALINE_SRC} main.cc)

set_property(TARGET praline PROPERTY CXX_STANDARD 11)
set_property(TARGET praline PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(pralinetest ${PRALINE_SRC} RequestHandlerTest.cc)

set_property(TARGET pralinetest PROPERTY CXX_STANDARD 11)
set_property(TARGET pralinetest PROPERTY CXX_STANDARD_REQUIRED ON)

add_custom_target(check COMMAND pralinetest)

include(ExternalProject)

set(POCO_PREFIX ${CMAKE_BINARY_DIR}/poco)

ExternalProject_Add(
  poco-1.6.0
  PREFIX poco
  URL http://pocoproject.org/releases/poco-1.6.0/poco-1.6.0-all.tar.gz
  CONFIGURE_COMMAND ../poco-1.6.0/configure --no-tests --no-samples --omit=Data/ODBC,Data/MySQL --prefix=${POCO_PREFIX}
  BUILD_COMMAND make
  )

include_directories(${POCO_PREFIX}/include)

foreach(lib Foundation Net Util)
add_library(Poco${lib} SHARED IMPORTED)
set_target_properties(Poco${lib} PROPERTIES IMPORTED_LOCATION ${POCO_PREFIX}/lib/${CMAKE_SHARED_MODULE_PREFIX}Poco${lib}${CMAKE_SHARED_LIBRARY_SUFFIX})
add_dependencies(Poco${lib} poco-1.6.0)
target_link_libraries(praline Poco${lib})
target_link_libraries(pralinetest Poco${lib})
endforeach()

target_link_libraries(praline ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(pralinetest ${CMAKE_THREAD_LIBS_INIT})
