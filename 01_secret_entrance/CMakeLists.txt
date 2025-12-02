add_executable(01_secret_entrance_a "01_secret_entrance_a.cpp")
target_link_libraries(01_secret_entrance_a PRIVATE shared)

add_executable(01_secret_entrance_b "01_secret_entrance_b.cpp")
target_link_libraries(01_secret_entrance_b PRIVATE shared)

file(COPY "01_secret_entrance.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
