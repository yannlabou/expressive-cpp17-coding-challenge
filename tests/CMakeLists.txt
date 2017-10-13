# Prepare "Catch" library for other executables
set(CATCH_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/catch)
add_library(Catch INTERFACE)
target_include_directories(Catch INTERFACE ${CATCH_INCLUDE_DIR})

# Make test executable
set(TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp)
add_executable(cpp17_challenge_test ${TEST_SOURCES})
target_link_libraries(cpp17_challenge_test Catch)