#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ argv)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();

	String^ PathToPicture = "";

	if (argv->Length > 0 && PhotoViewer::MainForm::IsCorrectExtension(argv[0]))
	{
		PathToPicture = argv[0];
	}

	PhotoViewer::MainForm mainForm(PathToPicture);
	Application::Run(% mainForm);
}