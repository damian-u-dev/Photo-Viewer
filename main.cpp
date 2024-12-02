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


	//PhotoViewer::MainForm mainForm(R"(D:\test\2c5bcad4a0e92ab14e6927424efc00be.jpg)");

	PhotoViewer::MainForm mainForm(PathToPicture);
	Application::Run(% mainForm);
}