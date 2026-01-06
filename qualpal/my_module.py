"""My module for Qualpal package."""

from __future__ import annotations

from _qualpal import _make_palette, _my_function


class MyClass:
    """A sample class in my module."""

    def __init__(self, value: int):
        """Initialize MyClass with a value."""
        self.value: int = value

    def get_value(self):
        """Return the stored value."""
        return self.value


def my_function(a: int, b: int) -> int:
    """Return the sum of two integers."""
    return _my_function(a, b)


def generate_palette() -> list[str]:
    """Return a list of hex color strings."""
    return _make_palette()
