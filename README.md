# Geometry Library

A high-performance C++ dynamic library for 3D geometry operations, including vector operations, 3D projection, Separating Axis Theorem (SAT) collision detection, and Minkowski difference calculation. The library provides bindings for C and Python, making it accessible from multiple programming languages.

## Features

- **Vector Operations**: Addition, subtraction, scalar multiplication, dot product, cross product, length calculation, and normalization
- **3D Projection**: Project vectors onto arbitrary axes
- **Collision Detection**: Separating Axis Theorem (SAT) for convex polygons
- **Minkowski Difference**: Calculate the Minkowski difference between two shapes
- **Multi-language Support**: C++, C, and Python bindings

## Directory Structure

```
├── CMakeLists.txt        # CMake build configuration
├── README.md             # This documentation
├── .gitignore            # Git ignore file
├── src/                  # Source code
│   ├── core/             # C++ core implementation
│   │   ├── geometry.h    # Core header file
│   │   └── geometry.cpp  # Core implementation
│   ├── c_interface/      # C interface
│   │   ├── geometry_c.h  # C header file
│   │   └── geometry_c.cpp # C interface implementation
│   └── python/           # Python bindings
│       ├── __init__.py   # Python package initialization
│       └── geometry.py   # Python binding implementation
└── examples/             # Example code
    ├── cpp/              # C++ examples
    ├── c/                # C examples
    └── python/           # Python examples
```

## Build Instructions

### Prerequisites

- CMake 3.10 or higher
- C++11 compatible compiler
- Python 3.x (for Python bindings)

### Build Steps

1. **Clone the repository**
   ```bash
   git clone <repository-url>
   cd geometry-library
   ```

2. **Create build directory**
   ```bash
   mkdir build && cd build
   ```

3. **Configure and build**
   ```bash
   cmake ..
   make
   ```

   This will generate the dynamic library `libgeometry.so` in the build directory.

## Usage

### C++ Usage

```cpp
#include <iostream>
#include <vector>
#include "geometry.h"

int main() {
    // Create vectors
    geometry::Vector3D v1(1.0f, 2.0f, 3.0f);
    geometry::Vector3D v2(4.0f, 5.0f, 6.0f);
    
    // Vector operations
    geometry::Vector3D sum = v1 + v2;
    float dot = v1.dot(v2);
    
    // Projection
    geometry::Vector3D axis(1.0f, 0.0f, 0.0f);
    geometry::Vector3D projection = geometry::project(v1, axis);
    
    // Collision detection
    std::vector<geometry::Vector3D> shape1 = {
        geometry::Vector3D(0.0f, 0.0f, 0.0f),
        geometry::Vector3D(1.0f, 0.0f, 0.0f),
        geometry::Vector3D(1.0f, 1.0f, 0.0f),
        geometry::Vector3D(0.0f, 1.0f, 0.0f)
    };
    
    std::vector<geometry::Vector3D> shape2 = {
        geometry::Vector3D(0.5f, 0.5f, 0.0f),
        geometry::Vector3D(1.5f, 0.5f, 0.0f),
        geometry::Vector3D(1.5f, 1.5f, 0.0f),
        geometry::Vector3D(0.5f, 1.5f, 0.0f)
    };
    
    bool collision = geometry::satCollision(shape1, shape2);
    
    return 0;
}
```

### C Usage

```c
#include <stdio.h>
#include "geometry_c.h"

int main() {
    // Create vectors
    Vector3D_C v1 = {1.0f, 2.0f, 3.0f};
    Vector3D_C v2 = {4.0f, 5.0f, 6.0f};
    
    // Vector operations
    Vector3D_C sum = vector3d_add(v1, v2);
    float dot = vector3d_dot(v1, v2);
    
    // Projection
    Vector3D_C axis = {1.0f, 0.0f, 0.0f};
    Vector3D_C projection = vector3d_project(v1, axis);
    
    // Collision detection
    Vector3D_C shape1[] = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };
    int shape1_size = 4;
    
    Vector3D_C shape2[] = {
        {0.5f, 0.5f, 0.0f},
        {1.5f, 0.5f, 0.0f},
        {1.5f, 1.5f, 0.0f},
        {0.5f, 1.5f, 0.0f}
    };
    int shape2_size = 4;
    
    bool collision = sat_collision(shape1, shape1_size, shape2, shape2_size);
    
    return 0;
}
```

### Python Usage

```python
from geometry import Vector, sat_collision, minkowski_difference

# Create vectors
v1 = Vector(1.0, 2.0, 3.0)
v2 = Vector(4.0, 5.0, 6.0)

# Vector operations
sum_vec = v1 + v2
dot = v1.dot(v2)

# Projection
axis = Vector(1.0, 0.0, 0.0)
projection = v1.project(axis)

# Collision detection
shape1 = [
    Vector(0.0, 0.0, 0.0),
    Vector(1.0, 0.0, 0.0),
    Vector(1.0, 1.0, 0.0),
    Vector(0.0, 1.0, 0.0)
]

shape2 = [
    Vector(0.5, 0.5, 0.0),
    Vector(1.5, 0.5, 0.0),
    Vector(1.5, 1.5, 0.0),
    Vector(0.5, 1.5, 0.0)
]

collision = sat_collision(shape1, shape2)
```

## Examples

The `examples` directory contains complete examples for each language:

- **C++ Example**: `examples/cpp/example.cpp`
- **C Example**: `examples/c/example.c`
- **Python Example**: `examples/python/example.py`

To run the examples:

1. Build the library as described above
2. For C++:
   ```bash
   g++ -std=c++11 -I src/core examples/cpp/example.cpp -L build -lgeometry -o examples/cpp/example
   LD_LIBRARY_PATH=build ./examples/cpp/example
   ```

3. For C:
   ```bash
   gcc -I src/c_interface examples/c/example.c -L build -lgeometry -o examples/c/example
   LD_LIBRARY_PATH=build ./examples/c/example
   ```

4. For Python:
   ```bash
   LD_LIBRARY_PATH=build python3 examples/python/example.py
   ```

## License

This project is licensed under the MIT License - see the LICENSE file for details.
