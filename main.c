#include <Python.h>
#include <numpy/arrayobject.h>
#include <stdio.h>

#if PY_MAJOR_VERSION >= 3
int
#else
void
#endif
init_numpy(){
  import_array();
}

//int main(void){
//  printf("Hello World!\n");
//  return 0;
//}

int main(void){
    Py_Initialize();
    init_numpy();
    //カレントディレクトリを探す範囲にいれる-------------------------
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path,PyUnicode_DecodeFSDefault("."));
    //---------------------------------------------------------------

    //探すファイルを指定-------------------------------------------
    PyObject *pName = PyUnicode_DecodeFSDefault("main");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    //関数を指定
    PyObject *pFunc = PyObject_GetAttrString(pModule, "py_func");

    npy_intp dimensions[2] = {2, 3}; //height,width;
    int d=2;
    int array_sample[2][3] = {{2,1,3},{3,1,4}};
    PyObject *pdemo2=PyArray_SimpleNewFromData(d,&dimensions[0], NPY_UINT32, (void *) array_sample);

    //Tupleの作成    -----------------------------------------------
    PyObject *pArgs = PyTuple_New(1);//Tupleを新しく作成する
    PyTuple_SetItem(pArgs,0,pdemo2);//Tupleの0の位置にpdemo2を設定

    //RUN
    PyObject *pValue= PyObject_CallObject(pFunc, pArgs);

		if (pValue != NULL)
    {
        int *vector = (int*) PyArray_DATA(pValue);
        for (int i=0;i<2;i++){
          for (int j=0;j<3;j++){
            printf("%d,",vector[i*3+j]);
          }
          printf("\n");
        }
		}else{
      printf("noting is returned\n");
    }

    Py_Finalize();
    return 0;
}
