#include "MainForm.h"
#include <stdlib.h>
#include <memory>
#include "About PV Form.h"


using namespace System::IO;
using namespace System::Collections::Generic;
using namespace System;
using namespace Windows::Forms;
using namespace System::Windows::Forms;

PhotoViewer::MainForm::MainForm(String^ pathToOpenedPicture)
{
	InitializeComponent();
	if (pathToOpenedPicture->Length == 0)
	{
		SetUpWindowForm();
		SetVisibilityButtons(false);
		timer1->Enabled = true;
	}
	else
	{
		SetUpPhotoViewer(pathToOpenedPicture);
	}
}

void PhotoViewer::MainForm::SetUpPhotoViewer(String^ pathToPicture)
{
	SortFiles(GetFilesCurrentDirectory(pathToPicture));
	FindOutIndexOpenedPicture(pathToPicture);
	SettingUpPictureBox();
	SetUpWindowForm();
	InitializeFavoritePictures();
}

void PhotoViewer::MainForm::InitializeDialog(OpenFileDialog^ refFileDialog)
{
	refFileDialog->Multiselect = false;
	refFileDialog->Title = "Select a picture file";
	refFileDialog->Filter = "Image files (*.png;*jpg)|*.png;*.jpg";
}

void PhotoViewer::MainForm::OpenPictureFromExplorerTimer()
{
	timer1->Enabled = false;
	
	OpenFileDialog fileDialog;
	InitializeDialog(%fileDialog);

	auto DialogResult = fileDialog.ShowDialog();
	
	if (DialogResult == Windows::Forms::DialogResult::OK)
	{
		ViewMode = PictureViewMode::FromDirectory;
		SetUpPhotoViewer(fileDialog.FileName);
	}
	else
	{
		ViewMode = PictureViewMode::NoPictureFromDir;
		NoPictureMainDir = true;

		empty_dir->Visible = true;
		FileToolStripMenuItem->Visible = false;
		savePictureLikeFavoriteToolStripMenuItem->Visible = false;

		InitializeFavoritePictures();
	}
}

void PhotoViewer::MainForm::ToolMenu_OpenPictureFromExplorerInAnyTime(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog fileDialog;
	InitializeDialog(% fileDialog);

	auto DialogResult = fileDialog.ShowDialog();
	if (DialogResult == Windows::Forms::DialogResult::OK)
	{
		Pictures.Clear();
		SortFiles(GetFilesCurrentDirectory(fileDialog.FileName));
		FindOutIndexOpenedPicture(fileDialog.FileName);

		if (ViewMode == PictureViewMode::FromFavoritePictures)
		{
			ShowToolMenuForFavoriteMode(false);
		}
		else if (ViewMode == PictureViewMode::NoPictureFromDir)
		{
			NoPictureMainDir = false;

			empty_dir->Visible = false;
			FileToolStripMenuItem->Visible = true;
			savePictureLikeFavoriteToolStripMenuItem->Visible = true;
		}

		ViewMode = PictureViewMode::FromDirectory;
		SettingUpPictureBox();
		SetUpButtons();
	}
}

void PhotoViewer::MainForm::SetVisibilityButtons(bool visible)
{
	bNextPicture->Visible = visible;
	bPreviousPicture->Visible = visible;
}

void PhotoViewer::MainForm::SortFiles(array<String^>^ allFiles)
{
	for (int i = 0; i < allFiles->Length; i++)
	{
		if (IsCorrectExtension(allFiles[i]))
		{
			Pictures.Add(allFiles[i]);
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
	SetPicture(GetPathToPictureAtPictureBox());
}

void PhotoViewer::MainForm::SetPicture(String^ pathToPicture)
{
	PictureBox->Image = Image::FromFile(pathToPicture);
	SetNewTitle(Path::GetFileNameWithoutExtension(pathToPicture));
}

void PhotoViewer::MainForm::SetNewTitle(String^ newTitle)
{
	newTitle += " - Photo-Viewer";
	this->Text = newTitle;
}

void PhotoViewer::MainForm::InitializeFavoritePictures()
{
	if (!File::Exists(PATH_FAVORITE_PICTURES))
		return;

	FavoritePictures.AddRange(File::ReadAllLines(PATH_FAVORITE_PICTURES));
	CheckFavoritePicturesOnExist();
}


void PhotoViewer::MainForm::SetUpWindowForm()
{
	if (Directory::Exists(DIRECTORY_SETTINGS))
	{
		SetUpLastWindowSize();
		SetUpLastWindowLocation();
		SetUpLastWindowState();
		SetUpWindowColor();
		SetUpUserFont();
	}
	SetUpButtons();
}

void PhotoViewer::MainForm::SetUpLastWindowSize()
{
	if (!File::Exists(PATH_LAST_WINDOW_SIZE))
		return;

	array<String^>^ lastWindowSize = File::ReadAllLines(PATH_LAST_WINDOW_SIZE);


	int lastWidth = Convert::ToInt32(lastWindowSize[0]);
	int lastHeight = Convert::ToInt32(lastWindowSize[1]);

	this->Size = Drawing::Size(lastWidth, lastHeight);

}

void PhotoViewer::MainForm::SetUpLastWindowLocation()
{
	if (!File::Exists(PATH_LAST_WINDOW_LOCATION))
		return;

	array<String^>^ lastWindowLocation = File::ReadAllLines(PATH_LAST_WINDOW_LOCATION);

	int lastX = Convert::ToInt32(lastWindowLocation[0]);
	int lastY = Convert::ToInt32(lastWindowLocation[1]);

	Drawing::Point lastLocation(lastX, lastY);

	Location = lastLocation;

}

void PhotoViewer::MainForm::SetUpLastWindowState()
{
	if (!File::Exists(PATH_LAST_WINDOW_STATE))
		return;

	String^ lastWindowModeStr = File::ReadAllText(PATH_LAST_WINDOW_STATE);

	if (lastWindowModeStr == "Normal")
	{
		WindowState = FormWindowState::Normal;
	}
	else
	{
		WindowState = FormWindowState::Maximized;
	}
}

void PhotoViewer::MainForm::SetUpWindowColor()
{
	if (!File::Exists(PATH_WINDOW_COLOR))
	{
		lightToolStripMenuItem_Click(nullptr, nullptr);
		return;
	}

	String^ lastColor = File::ReadAllText(PATH_WINDOW_COLOR);

	if (lastColor == Color::DimGray.Name)
	{
		DarkToolStripMenuItem_Click(nullptr, nullptr);
	}
	else
	{
		lightToolStripMenuItem_Click(nullptr, nullptr);
	}
}

void PhotoViewer::MainForm::SetUpUserFont()
{
	if (!File::Exists(PATH_FONT))
		return;

	String^ userFont = File::ReadAllText(PATH_FONT);

	float sizeFont{ };
	if (!File::Exists(PATH_SIZE_FONT))
	{
		sizeFont = 8.0;
	}

	sizeFont = static_cast<float>(Convert::ToDouble(File::ReadAllText(PATH_SIZE_FONT)));

	SetUserFont(% System::Drawing::Font(userFont, sizeFont));
}

array<String^>^ PhotoViewer::MainForm::GetFilesCurrentDirectory(String^ pathToPicture)
{
	String^ directory = Path::GetDirectoryName(pathToPicture);
	return Directory::GetFiles(directory);
}

bool PhotoViewer::MainForm::IsCorrectExtension(String^ extension)
{
	return (extension->EndsWith(".jpeg") || extension->EndsWith(".png") ||
		extension->EndsWith(".jpg") || extension->EndsWith(".gif"));
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
		SaveUserFont();
	}

	SaveLastWindowState();
	SaveWindowColor();
}

void PhotoViewer::MainForm::SaveLastWindowSize()
{
	String^ width = this->Size.Width.ToString();
	width += "\n";

	String^ height = this->Size.Height.ToString();

	File::WriteAllText(PATH_LAST_WINDOW_SIZE, width + height);
}

void PhotoViewer::MainForm::SaveLastWindowLocation()
{
	String^ lastX = this->Location.X.ToString();
	lastX += "\n";

	String^ lastY = this->Location.Y.ToString();

	File::WriteAllText(PATH_LAST_WINDOW_LOCATION, lastX + lastY);
}

void PhotoViewer::MainForm::SaveLastWindowState()
{
	File::WriteAllText(PATH_LAST_WINDOW_STATE, WindowState.ToString());
}

void PhotoViewer::MainForm::SaveWindowColor()
{
	File::WriteAllText(PATH_WINDOW_COLOR, this->BackColor.Name);
}

void PhotoViewer::MainForm::SaveUserFont()
{
	File::WriteAllText(PATH_FONT, FileToolStripMenuItem->Font->Name);
	File::WriteAllText(PATH_SIZE_FONT, FileToolStripMenuItem->Font->Size.ToString());
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
	if (ViewMode == PictureViewMode::NoPictureFromDir)
		return;

	Clipboard::SetImage(PictureBox->Image);
}

void PhotoViewer::MainForm::MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	bool isEmpty = ViewMode == PictureViewMode::NoPictureFromDir;
	if (isEmpty)
		return;

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

		SetPicture(GetPathToPictureAtPictureBox());
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

		SetPicture(GetPathToPictureAtPictureBox());
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
	if (ViewMode == PictureViewMode::NoPictureFromDir)
		return;

	String^ pathToExplorer = "\"C:\\Windows\\explorer.exe ";
	String^ currentDirectory = Path::GetDirectoryName(GetPathToPictureAtPictureBox());

	array<wchar_t>^ fullPathWChar = (pathToExplorer + currentDirectory)->ToCharArray();

	std::unique_ptr<char[]> fullPathChar(new char[fullPathWChar->Length + 1] {});

	for (int i = 0; i < fullPathWChar->Length; i++)
	{
		fullPathChar[i] = static_cast<char>(fullPathWChar[i]);
	}
	fullPathChar[fullPathWChar->Length] = '\0';

	system(fullPathChar.get());
}

void PhotoViewer::MainForm::CopyNameOfCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewMode == PictureViewMode::NoPictureFromDir)
		return;

	Clipboard::SetText(Path::GetFileNameWithoutExtension(GetPathToPictureAtPictureBox()));
}

void PhotoViewer::MainForm::AboutPhotoViewerToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	AboutPVForm aboutPhotoViewer;
	Color FontColor = (this->BackColor.Name == "DimGray") ? Color::White : Color::Black;

	aboutPhotoViewer.SetColorForm(this->BackColor, FontColor);
	aboutPhotoViewer.ShowDialog();
}

void PhotoViewer::MainForm::timer1_Tick(System::Object^ sender, System::EventArgs^ e)
{
	OpenPictureFromExplorerTimer();
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
	OnePictureInCurrentArray = IsOnePictureInArray();
	SetVisibilityButtons(!OnePictureInCurrentArray);
}

void PhotoViewer::MainForm::SaveFavoritePicturesPaths()
{
	List<String^> paths(FavoritePictures.Count);

	for (int i = 0; i < FavoritePictures.Count; i++)
	{
		paths.Add(FavoritePictures[i]->ToString());
	}

	File::WriteAllLines(PATH_FAVORITE_PICTURES, % paths);
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

	changeFontToolStripMenuItem->BackColor = BackColor;
	changeFontToolStripMenuItem->ForeColor = ForeColor;

	resetFontToolStripMenuItem->BackColor = BackColor;
	resetFontToolStripMenuItem->ForeColor = ForeColor;

	aboutPhotoViewerToolStripMenuItem->BackColor = BackColor;
	aboutPhotoViewerToolStripMenuItem->ForeColor = ForeColor;

	//TooStripMenu
	FileToolStripMenuItem->ForeColor = ForeColor;
	favoritePicturesToolStripMenuItem->ForeColor = ForeColor;
	settingsToolStripMenuItem->ForeColor = ForeColor;

	bNextPicture->ForeColor = ForeColorButtons;
	bPreviousPicture->ForeColor = ForeColorButtons;

	//empty dir
	empty_dir->ForeColor = ForeColor;

	//Open Menu
	openToolStripMenuItem->BackColor = BackColor;
	openToolStripMenuItem->ForeColor = ForeColor;
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
		String^ currentPicture = GetPathToPictureAtPictureBox();
		if (!IsThisPictureFavorite(currentPicture))
		{
			FavoritePictures.Add(currentPicture);
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

String^ PhotoViewer::MainForm::GetPathToPictureAtPictureBox()
{
	if (ViewMode == PictureViewMode::FromDirectory)
	{
		return Pictures[IndexCurrentPicture]->ToString();
	}
	else
	{
		return FavoritePictures[IndexFavoritePicture]->ToString();
	}
}

void PhotoViewer::MainForm::ShowToolMenuForFavoriteMode(bool Value)
{
	removePictureFromFavoriteToolStripMenuItem->Visible = Value;
	exitFromFavoriteModeToolStripMenuItem->Visible = Value;
}

void PhotoViewer::MainForm::SwitchToFavoritePicturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (FavoritePictures.Count > 0)
	{
		if (ViewMode == PictureViewMode::NoPictureFromDir)
		{
			empty_dir->Visible = false;
		}

		ViewMode = PictureViewMode::FromFavoritePictures;

		ShowToolMenuForFavoriteMode(true);

		SetUpButtons();
		SetPicture(GetPathToPictureAtPictureBox());
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
		//FavoritePictures.Count - 1 == end of the array
		if (IndexFavoritePicture == FavoritePictures.Count - 1)
		{
			FavoritePictures.RemoveAt(IndexFavoritePicture);
			IndexFavoritePicture = 0;
		}
		else
		{
			FavoritePictures.RemoveAt(IndexFavoritePicture);
		}

		SetUpButtons();
		SetPicture(GetPathToPictureAtPictureBox());
	}
}

System::Void PhotoViewer::MainForm::ExitFromFavoriteModeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (NoPictureMainDir)
	{
		empty_dir->Visible = true;
		PictureBox->Image = nullptr;
		ViewMode = PictureViewMode::NoPictureFromDir;
		ShowToolMenuForFavoriteMode(false);
		SetVisibilityButtons(false);
		this->Text = "Photo-Viewer";
		return;
	}

	ViewMode = PictureViewMode::FromDirectory;
	SetPicture(GetPathToPictureAtPictureBox());

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
	if (ViewMode == PictureViewMode::NoPictureFromDir)
		return;

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
	FontDialog.Font = FileToolStripMenuItem->Font;
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

void PhotoViewer::MainForm::ResetFontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetUserFont(% System::Drawing::Font("Segoe UI", 9));
}