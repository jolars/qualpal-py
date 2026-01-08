"""Qualpal: Automatic generation of qualitative color palettes."""

from __future__ import annotations

from .color import Color
from .palette import Palette
from .qualpal import Qualpal
from .utils import list_palettes

__all__ = ["Color", "Palette", "Qualpal", "list_palettes"]

__version__ = "0.1.0"
