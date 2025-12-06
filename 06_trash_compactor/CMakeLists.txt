add_executable(06_trash_compactor_a "06_trash_compactor_a.cpp")
target_link_libraries(06_trash_compactor_a PRIVATE shared)

add_executable(06_trash_compactor_b "06_trash_compactor_b.cpp")
target_link_libraries(06_trash_compactor_b PRIVATE shared)

file(COPY "06_trash_compactor.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
