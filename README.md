# Qualpal <picture><source media="(prefers-color-scheme: light)" srcset="https://raw.githubusercontent.com/jolars/qualpal/refs/heads/main/docs/images/logo.svg" align="right" width="139"> <img alt="The logo for Qualpal, which is a painting palette with five distinct colors." src="https://raw.githubusercontent.com/jolars/qualpal/refs/heads/main/docs/images/logo-dark.svg" align="right" width="139"> </picture>

[![Tests](https://github.com/jolars/qualpal-py/actions/workflows/test.yml/badge.svg)](https://github.com/jolars/qualpal-py/actions/workflows/test.yml)
[![codecov](https://codecov.io/github/jolars/qualpal-py/graph/badge.svg?token=VBIeMY0zJt)](https://codecov.io/github/jolars/qualpal-py)
[![DOI](https://joss.theoj.org/papers/10.21105/joss.08936/status.svg)](https://doi.org/10.21105/joss.08936)
[![App](https://img.shields.io/badge/🌐%20%20App-qualpal.cc-blue)](https://qualpal.cc)

Automatically generate qualitative color palettes with distinct colors.

## Status

🚧 **Under Active Development** - See [ROADMAP.md](ROADMAP.md) for progress.

## Installation

**Requirements:** Python 3.9+, C++ compiler, CMake 3.15+

```bash
git clone https://github.com/jolars/qualpal-py.git
cd qualpal-py
uv pip install -e .
```

## Quick Start

```python
from qualpal import Color

# Create and work with colors
color = Color("#ff0000")
print(color.hex())     # "#ff0000"
print(color.rgb())     # (1.0, 0.0, 0.0)
print(color.rgb255())  # (255, 0, 0)

# Create from RGB
green = Color.from_rgb(0.0, 1.0, 0.0)

# Coming soon: Palette generation
# from qualpal import Qualpal
# qp = Qualpal(colorspace={'h': (0, 360), 's': (0.5, 1), 'l': (0.3, 0.7)})
# palette = qp.generate(6)
```

## Documentation

- [API Design](API_DESIGN.md) - Target API specification
- [Roadmap](ROADMAP.md) - Implementation plan and progress
- [Docs](https://jolars.github.io/qualpal-py/) - Full documentation

## Architecture

**Python-first approach:**
- Python: API, data structures (Color, Palette, Qualpal), validation
- C++: Performance-critical algorithms (palette generation, distances)

## Contributing

Contributions welcome! See [ROADMAP.md](ROADMAP.md) for current status.

## License

MIT License - see [LICENSE](LICENSE)

## References

Based on qualpal C++ library: https://github.com/jolars/qualpal


