ocaml-cmake
===========

CMake Scripts for OCaml

The scripts are in the directory cmake/.

You can find some examples in the directory examples/.

NOTES
=====

These scripts are an adaptation from https://github.com/ocaml-cmake/ocaml-cmake
with the goal of simplifying cross-platform compilation of mixed OCaml and C
code.

They have only been tested in a single project in order to produce a shared
library that can be used from C, compiling it from a Debian amd64 system using
the packaged compiler and the packaged mingw32 and mingw64 cross-compilers.

The scripts are not bug-free and not complete yet and will probably require
some changes to suit most needs. Feel free to contribute back your changes.
