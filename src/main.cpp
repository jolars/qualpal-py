#include "color_conversions.h"
#include "palette_generation.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(_qualpal,
                m,
                py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil())
{
  m.doc() = "qualpal C++ core algorithms";

  // Unified generation function with all options
  m.def("generate_palette_unified_cpp",
        &generate_palette_unified_cpp,
        py::arg("n"),
        py::arg("h_range") = py::none(),
        py::arg("c_range") = py::none(),
        py::arg("l_range") = py::none(),
        py::arg("colors") = py::none(),
        py::arg("palette_name") = py::none(),
        py::arg("cvd") = py::none(),
        py::arg("background") = py::none(),
        py::arg("metric") = py::none(),
        py::arg("max_memory") = py::none(),
        "Generate palette with full configuration options");

  // Convenience wrappers (backwards compatible)
  m.def("generate_palette_cpp",
        &generate_palette_cpp,
        py::arg("n"),
        py::arg("h_range"),
        py::arg("c_range"),
        py::arg("l_range"),
        "Generate palette using colorspace input");

  m.def("generate_palette_from_colors_cpp",
        &generate_palette_from_colors_cpp,
        py::arg("n"),
        py::arg("colors"),
        "Generate palette using hex colors as input");

  m.def("generate_palette_from_palette_cpp",
        &generate_palette_from_palette_cpp,
        py::arg("n"),
        py::arg("palette_name"),
        "Generate palette using named palette as input");

  // Color space conversions
  m.def("rgb_to_hsl",
        &rgb_to_hsl,
        py::arg("r"),
        py::arg("g"),
        py::arg("b"),
        "Convert RGB to HSL");

  m.def("hsl_to_rgb",
        &hsl_to_rgb,
        py::arg("h"),
        py::arg("s"),
        py::arg("l"),
        "Convert HSL to RGB");

  m.def("rgb_to_xyz",
        &rgb_to_xyz,
        py::arg("r"),
        py::arg("g"),
        py::arg("b"),
        "Convert RGB to XYZ");

  m.def("rgb_to_lab",
        &rgb_to_lab,
        py::arg("r"),
        py::arg("g"),
        py::arg("b"),
        "Convert RGB to Lab");

  m.def("rgb_to_lch",
        &rgb_to_lch,
        py::arg("r"),
        py::arg("g"),
        py::arg("b"),
        "Convert RGB to LCH");
}
