file(REMOVE_RECURSE
  "CS2D_tests"
  "CS2D_tests.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/CS2D_tests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
