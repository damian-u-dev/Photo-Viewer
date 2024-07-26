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
	SetUpWindowForm();
}

void PhotoViewer::MainForm::SetUpWindowForm()
{
	SetUpLastWindowSize();
	SetUpLastWindowLocation();
	SetUpLastWindowState();
}

void PhotoViewer::MainForm::SetUpLastWindowSize()
{
	array<String^>^ LastWindowSize = File::ReadAllLines(PATH_LAST_WINDOW_SIZE);


	int LastWidth = Convert::ToInt32(LastWindowSize[0]);
	int LastHeight = Convert::ToInt32(LastWindowSize[1]);

	this->Size = Drawing::Size(LastWidth, LastHeight);

}

void PhotoViewer::MainForm::SetUpLastWindowLocation()
{
	array<String^>^ LastWindowLocation = File::ReadAllLines(LAST_WINDOW_LOCATION);

	int LastX = Convert::ToInt32(LastWindowLocation[0]);
	int LastY = Convert::ToInt32(LastWindowLocation[1]);

	Drawing::Point LastLocation(LastX, LastY);

	Location = LastLocation;

}

void PhotoViewer::MainForm::SetUpLastWindowState()
{
	String^ LastWindowModeStr = File::ReadAllText(LAST_WINDOW_STATE);

	if (LastWindowModeStr == "Normal")
	{
		WindowState = FormWindowState::Normal;
	}
	else
	{
		WindowState = FormWindowState::Maximized;
	}
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
	if (Directory::Exists(DIRECTORY_SETTINGS))
	{
		if (WindowState == FormWindowState::Normal)
		{
			SaveLastWindowSize();
			SaveLastWindowLocation();
		}

		SaveLastWindowState();
	}
}

void PhotoViewer::MainForm::SaveLastWindowSize()
{
	String^ Width = this->Size.Width.ToString();
	Width += "\n";

	String^ Height = this->Size.Height.ToString();

	File::WriteAllText(PATH_LAST_WINDOW_SIZE, Width + Height);
}

void PhotoViewer::MainForm::SaveLastWindowLocation()
{
	String^ LastX = this->Location.X.ToString();
	LastX += "\n";

	String^ LastY = this->Location.Y.ToString();

	File::WriteAllText(LAST_WINDOW_LOCATION, LastX + LastY);
}

void PhotoViewer::MainForm::SaveLastWindowState()
{
	File::WriteAllText(LAST_WINDOW_STATE, WindowState.ToString());
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
	if (e->KeyCode == Keys::D)
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

void PhotoViewer::MainForm::bPreviousPicture_Click(System::Object^ sender, System::EventArgs^ e)
{
	SwitchPicture(INDEX_FIRST_PICTURE, IndexLastPicture, IndexCurrentPicture - 1);
}