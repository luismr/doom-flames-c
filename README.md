[![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Linux%20%7C%20Windows-blue?style=flat-square)](https://github.com/luismr/doom-flames-c)
[![Language](https://img.shields.io/badge/Language-C99-green?style=flat-square&logo=c)](https://en.wikipedia.org/wiki/C99)
[![License](https://img.shields.io/badge/License-MIT-yellow?style=flat-square)](LICENSE.md)
[![Build Status](https://github.com/luismr/doom-flames-c/workflows/CI%20-%20Build%20and%20Test/badge.svg)](https://github.com/luismr/doom-flames-c/actions/workflows/ci.yml)
[![Terminal](https://img.shields.io/badge/Terminal-256%20Colors-orange?style=flat-square&logo=gnome-terminal)](https://github.com/luismr/doom-flames-c)
[![Performance](https://img.shields.io/badge/Performance-60%20FPS-red?style=flat-square&logo=speedtest)](https://github.com/luismr/doom-flames-c)
[![Dependencies](https://img.shields.io/badge/Dependencies-Zero-purple?style=flat-square)](https://github.com/luismr/doom-flames-c)
[![Code Quality](https://img.shields.io/badge/Code%20Quality-A+-success?style=flat-square&logo=codeclimate)](https://github.com/luismr/doom-flames-c)
[![ANSI](https://img.shields.io/badge/ANSI-Escape%20Codes-lightblue?style=flat-square)](https://en.wikipedia.org/wiki/ANSI_escape_code)
[![Unicode](https://img.shields.io/badge/Unicode-Half%20Blocks-blueviolet?style=flat-square)](https://unicode.org/charts/PDF/U2580.pdf)
[![Retro](https://img.shields.io/badge/Retro-1993%20DOOM-darkred?style=flat-square&logo=steam)](https://store.steampowered.com/app/2280/Ultimate_Doom/)
[![Fire](https://img.shields.io/badge/🔥-Authentic%20Algorithm-ff6b35?style=flat-square)](https://github.com/luismr/doom-flames-c)

# DOOM Fire Effect in C

A cross-platform terminal implementation of the classic DOOM fire effect algorithm. Experience the mesmerizing flames that made DOOM famous, right in your terminal!

This project is a recreation of my original Borland C flames implementation, which was requested as part of my Computer Graphics 1 coursework during my Computer Science graduation in 1999.

![DOOM Fire Effect](img/Screenshot%202026-01-20%20at%2011.39.18.png)

## Features

- 🔥 **Authentic DOOM Fire Algorithm**: Based on the original PSX DOOM fire effect
- 🌍 **Cross-Platform**: Runs on macOS, Linux, and Windows
- 🎨 **Multiple Fire Intensity Modes**: Red/Orange, Classic DOOM, and Hot White flames
- 🎨 **256-Color Support**: Beautiful fire colors using ANSI escape codes
- ⚡ **Optimized Rendering**: Unicode half-blocks for double vertical resolution
- 🎮 **Interactive Controls**: Real-time wind control, speed adjustment, and pause
- 📦 **Zero Dependencies**: Pure C with standard library only
- 🚀 **High Performance**: Smooth 30-60 FPS animation

## Quick Start

### Build and Run

```bash
# Clone the repository
git clone https://github.com/luismr/doom-flames-c.git
cd doom-flames-c

# Build the project
make

# Run the fire effect
make run

# Or run with optimized Unicode rendering
make run-optimized
```

> **📋 Platform-Specific Instructions**: For detailed build instructions on macOS, Linux, and Windows, see the [Building](#building) section below.

### Usage

```bash
# Basic usage
./build/doomfire

# Custom dimensions and settings
./build/doomfire --width 120 --height 40 --fps 60 --optimized

# With wind effect and red/orange flames
./build/doomfire --wind 1 --optimized --intensity 0

# Classic DOOM fire with yellow/white flames
./build/doomfire --intensity 1 --optimized
```

## Command Line Options

| Option | Description | Default |
|--------|-------------|---------|
| `-w, --width WIDTH` | Set fire width | Terminal width |
| `-h, --height HEIGHT` | Set fire height | Terminal height |
| `-f, --fps FPS` | Frames per second (1-120) | 30 |
| `-d, --wind DIR` | Wind direction (-1=left, 0=none, 1=right) | 0 |
| `-i, --intensity MODE` | Fire intensity (0=red/orange, 1=classic, 2=hot white) | 0 |
| `-o, --optimized` | Use Unicode half-blocks for better resolution | Standard |
| `--help` | Show help message | - |

## Interactive Controls

While the fire is running, you can use these controls:

| Key | Action |
|-----|--------|
| `q`, `ESC`, `Ctrl+C` | Quit the program |
| `SPACE` | Toggle pause/resume |
| `LEFT` arrow, `a`, `A` | Set wind direction left |
| `RIGHT` arrow, `d`, `D` | Set wind direction right |
| `s`, `S` | Stop wind (no direction) |
| `+`, `=` | Increase animation speed |
| `-`, `_` | Decrease animation speed |

## Fire Intensity Modes

The DOOM fire effect supports three different intensity modes to match your visual preferences:

### 🔥 Mode 0: Red/Orange (Default)
Perfect for authentic red and orange flames without excessive yellow/white.
```bash
./build/doomfire --intensity 0
```
- **Colors**: Predominantly red, orange, and orange-yellow tones
- **Best for**: Classic retro gaming aesthetic with warm colors
- **Visual**: Deep reds transitioning to bright oranges

### 🔥 Mode 1: Classic DOOM
Original DOOM fire effect with more yellow and white flames.
```bash
./build/doomfire --intensity 1
```
- **Colors**: Yellow, light yellow, and white flames
- **Best for**: Authentic original DOOM experience
- **Visual**: Bright yellow flames with white-hot cores

### 🔥 Mode 2: Hot White
Extremely intense white-hot flames for maximum heat effect.
```bash
./build/doomfire --intensity 2
```
- **Colors**: Predominantly white and very light yellow
- **Best for**: Industrial or high-temperature fire simulation
- **Visual**: Blazing white flames with maximum intensity

### Combining with Other Options
```bash
# Red/orange flames with optimized rendering and wind
./build/doomfire --intensity 0 --optimized --wind 1 --fps 60

# Classic DOOM fire in a specific size
./build/doomfire --intensity 1 --width 80 --height 30

# Hot white flames with maximum performance
./build/doomfire --intensity 2 --fps 120 --optimized
```

## Building

### Prerequisites

- C99 compatible compiler (GCC, Clang, or MSVC)
- Make (Unix-like systems) or MinGW (Windows)
- Terminal with 256-color support (recommended)

### Platform-Specific Build Instructions

#### 🍎 macOS

**Prerequisites:**
```bash
# Install Xcode Command Line Tools (includes Clang and Make)
xcode-select --install

# Or install via Homebrew
brew install gcc make
```

**Build and Run:**
```bash
# Clone the repository
git clone https://github.com/luismr/doom-flames-c.git
cd doom-flames-c

# Build (uses Clang by default)
make

# Run the fire effect
./build/doomfire

# Run with optimized rendering
./build/doomfire --optimized --intensity 0
```

**Recommended Terminals:**
- **iTerm2** (Best experience with full color and Unicode support)
- **Terminal.app** (Built-in, good color support)
- **Alacritty** (High performance, excellent rendering)

#### 🐧 Linux

**Prerequisites:**

**Ubuntu/Debian:**
```bash
# Install build tools
sudo apt update
sudo apt install build-essential gcc make

# Optional: Install additional terminals
sudo apt install alacritty kitty
```

**Fedora/RHEL/CentOS:**
```bash
# Install build tools
sudo dnf install gcc make

# Or on older versions
sudo yum install gcc make
```

**Arch Linux:**
```bash
# Install build tools
sudo pacman -S gcc make

# Optional: Install additional terminals
sudo pacman -S alacritty kitty
```

**Build and Run:**
```bash
# Clone the repository
git clone https://github.com/luismr/doom-flames-c.git
cd doom-flames-c

# Build
make

# Run the fire effect
./build/doomfire

# Run with red/orange flames and wind
./build/doomfire --intensity 0 --wind 1 --optimized
```

**Recommended Terminals:**
- **Alacritty** (Best performance and rendering)
- **Kitty** (Excellent Unicode and color support)
- **GNOME Terminal** (Default on many distributions)
- **Konsole** (KDE default, good features)

#### 🪟 Windows

**Prerequisites:**

**Option 1: MinGW-w64 (Recommended)**
```bash
# Install via MSYS2 (https://www.msys2.org/)
# After installing MSYS2, run in MSYS2 terminal:
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-make

# Add to PATH: C:\msys64\mingw64\bin
```

**Option 2: Visual Studio Build Tools**
```bash
# Install Visual Studio Build Tools or Visual Studio Community
# Include C++ build tools and Windows SDK
```

**Option 3: WSL (Windows Subsystem for Linux)**
```bash
# Install WSL2 with Ubuntu
wsl --install

# Then follow Linux Ubuntu instructions inside WSL
```

**Build and Run:**

**Using MinGW/MSYS2:**
```bash
# Clone the repository (in MSYS2 terminal)
git clone https://github.com/luismr/doom-flames-c.git
cd doom-flames-c

# Build
make

# Run the fire effect
./build/doomfire.exe

# Run with classic DOOM colors
./build/doomfire.exe --intensity 1 --optimized
```

**Using Command Prompt/PowerShell (with MinGW in PATH):**
```cmd
REM Clone the repository
git clone https://github.com/luismr/doom-flames-c.git
cd doom-flames-c

REM Build
mingw32-make

REM Run
build\doomfire.exe --intensity 0 --optimized
```

**Recommended Terminals:**
- **Windows Terminal** (Best experience, full color and Unicode support)
- **ConEmu** (Good alternative with customization options)
- **MSYS2 Terminal** (When using MinGW build environment)

### Universal Build Options

```bash
# Release build (optimized)
make

# Debug build
make debug

# Clean build artifacts
make clean

# Show build information
make info

# Run comprehensive tests
make test

# Create distribution package
make package
```

### Build Troubleshooting

#### Common Issues

**"make: command not found"**
- **macOS**: Install Xcode Command Line Tools
- **Linux**: Install `build-essential` or `base-devel` package
- **Windows**: Use MinGW/MSYS2 or Visual Studio Developer Command Prompt

**"No colors displayed"**
- Ensure your terminal supports ANSI escape codes
- Try Windows Terminal on Windows
- Update your terminal emulator

**"Unicode characters not displayed"**
- Use `--intensity 0` instead of `--optimized` for basic rendering
- Ensure terminal supports Unicode (most modern terminals do)

**Compilation errors on Windows**
- Ensure MinGW is properly installed and in PATH
- Try building in MSYS2 environment
- Consider using WSL for Linux-like environment

## Algorithm Details

The DOOM fire effect uses a simple but effective particle system:

1. **Fire Source**: Bottom row initialized with maximum intensity
2. **Propagation**: Each pixel's intensity calculated from the pixel below
3. **Decay**: Random intensity reduction as fire moves upward  
4. **Wind Effect**: Horizontal pixel shifting for realistic movement
5. **Color Mapping**: 37-color palette with configurable intensity modes
6. **Intensity Modes**: Three different fire styles (red/orange, classic, hot white)

### Technical Implementation

- **Fire Buffer**: 2D array of intensity values (0-36)
- **Color Palette**: ANSI 256-color codes with three intensity modes
- **Intensity Control**: Configurable fire source intensity for different visual styles
- **Frame Rate**: Configurable timing with platform-specific sleep functions
- **Memory Usage**: Single buffer allocation, minimal memory footprint

## Terminal Compatibility

### Recommended Terminals

| Platform | Terminal | Color Support | Unicode Support |
|----------|----------|---------------|-----------------|
| macOS | iTerm2 | ✅ Excellent | ✅ Full |
| macOS | Terminal.app | ✅ Good | ✅ Full |
| Linux | Alacritty | ✅ Excellent | ✅ Full |
| Linux | Kitty | ✅ Excellent | ✅ Full |
| Linux | GNOME Terminal | ✅ Good | ✅ Full |
| Windows | Windows Terminal | ✅ Excellent | ✅ Full |
| Windows | ConEmu | ✅ Good | ✅ Good |

### Troubleshooting

- **No colors**: Your terminal may not support ANSI escape codes
- **Garbled output**: Try the standard rendering mode (without `--optimized`)
- **Slow performance**: Reduce FPS or terminal size
- **Build errors on Windows**: Ensure MinGW or MSYS2 is properly installed

## Testing

The project includes a comprehensive test suite that validates all functionality:

### Test Categories

- **Build System Tests**: Verify clean, debug, and release builds
- **Command Line Interface Tests**: Validate argument parsing and help system
- **Fire Effect Functionality Tests**: Test basic rendering, optimized mode, wind effects, and performance
- **Input Handling Tests**: Verify keyboard controls (q, space, arrows, +/-)
- **Anti-Scrolling Tests**: Ensure fire renders in place without terminal scrolling
- **Memory and Performance Tests**: Check for memory leaks and performance issues
- **Cross-Platform Compatibility Tests**: Validate ANSI colors and terminal detection

### Running Tests

```bash
# Run full test suite
make test

# Or run directly
./test.sh

# Quick test (help command only)
make test-quick
```

### ⚠️ Windows Testing Note

**Windows builds are tested in CI but marked as non-blocking** to prevent CI failures from blocking development. Windows-specific issues may not be caught automatically.

**For Windows contributors and users:**
- Please test Windows builds manually on a Windows machine
- Report any Windows-specific issues in GitHub Issues
- Windows builds use MinGW/MSYS2 in CI but may behave differently on native Windows
- Consider testing with both MinGW and Visual Studio compilers if possible

### Test Results

The test suite validates the recent fixes for:
- ✅ **Scrolling Issues**: Fire now renders in place without scrolling
- ✅ **Input Handling**: All keyboard controls (q, space, arrows) work correctly
- ✅ **Terminal Compatibility**: Proper handling of interactive vs non-interactive modes
- ✅ **Performance**: Smooth operation at various FPS settings
- ✅ **Cross-Platform**: Works consistently across different terminal environments

## Contributing

Contributions are welcome! We appreciate bug reports, feature requests, documentation improvements, and code contributions.

### 🚀 Quick Start for Contributors

1. **Fork the Repository**
   ```bash
   # Fork on GitHub: https://github.com/luismr/doom-flames-c/fork
   # Then clone your fork
   git clone https://github.com/YOUR_USERNAME/doom-flames-c.git
   cd doom-flames-c
   ```

2. **Set Up Development Environment**
   ```bash
   # Add upstream remote
   git remote add upstream https://github.com/luismr/doom-flames-c.git
   
   # Create a feature branch
   git checkout -b feature/your-feature-name
   
   # Build and test
   make debug
   make test
   ```

3. **Make Your Changes**
   ```bash
   # Edit code, add features, fix bugs
   # Follow the existing code style and conventions
   
   # Test your changes
   make test
   ./build/doomfire --help  # Test basic functionality
   ```

4. **Submit Pull Request**
   ```bash
   # Commit your changes
   git add .
   git commit -m "Add: Brief description of your changes"
   
   # Push to your fork
   git push origin feature/your-feature-name
   
   # Create pull request on GitHub
   ```

### 📋 Contribution Guidelines

#### 🐛 Bug Reports
When reporting bugs, please include:
- **Operating System**: macOS, Linux distribution, or Windows version
- **Terminal**: Which terminal emulator you're using
- **Build Environment**: Compiler version, make version
- **Steps to Reproduce**: Exact commands and expected vs actual behavior
- **Error Output**: Complete error messages or unexpected output

**Create Issue**: [https://github.com/luismr/doom-flames-c/issues/new](https://github.com/luismr/doom-flames-c/issues/new)

#### 💡 Feature Requests
For new features, please describe:
- **Use Case**: What problem does this solve?
- **Proposed Solution**: How should it work?
- **Alternatives**: Other ways to achieve the same goal
- **Compatibility**: Impact on existing functionality

#### 🔧 Code Contributions

**Coding Standards:**
- **Language**: C99 standard compliance
- **Style**: Follow existing code formatting and naming conventions
- **Comments**: Document complex algorithms and platform-specific code
- **Testing**: Add tests for new features, ensure existing tests pass

**Areas for Contribution:**
- 🎨 **New Fire Effects**: Additional intensity modes or color palettes
- 🖥️ **Platform Support**: Improved Windows/macOS/Linux compatibility
- ⚡ **Performance**: Optimization improvements
- 🎮 **Features**: New interactive controls or command-line options
- 📚 **Documentation**: README improvements, code comments
- 🧪 **Testing**: Additional test cases or platform testing

#### 📝 Pull Request Process

1. **Before Starting**: Check existing issues and PRs to avoid duplicates
2. **Branch Naming**: Use descriptive names like `feature/wind-controls` or `fix/windows-colors`
3. **Commit Messages**: Use clear, descriptive commit messages
4. **Testing**: Ensure all tests pass with `make test`
5. **Documentation**: Update README.md if adding new features
6. **Review**: Be responsive to feedback and suggestions

**Pull Request Template:**
```markdown
## Description
Brief description of changes

## Type of Change
- [ ] Bug fix
- [ ] New feature
- [ ] Documentation update
- [ ] Performance improvement

## Testing
- [ ] All existing tests pass (`make test`)
- [ ] New tests added for new functionality
- [ ] Tested on multiple platforms

## Checklist
- [ ] Code follows project style guidelines
- [ ] Self-review completed
- [ ] Documentation updated if needed
```

### 🛠️ Development Workflow

```bash
# Keep your fork updated
git fetch upstream
git checkout main
git merge upstream/main

# Build debug version with symbols
make debug

# Run comprehensive test suite
make test

# Run quick functionality test
make test-quick

# Check build configuration
make info

# Manual testing with different options
./test.sh

# Test specific features
./build/doomfire --intensity 0 --optimized
./build/doomfire --intensity 1 --wind 1
./build/doomfire --help
```

#### 🚀 CI/CD Integration

The project includes comprehensive GitHub Actions workflows:

**📋 Continuous Integration (`ci.yml`)**
- **Triggers**: Every push to `main`/`develop`, all pull requests
- **Platforms**: Ubuntu, macOS, Windows (with MinGW) 
- **Tests**: Build verification, test suite execution, cross-platform compatibility
- **Note**: Windows builds are non-blocking (won't fail PRs) - manual testing recommended
- **Artifacts**: Build outputs uploaded for 30 days

**🏷️ Automated Releases (`release.yml`)**
- **Triggers**: Version tags matching `v*.*.*` (e.g., `v1.0.0`)
- **Builds**: Release binaries for all platforms
- **Packages**: `.tar.gz` (Linux/macOS), `.zip` (Windows)
- **Release Notes**: Generated from tag commit message

**🔍 Pull Request Checks (`pr-checks.yml`)**
- **Title Validation**: Enforces conventional commit format
- **Changelog Reminders**: Suggests documentation updates for significant changes
- **Security Scanning**: Automated code security analysis

**Example Workflow:**
```bash
# 1. Make changes and test locally
make test

# 2. Commit with conventional format
git commit -m "feat(fire): add new intensity modes for better color control"

# 3. Push to your fork (triggers CI)
git push origin feature/intensity-modes

# 4. Create PR (triggers PR checks)
# 5. After merge, tag for release
git tag -a v1.1.0 -m "Add fire intensity modes and improved controls"
git push origin v1.1.0  # Triggers automated release
```

### 🏷️ Release Process

The project uses automated releases via GitHub Actions:

#### 🤖 Automated Releases
1. **Create a Tag**: Push a version tag in the format `vX.Y.Z`
   ```bash
   git tag -a v1.2.0 -m "Add fire intensity modes and improved cross-platform support"
   git push origin v1.2.0
   ```

2. **Automatic Build**: GitHub Actions will automatically:
   - Build for Linux, macOS, and Windows
   - Run comprehensive tests on all platforms
   - Create release packages (`.tar.gz` for Unix, `.zip` for Windows)
   - Generate release notes from the tag message
   - Upload binaries to GitHub Releases

3. **Release Notes**: The tag message becomes the release notes, so write descriptive commit messages:
   ```bash
   git tag -a v1.2.0 -m "
   ## New Features
   - Added fire intensity modes (red/orange, classic, hot white)
   - Improved cross-platform terminal compatibility
   - Enhanced Unicode rendering with half-blocks
   
   ## Bug Fixes
   - Fixed scrolling issues on all platforms
   - Improved input handling for interactive controls
   
   ## Performance
   - Optimized fire algorithm for smoother animation
   - Reduced memory usage by 15%
   "
   ```

#### 📋 Manual Release Checklist (for maintainers)
- [ ] Update version in source code if needed
- [ ] Test on all supported platforms
- [ ] Update README.md with new features
- [ ] Write comprehensive tag message
- [ ] Push tag to trigger automated release
- [ ] Verify release artifacts are created correctly

#### 🔄 CI/CD Pipeline
- **Continuous Integration**: Every push and PR triggers builds and tests on Linux, macOS, and Windows
- **Automated Testing**: Comprehensive test suite runs on all platforms
- **Code Quality**: Static analysis and style checks
- **Release Automation**: Tagged versions automatically create GitHub releases with binaries

### 📞 Getting Help

- **GitHub Issues**: [https://github.com/luismr/doom-flames-c/issues](https://github.com/luismr/doom-flames-c/issues)
- **Discussions**: [https://github.com/luismr/doom-flames-c/discussions](https://github.com/luismr/doom-flames-c/discussions)
- **Email**: Contact repository maintainers for sensitive issues

### 🙏 Recognition

Contributors will be acknowledged in:
- README.md acknowledgments section
- Git commit history
- Release notes for significant contributions

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.

## Acknowledgments

- **id Software**: For creating DOOM and the original fire effect
- **Fabien Sanglard**: For documenting the DOOM fire algorithm
- **PSX DOOM Team**: For the optimized fire implementation that inspired this version
- **Contributors**: All developers who have contributed to this project ([View Contributors](https://github.com/luismr/doom-flames-c/graphs/contributors))

## Repository Information

- **GitHub**: [https://github.com/luismr/doom-flames-c](https://github.com/luismr/doom-flames-c)
- **Issues**: [Report bugs or request features](https://github.com/luismr/doom-flames-c/issues)
- **Discussions**: [Community discussions](https://github.com/luismr/doom-flames-c/discussions)
- **Releases**: [Download releases](https://github.com/luismr/doom-flames-c/releases)

## Screenshots

*Note: Screenshots show the fire effect in different terminal configurations and intensity modes*

### Fire Intensity Modes

#### Red/Orange Mode (--intensity 0)
```
🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥
🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠
  🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠
    🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡
      🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡
        ⚫⚫⚫⚫⚫⚫⚫⚫
```

#### Classic DOOM Mode (--intensity 1)
```
⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪⚪
🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡
  🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡🟡
    🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠🟠
      🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥🔥
        ⚫⚫⚫⚫⚫⚫⚫⚫
```

### Rendering Modes

#### Standard Rendering
*Character-based rendering using background colors*

#### Optimized Unicode Rendering
*Higher resolution with Unicode half-block characters for smoother appearance*

---

**Enjoy the flames! 🔥**
