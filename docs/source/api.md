# API Documentation

```{eval-rst}
.. currentmodule:: qualpal
```

## Status

🚧 **Under Active Development** - The API is being implemented according to [API_DESIGN.md](https://github.com/jolars/qualpal-py/blob/main/API_DESIGN.md).

### Implemented

- ✅ **Color class** - Pure Python implementation (Phase 1.1 complete)

### Coming Soon

- 🚧 Color space conversions (Phase 1.2)
- 🚧 Palette class (Phase 1.3)
- 🚧 Qualpal class (Phase 2)
- 🚧 Palette generation (Phase 2)
- 🚧 Analysis and distance metrics (Phase 3)

## Classes

### Color

```{eval-rst}
.. currentmodule::  qualpal

.. autosummary::
   :toctree: generated
   :template: class.rst

    Color
```

The `Color` class provides a simple interface for working with colors.

**Example:**

```python
from qualpal import Color

# Create from hex
color = Color("#ff0000")
print(color.hex())     # "#ff0000"
print(color.rgb())     # (1.0, 0.0, 0.0)
print(color.rgb255())  # (255, 0, 0)

# Create from RGB
green = Color.from_rgb(0.0, 1.0, 0.0)

# Equality
assert Color("#ff0000") == Color("#ff0000")
assert Color("#ff0000") == "#ff0000"
```

## Architecture

This package uses a **Python-first architecture**:

- **Python layer**: API, data structures (Color, Palette, Qualpal classes), validation
- **C++ layer**: Performance-critical algorithms (palette generation, distance calculations)

This means you can test and use Color/Palette classes without building C++ code.

