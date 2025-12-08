add_executable(08_playground_a "08_playground_a.cpp")
target_link_libraries(08_playground_a PRIVATE shared)

add_executable(08_playground_b "08_playground_b.cpp")
target_link_libraries(08_playground_b PRIVATE shared)

file(COPY "08_playground.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
