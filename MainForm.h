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
	public:
		ArrayList Pictures;
		
		const int INDEX_FIRST_PICTURE = 0;
		
		String^ DIRECTORY_SETTINGS = R"(D:\Settings)";
		String^ PATH_LAST_WINDOW_SIZE = R"(D:\Settings\LastWindowSize.txt)";
		String^ LAST_WINDOW_LOCATION = R"(D:\Settings\LastWindowLocation.txt)";
		String^ LAST_WINDOW_STATE = R"(D:\Settings\LastWindowState.txt)";
		
		int IndexCurrentPicture = 0;
		int IndexLastPicture;
		
		MainForm(String^ directoryToFirstPhoto);
		void SetUpWindowForm();
		void SetUpLastWindowSize();
		void SetUpLastWindowLocation();
		void SetUpLastWindowState();

		array<String^>^ GetFilesCurrentDirectory(String^ directory);
		bool IsCorrectExtension(String^ extension);
		void SortFiles(array<String^>^ AllFiles);
		void FindOutIndexOpenedPicture(String^ pathToOpenedPicture);
		void SettingUpPictureBox();
		


	protected:
	~MainForm();
	void SaveSettingsForm();
	void SaveLastWindowSize();
	void SaveLastWindowLocation();
	void SaveLastWindowState();

	private: void CopyCurrentPictureToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e);
	private: void MainForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

	void SwitchPicture(const int lastOrFirstPicture, const int initializeValue, const int addValue);
	private: void bNextPicture_Click(System::Object^ sender, System::EventArgs^ e);
	private: void bPreviousPicture_Click(System::Object^ sender, System::EventArgs^ e);


	
	
	
	
	
	private: System::Windows::Forms::PictureBox^ PictureBox;
	private: System::Windows::Forms::SplitContainer^ SplitContainer;
	private: System::Windows::Forms::SplitContainer^ SplitContainer2;
	private: System::Windows::Forms::Button^ bNextPicture;
	private: System::Windows::Forms::Button^ bPreviousPicture;
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ FileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ CopyCurrentPictureToolStripMenuItem;


#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->SplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			   this->PictureBox = (gcnew System::Windows::Forms::PictureBox());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->FileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->CopyCurrentPictureToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->SplitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			   this->bNextPicture = (gcnew System::Windows::Forms::Button());
			   this->bPreviousPicture = (gcnew System::Windows::Forms::Button());
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
			   this->SplitContainer->Panel1->Controls->Add(this->PictureBox);
			   this->SplitContainer->Panel1->Controls->Add(this->menuStrip1);
			   // 
			   // SplitContainer.Panel2
			   // 
			   this->SplitContainer->Panel2->Controls->Add(this->SplitContainer2);
			   this->SplitContainer->Size = System::Drawing::Size(324, 365);
			   this->SplitContainer->SplitterDistance = 319;
			   this->SplitContainer->TabIndex = 0;
			   this->SplitContainer->TabStop = false;
			   // 
			   // PictureBox
			   // 
			   this->PictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->PictureBox->Location = System::Drawing::Point(0, 24);
			   this->PictureBox->Name = L"PictureBox";
			   this->PictureBox->Size = System::Drawing::Size(324, 295);
			   this->PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->PictureBox->TabIndex = 0;
			   this->PictureBox->TabStop = false;
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->FileToolStripMenuItem });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Size = System::Drawing::Size(324, 24);
			   this->menuStrip1->TabIndex = 1;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // FileToolStripMenuItem
			   // 
			   this->FileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->CopyCurrentPictureToolStripMenuItem });
			   this->FileToolStripMenuItem->Name = L"FileToolStripMenuItem";
			   this->FileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
			   this->FileToolStripMenuItem->Text = L"File";
			   // 
			   // CopyCurrentPictureToolStripMenuItem
			   // 
			   this->CopyCurrentPictureToolStripMenuItem->Name = L"CopyCurrentPictureToolStripMenuItem";
			   this->CopyCurrentPictureToolStripMenuItem->ShortcutKeyDisplayString = L"Ctrl + C";
			   this->CopyCurrentPictureToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::C));
			   this->CopyCurrentPictureToolStripMenuItem->Size = System::Drawing::Size(231, 22);
			   this->CopyCurrentPictureToolStripMenuItem->Text = L"Copy current picture";
			   this->CopyCurrentPictureToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::CopyCurrentPictureToolStripMenuItem_Click);
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
			   this->SplitContainer2->Size = System::Drawing::Size(324, 42);
			   this->SplitContainer2->SplitterDistance = 28;
			   this->SplitContainer2->SplitterWidth = 1;
			   this->SplitContainer2->TabIndex = 0;
			   this->SplitContainer2->TabStop = false;
			   // 
			   // bNextPicture
			   // 
			   this->bNextPicture->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bNextPicture->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->bNextPicture->Location = System::Drawing::Point(168, 15);
			   this->bNextPicture->Name = L"bNextPicture";
			   this->bNextPicture->Size = System::Drawing::Size(75, 23);
			   this->bNextPicture->TabIndex = 1;
			   this->bNextPicture->Text = L">";
			   this->bNextPicture->UseVisualStyleBackColor = true;
			   this->bNextPicture->Click += gcnew System::EventHandler(this, &MainForm::bNextPicture_Click);
			   // 
			   // bPreviousPicture
			   // 
			   this->bPreviousPicture->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bPreviousPicture->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->bPreviousPicture->Location = System::Drawing::Point(56, 15);
			   this->bPreviousPicture->Name = L"bPreviousPicture";
			   this->bPreviousPicture->Size = System::Drawing::Size(75, 23);
			   this->bPreviousPicture->TabIndex = 1;
			   this->bPreviousPicture->Text = L"<";
			   this->bPreviousPicture->UseVisualStyleBackColor = true;
			   this->bPreviousPicture->Click += gcnew System::EventHandler(this, &MainForm::bPreviousPicture_Click);
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(324, 365);
			   this->Controls->Add(this->SplitContainer);
			   this->KeyPreview = true;
			   this->MainMenuStrip = this->menuStrip1;
			   this->MinimumSize = System::Drawing::Size(340, 404);
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
