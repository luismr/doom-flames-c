# DOOM Fire Effect - Cross-platform Makefile
# Supports macOS, Linux, and Windows (with MinGW)

# Project configuration
PROJECT_NAME = doomfire
VERSION = 1.0.0

# Directories
SRC_DIR = src
BUILD_DIR = build
INSTALL_DIR = /usr/local/bin

# Source files
SOURCES = $(SRC_DIR)/main.c $(SRC_DIR)/fire.c $(SRC_DIR)/terminal.c
HEADERS = $(SRC_DIR)/fire.h
OBJECTS = $(SOURCES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

# Compiler detection
CC ?= gcc
ifeq ($(CC),)
    CC = gcc
endif

# Platform detection
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
UNAME_M := $(shell uname -m 2>/dev/null || echo x86_64)

# Default flags
CFLAGS = -std=c99 -Wall -Wextra -Wpedantic
LDFLAGS = 
LIBS = 

# Platform-specific configuration
ifeq ($(UNAME_S),Darwin)
    # macOS
    PLATFORM = macos
    CFLAGS += -D_DARWIN_C_SOURCE
    TARGET = $(PROJECT_NAME)
else ifeq ($(UNAME_S),Linux)
    # Linux
    PLATFORM = linux
    CFLAGS += -D_GNU_SOURCE
    TARGET = $(PROJECT_NAME)
else ifeq ($(findstring MINGW,$(UNAME_S)),MINGW)
    # Windows with MinGW
    PLATFORM = windows
    CFLAGS += -D_WIN32
    LIBS += -lkernel32 -luser32
    TARGET = $(PROJECT_NAME).exe
else ifeq ($(findstring MSYS,$(UNAME_S)),MSYS)
    # Windows with MSYS2
    PLATFORM = windows
    CFLAGS += -D_WIN32
    LIBS += -lkernel32 -luser32
    TARGET = $(PROJECT_NAME).exe
else
    # Default to Unix-like
    PLATFORM = unix
    TARGET = $(PROJECT_NAME)
endif

# Build configuration
DEBUG ?= 0
ifeq ($(DEBUG),1)
    CFLAGS += -g -O0 -DDEBUG
    BUILD_TYPE = debug
else
    CFLAGS += -O3 -DNDEBUG
    BUILD_TYPE = release
endif

# Final target path
TARGET_PATH = $(BUILD_DIR)/$(TARGET)

# Default target
.PHONY: all
all: $(TARGET_PATH)

# Create build directory
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

# Compile object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BUILD_DIR)
	@echo "Compiling $< for $(PLATFORM)..."
	$(CC) $(CFLAGS) -c $< -o $@

# Link executable
$(TARGET_PATH): $(OBJECTS)
	@echo "Linking $(TARGET) for $(PLATFORM)..."
	$(CC) $(OBJECTS) $(LDFLAGS) $(LIBS) -o $@
	@echo "Build complete: $(TARGET_PATH)"

# Debug build
.PHONY: debug
debug:
	$(MAKE) DEBUG=1

# Release build (default)
.PHONY: release
release:
	$(MAKE) DEBUG=0

# Clean build artifacts
.PHONY: clean
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD_DIR)

# Install (Unix-like systems only)
.PHONY: install
install: $(TARGET_PATH)
ifeq ($(PLATFORM),windows)
	@echo "Install target not supported on Windows. Copy $(TARGET_PATH) manually."
else
	@echo "Installing $(TARGET) to $(INSTALL_DIR)..."
	@install -m 755 $(TARGET_PATH) $(INSTALL_DIR)/$(PROJECT_NAME)
	@echo "Installation complete."
endif

# Uninstall (Unix-like systems only)
.PHONY: uninstall
uninstall:
ifeq ($(PLATFORM),windows)
	@echo "Uninstall target not supported on Windows."
else
	@echo "Removing $(INSTALL_DIR)/$(PROJECT_NAME)..."
	@rm -f $(INSTALL_DIR)/$(PROJECT_NAME)
	@echo "Uninstall complete."
endif

# Run the program
.PHONY: run
run: $(TARGET_PATH)
	@echo "Running DOOM Fire Effect..."
	@$(TARGET_PATH)

# Run with optimized rendering
.PHONY: run-optimized
run-optimized: $(TARGET_PATH)
	@echo "Running DOOM Fire Effect (optimized)..."
	@$(TARGET_PATH) --optimized

# Test build on current platform
.PHONY: test
test: $(TARGET_PATH)
	@echo "Running comprehensive test suite..."
	@./test.sh

# Quick test - just help command
.PHONY: test-quick
test-quick: $(TARGET_PATH)
	@echo "Testing $(TARGET) on $(PLATFORM)..."
	@$(TARGET_PATH) --help

# Show build information
.PHONY: info
info:
	@echo "DOOM Fire Effect Build Information"
	@echo "=================================="
	@echo "Project: $(PROJECT_NAME) v$(VERSION)"
	@echo "Platform: $(PLATFORM)"
	@echo "Architecture: $(UNAME_M)"
	@echo "Compiler: $(CC)"
	@echo "Build Type: $(BUILD_TYPE)"
	@echo "Target: $(TARGET_PATH)"
	@echo "CFLAGS: $(CFLAGS)"
	@echo "LDFLAGS: $(LDFLAGS)"
	@echo "LIBS: $(LIBS)"

# Package for distribution
.PHONY: package
package: clean $(TARGET_PATH)
	@echo "Creating package for $(PLATFORM)..."
	@mkdir -p $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
	@cp $(TARGET_PATH) $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/
	@cp README.md $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/ 2>/dev/null || true
	@cp LICENSE $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)/ 2>/dev/null || true
ifeq ($(PLATFORM),windows)
	@zip -r $(PROJECT_NAME)-$(VERSION)-$(PLATFORM).zip $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
else
	@tar -czf $(PROJECT_NAME)-$(VERSION)-$(PLATFORM).tar.gz $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
endif
	@rm -rf $(PROJECT_NAME)-$(VERSION)-$(PLATFORM)
	@echo "Package created successfully."

# Help target
.PHONY: help
help:
	@echo "DOOM Fire Effect - Makefile Help"
	@echo "================================"
	@echo ""
	@echo "Available targets:"
	@echo "  all          - Build the project (default)"
	@echo "  debug        - Build with debug symbols"
	@echo "  release      - Build optimized release version"
	@echo "  clean        - Remove build artifacts"
	@echo "  install      - Install to system (Unix-like only)"
	@echo "  uninstall    - Remove from system (Unix-like only)"
	@echo "  run          - Build and run the program"
	@echo "  run-optimized- Build and run with optimized rendering"
	@echo "  test         - Build and test the program"
	@echo "  info         - Show build configuration"
	@echo "  package      - Create distribution package"
	@echo "  help         - Show this help message"
	@echo ""
	@echo "Variables:"
	@echo "  DEBUG=1      - Enable debug build"
	@echo "  CC=compiler  - Specify compiler (gcc, clang, etc.)"
	@echo ""
	@echo "Examples:"
	@echo "  make                    # Build release version"
	@echo "  make debug              # Build debug version"
	@echo "  make CC=clang           # Use clang compiler"
	@echo "  make run-optimized      # Run with Unicode rendering"

# Declare phony targets
.PHONY: all debug release clean install uninstall run run-optimized test info package help