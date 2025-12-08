add_executable(07_laboratories_a "07_laboratories_a.cpp")
target_link_libraries(07_laboratories_a PRIVATE shared)

add_executable(07_laboratories_b "07_laboratories_b.cpp")
target_link_libraries(07_laboratories_b PRIVATE shared)

file(COPY "07_laboratories.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
