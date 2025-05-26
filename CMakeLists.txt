cmake_minimum_required(VERSION 3.30)
project(convert-to-string VERSION 1.0 LANGUAGES C)
add_executable(convert-to-string
	src/main.c
)
target_link_libraries(convert-to-string c-string)
install(TARGETS convert-to-string DESTINATION bin)
