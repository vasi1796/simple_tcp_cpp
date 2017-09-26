cmake_minimum_required(VERSION 2.8)
project (simple_tcp_cpp)

set(Boost_INCLUDE_DIR D:/lib/boost_1_65_1)
set(Boost_LIBRARY_DIR D:/lib/boost_1_65_1/lib64-msvc-14.0)
set(SERVER_SRC src/server.cpp)
set(CLIENT_SRC src/client.cpp)

find_package(OpenCV REQUIRED)
find_package(Boost COMPONENTS system filesystem REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})
link_directories(${OpenCV_LIB_DIR})

add_executable(simple_server_cpp ${SERVER_SRC})
add_executable(simple_client_cpp ${CLIENT_SRC})

target_link_libraries(simple_server_cpp ${OpenCV_LIBS})
target_link_libraries(simple_client_cpp ${OpenCV_LIBS})
target_link_libraries (simple_server_cpp ${BOOST_LIBRARIES})
target_link_libraries (simple_client_cpp ${BOOST_LIBRARIES})