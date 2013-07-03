#=============================================================================
# Setup unit tests
#=============================================================================
find_package(Boost 1.53 REQUIRED)

add_custom_target(unit COMMENT "build all the unit tests")

function(mpl_extensions_add_test name sources)
    add_executable(${name} EXCLUDE_FROM_ALL ${sources})
    set_property(TARGET ${name}
        APPEND PROPERTY INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
    )
    set_property(TARGET ${name}
        APPEND PROPERTY INCLUDE_DIRECTORIES ${mpl_extensions_SOURCE_DIR}/include
    )
    add_test(NAME ${name} COMMAND ${name})
    add_dependencies(unit ${name})
endfunction()


mpl_extensions_add_test(deferred_apply  deferred_apply.cpp)
mpl_extensions_add_test(is_adjacent     is_adjacent.cpp)
mpl_extensions_add_test(is_reachable    is_reachable.cpp)
mpl_extensions_add_test(matches         matches.cpp)
mpl_extensions_add_test(reachable_set   reachable_set.cpp)
mpl_extensions_add_test(set_equal       set_equal.cpp)
