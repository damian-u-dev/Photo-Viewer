#include "MainForm.h"
#include <stdlib.h>
#include <memory>


using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System;
using namespace Windows::Forms;

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
	if (Directory::Exists(DIRECTORY_SETTINGS))
	{
		SetUpLastWindowSize();
		SetUpLastWindowLocation();
		SetUpLastWindowState();
		SetUpWindowColor();
	}
	SetUpButtons();
}

void PhotoViewer::MainForm::SetUpLastWindowSize()
{
	if (!File::Exists(PATH_LAST_WINDOW_SIZE))
		return;

	array<String^>^ LastWindowSize = File::ReadAllLines(PATH_LAST_WINDOW_SIZE);


	int LastWidth = Convert::ToInt32(LastWindowSize[0]);
	int LastHeight = Convert::ToInt32(LastWindowSize[1]);

	this->Size = Drawing::Size(LastWidth, LastHeight);

}

void PhotoViewer::MainForm::SetUpLastWindowLocation()
{
	if (!File::Exists(PATH_LAST_WINDOW_LOCATION))
		return;

	array<String^>^ LastWindowLocation = File::ReadAllLines(PATH_LAST_WINDOW_LOCATION);

	int LastX = Convert::ToInt32(LastWindowLocation[0]);
	int LastY = Convert::ToInt32(LastWindowLocation[1]);

	Drawing::Point LastLocation(LastX, LastY);

	Location = LastLocation;

}

void PhotoViewer::MainForm::SetUpLastWindowState()
{
	if (!File::Exists(PATH_LAST_WINDOW_STATE))
		return;

	String^ LastWindowModeStr = File::ReadAllText(PATH_LAST_WINDOW_STATE);

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

void PhotoViewer::MainForm::CheckFavoritePicturesOnExist()
{
	for (int i = 0; i < FavoritePictures.Count; i++)
	{
		if (!File::Exists(FavoritePictures[i]->ToString()))
		{
			FavoritePictures.RemoveAt(i);
		}
	}
}

void PhotoViewer::MainForm::SaveSettingsForm()
{
	if (!Directory::Exists(DIRECTORY_SETTINGS))
	{
		Directory::CreateDirectory(DIRECTORY_SETTINGS);
	}

	if (WindowState == FormWindowState::Normal)
	{
		SaveLastWindowSize();
		SaveLastWindowLocation();
	}

	SaveLastWindowState();
	SaveWindowColor();
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

	File::WriteAllText(PATH_LAST_WINDOW_LOCATION, LastX + LastY);
}

void PhotoViewer::MainForm::SaveLastWindowState()
{
	File::WriteAllText(PATH_LAST_WINDOW_STATE, WindowState.ToString());
}

void PhotoViewer::MainForm::SaveWindowColor()
{
	File::WriteAllText(PATH_WINDOW_COLOR, this->BackColor.Name);
}

PhotoViewer::MainForm::~MainForm()
{
	SaveSettingsForm();
	SaveFavoritePicturesPaths();
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
	if (e->KeyCode == Keys::A && !OnePictureInCurrentArray)
	{
		bPreviousPicture_Click(nullptr, nullptr);
	}
	if (e->KeyCode == Keys::D && !OnePictureInCurrentArray)
	{
		bNextPicture_Click(nullptr, nullptr);
	}
	if (e->KeyCode == Keys::Escape && IsFullView)
	{
		FullViewToolStripMenuItem_Click(nullptr, nullptr);
	}
}

void PhotoViewer::MainForm::SwitchPicture(const int lastOrFirstPicture, const int initializeValue, const int addValue)
{
	if (ViewMode == PictureViewMode::FromDirectory)
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
	else
	{
		if (IndexFavoritePicture == lastOrFirstPicture)
		{
			IndexFavoritePicture = initializeValue;
		}
		else
		{
			IndexFavoritePicture = addValue;
		}

		PictureBox->Image = Image::FromFile(FavoritePictures[IndexFavoritePicture]->ToString());
	}
}

void PhotoViewer::MainForm::bNextPicture_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewMode == PictureViewMode::FromDirectory)
	{
		SwitchPicture(IndexLastPicture, INDEX_FIRST_PICTURE, IndexCurrentPicture + 1);
	}
	else
	{
		SwitchPicture(FavoritePictures.Count - 1, INDEX_FIRST_PICTURE, IndexFavoritePicture + 1);
	}
}

void PhotoViewer::MainForm::bPreviousPicture_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewMode == PictureViewMode::FromDirectory)
	{
		SwitchPicture(INDEX_FIRST_PICTURE, IndexLastPicture, IndexCurrentPicture - 1);
	}
	else
	{
		SwitchPicture(INDEX_FIRST_PICTURE, FavoritePictures.Count - 1, IndexFavoritePicture - 1);
	}
}

void PhotoViewer::MainForm::OpenDirectoryCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ PathToExplorer = "\"C:\\Windows\\explorer.exe ";
	String^ CurrentDirectory = Path::GetDirectoryName(Pictures[IndexCurrentPicture]->ToString());

	array<wchar_t>^ FullPath = (PathToExplorer + CurrentDirectory)->ToCharArray();

	std::unique_ptr<char[]> Array(new char[FullPath->Length + 1] {});

	for (int i = 0; i < FullPath->Length; i++)
	{
		Array[i] = static_cast<char>(FullPath[i]);
	}
	Array[FullPath->Length] = '\0';

	system(Array.get());
}

void PhotoViewer::MainForm::CopyNameOfCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Clipboard::SetText(Path::GetFileNameWithoutExtension(Pictures[IndexCurrentPicture]->ToString()));
}

bool PhotoViewer::MainForm::IsOnePictureInArray()
{
	if (ViewMode == PictureViewMode::FromDirectory)
	{
		return Pictures.Count == 1;
	}
	return FavoritePictures.Count == 1;
}

void PhotoViewer::MainForm::SetUpButtons()
{
	if (IsOnePictureInArray())
	{
		OnePictureInCurrentArray = true;
		bNextPicture->Visible = false;
		bPreviousPicture->Visible = false;
	}
	else
	{
		OnePictureInCurrentArray = false;
		bNextPicture->Visible = true;
		bPreviousPicture->Visible = true;
	}
}

void PhotoViewer::MainForm::SaveFavoritePicturesPaths()
{
	//PLACE HOLDER
}

void PhotoViewer::MainForm::ShowToolMenuForFavoriteMode(bool Value)
{
	removePictureFromFavoriteToolStripMenuItem->Visible = Value;
	exitFromFavoriteModeToolStripMenuItem->Visible = Value;
}

void PhotoViewer::MainForm::SetColorForm(Color BackColor, Color ForeColor, Color ColorMenuStrip, Color ForeColorButtons)
{
	this->BackColor = BackColor;

	bNextPicture->BackColor = BackColor;
	bPreviousPicture->BackColor = BackColor;
	menuStrip1->BackColor = ColorMenuStrip;

	//FileToolStrip
	CopyCurrentPictureToolStripMenuItem->BackColor = BackColor;
	CopyCurrentPictureToolStripMenuItem->ForeColor = ForeColor;

	openDirectoryCurrentPictureToolStripMenuItem->BackColor = BackColor;
	openDirectoryCurrentPictureToolStripMenuItem->ForeColor = ForeColor;

	copyNameOfCurrentPictureToolStripMenuItem->BackColor = BackColor;
	copyNameOfCurrentPictureToolStripMenuItem->ForeColor = ForeColor;

	fullViewToolStripMenuItem->BackColor = BackColor;
	fullViewToolStripMenuItem->ForeColor = ForeColor;

	exitToolStripMenuItem->BackColor = BackColor;
	exitToolStripMenuItem->ForeColor = ForeColor;

	//FavoritePicture toolstrip
	savePictureLikeFavoriteToolStripMenuItem->BackColor = BackColor;
	savePictureLikeFavoriteToolStripMenuItem->ForeColor = ForeColor;

	switchToFavoritePicturesToolStripMenuItem->BackColor = BackColor;
	switchToFavoritePicturesToolStripMenuItem->ForeColor = ForeColor;

	removePictureFromFavoriteToolStripMenuItem->BackColor = BackColor;
	removePictureFromFavoriteToolStripMenuItem->ForeColor = ForeColor;

	exitFromFavoriteModeToolStripMenuItem->BackColor = BackColor;
	exitFromFavoriteModeToolStripMenuItem->ForeColor = ForeColor;

	//Settings Tool Strip
	themeToolStripMenuItem->BackColor = BackColor;
	themeToolStripMenuItem->ForeColor = ForeColor;

	lightToolStripMenuItem->BackColor = BackColor;
	lightToolStripMenuItem->ForeColor = ForeColor;

	darkToolStripMenuItem->BackColor = BackColor;
	darkToolStripMenuItem->ForeColor = ForeColor;

	//TooStripMenu
	FileToolStripMenuItem->ForeColor = ForeColor;
	favoritePicturesToolStripMenuItem->ForeColor = ForeColor;
	settingsToolStripMenuItem->ForeColor = ForeColor;

	bNextPicture->ForeColor = ForeColorButtons;
	bPreviousPicture->ForeColor = ForeColorButtons;
}

void PhotoViewer::MainForm::SetUpWindowColor()
{
	if (!File::Exists(PATH_WINDOW_COLOR))
	{
		lightToolStripMenuItem_Click(nullptr, nullptr);
		return;
	}

	String^ LastColor = File::ReadAllText(PATH_WINDOW_COLOR);

	if (LastColor == Color::DimGray.Name)
	{
		DarkToolStripMenuItem_Click(nullptr, nullptr);
	}
	else
	{
		lightToolStripMenuItem_Click(nullptr, nullptr);
	}
}

void PhotoViewer::MainForm::SetUserFont(System::Drawing::Font^ UserFont)
{
	//File ToolStrip Menu
	FileToolStripMenuItem->Font = UserFont;
	CopyCurrentPictureToolStripMenuItem->Font = UserFont;
	copyNameOfCurrentPictureToolStripMenuItem->Font = UserFont;
	fullViewToolStripMenuItem->Font = UserFont;
	exitToolStripMenuItem->Font = UserFont;

	//FavoritePictures ToolStripMenuItem
	favoritePicturesToolStripMenuItem->Font = UserFont;
	savePictureLikeFavoriteToolStripMenuItem->Font = UserFont;
	switchToFavoritePicturesToolStripMenuItem->Font = UserFont;
	removePictureFromFavoriteToolStripMenuItem->Font = UserFont;
	exitFromFavoriteModeToolStripMenuItem->Font = UserFont;

	//settings ToolStripMenuItem
	settingsToolStripMenuItem->Font = UserFont;
	themeToolStripMenuItem->Font = UserFont;
	lightToolStripMenuItem->Font = UserFont;
	darkToolStripMenuItem->Font = UserFont;
	changeFontToolStripMenuItem->Font = UserFont;
}

void PhotoViewer::MainForm::SavePictureLikeFavoriteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewMode == PictureViewMode::FromDirectory)
	{
		if (!IsThisPictureFavorite(Pictures[IndexCurrentPicture]->ToString()))
		{
			FavoritePictures.Add(Pictures[IndexCurrentPicture]);
		}
	}
}

bool PhotoViewer::MainForm::IsThisPictureFavorite(String^ CurrentPicture)
{
	for (int i = 0; i < FavoritePictures.Count; i++)
	{
		if (FavoritePictures[i]->Equals(CurrentPicture))
		{
			return true;
		}
	}
	return false;
}

void PhotoViewer::MainForm::SwitchToFavoritePicturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (FavoritePictures.Count > 0)
	{
		ViewMode = PictureViewMode::FromFavoritePictures;

		ShowToolMenuForFavoriteMode(true);

		SetUpButtons();
		PictureBox->Image = Image::FromFile(FavoritePictures[IndexFavoritePicture]->ToString());
	}
	else
	{
		MessageBox::Show("You don't have any favorite pictures.", "Favorite Pictures");
	}
}

System::Void PhotoViewer::MainForm::RemovePictureFromFavoriteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (IsOnePictureInArray())
	{
		FavoritePictures.Clear();
		ExitFromFavoriteModeToolStripMenuItem_Click(nullptr, nullptr);
	}
	else
	{


		//IndexFavoritePicture--;

		if (IndexFavoritePicture == FavoritePictures.Count - 1)
		{
			FavoritePictures.RemoveAt(IndexFavoritePicture);
			IndexFavoritePicture = 0;
		}
		else //IndexFavoritePicture == INDEX_FIRST_PICTURE
		{
			FavoritePictures.RemoveAt(IndexFavoritePicture);
		}

		SetUpButtons();
		PictureBox->Image = Image::FromFile(FavoritePictures[IndexFavoritePicture]->ToString());
	}
}

System::Void PhotoViewer::MainForm::ExitFromFavoriteModeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	ViewMode = PictureViewMode::FromDirectory;
	PictureBox->Image = Image::FromFile(Pictures[IndexCurrentPicture]->ToString());

	ShowToolMenuForFavoriteMode(false);

	SetUpButtons();
}

void PhotoViewer::MainForm::DarkToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	lightToolStripMenuItem->Checked = false;
	darkToolStripMenuItem->Checked = true;

	SetColorForm(Color::DimGray, Color::White, Color::DimGray, Color::Indigo);
}

void PhotoViewer::MainForm::lightToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	lightToolStripMenuItem->Checked = true;
	darkToolStripMenuItem->Checked = false;

	Color DefaultBackColorForm = Color::FromArgb(255, 240, 240, 240);
	Color DefaultForeColorForm = Color::FromArgb(255, 0, 0, 0);

	SetColorForm(DefaultBackColorForm, DefaultForeColorForm, Color::WhiteSmoke, Color::Black);
}

void PhotoViewer::MainForm::FullViewToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!IsFullView)
	{
		WindowStateBeforeFullView = this->WindowState;

		IsFullView = true;
		this->WindowState = FormWindowState::Maximized;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;

		this->menuStrip1->Visible = false;
	}
	else
	{
		IsFullView = false;

		this->WindowState = WindowStateBeforeFullView;
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;

		this->menuStrip1->Visible = true;
	}
}

void PhotoViewer::MainForm::ExitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Close();
}

void PhotoViewer::MainForm::ChangeFontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	FontDialog FontDialog;
	FontDialog.AllowScriptChange = false;
	FontDialog.FontMustExist = true;
	FontDialog.MaxSize = 14;
	FontDialog.ShowColor = false;
	FontDialog.ShowEffects = false;
	FontDialog.ShowHelp = false;


	Windows::Forms::DialogResult DialogResult = FontDialog.ShowDialog();

	if (DialogResult == Windows::Forms::DialogResult::OK)
	{
		SetUserFont(FontDialog.Font);
	}
}
