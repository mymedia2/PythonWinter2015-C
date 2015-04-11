#include <stdio.h>
#include <Python.h>

int main(int argc, char* argv[]) {
	enum { global_dict, local_dict, list, slice, repeated, string, _end };
	PyObject* obj[_end] = { };
	int code = 0;
	size_t i;

	if (argc != 5) {
		fprintf(stderr, "Invalid arguments\nusage: %s <code> <start> <stop> <repeat>\n", argv[0]);
		return 127;
	}
	Py_InitializeEx(1);

	obj[global_dict] = Py_BuildValue("{}");
	obj[local_dict] = Py_BuildValue("{}");
	obj[list] = PyRun_String(argv[1], Py_eval_input, obj[global_dict], obj[local_dict]);

	obj[slice] = PySequence_GetSlice(obj[list], atoi(argv[2]), atoi(argv[3]));
	obj[repeated] = PySequence_Repeat(obj[slice], atoi(argv[4]));

	obj[string] = PyObject_Repr(obj[repeated]);
	if (obj[repeated]) {
		printf("%s\n", PyString_AsString(obj[string]));
	} else {
		PyErr_Print();
		code = 126;
	}

	for (i = 0; i < _end; i++)
		if (obj[i]) Py_DECREF(obj[i]);
	Py_Finalize();
	return code;
}
