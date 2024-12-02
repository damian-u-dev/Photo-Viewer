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
		bool NoPicture = false;

		FormWindowState WindowStateBeforeFullView;

		PictureViewMode ViewMode = PictureViewMode::FromDirectory;
	System::Windows::Forms::Timer^ timer1;
	System::Windows::Forms::Label^ empty_dir;
	System::Windows::Forms::ToolStripMenuItem^ aboutPhotoViewerToolStripMenuItem;


	public:
		MainForm(String^ directoryToFirstPhoto);
		void SetUpPhotoViewer(String^ pathToPicture);
		void OpenPictureFromExplorer();
		void SortFiles(array<String^>^ AllFiles);
		void FindOutIndexOpenedPicture(String^ pathToOpenedPicture);
		void SettingUpPictureBox();

		void SetUpWindowForm();
		void SetUpLastWindowSize();
		void SetUpLastWindowLocation();
		void SetUpLastWindowState();
		void SetUpWindowColor();
		void SetUpUserFont();
		void SetUserFont(System::Drawing::Font^ UserFont);
		void InitializeFavoritePictures();

		array<String^>^ GetFilesCurrentDirectory(String^ directory);
		static bool IsCorrectExtension(String^ extension);
		void CheckFavoritePicturesOnExist();
		void SetPicture(String^ PathToPicture);
		void SetNewTitle(String^ NewTitle);

		~MainForm();
		void SaveSettingsForm();
		void SaveLastWindowSize();
		void SaveLastWindowLocation();
		void SaveLastWindowState();
		void SaveWindowColor();
		void SaveUserFont();

		void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		void SwitchPicture(const int lastOrFirstPicture, const int initializeValue, const int addValue);
		bool IsOnePictureInArray();
		void SetUpButtons();
		void SaveFavoritePicturesPaths();
		void ShowToolMenuForFavoriteMode(bool Value);
		void SetColorForm(Color BackColor, Color ForeColor, Color ColorMenuStrip, Color ForeColorButtons);

		bool IsThisPictureFavorite(String^ CurrentPicture);

		String^ GetPathToPictureAtPictureBox();

		void SavePictureLikeFavoriteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void SwitchToFavoritePicturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void RemovePictureFromFavoriteToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void ExitFromFavoriteModeToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void DarkToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
		void lightToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
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
	void timer1_Tick(System::Object^ sender, System::EventArgs^ e);

	private: System::Windows::Forms::PictureBox^ PictureBox;
	private: System::Windows::Forms::SplitContainer^ SplitContainer;
	private: System::Windows::Forms::SplitContainer^ SplitContainer2;
	private: System::Windows::Forms::Button^ bNextPicture;
	private: System::Windows::Forms::Button^ bPreviousPicture;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ FileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ CopyCurrentPictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openDirectoryCurrentPictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ copyNameOfCurrentPictureToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ favoritePicturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ savePictureLikeFavoriteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ switchToFavoritePicturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ removePictureFromFavoriteToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitFromFavoriteModeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ settingsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ themeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ lightToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ darkToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ fullViewToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ changeFontToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ resetFontToolStripMenuItem;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			   this->SplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			   this->empty_dir = (gcnew System::Windows::Forms::Label());
			   this->PictureBox = (gcnew System::Windows::Forms::PictureBox());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->CopyCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openDirectoryCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->copyNameOfCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->fullViewToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->favoritePicturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->savePictureLikeFavoriteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->switchToFavoritePicturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->removePictureFromFavoriteToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->exitFromFavoriteModeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->settingsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->themeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->lightToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->darkToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->changeFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->resetFontToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->aboutPhotoViewerToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->SplitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			   this->bNextPicture = (gcnew System::Windows::Forms::Button());
			   this->bPreviousPicture = (gcnew System::Windows::Forms::Button());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
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
			   this->SplitContainer->Location = System::Drawing::Point(0, 0);
			   this->SplitContainer->Name = L"SplitContainer";
			   this->SplitContainer->Orientation = System::Windows::Forms::Orientation::Horizontal;
			   // 
			   // SplitContainer.Panel1
			   // 
			   this->SplitContainer->Panel1->Controls->Add(this->empty_dir);
			   this->SplitContainer->Panel1->Controls->Add(this->PictureBox);
			   this->SplitContainer->Panel1->Controls->Add(this->menuStrip1);
			   // 
			   // SplitContainer.Panel2
			   // 
			   this->SplitContainer->Panel2->Controls->Add(this->SplitContainer2);
			   this->SplitContainer->Size = System::Drawing::Size(423, 505);
			   this->SplitContainer->SplitterDistance = 440;
			   this->SplitContainer->TabIndex = 0;
			   this->SplitContainer->TabStop = false;
			   // 
			   // empty_dir
			   // 
			   this->empty_dir->Font = (gcnew System::Drawing::Font(L"Arial Black", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->empty_dir->Location = System::Drawing::Point(3, 40);
			   this->empty_dir->Name = L"empty_dir";
			   this->empty_dir->Size = System::Drawing::Size(417, 120);
			   this->empty_dir->TabIndex = 2;
			   this->empty_dir->Text = L"To view picture you need to move a picture from explorer or use button \"Open expl"
				   L"orer to choose the picture\". Also you can switch to favorite pictures";
			   this->empty_dir->Visible = false;
			   // 
			   // PictureBox
			   // 
			   this->PictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->PictureBox->Location = System::Drawing::Point(0, 24);
			   this->PictureBox->Name = L"PictureBox";
			   this->PictureBox->Size = System::Drawing::Size(423, 416);
			   this->PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->PictureBox->TabIndex = 0;
			   this->PictureBox->TabStop = false;
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->FileToolStripMenuItem,
					   this->favoritePicturesToolStripMenuItem, this->settingsToolStripMenuItem
			   });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(423, 24);
			   this->menuStrip1->TabIndex = 1;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // FileToolStripMenuItem
			   // 
			   this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				   this->CopyCurrentPictureToolStripMenuItem,
					   this->openDirectoryCurrentPictureToolStripMenuItem, this->copyNameOfCurrentPictureToolStripMenuItem, this->fullViewToolStripMenuItem,
					   this->exitToolStripMenuItem
			   });
			   this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			   this->FileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			   this->FileToolStripMenuItem->Text = L"File";
			   // 
			   // CopyCurrentPictureToolStripMenuItem
			   // 
			   this->CopyCurrentPictureToolStripMenuItem->Name = L"CopyCurrentPictureToolStripMenuItem";
			   this->CopyCurrentPictureToolStripMenuItem->ShortcutKeyDisplayString = L"";
			   this->CopyCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			   this->CopyCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(318, 22);
			   this->CopyCurrentPictureToolStripMenuItem->Text = L"Copy current picture";
			   this->CopyCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::CopyCurrentPictureToolStripMenuItem_Click);
			   // 
			   // openDirectoryCurrentPictureToolStripMenuItem
			   // 
			   this->openDirectoryCurrentPictureToolStripMenuItem->Name = L"openDirectoryCurrentPictureToolStripMenuItem";
			   this->openDirectoryCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>(((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::Shift)
				   | System::Windows::Forms::Keys::F10));
			   this->openDirectoryCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(318, 22);
			   this->openDirectoryCurrentPictureToolStripMenuItem->Text = L"Open directory current picture";
			   this->openDirectoryCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::OpenDirectoryCurrentPictureToolStripMenuItem_Click);
			   // 
			   // copyNameOfCurrentPictureToolStripMenuItem
			   // 
			   this->copyNameOfCurrentPictureToolStripMenuItem->Name = L"copyNameOfCurrentPictureToolStripMenuItem";
			   this->copyNameOfCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::N));
			   this->copyNameOfCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(318, 22);
			   this->copyNameOfCurrentPictureToolStripMenuItem->Text = L"Copy name of current picture";
			   this->copyNameOfCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::CopyNameOfCurrentPictureToolStripMenuItem_Click);
			   // 
			   // fullViewToolStripMenuItem
			   // 
			   this->fullViewToolStripMenuItem->Name = L"fullViewToolStripMenuItem";
			   this->fullViewToolStripMenuItem->ShortcutKeys = System::Windows::Forms::Keys::F11;
			   this->fullViewToolStripMenuItem->Size = System::Drawing::Size(318, 22);
			   this->fullViewToolStripMenuItem->Text = L"Full View";
			   this->fullViewToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::FullViewToolStripMenuItem_Click);
			   // 
			   // exitToolStripMenuItem
			   // 
			   this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			   this->exitToolStripMenuItem->ShortcutKeyDisplayString = L"";
			   this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::W));
			   this->exitToolStripMenuItem->Size = System::Drawing::Size(318, 22);
			   this->exitToolStripMenuItem->Text = L"Exit";
			   this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ExitToolStripMenuItem_Click);
			   // 
			   // favoritePicturesToolStripMenuItem
			   // 
			   this->favoritePicturesToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				   this->savePictureLikeFavoriteToolStripMenuItem,
					   this->switchToFavoritePicturesToolStripMenuItem, this->removePictureFromFavoriteToolStripMenuItem, this->exitFromFavoriteModeToolStripMenuItem
			   });
			   this->favoritePicturesToolStripMenuItem->Name = L"favoritePicturesToolStripMenuItem";
			   this->favoritePicturesToolStripMenuItem->Size = System::Drawing::Size(106, 20);
			   this->favoritePicturesToolStripMenuItem->Text = L"Favorite Pictures";
			   // 
			   // savePictureLikeFavoriteToolStripMenuItem
			   // 
			   this->savePictureLikeFavoriteToolStripMenuItem->Name = L"savePictureLikeFavoriteToolStripMenuItem";
			   this->savePictureLikeFavoriteToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::S));
			   this->savePictureLikeFavoriteToolStripMenuItem->Size = System::Drawing::Size(251, 22);
			   this->savePictureLikeFavoriteToolStripMenuItem->Text = L"Save picture like favorite";
			   this->savePictureLikeFavoriteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::SavePictureLikeFavoriteToolStripMenuItem_Click);
			   // 
			   // switchToFavoritePicturesToolStripMenuItem
			   // 
			   this->switchToFavoritePicturesToolStripMenuItem->Name = L"switchToFavoritePicturesToolStripMenuItem";
			   this->switchToFavoritePicturesToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F));
			   this->switchToFavoritePicturesToolStripMenuItem->Size = System::Drawing::Size(251, 22);
			   this->switchToFavoritePicturesToolStripMenuItem->Text = L"Switch to favorite pictures";
			   this->switchToFavoritePicturesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::SwitchToFavoritePicturesToolStripMenuItem_Click);
			   // 
			   // removePictureFromFavoriteToolStripMenuItem
			   // 
			   this->removePictureFromFavoriteToolStripMenuItem->Name = L"removePictureFromFavoriteToolStripMenuItem";
			   this->removePictureFromFavoriteToolStripMenuItem->ShortcutKeyDisplayString = L"";
			   this->removePictureFromFavoriteToolStripMenuItem->Size = System::Drawing::Size(251, 22);
			   this->removePictureFromFavoriteToolStripMenuItem->Text = L"Remove picture from favorite";
			   this->removePictureFromFavoriteToolStripMenuItem->Visible = false;
			   this->removePictureFromFavoriteToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::RemovePictureFromFavoriteToolStripMenuItem_Click);
			   // 
			   // exitFromFavoriteModeToolStripMenuItem
			   // 
			   this->exitFromFavoriteModeToolStripMenuItem->Name = L"exitFromFavoriteModeToolStripMenuItem";
			   this->exitFromFavoriteModeToolStripMenuItem->Size = System::Drawing::Size(251, 22);
			   this->exitFromFavoriteModeToolStripMenuItem->Text = L"Exit from favorite mode";
			   this->exitFromFavoriteModeToolStripMenuItem->Visible = false;
			   this->exitFromFavoriteModeToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ExitFromFavoriteModeToolStripMenuItem_Click);
			   // 
			   // settingsToolStripMenuItem
			   // 
			   this->settingsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				   this->themeToolStripMenuItem,
					   this->changeFontToolStripMenuItem, this->resetFontToolStripMenuItem, this->aboutPhotoViewerToolStripMenuItem
			   });
			   this->settingsToolStripMenuItem->Name = L"settingsToolStripMenuItem";
			   this->settingsToolStripMenuItem->Size = System::Drawing::Size(61, 20);
			   this->settingsToolStripMenuItem->Text = L"Settings";
			   // 
			   // themeToolStripMenuItem
			   // 
			   this->themeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->lightToolStripMenuItem,
					   this->darkToolStripMenuItem
			   });
			   this->themeToolStripMenuItem->Name = L"themeToolStripMenuItem";
			   this->themeToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			   this->themeToolStripMenuItem->Text = L"Theme";
			   // 
			   // lightToolStripMenuItem
			   // 
			   this->lightToolStripMenuItem->Checked = true;
			   this->lightToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			   this->lightToolStripMenuItem->Name = L"lightToolStripMenuItem";
			   this->lightToolStripMenuItem->Size = System::Drawing::Size(101, 22);
			   this->lightToolStripMenuItem->Text = L"Light";
			   this->lightToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::lightToolStripMenuItem_Click);
			   // 
			   // darkToolStripMenuItem
			   // 
			   this->darkToolStripMenuItem->Name = L"darkToolStripMenuItem";
			   this->darkToolStripMenuItem->Size = System::Drawing::Size(101, 22);
			   this->darkToolStripMenuItem->Text = L"Dark";
			   this->darkToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::DarkToolStripMenuItem_Click);
			   // 
			   // changeFontToolStripMenuItem
			   // 
			   this->changeFontToolStripMenuItem->Name = L"changeFontToolStripMenuItem";
			   this->changeFontToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			   this->changeFontToolStripMenuItem->Text = L"Change Font";
			   this->changeFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ChangeFontToolStripMenuItem_Click);
			   // 
			   // resetFontToolStripMenuItem
			   // 
			   this->resetFontToolStripMenuItem->Name = L"resetFontToolStripMenuItem";
			   this->resetFontToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			   this->resetFontToolStripMenuItem->Text = L"Reset Font";
			   this->resetFontToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::ResetFontToolStripMenuItem_Click);
			   // 
			   // aboutPhotoViewerToolStripMenuItem
			   // 
			   this->aboutPhotoViewerToolStripMenuItem->Name = L"aboutPhotoViewerToolStripMenuItem";
			   this->aboutPhotoViewerToolStripMenuItem->Size = System::Drawing::Size(182, 22);
			   this->aboutPhotoViewerToolStripMenuItem->Text = L"About Photo-Viewer";
			   this->aboutPhotoViewerToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::AboutPhotoViewerToolStripMenuItem_Click);
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
			   this->SplitContainer2->Size = System::Drawing::Size(423, 61);
			   this->SplitContainer2->SplitterDistance = 28;
			   this->SplitContainer2->SplitterWidth = 1;
			   this->SplitContainer2->TabIndex = 0;
			   this->SplitContainer2->TabStop = false;
			   // 
			   // bNextPicture
			   // 
			   this->bNextPicture->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bNextPicture->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->bNextPicture->Location = System::Drawing::Point(214, 24);
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
			   this->bPreviousPicture->Location = System::Drawing::Point(102, 24);
			   this->bPreviousPicture->Name = L"bPreviousPicture";
			   this->bPreviousPicture->Size = System::Drawing::Size(75, 23);
			   this->bPreviousPicture->TabIndex = 1;
			   this->bPreviousPicture->Text = L"<-";
			   this->bPreviousPicture->UseVisualStyleBackColor = true;
			   this->bPreviousPicture->Click += gcnew System::EventHandler(this, &MainForm::bPreviousPicture_Click);
			   // 
			   // timer1
			   // 
			   this->timer1->Interval = 500;
			   this->timer1->Tick += gcnew System::EventHandler(this, &MainForm::timer1_Tick);
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(423, 505);
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
