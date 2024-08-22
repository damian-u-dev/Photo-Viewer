#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

#ifdef _DEBUG

[STAThreadAttribute]
int main(array<String^>^ argv)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	PhotoViewer::MainForm mainForm(R"(D:\Media\Entertainment\Plushie\Pictures\elliesnewbbg_1705251529_7323999466669755694_index_0_12.jpeg)");
	Application::Run(% mainForm);
}
#endif // _DEBUG



#ifndef _DEBUG
[STAThreadAttribute]
int main(array<String^>^ argv)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	PhotoViewer::MainForm mainForm(argv[0]);
	Application::Run(% mainForm);
}
#endif // !_DEBUG
