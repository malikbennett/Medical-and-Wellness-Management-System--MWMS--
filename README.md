# Medical and Wellness Management System (MWMS)

**Version:** 1.0
**Author:** Malik Bennett
**Date:** April 22, 2025

---

## Table of Contents
1. [Introduction](#introduction)
2. [Features Overview](#features-overview)
3. [Getting Started](#getting-started)
   - [Prerequisites](#prerequisites)
   - [Installing Dependencies](#installing-dependencies)
   - [Cloning the Repository](#cloning-the-repository)
4. [Building the Application](#building-the-application)
   - [Using CMake Presets](#using-cmake-presets)
   - [Manual Build Steps](#manual-build-steps)
5. [Running the Application](#running-the-application)
6. [User Accounts](#user-accounts)
7. [Detailed Feature Guide](#detailed-feature-guide)
   - [1. Login & Authentication](#1-login--authentication)
   - [2. Role-Based Dashboards](#2-role-based-dashboards)
   - [3. Staff Records Management](#3-staff-records-management)
   - [4. Patient Records Management](#4-patient-records-management)
   - [5. Appointment Scheduling](#5-appointment-scheduling)
   - [6. Medication & Prescription Tracking](#6-medication--prescription-tracking)
8. [Footer & Navigation Controls](#footer--navigation-controls)
9. [Packaging & Distribution](#packaging--distribution)
10. [Troubleshooting & FAQs](#troubleshooting--faqs)
11. [License](#license)

---

## Introduction
The **Medical and Wellness Management System (MWMS)** is a desktop application designed for UTech Medical Centre. Built with C++ and wxWidgets, MWMS features administrative tasks, secures patient data, and provides role-specific dashboards for medical professionals, receptionists, administrators, and patients.

## Features Overview
- **Secure Login & Role-Based Access**
- **Dynamic Dashboards** tailored to each user role
- **Staff Records Management** with scheduling and certifications
- **Patient Records Management** with medical history
- **Appointment Scheduling** (booking, cancellation, real‑time availability)
- **Medication & Prescription Tracking** with digital logging

## Getting Started

### Prerequisites
- **Linux**: GCC ≥ 11.4, wxWidgets ≥ 3.1.5, CMake ≥ 3.10
- **Windows**: MinGW-w64 ≥ 8.1.0, wxWidgets ≥ 3.1.5, CMake ≥ 3.10

### Installing Dependencies

#### Linux (Debian/Ubuntu)
```bash
sudo apt update
sudo apt install build-essential libwxgtk3.0-gtk3-dev cmake
```

#### Windows
1. Install MSYS2 → Update (`pacman -Syu`) → `pacman -S mingw-w64-x86_64-toolchain`
2. Download/build wxWidgets 3.1.5 → Set `WXWIN` environment variable
3. Download CMake → Add to PATH

### Cloning the Repository
```bash
git clone https://github.com/malikbennett/Medical-and-Wellness-Management-System--MWMS--.git
cd Medical-and-Wellness-Management-System--MWMS--
```

## Building the Application

### Using CMake Presets
Run one of:
```bash
cmake --preset=linux-debug         # Debug on Linux
cmake --preset=linux-release --config Release  # Release on Linux
cmake --preset=windows-debug       # Debug on Windows
cmake --preset=windows-release --config Release  # Release on Windows
```
Then:
```bash
cmake --build build/<debug|release>
```

### Manual Build Steps
```bash
mkdir build && cd build
cmake ..                                # Add -DCMAKE_BUILD_TYPE=Release for release builds
cmake --build . --parallel 4
```

## Running the Application

- **Linux**: `./build/debug/MWMS`  or `./build/release/MWMS`
- **Windows**: `build\debug\MWMS.exe`  or `build\release\MWMS.exe`

## User Accounts
All sample users use the password **`password`**:
| Role            | Username      |
|-----------------|---------------|
| Administrator   | `admin`       |
| Doctor          | `doctor`      |
| Nurse           | `nurse`       |
| Dietitian       | `dietitian`   |
| Psychologist    | `psychologist`|
| Receptionist    | `receptionist`|
| Patient         | `patient`     |

## Feature Guide

### 1. Login & Authentication
- **Encrypted passwords** stored via XOR + HEX
- **3 login attempts** before account lockout
- **Administrator** can unlock accounts

### 2. Role-Based Dashboards
- **Admin Dashboard**: Manage staff, patients, appointments, reports
- **Doctor Dashboard**: View today’s appointments, patient list, referrals, prescriptions
- **Nurse Dashboard**: View patient vitals, check‑in appointments, administer medications
- **Receptionist Dashboard**: Book, reschedule, cancel appointments; view visit logs
- **Patient Dashboard**: Book/reschedule/cancel appointments; view medical history

### 3. Staff Records Management
- **Add/Edit/Delete** employee profiles
- Fields: ID, Name (first/middle/last), DOB, DOE, Department, Gender, TRN, Job Title, Supervisor

### 4. Patient Records Management
- **CRUD** patient profiles
- Fields: Patient ID, Name, TRN, DOB, First Visit, Gender, Marital Status, Next‑of‑Kin, Contact, Email, Address, History

### 5. Appointment Scheduling
- **Calendar view** of available slots
- **Book**, **Reschedule**, **Cancel**
- **Random‑Access file** for fast updates
- **Queue management** for walk‑ins

### 6. Medication & Prescription Tracking
- **Prescription panel**: add, edit, delete prescriptions
- **Medication inventory** with expiry alerts
- **Patient history** shows past prescriptions

## Footer & Navigation Controls
- **Persistent footer** updates buttons/context per screen via `MainFrame::SwitchPanel()`
- **Dynamic content**: Signup vs. Logout, search, help links, status messages

## Packaging & Distribution
1. Build in **Release** mode
2. Include `MWMS` executable + required `*.so`/`*.dll`
3. Add `MWMS.desktop` shortcut (Linux) or `.lnk` file (Windows) in root folder
4. Zip the entire project folder for delivery

## Troubleshooting & FAQs
- **Missing wxWidgets symbols** → ensure `wx-config` in PATH (Linux) or `WXWIN` set (Windows)
- **Segfaults on login** → check correct installation of `encryption.key` in `data/`
- **UI layout issues** → delete `build/` and rebuild in fresh directory

## License
This project is released under the **MIT License**.

---
*Thank you for using MWMS!*
