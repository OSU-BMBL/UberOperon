if(WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc")
endif(WIN32)

aux_source_directory(. SRC_LIST)

add_executable(GOST ${SRC_LIST})
