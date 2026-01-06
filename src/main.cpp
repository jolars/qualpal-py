#include <pybind11/pybind11.h>

int
my_function(int i, int j)
{
  return i + j;
}

namespace py = pybind11;

PYBIND11_MODULE(_qualpal,
                m,
                py::mod_gil_not_used(),
                py::multiple_interpreters::per_interpreter_gil())
{
  m.def("_my_function", &my_function);
}
