#pragma once

namespace PhotoViewer
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	private:
		enum class PictureViewMode
		{
			FromDirectory,
			FromFavoritePictures,
			NoPictureFromDir
		};
	public:
#ifdef _DEBUG
		String^ DIRECTORY_SETTINGS = R"(D:\Settings)";
		String^ PATH_LAST_WINDOW_SIZE = R"(D:\Settings\LastWindowSize.txt)";
		String^ PATH_LAST_WINDOW_LOCATION = R"(D:\Settings\LastWindowLocation.txt)";
		String^ PATH_LAST_WINDOW_STATE = R"(D:\Settings\LastWindowState.txt)";
		String^ PATH_FAVORITE_PICTURES = R"(D:\Settings\FavoritePictures.txt)";
		String^ PATH_FONT = R"(D:\Settings\Font.txt)";
		String^ PATH_SIZE_FONT = R"(D:\Settings\SizeFont.txt)";
		String^ PATH_WINDOW_COLOR = R"(D:\Settings\WindowColor.txt)";

#endif // _DEBUG

#ifndef _DEBUG
		String^ DIRECTORY_SETTINGS = R"(C:\ProgramData\Photo-Viewer)";
		String^ PATH_LAST_WINDOW_SIZE = R"(C:\ProgramData\Photo-Viewer\LastWindowSize.txt)";
		String^ PATH_LAST_WINDOW_LOCATION = R"(C:\ProgramData\Photo-Viewer\LastWindowLocation.txt)";
		String^ PATH_LAST_WINDOW_STATE = R"(C:\ProgramData\Photo-Viewer\LastWindowState.txt)";
		String^ PATH_FAVORITE_PICTURES = R"(C:\ProgramData\Photo-Viewer\FavoritePictures.txt)";
		String^ PATH_FONT = R"(C:\ProgramData\Photo-Viewer\Font.txt)";
		String^ PATH_SIZE_FONT = R"(C:\ProgramData\Photo-Viewer\SizeFont.txt)";
		String^ PATH_WINDOW_COLOR = R"(C:\ProgramData\Photo-Viewer\WindowColor.txt)";
#endif // !_DEBUG


		ArrayList Pictures;
		ArrayList FavoritePictures;

		int IndexCurrentPicture = 0;
		int IndexFavoritePicture = 0;
		int IndexLastPicture;

		const int INDEX_FIRST_PICTURE = 0;
		bool OnePictureInCurrentArray = false;

		bool IsFullView = false;
		bool NoPictureMainDir = false;
		FormWindowState WindowStateBeforeFullView;
		PictureViewMode ViewMode = PictureViewMode::FromDirectory;

	public:
		MainForm(String^ directoryToFirstPhoto);
		void SetUpPhotoViewer(String^ pathToPicture);
		void OpenPictureFromExplorerTimer();
		void SortFiles(array<String^>^ AllFiles);
		void FindOutIndexOpenedPicture(String^ pathToOpenedPicture);
		void SettingUpPictureBox();

		void SetUpWindowForm();
		void SetUpLastWindowSize();
		void SetUpLastWindowLocation();
		void SetUpLastWindowState();
		void SetUpWindowColor();
		void SetUpUserFont();
		void SetUserFont(System::Drawing::Font^ userFont);
		void InitializeFavoritePictures();

		void SetVisibilityButtons(bool visible);
		array<String^>^ GetFilesCurrentDirectory(String^ directory);
		static bool IsCorrectExtension(String^ extension);
		void CheckFavoritePicturesOnExist();
		void SetPicture(String^ pathToPicture);
		void SetNewTitle(String^ newTitle);
		void InitializeDialog(OpenFileDialog^ fileDialog);

		~MainForm();
		void SaveSettingsForm();
		void SaveLastWindowSize();
		void SaveLastWindowLocation();
		void SaveLastWindowState();
		void SaveWindowColor();
		void SaveUserFont();

		void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);
		void SwitchPicture(int rangeOfArray, int defaultValue, int changedIndex);
		bool IsOnePictureInArray();
		void SetUpButtons();
		void SaveFavoritePicturesPaths();
		void ShowToolMenuForFavoriteMode(bool visible);
		void SetColorForm(Color backColor, Color foreColor, Color colorMenuStrip, Color foreColorButtons);
		bool IsThisPictureFavorite(String^ currentPicture);
		String^ GetPathToPictureAtPictureBox();

		void SavePictureLikeFavoriteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void SwitchToFavoritePicturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void RemovePictureFromFavoriteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void ExitFromFavoriteModeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void DarkToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void LightToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void FullViewToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void ExitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void ChangeFontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void ResetFontToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void CopyCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void bNextPicture_Click(System::Object^ sender, System::EventArgs^ e);
		void bPreviousPicture_Click(System::Object^ sender, System::EventArgs^ e);
		void OpenDirectoryCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void CopyNameOfCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void AboutPhotoViewerToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void TimerExplorer_Tick(System::Object^ sender, System::EventArgs^ e);
		void ToolMenu_OpenPictureFromExplorerInAnyTime(System::Object^ sender, System::EventArgs^ e);


	private: System::Windows::Forms::PictureBox^ PictureBox;
	private: System::Windows::Forms::SplitContainer^ SplitContainer;
	private: System::Windows::Forms::SplitContainer^ SplitContainer2;
	private: System::Windows::Forms::Button^ bNextPicture;
	private: System::Windows::Forms::Button^ bPreviousPicture;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ FileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ CopyCurrentPictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ OpenDirectoryCurrentPictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ CopyNameOfCurrentPictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ FavoritePicturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SavePictureLikeFavoriteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SwitchToFavoritePicturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ RemovePictureFromFavoriteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ExitFromFavoriteModeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ SettingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ThemeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ LightToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ DarkToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ FullViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ExitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ChangeFontToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ResetFontToolStripMenuItem;
	private: System::Windows::Forms::Timer^ TimerOpeningExplorer;
	private: System::Windows::Forms::Label^ Empty_dir;
	private: System::Windows::Forms::ToolStripMenuItem^ OpenToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ AboutPhotoViewerToolStripMenuItem;
#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			   this->SplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			   this->Empty_dir = (gcnew System::Windows::Forms::Label());
			   this->PictureBox = (gcnew System::Windows::Forms::PictureBox());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->CopyCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->OpenDirectoryCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->CopyNameOfCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->FullViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->ExitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->FavoritePicturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->SavePictureLikeFavoriteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->SwitchToFavoritePicturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->RemovePictureFromFavoriteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->ExitFromFavoriteModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->SettingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->ThemeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->LightToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->DarkToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->ChangeFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->ResetFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->AboutPhotoViewerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->OpenToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->SplitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			   this->bNextPicture = (gcnew System::Windows::Forms::Button());
			   this->bPreviousPicture = (gcnew System::Windows::Forms::Button());
			   this->TimerOpeningExplorer = (gcnew System::Windows::Forms::Timer(this->components));
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer))->BeginInit();
			   this->SplitContainer->Panel1->SuspendLayout();
			   this->SplitContainer->Panel2->SuspendLayout();
			   this->SplitContainer->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureBox))->BeginInit();
			   this->menuStrip1->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer2))->BeginInit();
			   this->SplitContainer2->Panel1->SuspendLayout();
			   this->SplitContainer2->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // SplitContainer
			   // 
			   this->SplitContainer->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->SplitContainer->IsSplitterFixed = true;
			   this->SplitContainer->Location = System::Drawing::Point(0, 0);
			   this->SplitContainer->Name = L"SplitContainer";
			   this->SplitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			   // 
			   // SplitContainer.Panel1
			   // 
			   this->SplitContainer->Panel1->Controls->Add(this->Empty_dir);
			   this->SplitContainer->Panel1->Controls->Add(this->PictureBox);
			   this->SplitContainer->Panel1->Controls->Add(this->menuStrip1);
			   // 
			   // SplitContainer.Panel2
			   // 
			   this->SplitContainer->Panel2->Controls->Add(this->SplitContainer2);
			   this->SplitContainer->Size = System::Drawing::Size(334, 365);
			   this->SplitContainer->SplitterDistance = 318;
			   this->SplitContainer->TabIndex = 0;
			   this->SplitContainer->TabStop = false;
			   // 
			   // Empty_dir
			   // 
			   this->Empty_dir->Font = (gcnew System::Drawing::Font(L"Arial Black", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->Empty_dir->Location = System::Drawing::Point(3, 40);
			   this->Empty_dir->Name = L"Empty_dir";
			   this->Empty_dir->Size = System::Drawing::Size(319, 120);
			   this->Empty_dir->TabIndex = 2;
			   this->Empty_dir->Text = L"To view picture use button \"Open\" to choose your picture from explorer\r\n\r\nAlso yo"
				   L"u can switch to favorite pictures";
			   this->Empty_dir->Visible = false;
			   // 
			   // PictureBox
			   // 
			   this->PictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->PictureBox->Location = System::Drawing::Point(0, 25);
			   this->PictureBox->Name = L"PictureBox";
			   this->PictureBox->Size = System::Drawing::Size(334, 293);
			   this->PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->PictureBox->TabIndex = 0;
			   this->PictureBox->TabStop = false;
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				   this->FileToolStripMenuItem,
					   this->FavoritePicturesToolStripMenuItem, this->SettingsToolStripMenuItem, this->OpenToolStripMenuItem
			   });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(334, 25);
			   this->menuStrip1->TabIndex = 1;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // FileToolStripMenuItem
			   // 
			   this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				   this->CopyCurrentPictureToolStripMenuItem,
					   this->OpenDirectoryCurrentPictureToolStripMenuItem, this->CopyNameOfCurrentPictureToolStripMenuItem, this->FullViewToolStripMenuItem,
					   this->ExitToolStripMenuItem
			   });
			   this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			   this->FileToolStripMenuItem->Size = System::Drawing::Size(41, 21);
			   this->FileToolStripMenuItem->Text = L"File";
			   // 
			   // CopyCurrentPictureToolStripMenuItem
			   // 
			   this->CopyCurrentPictureToolStripMenuItem->Name = L"CopyCurrentPictureToolStripMenuItem";
			   this->CopyCurrentPictureToolStripMenuItem->ShortcutKeyDisplayString = L"";
			   this->CopyCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			   this->CopyCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(342, 22);
			   this->CopyCurrentPictureToolStripMenuItem->Text = L"Copy current picture";
			   this->CopyCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::CopyCurrentPictureToolStripMenuItem_Click);
			   // 
			   // OpenDirectoryCurrentPictureToolStripMenuItem
			   // 
			   this->OpenDirectoryCurrentPictureToolStripMenuItem->Name = L"OpenDirectoryCurrentPictureToolStripMenuItem";
			   this->OpenDirectoryCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				   | System::Windows::Forms::Keys::F10));
			   this->OpenDirectoryCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(342, 22);
			   this->OpenDirectoryCurrentPictureToolStripMenuItem->Text = L"Open directory current picture";
			   this->OpenDirectoryCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::OpenDirectoryCurrentPictureToolStripMenuItem_Click);
			   // 
			   // CopyNameOfCurrentPictureToolStripMenuItem
			   // 
			   this->CopyNameOfCurrentPictureToolStripMenuItem->Name = L"CopyNameOfCurrentPictureToolStripMenuItem";
			   this->CopyNameOfCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			   this->CopyNameOfCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(342, 22);
			   this->CopyNameOfCurrentPictureToolStripMenuItem->Text = L"Copy name of current picture";
			   this->CopyNameOfCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::CopyNameOfCurrentPictureToolStripMenuItem_Click);
			   // 
			   // FullViewToolStripMenuItem
			   // 
			   this->FullViewToolStripMenuItem->Name = L"FullViewToolStripMenuItem";
			   this->FullViewToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F11;
			   this->FullViewToolStripMenuItem->Size = System::Drawing::Size(342, 22);
			   this->FullViewToolStripMenuItem->Text = L"Full View";
			   this->FullViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::FullViewToolStripMenuItem_Click);
			   // 
			   // ExitToolStripMenuItem
			   // 
			   this->ExitToolStripMenuItem->Name = L"ExitToolStripMenuItem";
			   this->ExitToolStripMenuItem->ShortcutKeyDisplayString = L"";
			   this->ExitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::W));
			   this->ExitToolStripMenuItem->Size = System::Drawing::Size(342, 22);
			   this->ExitToolStripMenuItem->Text = L"Exit";
			   this->ExitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ExitToolStripMenuItem_Click);
			   // 
			   // FavoritePicturesToolStripMenuItem
			   // 
			   this->FavoritePicturesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				   this->SavePictureLikeFavoriteToolStripMenuItem,
					   this->SwitchToFavoritePicturesToolStripMenuItem, this->RemovePictureFromFavoriteToolStripMenuItem, this->ExitFromFavoriteModeToolStripMenuItem
			   });
			   this->FavoritePicturesToolStripMenuItem->Name = L"FavoritePicturesToolStripMenuItem";
			   this->FavoritePicturesToolStripMenuItem->Size = System::Drawing::Size(117, 21);
			   this->FavoritePicturesToolStripMenuItem->Text = L"Favorite Pictures";
			   // 
			   // SavePictureLikeFavoriteToolStripMenuItem
			   // 
			   this->SavePictureLikeFavoriteToolStripMenuItem->Name = L"SavePictureLikeFavoriteToolStripMenuItem";
			   this->SavePictureLikeFavoriteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			   this->SavePictureLikeFavoriteToolStripMenuItem->Size = System::Drawing::Size(274, 22);
			   this->SavePictureLikeFavoriteToolStripMenuItem->Text = L"Save picture like favorite";
			   this->SavePictureLikeFavoriteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::SavePictureLikeFavoriteToolStripMenuItem_Click);
			   // 
			   // SwitchToFavoritePicturesToolStripMenuItem
			   // 
			   this->SwitchToFavoritePicturesToolStripMenuItem->Name = L"SwitchToFavoritePicturesToolStripMenuItem";
			   this->SwitchToFavoritePicturesToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
			   this->SwitchToFavoritePicturesToolStripMenuItem->Size = System::Drawing::Size(274, 22);
			   this->SwitchToFavoritePicturesToolStripMenuItem->Text = L"Switch to favorite pictures";
			   this->SwitchToFavoritePicturesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::SwitchToFavoritePicturesToolStripMenuItem_Click);
			   // 
			   // RemovePictureFromFavoriteToolStripMenuItem
			   // 
			   this->RemovePictureFromFavoriteToolStripMenuItem->Name = L"RemovePictureFromFavoriteToolStripMenuItem";
			   this->RemovePictureFromFavoriteToolStripMenuItem->ShortcutKeyDisplayString = L"";
			   this->RemovePictureFromFavoriteToolStripMenuItem->Size = System::Drawing::Size(274, 22);
			   this->RemovePictureFromFavoriteToolStripMenuItem->Text = L"Remove picture from favorite";
			   this->RemovePictureFromFavoriteToolStripMenuItem->Visible = false;
			   this->RemovePictureFromFavoriteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::RemovePictureFromFavoriteToolStripMenuItem_Click);
			   // 
			   // ExitFromFavoriteModeToolStripMenuItem
			   // 
			   this->ExitFromFavoriteModeToolStripMenuItem->Name = L"ExitFromFavoriteModeToolStripMenuItem";
			   this->ExitFromFavoriteModeToolStripMenuItem->Size = System::Drawing::Size(274, 22);
			   this->ExitFromFavoriteModeToolStripMenuItem->Text = L"Exit from favorite mode";
			   this->ExitFromFavoriteModeToolStripMenuItem->Visible = false;
			   this->ExitFromFavoriteModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ExitFromFavoriteModeToolStripMenuItem_Click);
			   // 
			   // SettingsToolStripMenuItem
			   // 
			   this->SettingsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				   this->ThemeToolStripMenuItem,
					   this->ChangeFontToolStripMenuItem, this->ResetFontToolStripMenuItem, this->AboutPhotoViewerToolStripMenuItem
			   });
			   this->SettingsToolStripMenuItem->Name = L"SettingsToolStripMenuItem";
			   this->SettingsToolStripMenuItem->Size = System::Drawing::Size(68, 21);
			   this->SettingsToolStripMenuItem->Text = L"Settings";
			   // 
			   // ThemeToolStripMenuItem
			   // 
			   this->ThemeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->LightToolStripMenuItem,
					   this->DarkToolStripMenuItem
			   });
			   this->ThemeToolStripMenuItem->Name = L"ThemeToolStripMenuItem";
			   this->ThemeToolStripMenuItem->Size = System::Drawing::Size(185, 22);
			   this->ThemeToolStripMenuItem->Text = L"Theme";
			   // 
			   // LightToolStripMenuItem
			   // 
			   this->LightToolStripMenuItem->Checked = true;
			   this->LightToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			   this->LightToolStripMenuItem->Name = L"LightToolStripMenuItem";
			   this->LightToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->LightToolStripMenuItem->Text = L"Light";
			   this->LightToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::LightToolStripMenuItem_Click);
			   // 
			   // DarkToolStripMenuItem
			   // 
			   this->DarkToolStripMenuItem->Name = L"DarkToolStripMenuItem";
			   this->DarkToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->DarkToolStripMenuItem->Text = L"Dark";
			   this->DarkToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::DarkToolStripMenuItem_Click);
			   // 
			   // ChangeFontToolStripMenuItem
			   // 
			   this->ChangeFontToolStripMenuItem->Name = L"ChangeFontToolStripMenuItem";
			   this->ChangeFontToolStripMenuItem->Size = System::Drawing::Size(185, 22);
			   this->ChangeFontToolStripMenuItem->Text = L"Change Font";
			   this->ChangeFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ChangeFontToolStripMenuItem_Click);
			   // 
			   // ResetFontToolStripMenuItem
			   // 
			   this->ResetFontToolStripMenuItem->Name = L"ResetFontToolStripMenuItem";
			   this->ResetFontToolStripMenuItem->Size = System::Drawing::Size(185, 22);
			   this->ResetFontToolStripMenuItem->Text = L"Reset Font";
			   this->ResetFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ResetFontToolStripMenuItem_Click);
			   // 
			   // AboutPhotoViewerToolStripMenuItem
			   // 
			   this->AboutPhotoViewerToolStripMenuItem->Name = L"AboutPhotoViewerToolStripMenuItem";
			   this->AboutPhotoViewerToolStripMenuItem->Size = System::Drawing::Size(185, 22);
			   this->AboutPhotoViewerToolStripMenuItem->Text = L"About Photo-Viewer";
			   this->AboutPhotoViewerToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::AboutPhotoViewerToolStripMenuItem_Click);
			   // 
			   // OpenToolStripMenuItem
			   // 
			   this->OpenToolStripMenuItem->Name = L"OpenToolStripMenuItem";
			   this->OpenToolStripMenuItem->Size = System::Drawing::Size(48, 21);
			   this->OpenToolStripMenuItem->Text = L"Open";
			   this->OpenToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ToolMenu_OpenPictureFromExplorerInAnyTime);
			   // 
			   // SplitContainer2
			   // 
			   this->SplitContainer2->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->SplitContainer2->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			   this->SplitContainer2->Location = System::Drawing::Point(0, 0);
			   this->SplitContainer2->Name = L"SplitContainer2";
			   // 
			   // SplitContainer2.Panel1
			   // 
			   this->SplitContainer2->Panel1->Controls->Add(this->bNextPicture);
			   this->SplitContainer2->Panel1->Controls->Add(this->bPreviousPicture);
			   this->SplitContainer2->Panel2Collapsed = true;
			   this->SplitContainer2->Size = System::Drawing::Size(334, 43);
			   this->SplitContainer2->SplitterDistance = 28;
			   this->SplitContainer2->SplitterWidth = 1;
			   this->SplitContainer2->TabIndex = 0;
			   this->SplitContainer2->TabStop = false;
			   // 
			   // bNextPicture
			   // 
			   this->bNextPicture->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bNextPicture->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->bNextPicture->Location = System::Drawing::Point(176, 14);
			   this->bNextPicture->Name = L"bNextPicture";
			   this->bNextPicture->Size = System::Drawing::Size(75, 23);
			   this->bNextPicture->TabIndex = 1;
			   this->bNextPicture->Text = L"->";
			   this->bNextPicture->UseVisualStyleBackColor = true;
			   this->bNextPicture->Click += gcnew System::EventHandler(this, &MainForm::bNextPicture_Click);
			   // 
			   // bPreviousPicture
			   // 
			   this->bPreviousPicture->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bPreviousPicture->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->bPreviousPicture->Location = System::Drawing::Point(68, 14);
			   this->bPreviousPicture->Name = L"bPreviousPicture";
			   this->bPreviousPicture->Size = System::Drawing::Size(75, 23);
			   this->bPreviousPicture->TabIndex = 1;
			   this->bPreviousPicture->Text = L"<-";
			   this->bPreviousPicture->UseVisualStyleBackColor = true;
			   this->bPreviousPicture->Click += gcnew System::EventHandler(this, &MainForm::bPreviousPicture_Click);
			   // 
			   // TimerOpeningExplorer
			   // 
			   this->TimerOpeningExplorer->Interval = 500;
			   this->TimerOpeningExplorer->Tick += gcnew System::EventHandler(this, &MainForm::TimerExplorer_Tick);
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(334, 365);
			   this->Controls->Add(this->SplitContainer);
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->KeyPreview = true;
			   this->MainMenuStrip = this->menuStrip1;
			   this->MinimumSize = System::Drawing::Size(350, 404);
			   this->Name = L"MainForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			   this->Text = L"Photo-Viewer";
			   this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MainForm::MainForm_KeyDown);
			   this->SplitContainer->Panel1->ResumeLayout(false);
			   this->SplitContainer->Panel1->PerformLayout();
			   this->SplitContainer->Panel2->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer))->EndInit();
			   this->SplitContainer->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureBox))->EndInit();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->SplitContainer2->Panel1->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer2))->EndInit();
			   this->SplitContainer2->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion
	};
}
