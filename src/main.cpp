#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <qualpal.h>

int
my_function(int i, int j)
{
  return i + j;
}

std::vector<std::string>
make_palette()
{
  qualpal::Qualpal qp;

  qp.setInputColorspace({ -170, 60 }, { 0, 0.7 }, { 0.2, 0.8 });
  std::vector<qualpal::colors::RGB> pal = qp.generate(5);

  std::vector<std::string> hex_colors;
  for (const auto& color : pal) {
    hex_colors.push_back(color.hex());
  }

  return hex_colors;
}

namespace py = pybind11;

PYBIND11_MODULE(_qualpal,
                m,
                py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil())
{
  m.def("_my_function", &my_function);
  m.def("_make_palette", &make_palette);
}
