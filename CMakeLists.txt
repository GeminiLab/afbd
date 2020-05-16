cmake_minimum_required(VERSION 3.2)
project(afbd)

set(CMAKE_CXX_STANDARD 17)

# target static
aux_source_directory(static SOURCE_STATIC)
add_library(afbd_static STATIC ${SOURCE_STATIC})
target_compile_options(afbd_static PRIVATE -O2)

add_library(afbd_staticd STATIC ${SOURCE_STATIC})
target_compile_definitions(afbd_staticd PRIVATE STATIC_DEBUG)

aux_source_directory(static/test SOURCE_STATIC_TEST)
add_executable(afbd_static_test ${SOURCE_STATIC_TEST})
target_link_libraries(afbd_static_test afbd_static)

# target yosysf
aux_source_directory(3rd/yosys SOURCE_YOSYS)
aux_source_directory(3rd/libs/bigint SOURCE_3RD_BIGINT)
aux_source_directory(3rd/libs/ezsat SOURCE_3RD_EZSAT)
aux_source_directory(3rd/libs/json11 SOURCE_3RD_JSON11)
aux_source_directory(3rd/libs/minisat SOURCE_3RD_MINISAT)
aux_source_directory(3rd/libs/sha1 SOURCE_3RD_SHA1)
aux_source_directory(3rd/libs/subcircuit SOURCE_3RD_SUBCIRCUIT)

add_library(yosysf STATIC
        ${SOURCE_YOSYS} ${SOURCE_3RD_BIGINT} ${SOURCE_3RD_EZSAT} ${SOURCE_3RD_JSON11}
        ${SOURCE_3RD_MINISAT} ${SOURCE_3RD_SHA1} ${SOURCE_3RD_SUBCIRCUIT})

target_include_directories(yosysf PUBLIC 3rd)


# target afbdil
aux_source_directory(src/afbdil SOURCE_AFBDIL)

add_library(afbdil STATIC ${SOURCE_AFBDIL})
target_include_directories(afbdil PUBLIC include)
target_include_directories(afbdil PRIVATE 3rd/include)
target_include_directories(afbdil PRIVATE 3rd)


# target transpiler
set(CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/usr/lib/llvm-8/cmake;E:/Programming/llvm-7.0.0.src/build/lib/cmake/llvm")
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION} at ${LLVM_DIR}")

add_definitions(${LLVM_DEFINITIONS})


# target afbd
aux_source_directory(src/transpiler SOURCE_AFBD)

add_executable(afbd main.cpp ${SOURCE_AFBD})
target_include_directories(afbd PRIVATE ${LLVM_INCLUDE_DIRS})
target_include_directories(afbd PUBLIC include)

llvm_map_components_to_libnames(llvm_libs support core irreader
        #aarch64asmparser aarch64asmprinter aarch64codegen aarch64desc aarch64disassembler aarch64info aarch64utils
        #amdgpuasmparser amdgpuasmprinter amdgpucodegen amdgpudesc amdgpudisassembler amdgpuinfo amdgpuutils
        #armasmparser armasmprinter armcodegen armdesc armdisassembler arminfo armutils asmparser asmprinter
        #avrasmparser avrasmprinter avrcodegen avrdesc avrdisassembler avrinfo
        #bpfasmparser bpfasmprinter bpfcodegen bpfdesc bpfdisassembler bpfinfo
        #hexagonasmparser hexagoncodegen hexagondesc hexagondisassembler hexagoninfo
        #lanaiasmparser lanaiasmprinter lanaicodegen lanaidesc lanaidisassembler lanaiinfo
        #mipsasmparser mipsasmprinter mipscodegen mipsdesc mipsdisassembler mipsinfo mirparser
        #msp430asmparser msp430asmprinter msp430codegen msp430desc msp430info
        #nvptxasmprinter nvptxcodegen nvptxdesc nvptxinfo
        #powerpcasmparser powerpcasmprinter powerpccodegen powerpcdesc powerpcdisassembler powerpcinfo
        #sparcasmparser sparcasmprinter sparccodegen sparcdesc sparcdisassembler sparcinfo
        #systemzasmparser systemzasmprinter systemzcodegen systemzdesc systemzdisassembler systemzinfo
        #webassemblyasmparser webassemblyasmprinter webassemblycodegen webassemblydesc webassemblydisassembler webassemblyinfo windowsmanifest
        x86asmparser x86asmprinter x86codegen x86desc x86disassembler x86info x86utils
        #xcoreasmprinter xcorecodegen xcoredesc xcoredisassembler xcoreinfo
        )

target_link_libraries(afbd afbdil ${llvm_libs} yosysf)
