# Qualpal <picture><source media="(prefers-color-scheme: light)" srcset="https://raw.githubusercontent.com/jolars/qualpal/refs/heads/main/docs/images/logo.svg" align="right" width="139"> <img alt="The logo for Qualpal, which is a painting palette with five distinct colors." src="https://raw.githubusercontent.com/jolars/qualpal/refs/heads/main/docs/images/logo-dark.svg" align="right" width="139"> </picture>

[![Tests](https://github.com/jolars/qualpal-py/actions/workflows/test.yml/badge.svg)](https://github.com/jolars/qualpal-py/actions/workflows/test.yml)
[![codecov](https://codecov.io/github/jolars/qualpal-py/graph/badge.svg?token=VBIeMY0zJt)](https://codecov.io/github/jolars/qualpal-py)
[![DOI](https://joss.theoj.org/papers/10.21105/joss.08936/status.svg)](https://doi.org/10.21105/joss.08936)
[![App](https://img.shields.io/badge/🌐%20%20App-qualpal.cc-blue)](https://qualpal.cc)

Automatically generate qualitative color palettes with distinct colors.

## Installation

Qualpal will soon be available on PyPI. In the meantime, you can install it directly from source,
but note that this requires a C++ compiler.

```bash
pip install git+https://github.com/jolars/sortedl1
```

## Quick Start

```python
from qualpal import Color

# Create and work with colors
color = Color("#ff0000")
print(color.hex())  # "#ff0000"
print(color.rgb())  # (1.0, 0.0, 0.0)
print(color.rgb255())  # (255, 0, 0)

# Create from RGB
green = Color.from_rgb(0.0, 1.0, 0.0)
```

## Documentation

The full documentation is available at <https://jolars.github.io/qualpal-py/>.

## Contributing

Contributions are welcome!

Note that the main functionality comes from the underlying C++ library,
which is developed and maintained at <https://github.com/jolars/qualpal>.
So if you want to contribute to the core algorithms, please do so there.

## License

Qualpal is licensed under the [MIT license](LICENSE)

## References
