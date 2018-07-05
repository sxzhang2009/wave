cmake_minimum_required (VERSION 3.0.2)
project (wave_project)

set(Boost_USE_STATIC_LIBS ON) 
find_package(Boost)

FILE(GLOB_RECURSE SRC  src/*.cpp)


add_library(wave SHARED ${SRC})

# add_subdirectory(required/glog)
# target_link_libraries(wave glog::glog)

target_link_libraries(wave ${Boost_LIBRARIES})

FILE(GLOB_RECURSE TEST_SRC  test/*.cpp)
add_executable(unittest ${TEST_SRC})
target_link_libraries(unittest wave)


SET(CMAKE_CXX_FLAGS  "-std=c++0x" )

# message(STATUS "SRC=${SRC}")

message(STATUS "CMAKE_CURRENT_BINARY_DIR=${CMAKE_CURRENT_BINARY_DIR}")

set(project_src "${PROJECT_SOURCE_DIR}/src")

set(build_include_path "${CMAKE_CURRENT_BINARY_DIR}/include")
set(build_library_path "${CMAKE_CURRENT_BINARY_DIR}/lib")

message(STATUS "project_src=${project_src}")

file(RELATIVE_PATH RSRC "${project_src}" "${SRC}")

message(STATUS "Header=${HEADER}")

# list(REMOVE_DUPLICATES ${HEADER})

function(copy_header_files)
  message(STATUS "Copying header files into include directory.")
  FILE(GLOB_RECURSE HEADER  ${project_src}/*.hpp)
  foreach(h ${HEADER})
    file(RELATIVE_PATH rh ${project_src} ${h})
    # list(APPEND rsrc ${rh})
    message(STATUS ${build_include_path}/${rh})
    get_filename_component(folder ${build_include_path}/${rh} DIRECTORY)
    file(COPY ${h} DESTINATION ${folder})
  endforeach(h)
endfunction(copy_header_files)

INSTALL(TARGETS wave DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/lib")
# install(CODE "MESSAGE(\"Sample install message.\")")
#INSTALL(CODE "copy_header_files()")

# INSTALL(FILES ${HEADER} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include")

install(DIRECTORY "${project_src}/" # source directory
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/include" # target directory
        FILES_MATCHING # install only matched files
        PATTERN "*.hpp" # select header files
)

# message(STATUS "RSRC=${rsrc}")

# copy_header_files()

# get_cmake_property(_variableNames VARIABLES)
# list (SORT _variableNames)
# foreach (_variableName ${_variableNames})
#     message(STATUS "${_variableName}=${${_variableName}}")
#   endforeach()




