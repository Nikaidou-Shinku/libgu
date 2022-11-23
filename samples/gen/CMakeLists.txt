add_executable(perm gen_permutation.cpp)
target_link_libraries(perm PRIVATE libgu)

add_executable(tree gen_tree.cpp)
target_link_libraries(tree PRIVATE libgu)
