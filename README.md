# Geometry Processing - Smoothing
This is my implementation of Smoothing assignment in [CSC419/CSC2520 Geometry Processing](https://github.com/alecjacobson/geometry-processing-csc2520/).

## Build
```
git submodule update --init --recursive
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make 
```

## Execution

Once built, you can execute the assignment from inside the `build/` by running
on a given mesh with given scalar field (in
[dmat](http://libigl.github.io/libigl/file-formats/dmat.html) format).

    ./smoothing [path to mesh.obj] [path to data.dmat]

or to load a mesh with phony noisy data use:

    ./smoothing [path to mesh.obj] n

or to load a mesh with smooth z-values as data (for mesh smoothing only):

    ./smoothing [path to mesh.obj]

![](images/plane-smooth-data.gif)
![](images/plane-smooth-geometry.gif)
![](images/sphere-geometric-smoothing.gif)
![](images/beetle-data-denoising.gif)