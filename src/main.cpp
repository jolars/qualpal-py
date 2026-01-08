#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <qualpal.h>

#include "color_conversions.h"

namespace py = pybind11;

// Helper function to convert RGB palette to hex strings
std::vector<std::string>
rgb_palette_to_hex(const std::vector<qualpal::colors::RGB>& pal)
{
  std::vector<std::string> hex_colors;
  hex_colors.reserve(pal.size());
  for (const auto& color : pal) {
    hex_colors.push_back(color.hex());
  }
  return hex_colors;
}

// Helper function to apply optional configuration to Qualpal object
void
apply_optional_config(qualpal::Qualpal& qp,
                      const std::optional<std::map<std::string, double>>& cvd,
                      const std::optional<std::string>& background,
                      const std::optional<std::string>& metric,
                      const std::optional<double>& max_memory)
{
  if (cvd.has_value()) {
    qp.setCvd(cvd.value());
  }
  if (background.has_value()) {
    qp.setBackground(qualpal::colors::RGB(background.value()));
  }
  if (metric.has_value()) {
    // Map string to MetricType enum
    const auto& m = metric.value();
    if (m == "ciede2000") {
      qp.setMetric(qualpal::metrics::MetricType::CIEDE2000);
    } else if (m == "din99d") {
      qp.setMetric(qualpal::metrics::MetricType::DIN99d);
    } else if (m == "cie76") {
      qp.setMetric(qualpal::metrics::MetricType::CIE76);
    }
  }
  if (max_memory.has_value()) {
    qp.setMemoryLimit(max_memory.value());
  }
}

// Unified palette generation function
std::vector<std::string>
generate_palette_unified_cpp(
  int n,
  const std::optional<std::vector<double>>& h_range,
  const std::optional<std::vector<double>>& c_range,
  const std::optional<std::vector<double>>& l_range,
  const std::optional<std::vector<std::string>>& colors,
  const std::optional<std::string>& palette_name,
  const std::optional<std::map<std::string, double>>& cvd,
  const std::optional<std::string>& background,
  const std::optional<std::string>& metric,
  const std::optional<double>& max_memory)
{
  qualpal::Qualpal qp;

  // Set input source (exactly one must be provided)
  if (h_range.has_value() && c_range.has_value() && l_range.has_value()) {
    qp.setInputColorspace({ h_range.value()[0], h_range.value()[1] },
                          { c_range.value()[0], c_range.value()[1] },
                          { l_range.value()[0], l_range.value()[1] });
  } else if (colors.has_value()) {
    qp.setInputHex(colors.value());
  } else if (palette_name.has_value()) {
    qp.setInputPalette(palette_name.value());
  }

  // Apply optional configuration
  apply_optional_config(qp, cvd, background, metric, max_memory);

  // Generate and return
  return rgb_palette_to_hex(qp.generate(n));
}

// Simpler wrapper functions for backwards compatibility and convenience
std::vector<std::string>
generate_palette_cpp(int n,
                     const std::vector<double>& h_range,
                     const std::vector<double>& c_range,
                     const std::vector<double>& l_range)
{
  return generate_palette_unified_cpp(n,
                                      h_range,
                                      c_range,
                                      l_range,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt);
}

std::vector<std::string>
generate_palette_from_colors_cpp(int n, const std::vector<std::string>& colors)
{
  return generate_palette_unified_cpp(n,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      colors,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt);
}

std::vector<std::string>
generate_palette_from_palette_cpp(int n, const std::string& palette_name)
{
  return generate_palette_unified_cpp(n,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      palette_name,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt,
                                      std::nullopt);
}

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
