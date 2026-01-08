"""Palette class."""

from __future__ import annotations

from typing import TYPE_CHECKING, overload

from qualpal.color import Color

if TYPE_CHECKING:
    from collections.abc import Iterator, Sequence


class Palette:
    """A collection of colors that behaves like a list.

    Palette objects are immutable.
    """

    def __init__(self, colors: Sequence[Color | str]) -> None:
        """Create a Palette from a list of colors.

        Parameters
        ----------
        colors : Sequence[Color | str]
            Sequence of Color objects or hex strings

        Raises
        ------
        ValueError
            If any color is invalid
        """
        self._colors: list[Color] = []
        for c in colors:
            if isinstance(c, Color):
                self._colors.append(c)
            elif isinstance(c, str):
                self._colors.append(Color(c))
            else:
                msg = f"Invalid color type: {type(c)}"
                raise TypeError(msg)

    def __len__(self) -> int:
        """Return the number of colors in the palette."""
        return len(self._colors)

    @overload
    def __getitem__(self, index: int) -> Color: ...

    @overload
    def __getitem__(self, index: slice) -> Palette: ...

    def __getitem__(self, index: int | slice) -> Color | Palette:
        """Get color(s) by index or slice.

        Parameters
        ----------
        index : int | slice
            Index or slice object

        Returns
        -------
        Color | Palette
            Single Color if index is int, new Palette if index is slice
        """
        if isinstance(index, slice):
            return Palette(self._colors[index])
        return self._colors[index]

    def __iter__(self) -> Iterator[Color]:
        """Iterate over colors in the palette."""
        return iter(self._colors)

    def __contains__(self, item: object) -> bool:
        """Check if a color is in the palette.

        Parameters
        ----------
        item : object
            Color object or hex string to check

        Returns
        -------
        bool
            True if color is in palette, False otherwise
        """
        if isinstance(item, Color):
            return item in self._colors
        if isinstance(item, str):
            try:
                color = Color(item)
                return color in self._colors
            except ValueError:
                return False
        return False

    def hex(self) -> list[str]:
        """Get list of hex color strings.

        Returns
        -------
        list[str]
            List of hex strings in format #rrggbb (lowercase)
        """
        return [c.hex() for c in self._colors]

    def rgb(self) -> list[tuple[float, float, float]]:
        """Get RGB values as list of tuples.

        Returns
        -------
        list[tuple[float, float, float]]
            List of RGB tuples in range [0.0, 1.0]
        """
        return [c.rgb() for c in self._colors]

    def __str__(self) -> str:
        """String representation showing hex colors."""
        hex_list = ", ".join(f"'{c.hex()}'" for c in self._colors)
        return f"Palette([{hex_list}])"

    def __repr__(self) -> str:
        """Developer representation."""
        return self.__str__()

    def __eq__(self, other: object) -> bool:
        """Check equality with another Palette."""
        if not isinstance(other, Palette):
            return NotImplemented

        return self._colors == other._colors

    def __ne__(self, other: object) -> bool:
        """Check inequality."""
        result = self.__eq__(other)

        if result is NotImplemented:
            return result

        return not result
