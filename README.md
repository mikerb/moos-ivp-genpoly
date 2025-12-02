# moos-ivp-extend

|              |                            |
|:------------ |:-------------------------- |
| FILE:        | moos-ivp-genpoly/README.md |
| DATE:        | 2025/12/01                 |
| DESCRIPTION: | Contains info on the moos-ivp-genpoly repo. |


# Introduction

The moos-ivp-genpoly repository contains code for (a) representing general,
non-convex polygons, (b) algorithms for covering a genpoly with a set of
convex polygons, and (c) an engineering GUI for testing.

# Directory Structure

The directory structure for the moos-ivp-extend is described below:

| Directory        | Description                                 |
|:---------------- |:------------------------------------------- |
| bin              | Directory for generated executable files    |
| build            | Directory for build object files            |
| build.sh         | Script for building moos-ivp-extend         |
| CMakeLists.txt   | CMake configuration file for the project    |
| lib              | Directory for generated library files       |
| README           | Contains helpful information - (this file). |
| src              | Directory for source code                   |


# Build Instructions

## Linux and Mac Users

To build on Linux and Apple platforms, execute the build script within this
directory:

```bash
   $ ./build.sh
```

# Environment variables

The moos-ivp-genpoly binaries files should be added to your path to allow them
to be launched from pAntler.

# END of README

