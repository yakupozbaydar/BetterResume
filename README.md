# BetterResume

A C++ application for generating professional resumes in PDF format.

## Prerequisites

- CMake (>= 3.10)
- C++17 compatible compiler
- libharu (hpdf) library

On macOS, you can install the required dependencies using:
```bash
brew install libharu
```

## Building

```bash
mkdir build
cd build
cmake ..
make
```

## Git Hooks Setup

This project includes pre-push hooks to ensure code quality. To set up the hooks:

1. Copy the sample hook to git hooks directory:
```bash
mkdir -p .git/hooks
cp .githooks/pre-push .git/hooks/
chmod +x .git/hooks/pre-push
```

The pre-push hook will:
- Check if the project compiles successfully before pushing
- Prevent pushing if compilation fails
- Preserve your existing build directory if present

## Usage

Run the program:
```bash
./BetterResume
```

Follow the prompts to enter your:
- Personal Information
- Education History
- Work Experience
- Skills

The program will generate a professionally formatted PDF resume named "resume.pdf" in the current directory.
