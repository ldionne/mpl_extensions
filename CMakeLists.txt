#=============================================================================
# Setup project
#=============================================================================
project(mpl_extensions CXX)
cmake_minimum_required(VERSION 2.8)

if (CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(MPL_EXTENSIONS_IS_NESTED FALSE)
else()
    set(MPL_EXTENSIONS_IS_NESTED TRUE)
endif()


#=============================================================================
# Setup CMake options
#=============================================================================
include(CMakeDependentOption)
option(MPL_EXTENSIONS_ENABLE_PEDANTIC "Compile with pedantic enabled." ON)
option(MPL_EXTENSIONS_ENABLE_WERROR   "Fail and stop if a warning is triggered." OFF)
option(MPL_EXTENSIONS_ENABLE_CXX0X    "Enable -std=c++0x if the compiler supports it." ON)
option(MPL_EXTENSIONS_ENABLE_LIBCXX   "Enable -stdlib=libc++ if the compiler supports it." ON)
CMAKE_DEPENDENT_OPTION(
    MPL_EXTENSIONS_ENABLE_TESTS "Enable the unit tests. To avoid target name conflicts and cluttering the list of targets, unit tests are disabled when the library is nested inside another project."
    OFF "MPL_EXTENSIONS_IS_NESTED" # off if MPL_EXTENSIONS_IS_NESTED
    ON                             # on otherwise
)
CMAKE_DEPENDENT_OPTION(
    MPL_EXTENSIONS_ENABLE_DOC "Enable the documentation target. To avoid target name conflicts and cluttering the list of targets, this is disabled when the library is nested inside another project."
    OFF "MPL_EXTENSIONS_IS_NESTED" # off if MPL_EXTENSIONS_IS_NESTED
    ON                             # on otherwise
)


#=============================================================================
# Check available compiler flags
#=============================================================================
include(CheckCXXCompilerFlag)
check_cxx_compiler_flag(-pedantic                    MPL_EXTENSIONS_HAS_PEDANTIC_FLAG)
check_cxx_compiler_flag(-std=c++0x                   MPL_EXTENSIONS_HAS_STDCXX0X_FLAG)
check_cxx_compiler_flag(-stdlib=libc++               MPL_EXTENSIONS_HAS_STDLIB_LIBCXX_FLAG)
check_cxx_compiler_flag(-W                           MPL_EXTENSIONS_HAS_W_FLAG)
check_cxx_compiler_flag(-Wall                        MPL_EXTENSIONS_HAS_WALL_FLAG)
check_cxx_compiler_flag(-Werror                      MPL_EXTENSIONS_HAS_WERROR_FLAG)
check_cxx_compiler_flag(-Wextra                      MPL_EXTENSIONS_HAS_WEXTRA_FLAG)
check_cxx_compiler_flag(-Wno-long-long               MPL_EXTENSIONS_HAS_WNO_LONG_LONG_FLAG)
check_cxx_compiler_flag(-Wno-unused-local-typedefs   MPL_EXTENSIONS_HAS_WNO_UNUSED_LOCAL_TYPEDEFS_FLAG)
check_cxx_compiler_flag(-Wno-unused-parameter        MPL_EXTENSIONS_HAS_WNO_UNUSED_PARAMETER_FLAG)
check_cxx_compiler_flag(-Wwrite-strings              MPL_EXTENSIONS_HAS_WWRITE_STRINGS_FLAG)
check_cxx_compiler_flag(-ftemplate-backtrace-limit=0 MPL_EXTENSIONS_HAS_FTEMPLATE_BACKTRACE_LIMIT_0)


#=============================================================================
# Setup warning flags
#=============================================================================
macro(append_if condition lst var)
    if (${condition})
        list(APPEND ${lst} ${var})
    endif()
endmacro()
append_if(MPL_EXTENSIONS_HAS_WALL_FLAG                      MPL_EXTENSIONS_CXX_WARNING_FLAGS -Wall)
append_if(MPL_EXTENSIONS_HAS_WEXTRA_FLAG                    MPL_EXTENSIONS_CXX_WARNING_FLAGS -Wextra)
append_if(MPL_EXTENSIONS_HAS_W_FLAG                         MPL_EXTENSIONS_CXX_WARNING_FLAGS -W)
append_if(MPL_EXTENSIONS_HAS_WNO_UNUSED_LOCAL_TYPEDEFS_FLAG MPL_EXTENSIONS_CXX_WARNING_FLAGS -Wno-unused-local-typedefs)
append_if(MPL_EXTENSIONS_HAS_WNO_UNUSED_PARAMETER_FLAG      MPL_EXTENSIONS_CXX_WARNING_FLAGS -Wno-unused-parameter)
append_if(MPL_EXTENSIONS_HAS_WWRITE_STRINGS_FLAG            MPL_EXTENSIONS_CXX_WARNING_FLAGS -Wwrite-strings)
append_if(MPL_EXTENSIONS_HAS_WNO_LONG_LONG_FLAG             MPL_EXTENSIONS_CXX_WARNING_FLAGS -Wno-long-long)
append_if(MPL_EXTENSIONS_HAS_FTEMPLATE_BACKTRACE_LIMIT_0    MPL_EXTENSIONS_CXX_WARNING_FLAGS -ftemplate-backtrace-limit=0)

if (MPL_EXTENSIONS_ENABLE_WERROR)
    append_if(MPL_EXTENSIONS_HAS_WERROR_FLAG  MPL_EXTENSIONS_CXX_WARNING_FLAGS -Werror)
    append_if(MPL_EXTENSIONS_HAS_WX_FLAG      MPL_EXTENSIONS_CXX_WARNING_FLAGS -WX)
endif()

if (MPL_EXTENSIONS_ENABLE_PEDANTIC)
    append_if(MPL_EXTENSIONS_HAS_PEDANTIC_FLAG MPL_EXTENSIONS_CXX_WARNING_FLAGS -pedantic)
endif()


#=============================================================================
# Setup feature flags
#=============================================================================
if (MPL_EXTENSIONS_ENABLE_CXX0X AND MPL_EXTENSIONS_HAS_STDCXX0X_FLAG)
    list(APPEND MPL_EXTENSIONS_CXX_FEATURE_FLAGS -std=c++0x)
endif()

if (MPL_EXTENSIONS_ENABLE_LIBCXX AND MPL_EXTENSIONS_HAS_STDLIB_LIBCXX_FLAG)
    list(APPEND MPL_EXTENSIONS_CXX_FEATURE_FLAGS -stdlib=libc++)
    # the flag has to be passed to the linker too.
    set(CMAKE_EXE_LINKER_FLAGS -stdlib=libc++)
    set(CMAKE_SHARED_LINKER_FLAGS -stdlib=libc++)
    set(CMAKE_MODULE_LINKER_FLAGS -stdlib=libc++)
endif()

# This is the only place where add_definitions is called. Other properties
# are set on a per-target basis.
add_definitions(
    ${MPL_EXTENSIONS_CXX_WARNING_FLAGS}
    ${MPL_EXTENSIONS_CXX_FEATURE_FLAGS}
)


#=============================================================================
# Setup the documentation
#=============================================================================
if (MPL_EXTENSIONS_ENABLE_DOC)
    add_subdirectory(doc)
endif()


#=============================================================================
# Setup tests
#=============================================================================
if (MPL_EXTENSIONS_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
