![Build](https://github.com/agv-polsl/minimu-ahrs/workflows/Build/badge.svg)

# Minimu AHRS

AHRS Kalman based system using Pololu Minimu-9 v5 sensor combo.
This is a demo utlising Linux Minimu reader and Kalman filter AHRS libraries.

For more detail please visit submodules with mentioned libraries in the `lib`
directory.

## Build

If you haven't cloned recursively init submodules with:

```sh
git submodule init
git submodule update
```

This depends on the Linux kernel I2C driver via userspace access library.
On Debian that is the `libi2c-dev` package.

You can run build in Docker.
For example to map the project directory as a Docker volume run:
```docker run -v `pwd`:/proj -it agvpolsl/minimu-i2c-builder```.

Build follows standard CMake procedure; in the project directory run:

```sh
mkdir build && cd build
cmake ..
cmake --build .
```
