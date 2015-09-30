
#include "pyengine.h"
#include "sys.h"
#include "app.h"
#include <string>  
#include <iostream>
using namespace std;

#include "commonpyfunc.h"
int main()
{
	PyEngine *pPyEngine = new PyEngine();
	CApp *pApp = new CApp();
	pApp->run();
	delete pApp;
	delete pPyEngine;
    return 0;
}

