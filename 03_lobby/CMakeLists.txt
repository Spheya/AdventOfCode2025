add_executable(03_lobby_a "03_lobby_a.cpp")
target_link_libraries(03_lobby_a PRIVATE shared)

add_executable(03_lobby_b "03_lobby_b.cpp")
target_link_libraries(03_lobby_b PRIVATE shared)

file(COPY "03_lobby.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
