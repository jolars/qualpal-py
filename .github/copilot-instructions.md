# GitHub Copilot Instructions for qualpal-py

## Project Overview

**qualpal-py** is a Python package for automatically generating qualitative color palettes with distinct colors. It provides Python bindings to the [qualpal C++ library](https://github.com/jolars/qualpal).

**Status:** ✅ **Feature Complete** - Ready for v1.0.0 release

**Current Metrics:**
- 305 tests passing
- 96% test coverage
- Full CI/CD pipeline
- Complete documentation (tutorial + API)
- Cross-platform support (Linux, macOS, Windows)

**Code Quality Requirements:**

- ✅ `ruff format --check .` must pass (formatting)
- ✅ `ruff check .` must pass (linting)
- ✅ `basedpyright qualpal` must pass (type checking)
- ✅ `python -m pytest` must pass (tests)

**Quick Fix:** Use `ruff format .` and `ruff check --fix .` to auto-fix most issues before committing.

**Architecture:** Thin Python layer over C++ library

- **Python layer**: API, data structures (Color, Palette, Qualpal classes), validation, rich display
- **C++ layer**: Algorithms, color conversions, palette generation, performance-critical code

**Languages:** Python 3.9+, C++17  
**Build System:** scikit-build-core + CMake + pybind11  
**Package Manager:** uv (recommended)  
**Dependencies:** pybind11, matplotlib (optional extra)

## Repository Structure

```
qualpal-py/
├── qualpal/                 # Python package (pure Python)
│   ├── __init__.py         # Package exports
│   ├── color.py            # Color class with conversions & CVD
│   ├── palette.py          # Palette class with analysis
│   ├── qualpal.py          # Main Qualpal generator class
│   └── utils.py            # Utility functions (list_palettes)
├── src/
│   ├── main.cpp            # pybind11 module definition
│   ├── palette_generation.h/cpp  # C++ palette generation wrapper
│   └── color_conversions.h/cpp   # C++ color conversion helpers
├── tests/
│   ├── test_color.py       # Color class tests
│   ├── test_palette.py     # Palette class tests
│   ├── test_qualpal.py     # Qualpal generator tests
│   ├── test_cvd.py         # CVD simulation tests
│   ├── test_export.py      # Export format tests
│   ├── test_visualization.py # Matplotlib tests
│   └── test_display.py     # Rich display tests
├── docs/
│   ├── source/
│   │   ├── index.md        # Documentation homepage
│   │   ├── tutorial.md     # Comprehensive tutorial
│   │   ├── api.md          # API reference
│   │   └── changelog.md    # Version history
│   └── build/html/         # Built documentation
├── CMakeLists.txt          # C++ build configuration
├── pyproject.toml          # Python package configuration
└── Taskfile.yml            # Task runner (optional, uses uv)
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
uv pip install -e . --group dev

# Or with visualization support
uv pip install -e .[viz] --group dev
```

**Build time:** ~60-120 seconds (first build), ~10-30 seconds (incremental)

### Testing

```bash
# Run all tests (305 tests)
python -m pytest

# Run with coverage report
python -m coverage run -m pytest
python -m coverage report --include="qualpal/*"

# Run specific test file
python -m pytest tests/test_color.py
```

**Current test coverage:** 96% (qualpal package)

### Building Documentation

```bash
cd docs
make html
```

**Output:** `docs/build/html/index.html`

**Common Issue:** If getting import errors, ensure package is installed: `uv pip install -e . --group docs`

### Linting & Formatting

**REQUIRED: All code must pass these checks before committing:**

```bash
# 1. Format code (automatically fixes formatting)
ruff format .

# 2. Check and fix linting issues (automatically fixes most issues)
ruff check --fix .

# 3. Type check (no auto-fix, must fix manually)
basedpyright qualpal
```

**To verify before PR/commit:**

```bash
ruff format --check .     # Must pass - no formatting changes needed
ruff check .              # Must pass - no linting errors
basedpyright qualpal      # Must pass - no type errors
```

**Configuration:**

- Ruff: `pyproject.toml` under `[tool.ruff]`
- Docstring convention: numpy style
- Type checking: basedpyright with "standard" mode, Python 3.9+ target

**Pre-commit hooks** will run ruff automatically on commit (configured via `.pre-commit-config.yaml`).

## Build System Details

### CMake Build (C++ Extension)

The C++ extension is built automatically by `scikit-build-core` during `pip install`.

**Key CMake facts:**

- Fetches qualpal C++ library v3.4.0 from GitHub via FetchContent
- Sets `CMAKE_POSITION_INDEPENDENT_CODE ON` (required for Linux)
- Defines `_USE_MATH_DEFINES` on Windows (required for M_PI constant)
- Creates `_qualpal` module (imported as `from qualpal import _qualpal`)

**Build directory:** `build/{wheel_tag}/` (per Python version/platform)

**Common build issues:**

1. **Linux: "relocation R_X86_64_PC32" error**
   - Fixed by `CMAKE_POSITION_INDEPENDENT_CODE ON` in CMakeLists.txt
2. **Windows: "M_PI undeclared identifier"**
   - Fixed by `_USE_MATH_DEFINES` in CMakeLists.txt

### Python Package

- **Build backend:** `scikit_build_core.build`
- **Version:** 0.1.0 (ready to bump to 1.0.0)
- **Python support:** 3.9, 3.10, 3.11, 3.12, 3.13, 3.14
- **Optional dependencies:** `viz` extra for matplotlib support

## Core Features

### Implemented Features

All major features are complete and tested:

1. **Color Operations**
   - Create colors from hex, RGB, HSL
   - Convert between color spaces (RGB, HSL, LAB, LCH, XYZ)
   - Calculate perceptual distance (CIEDE2000)
   - Simulate color vision deficiency (CVD)

2. **Palette Generation**
   - Generate distinct color palettes
   - Customize color space constraints (hue, saturation, lightness)
   - Optimize for background colors
   - CVD-aware palette generation
   - Support for named palettes

3. **Palette Analysis**
   - Calculate minimum pairwise distance
   - Generate distance matrices
   - Identify weakest color pairs

4. **Export & Visualization**
   - Export to CSS custom properties
   - Export to JSON
   - Matplotlib visualization with labels
   - Rich HTML display in Jupyter notebooks

### Usage Examples

```python
from qualpal import Qualpal, Color

# Generate a palette
qp = Qualpal()
palette = qp.generate(6)

# Customize color space
qp_pastel = Qualpal(
    colorspace={'h': (0, 360), 's': (0.3, 0.6), 'l': (0.7, 0.9)}
)
pastels = qp_pastel.generate(5)

# CVD-aware palette
qp_accessible = Qualpal(cvd={'deutan': 0.7})
accessible = qp_accessible.generate(6)

# Color operations
red = Color("#ff0000")
print(red.rgb())      # (1.0, 0.0, 0.0)
print(red.hsl())      # (0.0, 1.0, 0.5)
protan = red.simulate_cvd("protan", severity=1.0)

# Palette analysis
min_dist = palette.min_distance()
matrix = palette.distance_matrix()

# Export
css = palette.to_css(prefix="theme")
json_str = palette.to_json()

# Visualization (requires matplotlib)
fig = palette.show(labels=True)
```

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
   - **Does NOT run linting/type checking** - assumes you've done that locally

2. **pypi.yml** - Build wheels for PyPI
   - Uses cibuildwheel for multi-platform wheels
   - Builds for: Linux (x86_64, ARM), Windows (x86_64, ARM), macOS (x86_64, ARM)

3. **release.yml** - Automated releases with semantic-release

**All CI uses uv** - commands use `uv pip install --system` in CI environments.

**Pre-commit hooks** - Run `ruff check` and `ruff format` automatically on commit.

### Common CI Issues

**uv not found:** Workflows install uv via `astral-sh/setup-uv@v5` action.

**Externally managed Python:** CI uses `--system` flag with uv (safe in isolated containers).

## Key Files & Configuration

### pyproject.toml

- Package metadata (version 0.1.0, ready for 1.0.0)
- Build system config (`scikit-build-core`)
- Dependency groups: test, docs, dev
- Optional dependencies: viz (matplotlib)
- Pytest config
- Ruff linting rules (numpy docstring convention)
- cibuildwheel configuration for multi-platform wheels

### CMakeLists.txt

- C++ build configuration
- Fetches qualpal C++ library v3.4.0
- Creates `_qualpal` Python module
- Platform-specific fixes (OpenMP, M_PI)

### Documentation

- **docs/source/index.md** - Homepage with features and quick start
- **docs/source/tutorial.md** - Comprehensive tutorial (308 lines)
- **docs/source/api.md** - Auto-generated API reference
- **docs/source/changelog.md** - Version history
- Built with Sphinx + myst-nb (supports Jupyter notebooks)

## Development Workflow

### Code Organization

**Design principle:** Implement in pure Python first, only use C++ for performance-critical algorithms.

- **Python files** (`qualpal/*.py`): API, data structures, validation, rich display
- **C++ files** (`src/*.cpp`, `src/*.h`): Bindings, palette generation, color conversions
- **Tests** (`tests/test_*.py`): Comprehensive test suite with 305 tests

### Making Changes

1. **Make minimal changes** - only modify what's necessary
2. **Run quality checks** before committing:
   ```bash
   ruff format .
   ruff check --fix .
   basedpyright qualpal
   python -m pytest
   ```
3. **Update tests** if adding new features
4. **Update docstrings** if changing APIs (numpy style)
5. **Update documentation** if adding major features

### Testing Strategy

1. **Unit tests** for Python classes (fast, no C++ build needed)
2. **Integration tests** for C++ bindings (requires build)
3. **All tests** run in CI on multiple platforms

Run specific test categories:
```bash
python -m pytest tests/test_color.py      # Color class only
python -m pytest tests/test_palette.py    # Palette class only
python -m pytest tests/test_qualpal.py    # Generator only
python -m pytest -k cvd                   # All CVD-related tests
```

## Common Commands Summary

```bash
# Install for development
uv pip install -e . --group dev

# Install with matplotlib support
uv pip install -e .[viz] --group dev

# Run all tests (305 tests)
python -m pytest

# Run tests with coverage
python -m coverage run -m pytest
python -m coverage report --include="qualpal/*"

# Run specific tests
python -m pytest tests/test_color.py
python -m pytest -k cvd

# REQUIRED: Quality checks (run before commit)
ruff format .              # Auto-format code
ruff check --fix .         # Auto-fix linting issues
basedpyright qualpal       # Type check (manual fixes needed)

# Verify all checks pass (for CI/PR)
ruff format --check .      # Verify formatting
ruff check .               # Verify no lint errors
basedpyright qualpal       # Verify no type errors
python -m pytest           # Verify all tests pass

# Build documentation
cd docs && make html       # Output: docs/build/html/index.html

# Clean build artifacts
rm -rf build/

# Task runner (optional)
task install   # Install with dev dependencies
task test      # Run tests
task docs      # Build docs
```

## Package Status & Metrics

**Current Version:** 0.1.0 (ready for 1.0.0)

**Quality Metrics:**
- ✅ 305 tests passing
- ✅ 96% test coverage (exceeds 90% target)
- ✅ All quality checks passing (ruff, basedpyright)
- ✅ Full CI/CD pipeline operational
- ✅ Cross-platform support (Linux, macOS, Windows)
- ✅ Multi-Python version (3.10, 3.13)
- ✅ Complete documentation (tutorial + API)

**Feature Completeness:**
- ✅ Color operations (creation, conversion, distance)
- ✅ CVD simulation (protan, deutan, tritan)
- ✅ Palette generation (customizable constraints)
- ✅ CVD-aware palette generation
- ✅ Palette analysis (min distance, distance matrix)
- ✅ Export formats (CSS, JSON)
- ✅ Matplotlib visualization
- ✅ Jupyter rich display

**Release Status:**
- Infrastructure ready for v1.0.0
- Awaiting version bump and CHANGELOG update
- PyPI publication automated via release workflow

## Trust These Instructions

These instructions have been validated by:

- Complete implementation of all planned features
- 305 passing tests with 96% coverage
- Successful CI runs on 3 platforms, 2 Python versions
- Full documentation suite with tutorial
- Production-ready code quality

**Only search for additional information if:**

- You need details on the C++ library internals (see https://github.com/jolars/qualpal)
- You encounter an error not documented here
- You're adding entirely new features beyond current scope

## Questions or Issues?

- Check **docs/source/tutorial.md** for usage examples
- Check **docs/source/api.md** for API reference
- Check CI logs in `.github/workflows/` for build issues
- Check **CHANGELOG.md** for version history
- The maintainer uses `devenv` (Nix) for development environment
