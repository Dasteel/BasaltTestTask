# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/MyLibrary_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/MyLibrary_autogen.dir/ParseCache.txt"
  "CMakeFiles/untitled4_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/untitled4_autogen.dir/ParseCache.txt"
  "MyLibrary_autogen"
  "untitled4_autogen"
  )
endif()
