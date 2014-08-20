#include <Python.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    PyObject *pName, *pModule, *pFunc;
    PyObject *pArgs, *pValue;

    Py_Initialize();
    pName = PyString_FromString("plugin");      //file with script without py extension
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        pFunc = PyObject_GetAttrString(pModule, "add"); //method called from script
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc))
        {
            pArgs = PyTuple_New(2);
			pValue = PyInt_FromLong(2);
			PyTuple_SetItem(pArgs, 0, pValue);
			pValue = PyInt_FromLong(3);
			PyTuple_SetItem(pArgs, 1, pValue);
			
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL)
            {
                printf("Result of function call: %ld\n", PyInt_AsLong(pValue));
                Py_DECREF(pValue);
            }
            else
            {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        return 1;
    }
    Py_Finalize();
    getchar();
    return 0;
}
