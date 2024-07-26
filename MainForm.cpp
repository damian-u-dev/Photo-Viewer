#include "MainForm.h"

using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System;

PhotoViewer::MainForm::MainForm()
{
	InitializeComponent();
	SortFiles();
	FindOutIndexCurrentPicture();
	SettingUpPictureBox();
}

array<String^>^ PhotoViewer::MainForm::GetFilesCurrentDirectory(String^ directory)
{
	return Directory::GetFiles(directory);
}

bool PhotoViewer::MainForm::IsCorrectExtension(String^ extension)
{
	return (extension->EndsWith(".jpeg") || extension->EndsWith(".png") ||
		extension->EndsWith(".jpg") || extension->EndsWith(".gif"));
}

void PhotoViewer::MainForm::SortFiles()
{
	array<String^>^ AllFiles = GetFilesCurrentDirectory("D:\\Photos");

	for (int i = 0; i < AllFiles->Length; i++)
	{
		if (IsCorrectExtension(AllFiles[i]))
		{
			Pictures.Add(AllFiles[i]);
		}
	}

}

void PhotoViewer::MainForm::FindOutIndexCurrentPicture()
{
	for (int i = 0; i < Pictures.Count; i++)
	{
		//TODO: Change place holder
		if (Pictures[i]->Equals("D:\\Photos\\elliesnewbbg_1705251529_7323999466669755694_index_0_12.jpeg"))
		{
			IndexCurrentPicture = i;
			break;
		}
	}
}

void PhotoViewer::MainForm::SettingUpPictureBox()
{
	PictureBox->Image = Image::FromFile(Pictures[IndexCurrentPicture]->ToString());
}

PhotoViewer::MainForm::~MainForm()
{
	if (components)
	{
		delete components;
	}
}

void PhotoViewer::MainForm::CopyCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Clipboard::SetImage(PictureBox->Image);
}

void PhotoViewer::MainForm::MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	if (e->Control && e->KeyCode == Keys::C)
	{
		CopyCurrentPictureToolStripMenuItem_Click(sender, e);
	}
}
