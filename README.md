# Ray Tracing Project

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contact](#contact)

## Introduction
This project is an implementation of "Ray Tracing in One Weekend" with added features such as triangle tracing and a triangle mesh loader for `.obj` files. The goal is to create a rendering of 3D scenes using ray tracing techniques.

## Features
- Basic ray tracing capabilities
- Support for triangle tracing
- Mesh loading from `.obj` files
- Realistic rendering of 3D scenes

## Installation
To get started with this project, follow these steps:

1. **Clone the repository**:
    ```sh
    git clone https://github.com/Neamen1/Ray-tracing-prj.git
    cd Ray-tracing-prj
    ```

2. Ensure you have a C++ compiler installed (e.g., `g++`, `clang`).

3. Build the project using `CMake`:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```
## Usage
Run the program using the following command:
```sh
./ray_tracing_prj
```

Configuration is written in main file. To change the scene, camera settings, and output preferences modify main.cpp file.

## Examples
<div align="center">
    <img src="https://github.com/Neamen1/Ray-tracing-prj/blob/main/some%20result%20pictures/cube2.png" alt="Cube" width="500"/>
    <p>Figure 1: Rendering of a simple scene.</p>
</div>
<div align="center">
    <img src="https://github.com/Neamen1/Ray-tracing-prj/blob/main/some%20result%20pictures/Nefertiti.png" alt="Nefertiti" width="500"/>
    <p>Figure 2: Rendering of a complex scene with triangle meshes.</p>
</div>
<div align="center">
    <img src="https://github.com/Neamen1/Ray-tracing-prj/blob/main/some%20result%20pictures/gourd2.png" alt="Gourd" width="500"/>
    <p>Figure 3: Rendering of a complex scene with triangle meshes.</p>
</div>

## Contact
For any questions or feedback, please contact:
- [Oleksii](mailto:o.rakytskyi@gmail.com)

