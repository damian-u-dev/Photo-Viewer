#include "MainForm.h"

using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System;

PhotoViewer::MainForm::MainForm()
{
	InitializeComponent();
	SortFiles();
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

PhotoViewer::MainForm::~MainForm()
{
	if (components)
	{
		delete components;
	}
}
