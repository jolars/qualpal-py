# GitHub Copilot Instructions for qualpal-py

## Project Overview

**qualpal-py** is a Python package for automatically generating qualitative color palettes with distinct colors. It provides Python bindings to the [qualpal C++ library](https://github.com/jolars/qualpal).

**Status:** 🚧 Work in Progress - See `ROADMAP.md` for current implementation status.

**Architecture:** Python-first approach
- **Python layer**: API, data structures (Color, Palette, Qualpal classes), validation
- **C++ layer**: Performance-critical algorithms (palette generation, distance calculations)

**Key Point:** Pure Python classes (Color, Palette) can be developed and tested WITHOUT building the C++ extension.

**Languages:** Python 3.9+, C++17  
**Build System:** scikit-build-core + CMake + pybind11  
**Package Manager:** uv (recommended)  
**Dependencies:** pybind11, numpy (future), matplotlib (optional)

## Repository Structure

```
qualpal-py/
├── qualpal/                 # Python package (pure Python)
│   ├── __init__.py         # Package exports
│   ├── color.py            # Color class
│   └── (palette.py)        # Palette class (check ROADMAP.md)
├── src/
│   └── main.cpp            # C++ bindings (minimal - only algorithms)
├── tests/
│   ├── test_color.py       # Color class tests
│   └── ...
├── docs/                   # Sphinx documentation
├── CMakeLists.txt          # C++ build configuration
├── pyproject.toml          # Python package configuration
├── Taskfile.yml            # Task runner (optional, uses uv)
├── API_DESIGN.md           # Target API specification
└── ROADMAP.md              # Implementation plan with phase tracking
```

## Build & Development

### Environment Setup

**ALWAYS use `uv` for package management** - it's faster and handles dependency groups correctly.

```bash
# Install uv if not available
curl -LsSf https://astral.sh/uv/install.sh | sh

# Create virtual environment (if needed)
uv venv

# Activate (if using venv)
source .venv/bin/activate  # Linux/macOS
# or
.venv\Scripts\activate     # Windows
```

### Installation

**Development install (with C++ build):**
```bash
uv pip install -e .
```

**With test dependencies:**
```bash
uv pip install -e . --group test
```

**With docs dependencies:**
```bash
uv pip install -e . --group docs
```

**Build time:** ~60-120 seconds (first build), ~10-30 seconds (incremental)

### Testing

**Test pure Python code (NO C++ BUILD NEEDED):**
```bash
# Only test Color class (no build required)
python -m pytest tests/test_color.py -v
```

**Test after C++ build:**
```bash
# Run all tests
python -m pytest

# With coverage
coverage run -m pytest
coverage report
```

**Test command from CI:** `python -m pytest tests`

### Building Documentation

```bash
cd docs
make html
```

**Output:** `docs/build/html/index.html`

**Common Issue:** If getting import errors, ensure package is installed: `uv pip install -e . --group docs`

### Linting & Formatting

**Ruff** is used for linting and formatting:

```bash
# Check
ruff check .

# Fix
ruff check --fix .

# Format
ruff format .
```

**Pre-commit hooks** run ruff automatically. Configuration in `pyproject.toml` under `[tool.ruff]`.

## Build System Details

### CMake Build (C++ Extension)

The C++ extension is built automatically by `scikit-build-core` during `pip install`.

**Key CMake facts:**
- Fetches qualpal C++ library v3.4.0 from GitHub via FetchContent
- Sets `CMAKE_POSITION_INDEPENDENT_CODE ON` (required for Linux)
- Defines `_USE_MATH_DEFINES` on Windows (required for M_PI constant)
- **OpenMP is disabled on MSVC** (Windows) due to SIMD pragma issues
- Creates `_qualpal` module (imported as `from qualpal import _qualpal`)

**Build directory:** `build/{wheel_tag}/` (per Python version/platform)

**Common build issues:**

1. **Linux: "relocation R_X86_64_PC32" error**
   - Fixed by `CMAKE_POSITION_INDEPENDENT_CODE ON` in CMakeLists.txt
   
2. **Windows: "M_PI undeclared identifier"**
   - Fixed by `_USE_MATH_DEFINES` in CMakeLists.txt

3. **Windows: OpenMP SIMD errors**
   - OpenMP is intentionally disabled on MSVC (not performance-critical for typical use)

### Python Package

- **Build backend:** `scikit_build_core.build`
- **Version:** 0.1.0 (managed in `pyproject.toml`)
- **Python support:** 3.9, 3.10, 3.11, 3.12, 3.13, 3.14

## Development Workflow

### When Working on Pure Python Code (Color, Palette)

1. Edit Python files in `qualpal/`
2. Run tests directly: `python -m pytest tests/test_color.py`
3. **NO rebuild needed** - changes are immediate

### When Working on C++ Bindings

1. Edit `src/main.cpp`
2. Rebuild: `uv pip install -e . --no-build-isolation` (faster, skips dep check)
3. Test: `python -m pytest`

### Adding New Features

**Follow the ROADMAP.md phases** - check it for current status and what to work on next.

**Design principle:** Implement in pure Python first, only use C++ for performance-critical algorithms.

## CI/CD Pipeline

### GitHub Actions Workflows

1. **test.yml** - Main test workflow
   - Runs on: ubuntu-latest, windows-latest, macos-latest
   - Python versions: 3.10, 3.13.5
   - Steps:
     - Install dependencies with uv
     - Build package with `uv pip install -e . --group test`
     - Run pytest
     - Upload coverage to Codecov

2. **pypi.yml** - Build wheels for PyPI
   - Uses cibuildwheel for multi-platform wheels
   - Builds for: Linux (x86_64, ARM), Windows (x86_64, ARM), macOS (x86_64, ARM)

3. **release.yml** - Automated releases with semantic-release

**All CI uses uv** - commands use `uv pip install --system` in CI environments.

### Common CI Issues

**uv not found:** Workflows install uv via `astral-sh/setup-uv@v5` action.

**Externally managed Python:** CI uses `--system` flag with uv (safe in isolated containers).

## Key Files & Configuration

### pyproject.toml
- Package metadata
- Build system config (`scikit-build-core`)
- Dependency groups: test, docs, dev
- Pytest config
- Ruff linting rules (numpy docstring convention)
- cibuildwheel configuration

### CMakeLists.txt
- C++ build configuration
- Fetches qualpal C++ library
- Creates `_qualpal` Python module
- Platform-specific fixes (OpenMP, M_PI)

### API_DESIGN.md
- Complete specification of target API
- Includes all classes, methods, parameters
- Use this as reference for what to implement

### ROADMAP.md
- Phase-by-phase implementation plan
- Tracks completion status with checkboxes
- Estimated timeline: 8 weeks to v1.0

## Important Implementation Notes

### Python-First Architecture

**✅ DO:**
- Implement Color, Palette, Qualpal classes in pure Python
- Add validation, properties, conversions in Python
- Only call C++ for expensive operations (generation, distance matrices)

**❌ DON'T:**
- Create C++ class bindings for Color/Palette (wasteful)
- Put validation logic in C++ (harder to debug)

### Current C++ Bindings (src/main.cpp)

Currently exports only ONE function:
```cpp
generate_palette_cpp(n, h_range, c_range, l_range) -> vector<string>
```

This is intentional - minimal C++ bindings. Python wraps this in `Qualpal.generate()`.

### Testing Strategy

1. **Unit tests** for Python classes (no C++ needed)
2. **Integration tests** for C++ algorithm (requires build)
3. Run Python tests during development (fast feedback)
4. Run full suite before PR (includes C++ integration)

## Common Commands Summary

```bash
# Install for development
uv pip install -e .

# Test pure Python (fast, no build)
python -m pytest tests/test_color.py

# Test everything (requires build)
python -m pytest

# Lint and format
ruff check --fix .
ruff format .

# Build docs
cd docs && make html

# Clean build artifacts
rm -rf build/

# Task runner (optional)
task install   # Install with dev dependencies
task test      # Run tests
task docs      # Build docs
```

## Trust These Instructions

These instructions have been validated by:
- Running builds on Linux, macOS, Windows
- Testing with Python 3.10, 3.13
- Reviewing CI logs and fixing documented issues
- Implementing multiple phases successfully

**Only search for additional information if:**
- These instructions are incomplete for your task
- You encounter an error not documented here
- The codebase structure has changed significantly

## Questions or Issues?

- Check `ROADMAP.md` for what's implemented vs. planned
- Check `API_DESIGN.md` for target API specification
- Check CI logs in `.github/workflows/` for recent fixes
- The maintainer uses `devenv` (Nix) for development environment
