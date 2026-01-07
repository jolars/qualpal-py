# Qualpal

```{toctree}
:maxdepth: 2
:hidden:
:caption: Contents

Home<self>
api
changelog
```

## Automatically Generate Qualitative Color Palettes

🚧 **Under Active Development** - Python bindings are being implemented.

Qualpal automatically generates qualitative color palettes with distinct, perceptually uniform colors. It's perfect for:

- Data visualization
- Categorical plots
- Accessible color schemes
- Color vision deficiency (CVD) safe palettes

## Quick Start

```python
from qualpal import Color

# Create and work with colors
color = Color("#ff0000")
print(color.hex())     # "#ff0000"
print(color.rgb())     # (1.0, 0.0, 0.0)
print(color.rgb255())  # (255, 0, 0)

# Coming soon: Palette generation
# from qualpal import Qualpal
# qp = Qualpal(colorspace={'h': (0, 360), 's': (0.5, 1), 'l': (0.3, 0.7)})
# palette = qp.generate(6)
```

## Installation

**Requirements:**
- Python 3.9+
- C++ compiler (for building the extension)
- CMake 3.15+

```bash
# Install from source
git clone https://github.com/jolars/qualpal-py.git
cd qualpal-py
uv pip install -e .
```

## Development Status

See [ROADMAP.md](https://github.com/jolars/qualpal-py/blob/main/ROADMAP.md) for current implementation status.

**Completed:**
- ✅ Phase 1.1: Color class (pure Python)

**In Progress:**
- 🚧 Phase 1.2: Color space conversions
- 🚧 Phase 1.3: Palette class
- 🚧 Phase 2: Core generation algorithm

## Architecture

This package uses a **Python-first architecture**:
- **Python layer**: API, data structures, validation
- **C++ layer**: Performance-critical algorithms only

## References

Based on the qualpal C++ library: https://github.com/jolars/qualpal

