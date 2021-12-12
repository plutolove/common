cmake_minimum_required(VERSION 3.17)
project(patterns)

set(CMAKE_CXX_STANDARD 20)

find_package(LLVM REQUIRED CONFIG)
find_package(Arrow REQUIRED)
find_package(Boost REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/src/)
file(GLOB_RECURSE SRC_FILE ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*/*.cpp)

add_executable(patterns ${SRC_FILE})

set (REQUIRED_LLVM_LIBRARIES
        LLVMExecutionEngine
        LLVMRuntimeDyld
        LLVMX86CodeGen
        LLVMX86Desc
        LLVMX86Info
        LLVMAsmPrinter
        LLVMDebugInfoDWARF
        LLVMGlobalISel
        LLVMSelectionDAG
        LLVMMCDisassembler
        LLVMPasses
        LLVMCodeGen
        LLVMipo
        LLVMBitWriter
        LLVMInstrumentation
        LLVMScalarOpts
        LLVMAggressiveInstCombine
        LLVMInstCombine
        LLVMVectorize
        LLVMTransformUtils
        LLVMTarget
        LLVMAnalysis
        LLVMProfileData
        LLVMObject
        LLVMBitReader
        LLVMCore
        LLVMRemarks
        LLVMBitstreamReader
        LLVMMCParser
        LLVMMC
        LLVMBinaryFormat
        LLVMDebugInfoCodeView
        LLVMSupport
        LLVMDemangle
        )

target_link_libraries(patterns ${Boost_LIBRARIES} ${REQUIRED_LLVM_LIBRARIES} ${arrow_shared})