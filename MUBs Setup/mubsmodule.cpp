#include <math.h>
#include <complex>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <iostream>

#include "Python.h"
#include "numpy/arrayobject.h"


static PyObject*
example (PyObject *dummy, PyObject *args)
{
    PyObject *arg1=NULL, *arg2=NULL;
    PyArrayObject *arr1=NULL, *arr2=NULL;
    double r=-1;
    double b=-1;
    int n=0, m=0;

    if (!PyArg_ParseTuple(args, "OOddii", &arg1, &arg2, &b, &r, &n, &m)) return NULL;

    arr1 = (PyArrayObject*)PyArray_FROM_OTF(arg1, NPY_DOUBLE, NPY_IN_ARRAY);
    if (arr1 == NULL) return NULL;
    arr2 = (PyArrayObject*)PyArray_FROM_OTF(arg2, NPY_DOUBLE, NPY_IN_ARRAY);
    if (arr2 == NULL){
        Py_XDECREF(arr1);
        Py_XDECREF(arr2);
        return NULL;
    } 
    if (b == -1 | r == -1){
        Py_XDECREF(arr1);
        Py_XDECREF(arr2);
        return NULL;
    }


    /*vv* make MUBs random sample *vv*/

    double s = 1.;
    std::vector<std::complex<double> > z(n);

    std::complex<double> w;

    int i,j;


    if (b == n){
        for(i=0; i<n; i++)
            z[i] = 0;
        z[m] = 1.;
    }
    else{
        w = std::complex<double>(0,2*M_PI/n);
        s = 0.;


        for (i=0; i<n; i++){
            z[i] = exp(w*(i*r - (i*(i+1)/2)*b));
            s += real(z[i])*real(z[i]) + imag(z[i])*imag(z[i]);
        } 

        s = sqrt(s);
    }

    /*vv* return MUBs sample *vv*/


    for (i=0; i<arr1->dimensions[0]; ++i) {
        for (j=0; j<arr1->dimensions[1]; ++j) {
            double *v = (double*)PyArray_GETPTR2(arr1, i, j);
            *v = (double)real(z[i]/s);

            double *u = (double*)PyArray_GETPTR2(arr2, i, j);
            *u = (double)imag(z[i])/s;
        }
    }

    /*^^* code that makes use of arguments *^^*/
    
    Py_DECREF(arr1);
    Py_DECREF(arr2);
    Py_INCREF(Py_None);


    return Py_None;

    
}

static struct PyMethodDef methods[] = {
    {"mubs", example, METH_VARARGS, "descript of example"},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initmubs (void)
{
    srand(time(NULL));
    (void)Py_InitModule("mubs", methods);
    import_array();
}
