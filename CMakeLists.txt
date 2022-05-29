# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(blinky)

### EXAMPLE STATIC LIBRARY :: BEGIN ###

# Allow app to include headers from the library including normal or bindgen headers
set(LOGZ_EXAMPLE_LIB_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/logz-example-rs)
set(LOGZ_LIB_SRC_DIR ${LOGZ_EXAMPLE_LIB_SRC_DIR}/lib/logz)
# Cortex-M4F (NRF52)
# set(LOGZ_EXAMPLE_LIB_DIR ${LOGZ_EXAMPLE_LIB_SRC_DIR}/target/thumbv7em-none-eabihf/release)
# Cortex-M33F (NRF53)
set(LOGZ_EXAMPLE_LIB_DIR ${LOGZ_EXAMPLE_LIB_SRC_DIR}/target/thumbv8m.main-none-eabihf/release)
include_directories(AFTER ${LOGZ_EXAMPLE_LIB_SRC_DIR}/include ${LOGZ_EXAMPLE_LIB_SRC_DIR}/include/generated ${LOGZ_LIB_SRC_DIR}/include/generated)
add_library(liblogz_example_rs STATIC IMPORTED GLOBAL)
set_target_properties(liblogz_example_rs PROPERTIES IMPORTED_LOCATION ${LOGZ_EXAMPLE_LIB_DIR}/liblogz_example_rs.a)
# Always let cargo decide if the library should be rebuilt
add_custom_target(
  liblogz_example_rs_target
  ALL
  BYPRODUCTS ${LOGZ_EXAMPLE_LIB_DIR}/liblogz_example_rs.a
  WORKING_DIRECTORY ${LOGZ_EXAMPLE_LIB_SRC_DIR}
  COMMAND cargo make build
  )
add_dependencies(app liblogz_example_rs_target)
# A couple Cortex M math functions get multiple definitions
target_link_libraries(app PRIVATE ${LOGZ_EXAMPLE_LIB_DIR}/liblogz_example_rs.a -Wl,--allow-multiple-definition)

### EXAMPLE STATIC LIBRARY :: END ###


### The logger bindings still need to be compiled for zephyr, which is why we still have to build the static lib and bridge
target_sources(app PRIVATE src/main.c ${LOGZ_LIB_SRC_DIR}/src/bridge.c)