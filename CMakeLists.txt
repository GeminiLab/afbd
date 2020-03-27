cmake_minimum_required(VERSION 3.2)
project(rtlil)

set(CMAKE_CXX_STANDARD 17)

# target rtlil
aux_source_directory(src/rtlil SOURCE_RTLIL)

add_library(rtlil STATIC ${SOURCE_RTLIL})
target_include_directories(rtlil PUBLIC include)


# target transpiler
set(LLVM_DIR /usr/lib/llvm-8/cmake)
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})

aux_source_directory(src/transpiler SOURCE_TRANS)

add_executable(trans RTL.cpp ${SOURCE_TRANS})
target_include_directories(trans PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(trans PUBLIC include)

llvm_map_components_to_libnames(llvm_libs support core irreader
        aarch64asmparser aarch64asmprinter aarch64codegen aarch64desc aarch64disassembler aarch64info aarch64utils
        amdgpuasmparser amdgpuasmprinter amdgpucodegen amdgpudesc amdgpudisassembler amdgpuinfo amdgpuutils
        armasmparser armasmprinter armcodegen armdesc armdisassembler arminfo armutils asmparser asmprinter
        avrasmparser avrasmprinter avrcodegen avrdesc avrdisassembler avrinfo
        bpfasmparser bpfasmprinter bpfcodegen bpfdesc bpfdisassembler bpfinfo
        hexagonasmparser hexagoncodegen hexagondesc hexagondisassembler hexagoninfo
        lanaiasmparser lanaiasmprinter lanaicodegen lanaidesc lanaidisassembler lanaiinfo
        mipsasmparser mipsasmprinter mipscodegen mipsdesc mipsdisassembler mipsinfo mirparser
        msp430asmparser msp430asmprinter msp430codegen msp430desc msp430info
        nvptxasmprinter nvptxcodegen nvptxdesc nvptxinfo
        powerpcasmparser powerpcasmprinter powerpccodegen powerpcdesc powerpcdisassembler powerpcinfo
        sparcasmparser sparcasmprinter sparccodegen sparcdesc sparcdisassembler sparcinfo
        systemzasmparser systemzasmprinter systemzcodegen systemzdesc systemzdisassembler systemzinfo
        webassemblyasmparser webassemblyasmprinter webassemblycodegen webassemblydesc webassemblydisassembler webassemblyinfo windowsmanifest
        x86asmparser x86asmprinter x86codegen x86desc x86disassembler x86info x86utils
        xcoreasmprinter xcorecodegen xcoredesc xcoredisassembler xcoreinfo
        )

target_link_libraries(trans rtlil ${llvm_libs})
