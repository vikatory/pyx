#include "pyengine.h"
#include "commonpyfunc.h"
#include "sys.h"
#include "pywrap.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include <boost/python.hpp>
#include <boost/detail/lightweight_test.hpp>
#include <boost/property_tree/ptree.hpp>  
#include <boost/property_tree/ini_parser.hpp>  

using namespace std;

namespace bf = boost::filesystem;				// �򵥱���
namespace python = boost::python;

template <class T>
void safe_execute(T functor);

PyEngine::PyEngine()
{
	init();
}

PyEngine::~PyEngine()
{
	// Boost.Python doesn't support Py_Finalize yet.
	 Py_Finalize();
}

void PyEngine::init()
{
	bf::path oCurPath = bf::current_path();		// ȡ�õ�ǰĿ¼, һ����cpp�ļ��У�����exe�ó������У�����exe���ڵ��ļ���
	string sCurPath = oCurPath.string();
	cout << sCurPath << endl;
	// ͨ�����û�����������dll·��
	SetEnviromentValue("PYTHONPATH", "E:\\CODE\\project_1\\python-3.5.0-embed-amd64;E:\\CODE\\project_1\\python-3.5.0-embed-amd64\\Lib");
	Py_SetProgramName(L"python35");
	registerPyModule();  // ��Py_Initialize֮ǰ����
	Py_Initialize();
	//using namespace boost::python;				// ����������Ч
	test();

}

void evalPyExpr(const char *expression, std::string *result)
{
	python::object oPyMainModule = python::import("__main__");
	python::object oPyMainNamespace = oPyMainModule.attr("__dict__");
	python::object oResult = python::eval(expression, oPyMainNamespace);
	*result = python::extract<std::string>(oResult) BOOST_EXTRACT_WORKAROUND;
}

std::string PyEngine::eval(const char *expression)  // eval�������Լ���Python���ʽ�������ؽ��
{
	std::string sValue = "";
	safe_execute(boost::bind(evalPyExpr, expression, &sValue));
	return sValue;
}

void execPyCode(const char *code)
{
	python::object oPyMainModule = python::import("__main__");
	python::object oPyMainNamespace = oPyMainModule.attr("__dict__");
	python::object oResult = python::exec(code, oPyMainNamespace);
}

void PyEngine::exec(const char *code)  // ͨ��exec����ִ�ж�̬Python���룬exec�����ؽ��
{
	safe_execute(boost::bind(execPyCode, code));
}

void execPyFile(const char *filename)
{
	python::object oPyMainModule = python::import("__main__");
	python::object oPyMainNamespace = oPyMainModule.attr("__dict__");
	python::object result = python::exec_file(filename, oPyMainNamespace, oPyMainNamespace);
}

void PyEngine::execFile(const char *filename)
{
	safe_execute(boost::bind(execPyFile, filename));
}

std::string PyEngine::scriptPath()
{
	string sPath;
	try
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini("config.ini", pt);
		sPath = pt.get<std::string>("script.pyscript");
	}
	catch (std::exception &ex)
	{
		std::cout << "Error:" << ex.what() << std::endl;
	}
	return sPath;
}

void PyEngine::registerPyModule()  // ��Py_Initialize֮ǰ����
{
	registerPyFuncs();
}



void PyEngine::test()
{
	// TODO: windos�²�ɫ����̨, ����������boost.log���, py.log�Ż�
	exec("a='11ass77'");
	exec("import sys \n"
		"s=sys.version\n"
		"a=s");
	string value = eval("a");
	string sPyPath = scriptPath();
	exec(("scriptRoot = \"" + sPyPath + "\"\n").c_str());
	sPyPath.append("/main.py");
	execFile(sPyPath.c_str());
}


template <class T>
void safe_execute(T functor)
{
	void check_pyerr(bool pyerr_expected = false);
	if (python::handle_exception(functor))
	{
		check_pyerr();
	}
};

void check_pyerr(bool pyerr_expected = false)
{
	if (PyErr_Occurred())
	{
		if (!pyerr_expected)
		{
			//BOOST_ERROR("Python����");
			if (PyErr_ExceptionMatches(PyExc_SyntaxError))
			{
				void log_python_exception();
				log_python_exception();
			}
			else
			{
				PyErr_Print();
			}
		}
		else
			PyErr_Clear();
	}
	else
		BOOST_ERROR("һ��C++���ʽ���׳�������û�б��ʽ�����ע��r.");
}

std::string strErrorMsg;

void log_python_exception()
{
	if (!Py_IsInitialized())
	{
		strErrorMsg = "Python���л���û�г�ʼ��!";
		return;
	}
	if (PyErr_Occurred() != NULL)
	{
		PyObject *type_obj, *value_obj, *traceback_obj;
		PyErr_Fetch(&type_obj, &value_obj, &traceback_obj);
		if (value_obj == NULL)
			return;

		strErrorMsg.clear();
		PyErr_NormalizeException(&type_obj, &value_obj, 0);
		if (PyUnicode_Check(PyObject_Str(value_obj)))
		{
			strErrorMsg = _PyUnicode_AsString(PyObject_Str(value_obj));
		}

		if (traceback_obj != NULL)
		{
			strErrorMsg += "\nTraceback:";
			PyObject *pModuleName = PyUnicode_FromString("traceback");
			PyObject *pTraceModule = PyImport_Import(pModuleName);
			Py_XDECREF(pModuleName);
			if (pTraceModule != NULL)
			{
				PyObject *pModuleDict = PyModule_GetDict(pTraceModule);
				if (pModuleDict != NULL)
				{
					PyObject *pFunc = PyDict_GetItemString(pModuleDict, "format_exception");
					if (pFunc != NULL)
					{
						PyObject *errList = PyObject_CallFunctionObjArgs(pFunc, type_obj, value_obj, traceback_obj, NULL);
						if (errList != NULL)
						{
							Py_ssize_t listSize = PyList_Size(errList);
							for (Py_ssize_t i = 0; i < listSize; ++i)
							{
								strErrorMsg += _PyUnicode_AsString(PyList_GetItem(errList, i));
							}
						}
					}
				}
				Py_XDECREF(pTraceModule);
			}
		}
		Py_XDECREF(type_obj);
		Py_XDECREF(value_obj);
		Py_XDECREF(traceback_obj);
	}
	strErrorMsg.append("\n");
	cwrite(strErrorMsg.c_str(), "red_h");
}

