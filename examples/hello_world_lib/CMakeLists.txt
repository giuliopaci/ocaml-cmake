cmake_minimum_required(VERSION 2.6)

project(hello-world C)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../../cmake")

find_package(OCaml REQUIRED)

include(UseOCaml)

add_ocaml_executable(main-bytecode BYTECODE SOURCES hello.ml main_ocaml.ml)

add_ocaml_executable(main-native NATIVE SOURCES hello.ml main_ocaml.ml)

add_ocaml_library(hello_world NATIVE SOURCES hello.ml)

add_ocaml_library(hello_world-bytecode BYTECODE SOURCES hello.ml)

add_ocaml_executable(main2-native NATIVE SOURCES main_ocaml.ml PACKAGES hello_world)

add_ocaml_executable(main2-bytecode BYTECODE SOURCES main_ocaml.ml PACKAGES hello_world-bytecode)


# TODO: remove the following block that is probably better handled in UseOCaml.cmake
set(so_c_flags "")
set(so_link_flags "")
# TODO: remove this line that is needed just to load hunposwrap
list (APPEND so_link_flags -linkall)
if(${CMAKE_OCaml_CONFIG_os_type} MATCHES "[wW][iI][nN]32")
  if(${CMAKE_OCaml_CONFIG_native_c_compiler} MATCHES "[gG][cC][cC]")
    list (APPEND so_link_flags -cclib "-link -static-libgcc")
  endif()
elseif(${CMAKE_OCaml_CONFIG_system} MATCHES "[lL][iI][nN][uU][xX]")
  if("${CMAKE_OCaml_CONFIG_architecture}" STREQUAL "amd64")
    list (APPEND so_c_flags -fPIC)
    if(NOT ${CMAKE_OCaml_VERSION} VERSION_LESS "4.00")
      list (APPEND so_link_flags -runtime-variant _pic)
    endif()
  endif()
elseif(${CMAKE_OCaml_CONFIG_system} MATCHES "[mM][aA][cC][oO][sS][xX]")
  if("${CMAKE_OCaml_CONFIG_architecture}" STREQUAL "amd64")
    list (APPEND so_link_flags -cclib -dynamiclib)
  endif()
else()
endif()
set(so_flags)
if(so_c_flags)
  list (APPEND so_flags C_FLAGS ${so_c_flags})
endif()
if(so_link_flags)
  list (APPEND so_flags LINK_FLAGS ${so_link_flags})
endif()

add_ocaml_library(hello_world_wrap NATIVE SOURCES hellowrap_ocaml.ml PACKAGES hello_world)
add_ocaml_c_object(libhelloworld NATIVE SOURCES hellowrap-c.c hello.h PACKAGES hello_world hello_world_wrap ${so_flags})

add_executable(main-libhelloworld main.c)
target_link_libraries(main-libhelloworld libhelloworld)

add_ocaml_library(hello_world_wrap-bytecode BYTECODE SOURCES hellowrap_ocaml.ml PACKAGES hello_world-bytecode)
add_ocaml_c_object(libhelloworld-bytecode BYTECODE SOURCES hellowrap-c.c hello.h PACKAGES hello_world-bytecode hello_world_wrap-bytecode ${so_flags})

add_executable(main-libhelloworld-bytecode main.c)
target_link_libraries(main-libhelloworld-bytecode libhelloworld-bytecode)
