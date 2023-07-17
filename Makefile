exe_name = rblxcpp
compiler = g++
src_files = $(wildcard ./src/**.*.cpp ./src/*.cpp)

all:
	$(compiler) -std=c++11 $(src_files) -o ./build/$(exe_name).exe