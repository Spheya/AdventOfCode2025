add_executable(10_factory_a "10_factory_a.cpp" "10_factory_b.cpp")
target_link_libraries(10_factory_a PRIVATE shared)

add_executable(10_factory_b "10_factory_b.cpp")
target_link_libraries(10_factory_b PRIVATE shared)

file(COPY "10_factory.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
