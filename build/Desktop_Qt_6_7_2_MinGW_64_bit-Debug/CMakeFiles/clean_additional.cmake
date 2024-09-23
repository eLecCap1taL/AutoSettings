# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "AutoSetting_autogen"
  "CMakeFiles\\AutoSetting_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\AutoSetting_autogen.dir\\ParseCache.txt"
  )
endif()
