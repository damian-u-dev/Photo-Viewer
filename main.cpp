#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ argv)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	PhotoViewer::MainForm mainForm;
	Application::Run(% mainForm);
}