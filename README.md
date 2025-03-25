# Medical and Wellness Management System (MWMS)

A C++ Medical and Wellness Management System (MWMS) for UTech Medical Centre, automating patient records, appointment scheduling, and medical professional management through a secure, role-based digital platform.

## Table of Contents
- [Prerequisites](#prerequisites)
- [Installing Dependencies](#installing-dependencies)
  - [Linux](#linux)
  - [Windows](#windows)
- [Setting Up the Project](#setting-up-the-project)
- [Configure and Build the Project](#configure-and-build-the-project)
  - [Linux](#linux-1)
  - [Windows](#windows-1)
- [Running the Application](#running-the-application)
- [Using CMake Presets (Optional)](#using-cmake-presets-optional)
- [Notes](#notes)

## Prerequisites

### Linux:
- GCC (version 11.4 or later)
- Qt 5.x development libraries
- CMake (version 3.10 or later)

### Windows:
- MSVC 2022 (with NMake support)
- Qt 5.x (MSVC version 2019 or 2022)
- CMake (version 3.10 or later)

## Installing Dependencies

### Linux (Debian-based)
To install the required dependencies on a Linux system, run:
```bash
sudo apt update
sudo apt install build-essential qt5-qmake qtbase5-dev cmake
```

### Windows
1. **Install MSVC 2022**:
   - Install Visual Studio 2022 with the MSVC compiler and NMake
   - Ensure you have CMake installed (can be installed via Visual Studio Installer or from the [CMake website](https://cmake.org/))

2. **Install Qt**:
   - Download and install Qt from [Qt Downloads](https://www.qt.io/download))
   - Ensure you install the version compatible with your MSVC version (e.g., msvc2019_64 or msvc2022_64)
   - Set the `CMAKE_PREFIX_PATH` variable to point to the Qt installation directory (e.g., `C:/Qt/5.x/msvc2019_64`)

## Setting Up the Project

Clone the repository to your local machine:
```bash
git clone <repository_url>
cd <project_directory>
```

## Configure and Build the Project

### Linux
1. Create a build directory:
```bash
mkdir build
cd build
```

2. Run CMake to configure the project:
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

3. Build the project:
```bash
make
```

### Windows
1. Open Developer Command Prompt for Visual Studio
2. Navigate to the project directory and create a build directory:
```cmd
mkdir build
cd build
```

3. Run CMake to configure the project:
```cmd
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

4. Build the project:
```cmd
nmake
```

## Running the Application

Once the project is successfully built, you can run the application.

### Linux:
```bash
./Medical-and-Wellness-Management-System
```

### Windows:
Run the executable from the build directory:
```cmd
MWMS.exe
```

## Using CMake Presets (Optional)

If you prefer, you can use the `CMakePresets.json` file to configure your build automatically.

### Linux:
```bash
cmake --preset=linux-gcc
```

### Windows:
```cmd
cmake --preset=windows-msvc
```

## Notes
- If you make changes to the project or need to change the build configuration, delete the contents of the build directory and re-run `cmake`
- Ensure that Qt is installed and configured correctly on both Linux and Windows for the GUI components to work properly
- On Linux, make sure you have proper permissions for the directories you're working with
