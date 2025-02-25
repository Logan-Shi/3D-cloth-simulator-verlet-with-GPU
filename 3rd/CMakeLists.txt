cmake_minimum_required(VERSION 3.18 FATAL_ERROR)


# some settings for some package
set(ONLY_LIBS true CACHE BOOL "")
set(FREEGLUT_BUILD_DEMOS false CACHE BOOL "")


# helper target for FreeGLUT
add_subdirectory(FreeGLUT)
add_library(3rd_FreeGLUT INTERFACE) # 暂时使用静态库
target_link_libraries(3rd_FreeGLUT INTERFACE freeglut)
target_include_directories(3rd_FreeGLUT INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/FreeGLUT/include)


# helper target for GLM
add_library(3rd_GLM INTERFACE)
target_include_directories(3rd_GLM INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glm/)


# helper target for GLEW
add_subdirectory(glew-cmake)
add_library(3rd_GLEW INTERFACE)
target_link_libraries(3rd_GLEW INTERFACE libglew_static)
target_include_directories(3rd_GLEW INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/glew-cmake/include)


# helper target for FreeImage
# only support x64 now
add_library(3rd_FreeImage INTERFACE)

set(SEARCH_PATHS
    $ENV{ProgramFiles}/freeimage/include
    $ENV{SystemDrive}/freeimage/include
    $ENV{ProgramFiles}/freeimage
    $ENV{SystemDrive}/freeimage
    /usr/include
    /usr/local/include
    /sw/include
    /opt/local/include
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeImage/Dist/x64)
find_path(
  FREEIMAGE_INCLUDE_DIRS
  NAMES FreeImage.h
  PATHS ${SEARCH_PATHS}
  NO_DEFAULT_PATH)
if(NOT FREEIMAGE_INCLUDE_DIRS) # now look in system locations
  find_path(FREEIMAGE_INCLUDE_DIRS NAMES FreeImage.h)
endif()

set(SEARCH_LIBRARY_DIRS
    $ENV{ProgramFiles}/freeimage/lib
    $ENV{SystemDrive}/freeimage/lib
    $ENV{ProgramFiles}/freeimage/Dist/x64
    $ENV{SystemDrive}/freeimage/Dist/x64
    $ENV{ProgramFiles}/freeimage
    $ENV{SystemDrive}/freeimage
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeImage/Dist/x64
    /usr/lib64
    /usr/lib
    /usr/local/lib64
    /usr/local/lib
    /sw/lib
    /opt/local/lib)
find_library(
  FREEIMAGE_LIBRARY
  NAMES freeimage
  PATHS ${SEARCH_LIBRARY_DIRS}
  NO_DEFAULT_PATH)
if(NOT FREEIMAGE_LIBRARY) # now look in system locations
  find_library(FREEIMAGE_LIBRARY NAMES freeimage)
endif()

set(SEARCH_DLL_DIRS    # only for windows
    $ENV{ProgramFiles}/freeimage/lib
    $ENV{SystemDrive}/freeimage/lib
    $ENV{ProgramFiles}/freeimage/Dist/x64
    $ENV{SystemDrive}/freeimage/Dist/x64
    $ENV{ProgramFiles}/freeimage
    $ENV{SystemDrive}/freeimage
    ${CMAKE_CURRENT_SOURCE_DIR}/FreeImage/Dist/x64)
find_file(
  FREEIMAGE_DLL_FILE
  NAMES FreeImage.dll
  PATHS ${SEARCH_DLL_DIRS}
  NO_DEFAULT_PATH)
if(NOT FREEIMAGE_DLL_FILE) # now look in system locations
  find_file(FREEIMAGE_DLL_FILE NAMES FreeImage.dll)
endif()

if(FREEIMAGE_INCLUDE_DIRS AND FREEIMAGE_LIBRARY)
  message(
    STATUS
      "Found FreeImage: headers at ${FREEIMAGE_INCLUDE_DIRS}, libraries at ${FREEIMAGE_LIBRARY}"
  )
  target_include_directories(3rd_FreeImage INTERFACE ${FREEIMAGE_INCLUDE_DIRS})
  target_link_libraries(3rd_FreeImage INTERFACE ${FREEIMAGE_LIBRARY})
  install(FILES ${FREEIMAGE_DLL_FILE} DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
  message(SEND_ERROR "FreeImage Not Found")
endif()



# helper target for all libs
add_library(3rd_libs INTERFACE)
target_link_libraries(3rd_libs INTERFACE 3rd_FreeGLUT 3rd_GLM 3rd_GLEW 3rd_FreeImage)