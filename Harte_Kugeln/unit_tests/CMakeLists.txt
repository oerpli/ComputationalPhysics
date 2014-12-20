add_library(unit_testFunctions test_MatVec.cpp test_Kugel.cpp test_CollisionPair.cpp test_Box.cpp)

add_executable(unit_Test Test.cpp)
target_link_libraries (unit_Test unit_testFunctions)