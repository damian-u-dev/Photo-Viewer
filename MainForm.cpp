#include "MainForm.h"
#include "About PV Form.h"
#include <memory>


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
		TimerOpeningExplorer->Enabled = true;
	}
	else
	{
		SetUpPhotoViewer(pathToOpenedPicture);
	}
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

void PhotoViewer::MainForm::SetVisibilityButtons(bool visible)
{
	bNextPicture->Visible = visible;
	bPreviousPicture->Visible = visible;
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
	refFileDialog->Filter = "Image files (*.png;*jpg;*jpeg;*gif;*ico)|*.png;*.jpg;*.jpeg;*.gif;*.ico";
}

void PhotoViewer::MainForm::OpenPictureFromExplorerTimer()
{
	TimerOpeningExplorer->Enabled = false;

	OpenFileDialog fileDialog;
	InitializeDialog(% fileDialog);

	auto dialogResult = fileDialog.ShowDialog();

	if (dialogResult == Windows::Forms::DialogResult::OK)
	{
		ViewMode = PictureViewMode::FromDirectory;
		SetUpPhotoViewer(fileDialog.FileName);
	}
	else
	{
		ViewMode = PictureViewMode::NoPictureFromDir;
		NoPictureMainDir = true;

		Empty_dir->Visible = true;
		FileToolStripMenuItem->Visible = false;
		SavePictureLikeFavoriteToolStripMenuItem->Visible = false;

		InitializeFavoritePictures();
	}
}

void PhotoViewer::MainForm::ToolMenu_OpenPictureFromExplorerInAnyTime(System::Object^ sender, System::EventArgs^ e)
{
	OpenFileDialog fileDialog;
	InitializeDialog(% fileDialog);

	auto dialogResult = fileDialog.ShowDialog();
	if (dialogResult == Windows::Forms::DialogResult::OK)
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

			Empty_dir->Visible = false;
			FileToolStripMenuItem->Visible = true;
			SavePictureLikeFavoriteToolStripMenuItem->Visible = true;
		}

		ViewMode = PictureViewMode::FromDirectory;
		SettingUpPictureBox();
		SetUpButtons();
	}
}

void PhotoViewer::MainForm::Delegate_SlideShowTimer()
{
	bNextPicture_Click(nullptr, nullptr);
}

void PhotoViewer::MainForm::ReloadTimeSlideShow()
{
	timerSlideShow->Stop();
	timerSlideShow->Start();
}

void PhotoViewer::MainForm::ResetAction()
{
	Action = Action::NO_ACTION;
}

bool PhotoViewer::MainForm::IsAction()
{
	return Action != Action::NO_ACTION;
}

void PhotoViewer::MainForm::MessageAlreadyAction(String^ reason)
{
	String^ Message = "You can't do this, you turned on: ";
	Message += reason;
	MessageBox::Show(Message, "Reason");
}

void PhotoViewer::MainForm::ResetCheckboxesSlideShow()
{
	One_secondToolStripMenuItem->Checked = false;
	Two_secondsToolStripMenuItem1->Checked = false;
	Three_secondsToolStripMenuItem1->Checked = false;
	Four_secondsToolStripMenuItem1->Checked = false;
	Five_secondsToolStripMenuItem2->Checked = false;
	Six_secondsToolStripMenuItem3->Checked = false;
	Seven_secondsToolStripMenuItem4->Checked = false;
	Ten_secondsToolStripMenuItem5->Checked = false;
	Twenty_secondsToolStripMenuItem6->Checked = false;
}

System::Void PhotoViewer::MainForm::slideShowToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->slideShowToolStripMenuItem->Checked = !this->slideShowToolStripMenuItem->Checked;

	if (this->slideShowToolStripMenuItem->Checked)
	{
		timerSlideShow->Start();
		Action = Action::SlideShow;
	}
	else
	{
		timerSlideShow->Stop();
		ResetAction();
	}
}

System::Void PhotoViewer::MainForm::timerSlideShow_Tick(System::Object^ sender, System::EventArgs^ e)
{
	Delegate_SlideShowTimer();
}

System::Void PhotoViewer::MainForm::OnesecondToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	return System::Void();
}

System::Void PhotoViewer::MainForm::TwosecondsToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Two_secondsToolStripMenuItem1->Checked = true;
	timerSlideShow->Interval = 2000;
}

System::Void PhotoViewer::MainForm::ThreesecondsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Three_secondsToolStripMenuItem1->Checked = true;
	timerSlideShow->Interval = 3000;
}

System::Void PhotoViewer::MainForm::FoursecondsToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Four_secondsToolStripMenuItem1->Checked = true;
	timerSlideShow->Interval = 4000;
}

System::Void PhotoViewer::MainForm::FivesecondsToolStripMenuItem2_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Five_secondsToolStripMenuItem2->Checked = true;
	timerSlideShow->Interval = 5000;
}

System::Void PhotoViewer::MainForm::SixsecondsToolStripMenuItem3_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Six_secondsToolStripMenuItem3->Checked = true;
	timerSlideShow->Interval = 6000;
}

System::Void PhotoViewer::MainForm::SevensecondsToolStripMenuItem4_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Seven_secondsToolStripMenuItem4->Checked = true;
	timerSlideShow->Interval = 7000;
}

System::Void PhotoViewer::MainForm::TensecondsToolStripMenuItem5_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Ten_secondsToolStripMenuItem5->Checked = true;
	timerSlideShow->Interval = 10000;
}

System::Void PhotoViewer::MainForm::TwentysecondsToolStripMenuItem6_Click(System::Object^ sender, System::EventArgs^ e)
{
	ResetCheckboxesSlideShow();
	Twenty_secondsToolStripMenuItem6->Checked = true;
	timerSlideShow->Interval = 20000;

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
		LightToolStripMenuItem_Click(nullptr, nullptr);
		return;
	}

	String^ lastColor = File::ReadAllText(PATH_WINDOW_COLOR);

	if (lastColor == Color::DimGray.Name)
	{
		DarkToolStripMenuItem_Click(nullptr, nullptr);
	}
	else
	{
		LightToolStripMenuItem_Click(nullptr, nullptr);
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
	return (extension->EndsWith(".jpeg") || extension->EndsWith(".png")
		|| extension->EndsWith(".jpg") || extension->EndsWith(".gif"))
		|| extension->EndsWith(".ico");

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

void PhotoViewer::MainForm::SaveFavoritePicturesPaths()
{
	List<String^> paths(FavoritePictures.Count);

	for (int i = 0; i < FavoritePictures.Count; i++)
	{
		paths.Add(FavoritePictures[i]->ToString());
	}

	File::WriteAllLines(PATH_FAVORITE_PICTURES, % paths);
}

void PhotoViewer::MainForm::CopyCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (ViewMode == PictureViewMode::NoPictureFromDir)
		return;

	Clipboard::SetImage(PictureBox->Image);
}

void PhotoViewer::MainForm::MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{
	bool isEmpty = (ViewMode == PictureViewMode::NoPictureFromDir);
	if (isEmpty)
		return;

	if (e->KeyCode == Keys::A && !OnePictureInCurrentArray)
	{
		if (Action == Action::SlideShow)
		{
			ReloadTimeSlideShow();
		}
		bPreviousPicture_Click(nullptr, nullptr);
	}
	if (e->KeyCode == Keys::D && !OnePictureInCurrentArray)
	{
		if (Action == Action::SlideShow)
		{
			ReloadTimeSlideShow();
		}
		bNextPicture_Click(nullptr, nullptr);
	}
	if (e->KeyCode == Keys::Escape && IsFullView)
	{
		FullViewToolStripMenuItem_Click(nullptr, nullptr);
	}
}

void PhotoViewer::MainForm::SwitchPicture(int rangeOfArray, int defaultValue, int changedIndex)
{
	if (ViewMode == PictureViewMode::FromDirectory)
	{
		if (IndexCurrentPicture == rangeOfArray)
		{
			IndexCurrentPicture = defaultValue;
		}
		else
		{
			IndexCurrentPicture = changedIndex;
		}
	}
	else
	{
		if (IndexFavoritePicture == rangeOfArray)
		{
			IndexFavoritePicture = defaultValue;
		}
		else
		{
			IndexFavoritePicture = changedIndex;
		}

	}

	SetPicture(GetPathToPictureAtPictureBox());
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

void PhotoViewer::MainForm::TimerExplorer_Tick(System::Object^ sender, System::EventArgs^ e)
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

void PhotoViewer::MainForm::SetColorForm(Color backColor, Color foreColor, Color colorMenuStrip, Color foreColorButtons)
{
	this->BackColor = backColor;

	bNextPicture->BackColor = backColor;
	bPreviousPicture->BackColor = backColor;
	menuStrip1->BackColor = colorMenuStrip;

	//FileToolStrip
	CopyCurrentPictureToolStripMenuItem->BackColor = backColor;
	CopyCurrentPictureToolStripMenuItem->ForeColor = foreColor;

	OpenDirectoryCurrentPictureToolStripMenuItem->BackColor = backColor;
	OpenDirectoryCurrentPictureToolStripMenuItem->ForeColor = foreColor;

	FullViewToolStripMenuItem->BackColor = backColor;
	FullViewToolStripMenuItem->ForeColor = foreColor;

	CopyNameOfCurrentPictureToolStripMenuItem->BackColor = backColor;
	CopyNameOfCurrentPictureToolStripMenuItem->ForeColor = foreColor;

	ExitToolStripMenuItem->BackColor = backColor;
	ExitToolStripMenuItem->ForeColor = foreColor;

	slideShowToolStripMenuItem->BackColor = backColor;
	slideShowToolStripMenuItem->ForeColor = foreColor;

	//FavoritePicture toolstrip
	SavePictureLikeFavoriteToolStripMenuItem->BackColor = backColor;
	SavePictureLikeFavoriteToolStripMenuItem->ForeColor = foreColor;

	SwitchToFavoritePicturesToolStripMenuItem->BackColor = backColor;
	SwitchToFavoritePicturesToolStripMenuItem->ForeColor = foreColor;

	RemovePictureFromFavoriteToolStripMenuItem->BackColor = backColor;
	RemovePictureFromFavoriteToolStripMenuItem->ForeColor = foreColor;

	ExitFromFavoriteModeToolStripMenuItem->BackColor = backColor;
	ExitFromFavoriteModeToolStripMenuItem->ForeColor = foreColor;

	//Settings Tool Strip
	ThemeToolStripMenuItem->BackColor = backColor;
	ThemeToolStripMenuItem->ForeColor = foreColor;

	LightToolStripMenuItem->BackColor = backColor;
	LightToolStripMenuItem->ForeColor = foreColor;

	DarkToolStripMenuItem->BackColor = backColor;
	DarkToolStripMenuItem->ForeColor = foreColor;

	ChangeFontToolStripMenuItem->BackColor = backColor;
	ChangeFontToolStripMenuItem->ForeColor = foreColor;

	ResetFontToolStripMenuItem->BackColor = backColor;
	ResetFontToolStripMenuItem->ForeColor = foreColor;

	AboutPhotoViewerToolStripMenuItem->BackColor = backColor;
	AboutPhotoViewerToolStripMenuItem->ForeColor = foreColor;

	//TooStripMenu
	FileToolStripMenuItem->ForeColor = foreColor;
	FavoritePicturesToolStripMenuItem->ForeColor = foreColor;
	SettingsToolStripMenuItem->ForeColor = foreColor;

	bNextPicture->ForeColor = foreColorButtons;
	bPreviousPicture->ForeColor = foreColorButtons;

	//empty dir
	Empty_dir->ForeColor = foreColor;

	//Open Menu
	OpenToolStripMenuItem->BackColor = backColor;
	OpenToolStripMenuItem->ForeColor = foreColor;

	slideShowToolStripMenuItem1->BackColor = backColor;
	slideShowToolStripMenuItem1->ForeColor = foreColor;

	One_secondToolStripMenuItem->BackColor = backColor;
	One_secondToolStripMenuItem->ForeColor = foreColor;

	Two_secondsToolStripMenuItem1->BackColor = backColor;
	Two_secondsToolStripMenuItem1->ForeColor = foreColor;

	Three_secondsToolStripMenuItem1->BackColor = backColor;
	Three_secondsToolStripMenuItem1->ForeColor = foreColor;

	Four_secondsToolStripMenuItem1->BackColor = backColor;
	Four_secondsToolStripMenuItem1->ForeColor = foreColor;

	Five_secondsToolStripMenuItem2->BackColor = backColor;
	Five_secondsToolStripMenuItem2->ForeColor = foreColor;

	Six_secondsToolStripMenuItem3->BackColor = backColor;
	Six_secondsToolStripMenuItem3->ForeColor = foreColor;

	Seven_secondsToolStripMenuItem4->BackColor = backColor;
	Seven_secondsToolStripMenuItem4->ForeColor = foreColor;

	Ten_secondsToolStripMenuItem5->BackColor = backColor;
	Ten_secondsToolStripMenuItem5->ForeColor = foreColor;

	Twenty_secondsToolStripMenuItem6->BackColor = backColor;
	Twenty_secondsToolStripMenuItem6->ForeColor = foreColor;


}

void PhotoViewer::MainForm::SetUserFont(System::Drawing::Font^ userFont)
{
	//File ToolStrip Menu
	FileToolStripMenuItem->Font = userFont;
	CopyCurrentPictureToolStripMenuItem->Font = userFont;
	FullViewToolStripMenuItem->Font = userFont;
	FullViewToolStripMenuItem->Font = userFont;
	ExitToolStripMenuItem->Font = userFont;
	slideShowToolStripMenuItem->Font = userFont;

	//FavoritePictures ToolStripMenuItem
	FavoritePicturesToolStripMenuItem->Font = userFont;
	SavePictureLikeFavoriteToolStripMenuItem->Font = userFont;
	SwitchToFavoritePicturesToolStripMenuItem->Font = userFont;
	RemovePictureFromFavoriteToolStripMenuItem->Font = userFont;
	ExitFromFavoriteModeToolStripMenuItem->Font = userFont;

	//settings ToolStripMenuItem
	SettingsToolStripMenuItem->Font = userFont;
	ThemeToolStripMenuItem->Font = userFont;
	LightToolStripMenuItem->Font = userFont;
	DarkToolStripMenuItem->Font = userFont;
	ChangeFontToolStripMenuItem->Font = userFont;

	slideShowToolStripMenuItem1->Font = userFont;
	One_secondToolStripMenuItem->Font = userFont;
	Two_secondsToolStripMenuItem1->Font = userFont;
	Three_secondsToolStripMenuItem1->Font = userFont;
	Four_secondsToolStripMenuItem1->Font = userFont;
	Five_secondsToolStripMenuItem2->Font = userFont;
	Six_secondsToolStripMenuItem3->Font = userFont;
	Seven_secondsToolStripMenuItem4->Font = userFont;
	Ten_secondsToolStripMenuItem5->Font = userFont;
	Twenty_secondsToolStripMenuItem6->Font = userFont;

	//Open ToolStripMenu
	OpenToolStripMenuItem->Font = userFont;


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

bool PhotoViewer::MainForm::IsThisPictureFavorite(String^ currentPicture)
{
	for (int i = 0; i < FavoritePictures.Count; i++)
	{
		if (FavoritePictures[i]->Equals(currentPicture))
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

void PhotoViewer::MainForm::ShowToolMenuForFavoriteMode(bool visible)
{
	RemovePictureFromFavoriteToolStripMenuItem->Visible = visible;
	ExitFromFavoriteModeToolStripMenuItem->Visible = visible;
}

void PhotoViewer::MainForm::SwitchToFavoritePicturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (IsAction())
	{
		MessageAlreadyAction(Action == Action::SlideShow ? "Slide-Show" : "-");
		return;
	}
	if (FavoritePictures.Count > 0)
	{
		if (ViewMode == PictureViewMode::NoPictureFromDir)
		{
			Empty_dir->Visible = false;
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
	if (IsAction())
	{
		MessageAlreadyAction(Action == Action::SlideShow ? "Slide-Show" : "-");
		return;
	}
	if (NoPictureMainDir)
	{
		Empty_dir->Visible = true;
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
	LightToolStripMenuItem->Checked = false;
	DarkToolStripMenuItem->Checked = true;

	SetColorForm(Color::DimGray, Color::White, Color::DimGray, Color::AntiqueWhite);
}

void PhotoViewer::MainForm::LightToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	LightToolStripMenuItem->Checked = true;
	DarkToolStripMenuItem->Checked = false;

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
	FontDialog fontDialog;
	fontDialog.Font = FileToolStripMenuItem->Font;
	fontDialog.AllowScriptChange = false;
	fontDialog.FontMustExist = true;
	fontDialog.MaxSize = 14;
	fontDialog.ShowColor = false;
	fontDialog.ShowEffects = false;
	fontDialog.ShowHelp = false;


	Windows::Forms::DialogResult dialogResult = fontDialog.ShowDialog();

	if (dialogResult == Windows::Forms::DialogResult::OK)
	{
		SetUserFont(fontDialog.Font);
	}
}

void PhotoViewer::MainForm::ResetFontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	SetUserFont(% System::Drawing::Font("Segoe UI", 9));
}