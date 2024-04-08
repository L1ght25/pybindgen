#include <pybind11/pybind11.h>

#include "test.h"


namespace py = pybind11;

PYBIND11_MODULE(example, m) {

	py::class_<A>(m, "A")
		.def_readwrite("third", &A::third)
		.def("pubbar", &A::pubbar);

	m.def("foo", &foo);
}
