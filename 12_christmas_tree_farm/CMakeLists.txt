add_executable(12_christmas_tree_farm_a "12_christmas_tree_farm_a.cpp")
target_link_libraries(12_christmas_tree_farm_a PRIVATE shared)

file(COPY "12_christmas_tree_farm.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
