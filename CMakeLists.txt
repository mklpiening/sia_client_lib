cmake_minimum_required(VERSION 2.8)
project(sia_client)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Boost REQUIRED)

###########
# library #
###########

set(SIALIB_SOURCES
    src/SialibUart.cpp
)

include_directories(include
    ${Boost_INCLUDE_DIRS})

add_library(sialib SHARED ${SIALIB_SOURCES})
target_link_libraries(sialib
    ${Boost_LIBRARIES})

add_library(sialib_static STATIC ${SIALIB_SOURCES})
target_link_libraries(sialib_static
    ${Boost_LIBRARIES})


###################
# install library #
###################

install(TARGETS sialib sialib_static
        EXPORT sialibTargets
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib/static)

install(DIRECTORY include/sialib
        DESTINATION include ${CMAKE_INSTALL_INCLUDEDIR})


#######################
# install cmake stuff #
#######################

include(CMakePackageConfigHelpers)

set(INCLUDE_INSTALL_DIR include/)
set(LIB_INSTALL_DIR lib/)
set(SYSCONFIG_INSTALL_DIR etc/hyperlib/)

install(EXPORT sialibTargets
        FILE sialibTargets.cmake
        NAMESPACE sialib::
        DESTINATION ${LIB_INSTALL_DIR}/cmake/sialib)

configure_package_config_file(SialibConfig.cmake
                           ${CMAKE_CURRENT_BINARY_DIR}/SialibConfig.cmake
                            INSTALL_DESTINATION ${LIB_INSTALL_DIR}/cmake/hyperlib
                            PATH_VARS INCLUDE_INSTALL_DIR SYSCONFIG_INSTALL_DIR)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/SialibConfigVersion.cmake
                                COMPATIBILITY SameMajorVersion
                                VERSION 0.0.1)


install(FILES ${CMAKE_CURRENT_BINARY_DIR}/SialibConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/SialibConfigVersion.cmake
    DESTINATION ${LIB_INSTALL_DIR}/cmake/sialib)
