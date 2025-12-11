add_executable(11_reactor_a "11_reactor_a.cpp")
target_link_libraries(11_reactor_a PRIVATE shared)

add_executable(11_reactor_b "11_reactor_b.cpp")
target_link_libraries(11_reactor_b PRIVATE shared)

file(COPY "11_reactor.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
