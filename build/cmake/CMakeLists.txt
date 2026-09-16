cmake_minimum_required(VERSION 3.30)

project(thermostat)

# !!! find_package must go after project() declaration !!!
# Otherwise VCPKG does not set the CMAKE_PREFIX_PATH to find packages.
find_package(myci CONFIG REQUIRED)

set(srcs)
myci_add_source_files(srcs
    DIRECTORY
        ../../src/${PROJECT_NAME}
    RECURSIVE
)

# TODO: remove?
# list(APPEND srcs ../../src/version.cpp)

myci_declare_application(${PROJECT_NAME}-opengles
    SOURCES
        ${srcs}
    RESOURCE_DIRECTORY
        ../../res
    INCLUDE_DIRECTORIES
        ../../src
    DEPENDENCIES
        clargs
        ruisapp::ruisapp-opengles
    RUN_ARGUMENTS
        --res-path=res
        --window
)

# myci_declare_application(${PROJECT_NAME}-opengl
#     SOURCES
#         ${srcs}
#     RESOURCE_DIRECTORY
#         ../../res
#     INCLUDE_DIRECTORIES
#         ../../src
#     DEPENDENCIES
#         clargs
#         ruisapp::ruisapp-opengl
# )

# set(test_srcs)
# myci_add_source_files(test_srcs
#     DIRECTORY
#         ${CMAKE_CURRENT_LIST_DIR}/../../tests/unit/src
#     RECURSIVE
# )

# myci_declare_application(${PROJECT_NAME}-tests
#     SOURCES
#         ${test_srcs}
#     INCLUDE_DIRECTORIES
#         ../../src # TODO: should not be needed when gltf_loader is made public
#     DEPENDENCIES
#         utki
#         fsif
#         jsondom
#         tst
#         ruis-render-null
# )

# if(NOT TARGET test)
#     add_custom_target(test)
# endif()

# add_custom_target(test-${PROJECT_NAME})
# add_dependencies(test test-${PROJECT_NAME})

# add_custom_command(TARGET test-${PROJECT_NAME}
#     POST_BUILD
#     COMMAND
#         $<TARGET_FILE:${PROJECT_NAME}-tests>
# )
