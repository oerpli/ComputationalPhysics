add_executable(bsp_MatVec beispiel_MatVec.cpp)

add_executable(bsp_collision_update bsp_collision_update.cpp)
target_link_libraries (bsp_collision_update Rand)

add_executable(test_free-histo test_Free_Histo.cpp)
target_link_libraries (test_free-histo Histo)

add_executable(bsp_Box bsp_Box.cpp)
target_link_libraries (bsp_Box Rand)

add_executable(bsp_simulation bsp_simulation.cpp)
target_link_libraries (bsp_simulation Rand)
target_link_libraries (bsp_simulation Histo)

add_executable(bsp_simulation_2 bsp_simulation_2.cpp)
target_link_libraries (bsp_simulation_2 Rand)
target_link_libraries (bsp_simulation_2 Histo)