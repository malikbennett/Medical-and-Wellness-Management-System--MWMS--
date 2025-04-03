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
- [Using CMake Presets](#using-cmake-presets)
- [Notes](#notes)

## Prerequisites

### Linux:

- GCC (version 11.4 or later)
- wxWidgets (3.1.5 or later)
- CMake (version 3.10 or later)

### Windows:

- MinGW-w64 (version 8.1.0 or later)
- wxWidgets (3.1.5 or later)
- CMake (version 3.10 or later)

## Installing Dependencies

### Linux (Debian-based)

```bash
sudo apt update
sudo apt install build-essential libwxgtk3.0-gtk3-dev cmake
```

### Windows

1. **Install MinGW-w64**:

   - Download from [MSYS2](https://www.msys2.org/)
   - Run the installer and follow the prompts
   - Update packages: `pacman -Syu`
   - Install MinGW: `pacman -S mingw-w64-x86_64-toolchain`

2. **Install wxWidgets**:

   - Download from [wxWidgets Downloads](https://www.wxwidgets.org/downloads/)
   - Build from source or use pre-built binaries
   - Set environment variable: `WXWIN=C:\wxWidgets-3.1.5`

3. **Install CMake**:
   - Download from [CMake website](https://cmake.org/download/)
   - Add CMake to your system PATH

## Setting Up the Project

```bash
git clone https://github.com/malikbennett/Medical-and-Wellness-Management-System--MWMS--.git
cd Medical-and-Wellness-Management-System--MWMS--
```

## Configure and Build the Project

### Linux

```bash
mkdir build && cd build/
cmake ..
make
```

### Windows

```cmd
mkdir build && cd build/
cmake -G "MinGW Makefiles" ..
mingw32-make
```

## Running the Application

### Linux:

```bash
./build/MWMS
```

### Windows:

```cmd
build\MWMS.exe
```

## Using CMake Presets

The project includes `CMakePresets.json` for simplified configuration:

### Linux:

```bash
cmake --preset=linux-default
```

### Windows:

```cmd
cmake --preset=windows-default
```

## Build Notes

- For first-time wxWidgets setup on Windows, you may need to:
  ```cmd
  set PATH=%WXWIN%\lib\gcc_dll;%PATH%
  ```
- To enable debug builds, use `-DCMAKE_BUILD_TYPE=Debug`
- Ensure all build directories are cleaned when switching configurations

## User Logins

- Password for all users: password

1. _Admin_

- Username: admin

2. _Doctor_

- Username: doctor

3. _Nurse_

- Username: nurse

4. _Dietitian_

- Username: dietitian

5. _Psychologist/Councillor_

- Username: psychologist

6. _Receptionist_

- Username: receptionist

7. _Patient_

- Username: patient
