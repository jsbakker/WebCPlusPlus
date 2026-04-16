![C++](https://img.shields.io/badge/c++-23-blue.svg)
![linux](https://img.shields.io/badge/os-linux-green)
![macOS](https://img.shields.io/badge/os-macOS-green.svg?style=flat)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow)
[![CMake and CTest](https://github.com/jsbakker/WebCPlusPlus/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/jsbakker/WebCPlusPlus/actions/workflows/cmake-single-platform.yml)

# Web C Plus Plus (webcpp)
Webcpp converts source code from various programming languages into HTML with
syntax highlighting and colour themes.

Note: This is legacy project originally hosted on SourceForge by the same author.
It has been revised in 2026 for unit tests, language support, and modern C++ to
support other projects.


## Supported Languages / Detected Filetypes
|Language             |Extension(s)|
|---|---|
|Ada		              |.adb, .ads, .ali|
|Assembly	            |.asm, .s|
|Asp		              |.asp, .asa|
|Basic		            |.bas|
|C#		                |.cs|
|C Source	            |.c, .rc|
|C++ Source	          |.cc, .cpp, .cxx|
|C/C++ Header	        |.h, .hh, .hpp, .hxx|
|Cascading StyleSheet |	.css|
|Clojure              |.clj, .cljs, .cljc, .edn|
|D                    |.d, .di|
|Dart                 |.dart|
|DOS Batch	          |.bat, .cmd|
|Elixir               |.ex, .exs|
|EMF		              |.emf|
|Euphoria	            |.e, .eu|
|F#                   |.fs, .fsi, .fsx|
|Fortran		          |.f, .f77, .f90, .for, .ftn|
|Gherkin              |.feature|
|GLSL		              |.glsl, .vert, .frag, .geom, .tesc, .tese, .comp|
|Go		                |.go|
|Groovy               |.groovy, .gradle, .gvy|
|Haskell		          |.hs, .lhs|
|HLSL		              |.hlsl, .hlsli|
|Java		              |.java|
|JavaScript	          |.js|
|Julia                |.jl|
|Kotlin		            |.kt, .kts|
|Lua                  |.lua|
|Markup		            |.htm, .html, .shtml, .sgml|
|Modula 		          |.def, .mod|
|Nasa CLIPS	          |.clp|
|Nim                  |.nim, .nims|
|NVidia Cg	          |.cg|
|Objective-C	        |.m|
|Objective-C++	      |.mm|
|OCaml                |.ml, .mli|
|Pascal		            |.pas|
|Perl		              |.cgi, .pl, .plx, .plex, .pm|
|PHP		              |.inc, .php, .php3, .php4|
|Power Builder	      |.pbl, .pbr|
|PowerShell           |.ps1, .psm1, .psd1|
|Python		            |.py, .pyw|
|R                    |.r|
|RenderMan	          |.rib, .sl|
|Ruby		              |.rb|
|Rust		              |.rs|
|Scala                |.scala, .sc|
|SQL		              |.sql|
|Swift		            |.swift|
|Tcl		              |.tcl, .tk|
|TypeScript	          |.ts, .tsx|
|Unix shell	          |.sh|
|UnrealScript	        |.uc|
|Vala		              |.vala, .vapi|
|VHDL		              |.v, .vhd, .vhdl|
|WGSL                 |.wgsl|
|XML		              |.xml|
|Zig		              |.zig|


# Usage
```
Usage: $ webcpp <infile> <outfile> [options...]

Options:
  -c=<scheme>        Use a webcpp colour scheme.
  -w=<scheme>        The works, same as -m -l -a -h -c=<scheme>.
  -i=<filename>      Use an image for the background.
  -t=<width>         Convert tabs to spaces using the specified width.
  -x=<extension>     Force the filetype for syntax highlighting.
  -X,--external-css  Generate an external stylesheet.
  -s,--snippet-only  Don't generate HTML and BODY tags.
  -l,--line-numbers  Print the line numbers in the left margin.
  -a,--anchor-lines  Create anchors to line numbers.
  -h,--hyperinclude  Create hyperlinks to #include statements.
  -H,--superinclude  Hyperinclude that recursively genera.tes files.
  -t,--tabs-spaces   Convert tabs to spaces, default width is 8.
  -m,--made-with     Show made with webcpp footer.
  -A,--auto          Automatic naming in place of the output file.
  - ,--pipe          Use STDIN or STDOUT in place of the filename.
```


# Installation
This project uses the standard CMake build routine. Refer to [INSTALL.md](INSTALL.md) for detailed instructions.


# Testing
The test suite uses Google Test and is built alongside the main binary via CMake.

```bash
# Configure and build tests
cmake -S . -B build
cmake --build build --target webcpp_tests

# Run all tests
ctest --test-dir build --output-on-failure

# Run a single test suite
ctest --test-dir build -R CPlusPlusHighlight --output-on-failure
```
