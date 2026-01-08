# Implementation Roadmap for qualpal-py

**Created:** 2026-01-07  
**Updated:** 2026-01-07  
**Based on:** API_DESIGN.md  
**Architecture:** Python-first approach

---

## Overview

Incremental development plan for qualpal Python bindings. Classes
and methods will be implemented in phases, focusing on core functionality first, then adding features.

- Python handles API, data structures, validation. Python is mostly
  a thin layer unless it is trivial to implement in Python.
- C++ handles algorithms, color conversions, and so on.

Each phase builds on the previous, allowing testing and validation at every step.

---

## Phase 1: Core Foundation (Week 1)

**Goal:** Basic Python classes

### 1.1 Color Class (Days 1-2) ✅ COMPLETE

- [x] Pure Python `Color` class
- [x] Constructor from hex string
- [x] `hex()`, `rgb()`, `rgb255()` methods
- [x] `from_rgb()` class method
- [x] `__str__` and `__repr__` implementations
- [x] Equality operators (`==`, `!=`)
- [x] Hash support
- [x] Validation
- [x] Basic tests

**Deliverable:** `Color('#ff0000')` works

### 1.2 Color Conversions (Day 3)

- [x] Add color space conversion methods (pure Python)
- [x] `hsl()`, `hsv()`, `lab()`, `lch()`, `xyz()`
- [x] `from_hsl()` class method
- [x] Tests for round-trip conversions

### 1.3 Palette Class - Basic (Days 4-5)

- [x] Pure Python `Palette` class
- [x] `__len__`, `__getitem__`, `__iter__`, `__contains__`
- [x] Slicing support (returns new Palette)
- [x] `hex()` method
- [x] `rgb()` method with `as_array` parameter
- [x] `__str__` and `__repr__`
- [x] Basic tests

**Deliverable:** `Palette` object works like a Python list

---

## Phase 2: Core Generation (Week 2)

**Goal:** Qualpal class and C++ generation algorithm integration

### 2.1 Qualpal Class - Initialization (Days 1-2)

- [x] Pure Python `Qualpal` class
- [x] `__init__` with mutual exclusivity validation
- [x] Property setters with validation:
  - [x] `cvd`
  - [x] `metric`
  - [x] `background`
  - [x] `max_memory`
  - [x] `colorspace_size`
- [x] Colorspace parameter validation
- [x] Tests for all validation paths

**Deliverable:** `Qualpal()` initialization with all parameters

### 2.2 C++ Algorithm Binding (Day 3)

- [x] Test C++ `generate_palette_cpp()` binding
- [x] Add error handling for C++ exceptions
- [x] Test basic generation from Python

**Deliverable:** C++ algorithm callable from Python

### 2.3 Integration (Days 4-5) ✅ COMPLETE

- [x] Implement `Qualpal.generate(n)` method calling C++
- [x] Support colorspace-only mode first
- [x] Return `Palette` object with `Color` objects
- [x] Error handling (RuntimeError on failure)
- [x] Integration tests

**Deliverable:** `qp.generate(6)` returns valid `Palette` with `Color` objects

### 2.4 Additional Input Modes (Days 6-7) ✅ COMPLETE

- [x] Support `colors` input mode in `generate()`
- [x] Bind C++ `setInputHex()` and call from Python
- [x] Support `palette` input mode in `generate()`
- [x] Bind C++ `setInputPalette()` and call from Python
- [x] Add tests for colors and palette modes
- [x] Update integration tests

**Deliverable:** All three input modes (colorspace, colors, palette) working

---

## Phase 3: Analysis & Distance (Week 3)

**Goal:** Color distance and palette analysis (using C++ for computation)

### 3.1 Color Distance (Days 1-2) ✅ COMPLETE

- [x] Bind color difference metrics from C++
- [x] Add C++ function `color_difference_cpp(hex1, hex2, metric)`
- [x] `Color.distance(other, metric)` method (calls C++)
- [x] Support CIEDE2000, DIN99d, CIE76
- [x] Tests for all metrics

### 3.2 Palette Analysis (Days 3-4) ✅ COMPLETE

- [x] Bind C++ distance matrix computation
- [x] `Palette.min_distance(metric)` (calls C++)
- [x] `Palette.distance_matrix(metric)` (calls C++)
- [x] `Palette.min_distances(metric)` (calls C++)
- [x] Comprehensive tests

**Deliverable:** Full analysis API working

---

## Phase 4: CVD & Advanced Features (Week 4)

**Goal:** Color vision deficiency simulation

### 4.1 CVD Simulation (Days 1-3) ✅ COMPLETE

- [x] Bind CVD simulation from C++
- [x] `Color.simulate_cvd(type, severity)` method
- [x] Support for protan, deutan, tritan
- [x] Tests with different CVD types

**Note:** CVD is already integrated into palette generation via the `cvd` parameter in Qualpal (Phase 2.1)

### 4.2 Named Palettes (Days 4-5) ✅ COMPLETE

- [x] Support `palette` parameter in Qualpal (completed in Phase 2.4)
- [x] `list_palettes()` function
- [x] Tests for listing palettes

**Deliverable:** Named palette support complete

---

## Phase 5: Export & Visualization (Week 5)

**Goal:** Output formats and display

### 5.1 Export Formats (Days 1-3) ✅ COMPLETE

- [x] `Palette.to_css(prefix)`
- [x] `Palette.to_json()`
- [x] Tests for all formats

**Deliverable:** Export formats working

### 5.2 Matplotlib Integration (Days 4-5) ✅ COMPLETE

- [x] `Palette.show(labels)` with matplotlib
- [x] Return Figure object
- [x] Graceful handling when matplotlib not installed
- [x] Figure can be saved via `.savefig()`
- [x] Tests (19 tests including visual functionality)

**Deliverable:** Full export and visualization support

---

## Phase 6: Polish & Documentation (Week 6)

### 6.1 Rich Display (Days 1-2)

- [ ] Jupyter/IPython `_repr_html_()` for Color
- [ ] Jupyter/IPython `_repr_html_()` for Palette
- [ ] Test in actual Jupyter notebook

### 6.2 Documentation (Days 3-4)

- [ ] Docstrings for all public APIs
- [ ] Type hints complete
- [ ] Usage examples in docstrings
- [ ] Update README with examples

### 6.3 Testing & CI (Day 5)

- [ ] Test coverage > 90%
- [ ] CI pipeline running
- [ ] Test on multiple Python versions (3.9+)
- [ ] Performance benchmarks

**Deliverable:** Production-ready package

---

## Phase 7: Package & Release (Week 7)

### 7.1 Packaging (Days 1-3)

- [ ] Build system configuration
- [ ] Wheel building with scikit-build-core
- [ ] Test installation from wheel
- [ ] Cross-platform testing (Linux, macOS, Windows)

### 7.2 Release Preparation (Days 4-5)

- [ ] CHANGELOG complete
- [ ] Version 1.0.0 tag
- [ ] PyPI publication
- [ ] Documentation site (if needed)

**Deliverable:** v1.0.0 published on PyPI

---

## Testing Strategy

1. Unit tests for new functionality
2. Integration tests where applicable
3. Error handling tests
4. Type checking with mypy
5. Manual smoke testing

**Test categories:**

- Unit tests: Fast, isolated
- Integration tests: Multi-component
- Visual tests: Manual review (plots, colors)
- Performance tests: Benchmarks for large palettes

---

## Dependencies to Install

**Phase 1:**

- pybind11
- pytest

**Phase 6:**

- matplotlib (optional dependency)

**Phase 7:**

- mypy, sphinx (docs)

---

## Risk Management

**Risk:** C++ generation algorithm not exposed properly

- **Mitigation:** Start with simple colorspace generation in Phase 2

**Risk:** pybind11 exception handling issues

- **Mitigation:** Test exception paths early in Phase 1

**Risk:** NumPy array ownership issues

- **Mitigation:** Use proper buffer protocol in Phase 1

**Risk:** Matplotlib optional dependency issues

- **Mitigation:** Try/except imports, clear error messages

---

## Success Criteria

**Phase completion checklist:**

- [ ] All tests passing
- [ ] Code reviewed
- [ ] Documentation updated
- [ ] No known bugs in phase scope
- [ ] Manual testing complete

**v1.0.0 release criteria:**

- [ ] All API_DESIGN.md features implemented (except future enhancements)
- [ ] Test coverage ≥ 90%
- [ ] Documentation complete
- [ ] Works on Linux, macOS, Windows
- [ ] Python 3.9+ support
- [ ] No critical or high-priority bugs

---

## Notes

- Each phase should take ~5 working days
- Phases can overlap if team size allows
- Adjust timeline based on C++ codebase complexity
- Phase 1-3 are **critical path** - must be solid
- Phases 4-6 can be reordered based on priorities
- Future enhancements (named colors, config overrides) are **post-1.0**

---

End of roadmap.
