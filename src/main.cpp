#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <qualpal.h>

#include "color_conversions.h"

namespace py = pybind11;

// Generate palette using C++ algorithm
std::vector<std::string>
generate_palette_cpp(int n,
                     const std::vector<double>& h_range,
                     const std::vector<double>& c_range,
                     const std::vector<double>& l_range)
{
  qualpal::Qualpal qp;

  qp.setInputColorspace({ h_range[0], h_range[1] },
                        { c_range[0], c_range[1] },
                        { l_range[0], l_range[1] });

  std::vector<qualpal::colors::RGB> pal = qp.generate(n);

  std::vector<std::string> hex_colors;
  for (const auto& color : pal) {
    hex_colors.push_back(color.hex());
  }

  return hex_colors;
}

// ============================================================================
// Module definition
// ============================================================================

PYBIND11_MODULE(_qualpal,
                m,
                py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil())
{
  m.doc() = "qualpal C++ core algorithms";

  m.def("generate_palette_cpp",
        &generate_palette_cpp,
        py::arg("n"),
        py::arg("h_range"),
        py::arg("c_range"),
        py::arg("l_range"),
        "Generate palette using C++ algorithm");

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
