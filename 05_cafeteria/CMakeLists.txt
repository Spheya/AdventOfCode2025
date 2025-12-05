add_executable(05_cafeteria_a "05_cafeteria_a.cpp")
target_link_libraries(05_cafeteria_a PRIVATE shared)

add_executable(05_cafeteria_b "05_cafeteria_b.cpp")
target_link_libraries(05_cafeteria_b PRIVATE shared)

file(COPY "05_cafeteria.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
