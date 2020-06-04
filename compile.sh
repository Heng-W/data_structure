#!/bin/bash

base_dir=$(dirname $(readlink -f $0))
target_dir=$base_dir/build/linux
mkdir -p $target_dir
compile_cnt=0
build_cnt=0
for source in $(ls $base_dir/*.cpp)
do
	target=$target_dir/$(basename $source .cpp)
	((compile_cnt++))
	echo No.$compile_cnt compile $source
	g++ -std=c++11 $source -o $target
	if [ $? -eq 0 ]; then ((build_cnt++)); fi
	echo
done
echo $build_cnt/$compile_cnt targets built successfully!
