#include "About PV Form.h"

using namespace System::Windows::Forms;
using namespace System::Diagnostics;

PhotoViewer::AboutPVForm::AboutPVForm()
{
	InitializeComponent();
	link_GitHub->Text = GitHubLink;
}

PhotoViewer::AboutPVForm::~AboutPVForm()
{
	if (components)
	{
		delete components;
	}
}

void PhotoViewer::AboutPVForm::SetColorForm(Color FormColor, Color FontColor)
{
	this->Name = "About Photo-Viewer";

	this->BackColor = FormColor;

	l_NameOfProgramm->ForeColor = FontColor;
	l_Copyrights->ForeColor = FontColor;
	l_Developer->ForeColor = FontColor;
}

void PhotoViewer::AboutPVForm::AboutPVForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->KeyCode == Keys::Escape)
	{
		Close();
	}
}

void PhotoViewer::AboutPVForm::link_GitHub_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e)
{
	Process::Start(GitHubLink);
}
