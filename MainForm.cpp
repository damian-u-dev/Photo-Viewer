#include "MainForm.h"

using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System;

PhotoViewer::MainForm::MainForm(String^ pathToOpenedPicture)
{
	InitializeComponent();
	SortFiles(GetFilesCurrentDirectory(pathToOpenedPicture));
	FindOutIndexOpenedPicture(pathToOpenedPicture);
	SettingUpPictureBox();
}

array<String^>^ PhotoViewer::MainForm::GetFilesCurrentDirectory(String^ pathToPicture)
{
	String^ Directory = Path::GetDirectoryName(pathToPicture);
	return Directory::GetFiles(Directory);
}

bool PhotoViewer::MainForm::IsCorrectExtension(String^ extension)
{
	return (extension->EndsWith(".jpeg") || extension->EndsWith(".png") ||
		extension->EndsWith(".jpg") || extension->EndsWith(".gif"));
}

void PhotoViewer::MainForm::SortFiles(array<String^>^ AllFiles)
{
	for (int i = 0; i < AllFiles->Length; i++)
	{
		if (IsCorrectExtension(AllFiles[i]))
		{
			Pictures.Add(AllFiles[i]);
		}
	}
	IndexLastPicture = Pictures.Count - 1;
}

void PhotoViewer::MainForm::FindOutIndexOpenedPicture(String^ pathToOpenedPicture)
{
	for (int i = 0; i < Pictures.Count; i++)
	{
		if (Pictures[i]->Equals(pathToOpenedPicture))
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

void PhotoViewer::MainForm::SaveSettingsForm()
{
	//TODO: Place Holder with Directory
	if (Directory::Exists(DIRECTORY_SETTINGS))
	{
		SaveLastWindowSize();
	}
}

void PhotoViewer::MainForm::SaveLastWindowSize()
{
	String^ Width = this->Size.Width.ToString();
	Width += "\n";

	String^ Height = this->Size.Height.ToString();

	//TODO: Place Holder with path to windowSize.txt
	File::WriteAllText("D:\\Settings\\LastWindowSize.txt",Width + Height);
}

PhotoViewer::MainForm::~MainForm()
{
	SaveSettingsForm();
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
	if (e->KeyCode == Keys::A)
	{
		bPreviousPicture_Click(nullptr, nullptr);
	}
	if(e->KeyCode == Keys::D)
	{
		bNextPicture_Click(nullptr, nullptr);
	}
}

void PhotoViewer::MainForm::SwitchPicture(const int lastOrFirstPicture, const int initializeValue, const int addValue)
{
	if (IndexCurrentPicture == lastOrFirstPicture)
	{
		IndexCurrentPicture = initializeValue;
	}
	else
	{
		IndexCurrentPicture = addValue;
	}

	PictureBox->Image = Image::FromFile(Pictures[IndexCurrentPicture]->ToString());
}

void PhotoViewer::MainForm::bNextPicture_Click(System::Object^ sender, System::EventArgs^ e)
{
	SwitchPicture(IndexLastPicture, INDEX_FIRST_PICTURE, IndexCurrentPicture + 1);
}

System::Void PhotoViewer::MainForm::bPreviousPicture_Click(System::Object^ sender, System::EventArgs^ e)
{
	SwitchPicture(INDEX_FIRST_PICTURE, IndexLastPicture, IndexCurrentPicture - 1);
}