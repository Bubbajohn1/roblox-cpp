exe_name = rblxcpp
compiler = gcc
src_files = $(wildcard ./src/**.*.cpp ./src/*.cpp)

all:
	$(compiler) $(src_files) -o ./build/$(exe_name).exe