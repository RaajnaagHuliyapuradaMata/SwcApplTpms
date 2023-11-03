#include "stdafx.h"
#include "RDCi.h"

#include "RTE_Stub_Dialog.h"

#ifdef _EcuVirtual
#else
using namespace RDCi;
#endif

#define MAX_LOADSTRING 100

HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING];
TCHAR szWindowClass[MAX_LOADSTRING];

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow
){
   UNREFERENCED_PARAMETER(hPrevInstance);
   UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef _EcuVirtual
   UNUSED(hInstance);
   UNUSED(nCmdShow);
#else
	  System::STAThreadAttribute();
	  Application::Run( gcnew RTE_Stub_Dialog());
#endif

   return 0;
}

  
