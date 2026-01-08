# API Documentation

```{eval-rst}
.. currentmodule:: qualpal
```

## Status

🚧 **Under Active Development** - The API is being implemented according to
[API_DESIGN.md](https://github.com/jolars/qualpal-py/blob/main/API_DESIGN.md).
See [ROADMAP.md](https://github.com/jolars/qualpal-py/blob/main/ROADMAP.md) for
progress.

## Classes

### Color

```{eval-rst}
.. currentmodule::  qualpal

.. autosummary::
   :toctree: generated
   :template: class.rst

    Color
    Palette
```

The `Color` class provides a simple interface for working with colors.

**Example:**

```python
from qualpal import Color

# Create from hex
color = Color("#ff0000")
print(color.hex())  # "#ff0000"
print(color.rgb())  # (1.0, 0.0, 0.0)
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
- **C++ layer**: Algorithms, color conversions, performance-critical code.
