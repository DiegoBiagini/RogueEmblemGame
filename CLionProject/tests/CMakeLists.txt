find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES test_src/runTests.cpp test_src/resourceTests.cpp test_src/resourceSystemTest.cpp test_src/mapTests.cpp)
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests ${GTEST_BOTH_LIBRARIES} coreGame pthread)