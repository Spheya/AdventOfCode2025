add_executable(02_gift_shop_a "02_gift_shop_a.cpp")
target_link_libraries(02_gift_shop_a PRIVATE shared)

add_executable(02_gift_shop_b "02_gift_shop_b.cpp")
target_link_libraries(02_gift_shop_b PRIVATE shared)

file(COPY "02_gift_shop.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
