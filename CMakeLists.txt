# Set up cmake
cmake_minimum_required (VERSION 2.6)
project (test_crashpad_dongle CXX C)
add_compile_options(-std=c++17 -Wall -Wextra)

include_directories(${CMAKE_SOURCE_DIR}/third_party/google_crashpad/include)
link_directories(${CMAKE_SOURCE_DIR}/third_party/google_crashpad/lib_ubuntu)

# Set output
set(CMAKE_BIN "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BIN})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BIN})

# Crashpad
configure_file("${PROJECT_SOURCE_DIR}/third_party/google_crashpad/crashpad_handler"
                 "${CMAKE_BIN}/crashpad_handler" COPYONLY)

# Add code
add_executable(test_crashpad_dongle src/main.cpp)
target_link_libraries(test_crashpad_dongle libclient.a libutil.a libbase.a)

# Protect
#set(CAV "")
#set(CAV "-cav0")
set(CAV "-cav1")
add_custom_command(TARGET test_crashpad_dongle POST_BUILD COMMAND COMMAND AxProtectorLin -x -kcm -f6001031 -p1 -rd:now -cf0 -d:6.20 -fw:3.00 -sl -nn -cih ${CAV} -cae -cas100 -wu20 -we20 -eac -eec -eui -emc -car30,3 -v -cag0 -caa7 -o:\"${CMAKE_BIN}/test_crashpad_dongle\" \"${CMAKE_BIN}/test_crashpad_dongle\")
add_custom_command(TARGET test_crashpad_dongle POST_BUILD COMMAND COMMAND mkdir -p ${CMAKE_BIN}/crashpad/metrics/db)
