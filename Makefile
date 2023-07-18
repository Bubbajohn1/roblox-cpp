exe_name = rblxcpp
compiler = g++
src_files = $(wildcard ./src/**.*.cpp ./src/*.cpp ./src/include/**/*.cpp ./src/include/*.cpp)
c_args = -std=c++17 -O2 -Wall -Wextra

all:
	$(compiler) $(c_args) $(src_files) -o ./build/$(exe_name).exe 