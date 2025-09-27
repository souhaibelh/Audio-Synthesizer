# Audio Synthesizer
Audio synthesizer that allows to play notes using multiple waveforms (sine, saw, square) with frequency offsets, filters, and delay effects

## Table of contents
- [About](#about)
- [Features](#features)
- [Tech Stack](#tech-stack)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage / Examples](#usage--examples)

## About
A simple audio synthesizer built with C++ and ImGui. It supports multiple oscillators,
waveform selection, filters, delay effects, and basic note playback through either the 
keyboard or GUI buttons.

## Features
- **Oscillators**
  - Oscillator 1: square, saw, or sine waveforms with optional frequency offset  
  - Oscillator 2: square, saw, or sine waveforms  

- **Envelopes & Filters**
  - Attack & Release controls  
  - Filter Cutoff and Filter Resonance  

- **Delay Effects**
  - Adjustable Delay Time and Delay Mix  

- **Playback**
  - 12 playable notes using keyboard or on-screen buttons  
  - "Sample" button to play a preloaded audio sample  

## Tech Stack
<p align="center">
  <img src="https://img.shields.io/badge/C++-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" alt="C++"/>
  <img src="https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white" alt="CMake"/>
  <img src="https://img.shields.io/badge/ImGui-888888?style=for-the-badge&logo=imgui&logoColor=white" alt="ImGui"/>
</p>

## Getting Started

### Prerequisites
Make sure you have the following installed on your system:

- **CMake** [Download here](https://cmake.org/download/)
- **C++ Compiler**
  - On Windows: [MinGW-w64 (via MSYS2)](https://www.msys2.org/)  
  - On Linux: `sudo apt install build-essential`  
  - On macOS: `xcode-select --install`
- **Make tool** (`mingw32-make` on Windows, `make` on Linux/macOS)
- **Git**

### Installation
- Clone the project: ```git clone https://github.com/yourusername/Audio-Synthesizer.git```
- Open the project's root folder: ```cd Audio-Synthesizer```
- Create and enter the build directory: ```mkdir build && cd build```
- Run ```cmake -G "MinGW Makefiles" ..```
- Run ```cmake --build .```
- Run the .exe: 61610.synthetizer
