add_executable(04_printing_department_a "04_printing_department_a.cpp")
target_link_libraries(04_printing_department_a PRIVATE shared)

add_executable(04_printing_department_b "04_printing_department_b.cpp")
target_link_libraries(04_printing_department_b PRIVATE shared)

add_executable(04_printing_department_extra "04_printing_department_extra.cpp")
target_link_libraries(04_printing_department_extra PRIVATE shared)


file(COPY "04_printing_department.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
