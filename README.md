# Software Architecture Applied To Game Engines - ArtFX 2020

This repository contains the materials for the course on software architecture. It features a game project, whose architecture is a lighter version of industrial-grade ones.

The project's code contains voluntary errors and design flaws which are addressed during the classes. The repository is updated after every class, in order to reflect the evolution of its code.

## Installation

The following tools are required:

1. [Premake 5](https://premake.github.io/download.html)
2. [Visual Studio 2017 or higher](https://www.visualstudio.com/downloads/)

If you're not on Windows, or cannot use Visual Studio, Premake allows to use other toolchains, please read its documentation.

## Build

Open a terminal in _StealthFactor_ directory and follow the instructions for your platform.

### Windows

    premake5.exe vs2019

Open _build\StealthFactor.sln_, choose your target, and build.

### Linux

    apt-get install -y g++ g++-multilib libode-dev libsfml-dev make
    premake5 gmake2
    cd build
    make config=release_linux64

## External dependencies

In order to simplify installation of the project, the repository contains parts of external projects, in source code form or executable form.

Although the code should support multiple platforms, only precompiled libraries for Windows are provided.

1. [cli.cpp](https://github.com/KoltesDigital/cli.cpp), a CLI argument parser (header-only)
2. [ODE](http://www.ode.org/), a physics engine
3. [pugixml](http://pugixml.org/), an XML parser (header-only)
4. [SFML](https://www.sfml-dev.org/), a small multimedia framework
