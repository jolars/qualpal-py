# Python API Design for qualpal

**Date:** 2026-01-07  
**Status:** ✅ Ready for implementation

---

## Core API

### Main Entry Point: `Qualpal` Class

```python
from qualpal import Qualpal

# Option 1: Explicit colors as starting point
qp = Qualpal(
    colors=["#ff0000", "#00ff00", "#0000ff"],  # hex strings
    background="#ffffff",  # optional
    cvd={"protan": 0.5, "deutan": 0.2},  # optional CVD simulation
    metric="ciede2000",  # 'ciede2000', 'din99d', 'cie76'
    max_memory=1.0,  # GB
    colorspace_size=1000,  # for colorspace sampling
)

# Option 2: Colorspace input (mutually exclusive with colors/palette)
qp = Qualpal(
    colorspace={"h": (0, 360), "s": (0.5, 1.0), "l": (0.3, 0.7)},
    space="hsl",  # 'hsl' (default) or 'lchab'
    background="#ffffff",
)

# Option 3: Named palette input (mutually exclusive with colors/colorspace)
qp = Qualpal(palette="ColorBrewer:Set1", cvd={"protan": 0.5})

# Option 4: No input - uses default full colorspace
qp = Qualpal()  # Equivalent to colorspace={'h': (0, 360), 's': (0, 1), 'l': (0, 1)}

# IMPORTANT: Only one of colors/colorspace/palette can be provided
# Mixing them raises ValueError

# Generate palette
palette = qp.generate(6)  # Returns Palette object
# Raises RuntimeError if generation fails

# Extend existing palette
palette_extended = qp.extend(
    existing=["#ff0000", "#00ff00"],  # fixed colors
    n=6,  # total size including existing
)  # Also raises RuntimeError on failure
```

### Properties (Mutable with Validation)

```python
# Modify configuration after creation
# All setters validate input immediately
qp.cvd = {"protan": 1.0}
qp.background = "#000000"
qp.metric = "din99d"
qp.max_memory = 2.0
qp.colorspace_size = 2000

# Access current config
print(qp.cvd)
print(qp.metric)

# Invalid values raise errors immediately
qp.cvd = {
    "invalid": 1.0
}  # ValueError: cvd keys must be in {'protan', 'deutan', 'tritan'}
qp.metric = (
    "unknown"  # ValueError: metric must be one of {'ciede2000', 'din99d', 'cie76'}
)
qp.cvd = {"protan": 1.5}  # ValueError: cvd['protan'] must be between 0.0 and 1.0
```

---

## `Palette` Class

Returned by `generate()` and `extend()`.

### List-like Behavior

```python
palette = qp.generate(6)

# Length
len(palette)  # 6

# Indexing - returns Color objects
color = palette[0]

# Slicing - returns new Palette object
sub_palette = palette[0:3]
type(sub_palette)  # <class 'qualpal.Palette'>

# Iteration
for color in palette:
    print(color)  # Prints hex by default

# Membership
"#ff0000" in palette
```

### Conversion Methods

```python
# Get as hex strings
palette.hex()  # ['#ff0000', '#00ff00', ...]

# Get as RGB array (numpy)
palette.rgb()  # np.array([[1.0, 0.0, 0.0], [0.0, 1.0, 0.0], ...])
# Shape: (n, 3), dtype: float64

# Get as list of tuples
palette.rgb(as_array=False)  # [(1.0, 0.0, 0.0), (0.0, 1.0, 0.0), ...]
```

### Export Methods

```python
# Export to CSS custom properties
palette.to_css()  # ['--color-1: #ff0000;', '--color-2: #00ff00;', ...]
palette.to_css(prefix="theme")  # ['--theme-1: #ff0000;', ...]

# Export to JSON
palette.to_json()  # '["#ff0000", "#00ff00", ...]'
```

### Analysis Methods

```python
# Minimum pairwise color distance
min_dist = palette.min_distance(metric="ciede2000")  # float

# Full distance matrix
matrix = palette.distance_matrix(metric="ciede2000")  # np.array, shape (n, n)

# Per-color minimum distances
min_distances = palette.min_distances(metric="ciede2000")  # np.array, shape (n,)
```

### Visualization

```python
# Display color swatches (requires matplotlib)
palette.show()

# With labels
palette.show(labels=True)  # Shows hex codes
palette.show(labels=["A", "B", "C", ...])  # Custom labels

# Returns matplotlib Figure object for saving
fig = palette.show()
fig.savefig("palette.png")
```

### Representation

```python
# String representation
print(palette)
# Palette(['#ff0000', '#00ff00', '#0000ff'])

# Rich repr (in Jupyter/IPython)
palette  # Shows colored HTML representation
```

---

## `Color` Class

Individual color object returned by `palette[i]`.

### Constructors

```python
from qualpal import Color

# From hex
color = Color("#ff0000")

# From RGB tuple/list
color = Color.from_rgb(1.0, 0.0, 0.0)
color = Color.from_rgb([1.0, 0.0, 0.0])

# From HSL
color = Color.from_hsl(0, 1.0, 0.5)
```

### Conversion Methods

```python
# To hex
color.hex()  # '#ff0000'
str(color)  # '#ff0000'

# To RGB
color.rgb()  # (1.0, 0.0, 0.0)

# To other color spaces
color.hsl()  # (0.0, 1.0, 0.5)
color.hsv()  # (0.0, 1.0, 1.0)
color.lab()  # (53.24, 80.09, 67.20)
color.lch()  # (53.24, 104.55, 40.0)
color.xyz()  # (0.41, 0.21, 0.02)

# As 8-bit RGB integers
color.rgb255()  # (255, 0, 0)
```

### Color Operations

```python
# Distance to another color
color1.distance(color2, metric="ciede2000")  # float

# CVD simulation
color_simulated = color.simulate_cvd("protan", severity=0.5)

# Equality comparison (based on hex value)
color1 = Color("#ff0000")
color2 = Color("#ff0000")
color1 == color2  # True
color1 == "#ff0000"  # True (can compare with hex strings)
color1 != Color("#00ff00")  # True
```

### Representation

```python
# String
print(color)  # '#ff0000'

# Repr
repr(color)  # "Color('#ff0000')"

# Rich display in Jupyter
color  # Shows colored swatch + hex code
```

---

## Utility Functions

### Standalone Convenience Function

```python
from qualpal import qualpal

# Quick palette generation
palette = qualpal(n=8, colors=["#ff0000", "#00ff00", "#0000ff"])

# Equivalent to:
# Qualpal(colors=[...]).generate(8)
```

### Palette Analysis

```python
from qualpal import analyze_palette

# Analyze existing palette
stats = analyze_palette(["#ff0000", "#00ff00", "#0000ff"], metric="ciede2000")

# Returns dict with:
# {
#   'min_distance': 88.23,
#   'mean_distance': 105.67,
#   'distance_matrix': np.array(...),
#   'colors': Palette(...)
# }
```

### List Available Palettes

```python
from qualpal import list_palettes

palettes = list_palettes()
# Returns dict:
# {
#   'ColorBrewer': ['Set1', 'Set2', 'Set3', ...],
#   'Package2': ['Palette1', ...]
# }
```

---

## Parameter Details

### `cvd` Parameter

Color vision deficiency simulation. Dict with keys:

- `'protan'`: Protanomaly/Protanopia (red-weak/blind)
- `'deutan'`: Deuteranomaly/Deuteranopia (green-weak/blind)
- `'tritan'`: Tritanomaly/Tritanopia (blue-weak/blind)

Values: 0.0 (normal) to 1.0 (complete deficiency)

```python
cvd = {"protan": 0.5}  # Moderate protanomaly
cvd = {"deutan": 1.0}  # Complete deuteranopia
cvd = {"protan": 0.5, "deutan": 0.2}  # Combined
```

### `metric` Parameter

Color difference metric (string):

- `'ciede2000'` (default): CIEDE2000 color difference
- `'din99d'`: DIN99d perceptual color difference
- `'cie76'`: CIE76 (Euclidean in Lab space)

### `colorspace` Parameter

Dict specifying cylindrical colorspace ranges. Must be used with `space` parameter.

**Mutually exclusive with `colors` and `palette` parameters.**

```python
# HSL space (default)
colorspace = {
    "h": (0, 360),  # Hue in degrees
    "s": (0.5, 1.0),  # Saturation [0, 1]
    "l": (0.3, 0.7),  # Lightness [0, 1]
}
space = "hsl"  # default

# LCHab space (perceptually uniform)
colorspace = {
    "h": (-180, 180),  # Hue in degrees
    "c": (20, 100),  # Chroma (>= 0)
    "l": (30, 70),  # Lightness [0, 100]
}
space = "lchab"
```

### `space` Parameter

Color space for `colorspace` parameter (string):

- `'hsl'` (default): HSL cylindrical color space
- `'lchab'`: LCH (Lightness, Chroma, Hue) in CIELAB space - perceptually uniform

Only used when `colorspace` is provided. Ignored otherwise.

### `colors` Parameter

List of hex color strings to use as starting point or constraints.

**Mutually exclusive with `colorspace` and `palette` parameters.**

```python
colors = ["#ff0000", "#00ff00", "#0000ff"]
```

### `palette` Parameter

Named palette reference string in format `'source:name'`.

**Mutually exclusive with `colors` and `colorspace` parameters.**

```python
palette = "ColorBrewer:Set1"
palette = "Tableau:10"
```

If palette name doesn't exist, raises `ValueError` (from C++ exception via pybind11). Use `list_palettes()` to see available palettes.

---

## Design Principles

1. **Pythonic**: Use properties, not setters. Natural iteration and indexing.
2. **Flexible**: Multiple input types (hex, RGB, colorspace, palettes)
3. **Rich objects**: `Palette` and `Color` classes with useful methods
4. **NumPy integration**: Return NumPy arrays for scientific workflows
5. **Optional visualization**: Matplotlib integration when available
6. **Type hints**: Full typing support for modern Python
7. **Stateful builder**: `Qualpal` object can be reused and modified

---

## Example Workflows

### Basic Usage

```python
from qualpal import Qualpal

qp = Qualpal(colors=["#ff0000", "#00ff00", "#0000ff"])
palette = qp.generate(6)

for color in palette:
    print(color.hex(), color.rgb())
```

### CVD-Safe Palette

```python
qp = Qualpal(
    colorspace={"h": (0, 360), "s": (0.5, 1), "l": (0.4, 0.7)},
    cvd={"protan": 1.0, "deutan": 1.0},  # Simulate both
    background="#ffffff",
)
palette = qp.generate(8)
palette.show()
```

### Extend Existing Palette

```python
existing = ["#ff0000", "#00ff00"]
qp = Qualpal(colorspace={"h": (0, 360), "s": (0.6, 1), "l": (0.3, 0.7)})
palette = qp.extend(existing=existing, n=8)  # 6 new + 2 existing

print(f"Extended from {len(existing)} to {len(palette)} colors")
```

### Analyze Palette Quality

```python
from qualpal import analyze_palette

stats = analyze_palette(
    ["#e41a1c", "#377eb8", "#4daf4a", "#984ea3"], metric="ciede2000"
)

print(f"Min distance: {stats['min_distance']:.2f}")
print(f"Mean distance: {stats['mean_distance']:.2f}")
```

### Scientific Workflow

```python
import matplotlib.pyplot as plt
import numpy as np

from qualpal import Qualpal

# Generate palette
qp = Qualpal(colorspace={"h": (0, 360), "s": (0.6, 1), "l": (0.5, 0.7)})
palette = qp.generate(5)

# Use with matplotlib
colors = palette.rgb()  # NumPy array (5, 3)

for i, color in enumerate(colors):
    x = np.random.randn(100)
    y = np.random.randn(100)
    plt.scatter(x, y, c=[color], label=f"Group {i}")

plt.legend()
plt.show()
```

---

## Implementation Notes

### Dependencies

- **Optional**: `matplotlib` (for visualization)
- **Binding**: Use `pybind11` for C++ bindings

### Type Hints

```python
from typing import Literal, Optional, Union

import numpy as np
import numpy.typing as npt

ColorInput = Union[str, tuple[float, float, float], list[float]]
MetricType = Literal["ciede2000", "din99d", "cie76"]
CVDType = Literal["protan", "deutan", "tritan"]
```

### Error Handling

- Raise `ValueError` for invalid inputs (bad hex, out-of-range values, parameter conflicts)
- Raise `TypeError` for wrong types
- Raise `RuntimeError` for generation failures (e.g., cannot find sufficient distinct colors)

**Generation failure examples:**

```python
# Impossible constraints
qp = Qualpal(colorspace={"h": (0, 1), "s": (0.99, 1), "l": (0.5, 0.51)})
palette = qp.generate(100)  # RuntimeError: colorspace too small

# Too many colors for constraints
qp = Qualpal(colors=["#ff0000", "#ff0001"])
palette = qp.extend(existing=["#ff0000", "#ff0001"], n=50)
# RuntimeError: cannot generate 50 sufficiently distinct colors
```

### Property Setters with Validation

All mutable properties on `Qualpal` use property setters with validation:

```python
class Qualpal:
    def __init__(
        self,
        colors=None,
        colorspace=None,
        palette=None,
        space="hsl",
        cvd=None,
        metric="ciede2000",
        background=None,
        max_memory=1.0,
        colorspace_size=1000,
    ):
        # Validate mutual exclusivity
        provided = sum(
            [colors is not None, colorspace is not None, palette is not None]
        )
        if provided > 1:
            raise ValueError("Provide only one of: colors, colorspace, or palette")

        # Set defaults if none provided
        if provided == 0:
            colorspace = {"h": (0, 360), "s": (0, 1), "l": (0, 1)}
            space = "hsl"

        # Validate palette exists
        if palette is not None:
            if ":" not in palette:
                raise ValueError("palette must be in format 'source:name'")
            # Check if palette exists (implementation detail)

        # Validate colorspace structure
        if colorspace is not None:
            if space == "hsl":
                required = {"h", "s", "l"}
            elif space == "lchab":
                required = {"h", "c", "l"}
            else:
                raise ValueError(f"space must be 'hsl' or 'lchab', got '{space}'")

            if not isinstance(colorspace, dict):
                raise TypeError("colorspace must be a dict")
            if set(colorspace.keys()) != required:
                raise ValueError(f"colorspace must have keys {required}")

            for key, (min_val, max_val) in colorspace.items():
                if not isinstance(min_val, (int, float)) or not isinstance(
                    max_val, (int, float)
                ):
                    raise TypeError(f"colorspace['{key}'] range must be numeric")
                if min_val >= max_val:
                    raise ValueError(f"colorspace['{key}'] min must be < max")

        # Store input mode
        self._colors = colors
        self._colorspace = colorspace
        self._palette = palette
        self._space = space

        # Initialize private attributes
        self._cvd = None
        self._metric = None
        self._background = None
        self._max_memory = None
        self._colorspace_size = None

        # Use setters for validation even in __init__
        self.cvd = cvd
        self.metric = metric
        self.background = background
        self.max_memory = max_memory
        self.colorspace_size = colorspace_size

    @property
    def cvd(self) -> Optional[dict[str, float]]:
        return self._cvd

    @cvd.setter
    def cvd(self, value: Optional[dict[str, float]]):
        if value is not None:
            valid_types = {"protan", "deutan", "tritan"}
            if not isinstance(value, dict):
                raise TypeError("cvd must be a dict")
            if not set(value.keys()).issubset(valid_types):
                raise ValueError(f"cvd keys must be in {valid_types}")
            for k, v in value.items():
                if not isinstance(v, (int, float)):
                    raise TypeError(f"cvd['{k}'] must be a number")
                if not 0.0 <= v <= 1.0:
                    raise ValueError(f"cvd['{k}'] must be between 0.0 and 1.0")
        self._cvd = value

    @property
    def metric(self) -> str:
        return self._metric

    @metric.setter
    def metric(self, value: str):
        valid = {"ciede2000", "din99d", "cie76"}
        if value not in valid:
            raise ValueError(f"metric must be one of {valid}")
        self._metric = value

    @property
    def background(self) -> Optional[str]:
        return self._background

    @background.setter
    def background(self, value: Optional[str]):
        if value is not None:
            # Validate hex color format
            if not isinstance(value, str):
                raise TypeError("background must be a hex string")
            if not re.match(r"^#[0-9a-fA-F]{6}$", value):
                raise ValueError(f"Invalid hex color: {value}")
        self._background = value

    @property
    def max_memory(self) -> float:
        return self._max_memory

    @max_memory.setter
    def max_memory(self, value: float):
        if not isinstance(value, (int, float)):
            raise TypeError("max_memory must be a number")
        if value <= 0:
            raise ValueError("max_memory must be positive")
        self._max_memory = float(value)

    @property
    def colorspace_size(self) -> int:
        return self._colorspace_size

    @colorspace_size.setter
    def colorspace_size(self, value: int):
        if not isinstance(value, int):
            raise TypeError("colorspace_size must be an integer")
        if value <= 0:
            raise ValueError("colorspace_size must be positive")
        self._colorspace_size = value
```

This pattern ensures:

- **Mutual exclusivity** enforced: only one input mode allowed
- **Invalid values** caught immediately at assignment
- **Validation logic** reused in `__init__` and property setters
- **Clear error messages** for users
- **Internal state** (`self._property`) is always valid
- **Default behavior**: No parameters = full colorspace sampling

### NumPy Array Format

All RGB arrays:

- Shape: `(n, 3)` where n is number of colors
- dtype: `float64`
- Range: `[0.0, 1.0]` for each channel

---

## Design Decisions

### Resolved

1. ✅ **`Color` objects are immutable** - Methods like `lighten()` return new Color instances
2. ✅ **`Palette` supports slicing** - Returns new Palette objects
3. ✅ **`Qualpal` configuration is mutable with validation** - Property setters validate immediately
4. ✅ **Color manipulation methods included** - `lighten()`, `darken()`, `with_saturation()`, `blend()`
5. ✅ **Export formats supported** - CSS, JSON, SVG/PNG output
6. ✅ **`palette.show()` returns Figure** - Enables saving and customization
7. ✅ **`generate()` failure behavior** - Raises `RuntimeError`, never returns `None`
8. ✅ **Color equality** - Supports `==` and `!=` comparison with other Colors and hex strings
9. ✅ **Input mode mutual exclusivity** - Only one of `colors`, `colorspace`, or `palette` allowed

### Future Enhancements

- Named color support: `Color('red')` or `Color.from_name('red')`
- Temporary config overrides: `qp.generate(6, cvd={'protan': 1.0})` without mutating `qp`

### Implementation Notes

- C++ exceptions from invalid palette names will be automatically converted to Python `ValueError` via pybind11
- All validation happens eagerly (at assignment/initialization) rather than lazily (at generation time)

---

End of specification.
