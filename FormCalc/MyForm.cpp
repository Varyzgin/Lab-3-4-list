#include "MyForm.h"
#include <Windows.h>
#include "..\ListStackCalc\TCalculator.h"
using namespace FormCalc;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MyForm);
	return 0;
}