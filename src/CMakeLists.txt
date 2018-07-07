# subdirs(data)
#add_library(wave STATIC utils.cpp)

FILE(GLOB_RECURSE SRC  data/*.cpp)
set(LIB_SRC ${SRC} PARENT_SCOPE)

# add_library(wave STATIC ${SRC})

