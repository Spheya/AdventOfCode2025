add_executable(09_movie_theater_a "09_movie_theater_a.cpp")
target_link_libraries(09_movie_theater_a PRIVATE shared)

add_executable(09_movie_theater_b "09_movie_theater_b.cpp")
target_link_libraries(09_movie_theater_b PRIVATE shared)

file(COPY "09_movie_theater.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
