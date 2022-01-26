#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


int main()
{
	string userInput = "0";
	//int tableNum = 0;
	string userItem = "";

	while (userInput != "4") { 
		//Displays menu for user
		cout << "1: Produce a list of all items purchased in a given day along with the number of times each item was purchased." << endl;
		cout << "2: Produce a number representing how many times a specific item was purchased in a given day." << endl;
		cout << "3: Produce a text-based histogram listing all items purchased in a given day." << endl;
		cout << "   Along with a representation of the number of times each item was purchased." << endl;
		cout << "4: Exit" << endl;
		cout << "Enter your selection as a number 1, 2, 3 or 4." << endl;
		cin >> userInput;

		//Prints list of all grocery items and their purchase number
		if (userInput == "1") {
			CallProcedure("PrintList");
		}

		//Allows user to see purchase number of one item at a time
		else if (userInput == "2") {
			cout << "" << endl;
			cout << "Enter the item you would like to see the purchase number of:" << endl;
			cin >> userItem;
			int itemCount = callIntFunc("ItemCount", userItem);
			cout << "There were " << itemCount << " " << userItem << " " << "purchased today" << endl;
			cout << endl;
		}

		//Creates histrogram of item purchases
		else if (userInput == "3") {
			CallProcedure("CreateFile");
			ifstream myFile("frequency.dat");
			int itemCount;
			string itemName;
			if (myFile.is_open()) {
				while (myFile >> itemName >> itemCount)
				{
					cout << itemName << " ";
					for (int i = itemCount; i > 0; i--)
						cout << "*";
					cout << endl;
				}
				myFile.close();
			}
		}

		//Allows user to exit if they enter 4
		else if (userInput == "4") {
			break;
		}

		//Input validation
		else {
			cout << "Invalid input. Please enter 1, 2, 3 or 4..." << endl;
		}
	}
}