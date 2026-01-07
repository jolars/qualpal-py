"""Color class."""

from __future__ import annotations

import re
from typing import TYPE_CHECKING

if TYPE_CHECKING:
    from typing_extensions import Self


class Color:
    """A color with various representations and conversions.

    Color objects are immutable.
    """

    def __init__(self, hex_color: str) -> None:
        """Create a Color from a hex string.

        Parameters
        ----------
        hex_color : str
            Hex color string in format #RRGGBB

        Raises
        ------
        ValueError
            If hex_color is not a valid hex color string
        """
        # Validate format
        if not re.match(r"^#[0-9a-fA-F]{6}$", hex_color):
            msg = f"Invalid hex color format: {hex_color}"
            raise ValueError(msg)

        self._hex = hex_color.lower()

        # Parse RGB values (0-1 range)
        r_int = int(self._hex[1:3], 16)
        g_int = int(self._hex[3:5], 16)
        b_int = int(self._hex[5:7], 16)

        self._r = r_int / 255.0
        self._g = g_int / 255.0
        self._b = b_int / 255.0

    @classmethod
    def from_rgb(cls, r: float, g: float, b: float) -> Self:
        """Create a Color from RGB values.

        Parameters
        ----------
        r, g, b : float
            RGB values in range [0.0, 1.0]

        Returns
        -------
        Color
            New Color object
        """
        # Validate range
        if not (0.0 <= r <= 1.0 and 0.0 <= g <= 1.0 and 0.0 <= b <= 1.0):
            msg = "RGB values must be in range [0.0, 1.0]"
            raise ValueError(msg)

        # Convert to hex
        r_int = round(r * 255)
        g_int = round(g * 255)
        b_int = round(b * 255)

        hex_str = f"#{r_int:02x}{g_int:02x}{b_int:02x}"

        return cls(hex_str)

    def hex(self) -> str:
        """Get hex representation.

        Returns
        -------
        str
            Hex color string in format #rrggbb (lowercase)
        """
        return self._hex

    def rgb(self) -> tuple[float, float, float]:
        """Get RGB tuple in range [0.0, 1.0].

        Returns
        -------
        tuple[float, float, float]
            RGB values as (r, g, b)
        """
        return (self._r, self._g, self._b)

    def rgb255(self) -> tuple[int, int, int]:
        """Get RGB tuple in range [0, 255].

        Returns
        -------
        tuple[int, int, int]
            RGB values as (r, g, b) integers
        """
        return (
            round(self._r * 255),
            round(self._g * 255),
            round(self._b * 255),
        )

    def __str__(self) -> str:
        """String representation (hex color)."""
        return self._hex

    def __repr__(self) -> str:
        """Developer representation."""
        return f"Color('{self._hex}')"

    def __eq__(self, other: object) -> bool:
        """Check equality with another Color or hex string."""
        if isinstance(other, Color):
            return self._hex == other._hex

        if isinstance(other, str):
            # Normalize and compare
            try:
                other_color = Color(other)
                return self._hex == other_color._hex
            except ValueError:
                return False

        return NotImplemented

    def __ne__(self, other: object) -> bool:
        """Check inequality."""
        result = self.__eq__(other)

        if result is NotImplemented:
            return result

        return not result

    def __hash__(self) -> int:
        """Hash based on hex value (for use in sets/dicts)."""
        return hash(self._hex)
