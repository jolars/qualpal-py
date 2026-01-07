"""Quick type checking validation."""

from __future__ import annotations

from qualpal import Color

# Test type annotations work
color: Color = Color("#ff0000")
hex_value: str = color.hex()
rgb_tuple: tuple[float, float, float] = color.rgb()
rgb255_tuple: tuple[int, int, int] = color.rgb255()

# Test classmethod
green: Color = Color.from_rgb(0.0, 1.0, 0.0)

# Test equality
is_equal: bool = color == green
is_string_equal: bool = color == "#ff0000"
