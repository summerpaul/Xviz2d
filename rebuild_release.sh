#!/bin/bash
# @Author: Xia Yunkai
# @Date:   2023-12-26 20:56:25
# @Last Modified by:   Xia Yunkai
# @Last Modified time: 2024-02-03 22:30:07

rm -rf build
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make 