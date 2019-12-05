#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>


//int main(void){
//  printf("Hello World!\n");
//  return 0;
//}

int main(void){
    Py_Initialize();
    import_array();
    //カレントディレクトリを探す範囲にいれる-------------------------
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path,PyUnicode_DecodeFSDefault("."));
    //---------------------------------------------------------------

    //探すファイルを指定-------------------------------------------
    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    //---------------------------------------------------------------

    PyObject *pFunc = PyObject_GetAttrString(pModule, "py_func");

    npy_intp dimensions[2] = {2, 2}; //最初の２つはnumpy配列のwidthとheight
    int d=2;
    int array_sample[2][2] = {{2,1},{3,1}}; 
    PyObject *pdemo2=PyArray_SimpleNewFromData(d,&dimensions[0], NPY_UINT32, (void *) array_sample);

    //Tupleの作成    -----------------------------------------------
    PyObject *pArgs = PyTuple_New(1);//Tupleを新しく作成する
    PyTuple_SetItem(pArgs,0,pdemo2);//Tupleの0の位置にpdemo2を設定
    //---------------------------------------------------------------

    //RUN
    PyObject *presult = PyObject_CallObject(pFunc, pArgs);

    Py_Finalize();
    return 0;
}
