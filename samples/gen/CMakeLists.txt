add_executable(perm permutation.cpp)
target_link_libraries(perm PRIVATE libgu)

add_executable(tree tree.cpp)
target_link_libraries(tree PRIVATE libgu)

add_executable(tree_complex tree_complex.cpp)
target_link_libraries(tree_complex PRIVATE libgu)
