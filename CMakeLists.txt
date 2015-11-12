cmake_minimum_required(VERSION 3.3)

project(omptest)

FIND_PACKAGE(CUDA REQUIRED)
FIND_PACKAGE(MPI REQUIRED)

INCLUDE(FindCUDA)

#INCLUDE_DIRECTORIES(/usr/local/cuda/include ${MPI_INCLUDE_PATH})

FILE(GLOB SOURCES "*.cu" "*.cpp" "*.c" "*.h")
set(SOURCE_FILES test.cu)

CUDA_ADD_EXECUTABLE(omptest ${SOURCES})

LIST(APPEND CMAKE_CXX_FLAGS "-std=c++0x -O3 -ffast-math -Wall")

LIST(APPEND CUDA_NVCC_FLAGS --compiler-options -fno-strict-aliasing -lineinfo -use_fast_math -Xptxas -dlcm=cg)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_20,code=sm_20)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_30,code=sm_30)
LIST(APPEND CUDA_NVCC_FLAGS -gencode arch=compute_35,code=sm_35)

TARGET_LINK_LIBRARIES(omptest /usr/lib/x86_64-linux-gnu/libcudart.so ${MPI_LIBRARIES})

find_package(OpenMP REQUIRED)
if (OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif ()


#add_executable(omptest ${SOURCE_FILES})