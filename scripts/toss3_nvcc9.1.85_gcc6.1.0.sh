#!/bin/bash

##
## Copyright (c) 2017-18, Lawrence Livermore National Security, LLC.
##
## Produced at the Lawrence Livermore National Laboratory.
##
## LLNL-CODE-738930
##
## All rights reserved.
## 
## This file is part of the RAJA Performance Suite.
##
## For details about use and distribution, please read raja-perfsuite/LICENSE.
##

rm -rf build_toss3-nvcc9.1.85_gcc6.1.0 2>/dev/null
mkdir build_toss3-nvcc9.1.85_gcc6.1.0 && cd build_toss3-nvcc9.1.85_gcc6.1.0

module load cmake/3.5.2

cmake \
  -DCMAKE_BUILD_TYPE=Release \
  -C ../host-configs/toss3/nvcc_gcc6_1_0.cmake \
  -DENABLE_OPENMP=On \
  -DENABLE_CUDA=On \
  -DCUDA_TOOLKIT_ROOT_DIR=/usr/tce/packages/cuda/cuda-9.1.85 \
  -DPERFSUITE_ENABLE_WARNINGS=Off \
  -DENABLE_ALL_WARNINGS=Off \
  -DCMAKE_INSTALL_PREFIX=../install_toss3-nvcc9.1.85_gcc6.1.0 \
  "$@" \
  ..
