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
		MainForm();

		array<String^>^ GetFilesCurrentDirectory(String^ directory);
		bool IsCorrectExtension(String^ extension);
		void SortFiles();
		void SettingUpPictureBox();
		ArrayList Pictures;

	protected:
		~MainForm();

	private: System::Windows::Forms::PictureBox^ PictureBox;
	private: System::Windows::Forms::SplitContainer^ SplitContainer;
	private: System::Windows::Forms::SplitContainer^ SplitContainer2;
	private: System::Windows::Forms::Button^ bNextPhoto;
	private: System::Windows::Forms::Button^ bPreviousPhoto;
	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   void InitializeComponent(void)
		   {
			   this->SplitContainer = (gcnew System::Windows::Forms::SplitContainer());
			   this->PictureBox = (gcnew System::Windows::Forms::PictureBox());
			   this->SplitContainer2 = (gcnew System::Windows::Forms::SplitContainer());
			   this->bNextPhoto = (gcnew System::Windows::Forms::Button());
			   this->bPreviousPhoto = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer))->BeginInit();
			   this->SplitContainer->Panel1->SuspendLayout();
			   this->SplitContainer->Panel2->SuspendLayout();
			   this->SplitContainer->SuspendLayout();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureBox))->BeginInit();
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
			   // 
			   // SplitContainer.Panel2
			   // 
			   this->SplitContainer->Panel2->Controls->Add(this->SplitContainer2);
			   this->SplitContainer->Size = System::Drawing::Size(449, 402);
			   this->SplitContainer->SplitterDistance = 352;
			   this->SplitContainer->TabIndex = 0;
			   this->SplitContainer->TabStop = false;
			   // 
			   // PictureBox
			   // 
			   this->PictureBox->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->PictureBox->Location = System::Drawing::Point(0, 0);
			   this->PictureBox->Name = L"PictureBox";
			   this->PictureBox->Size = System::Drawing::Size(449, 352);
			   this->PictureBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			   this->PictureBox->TabIndex = 0;
			   this->PictureBox->TabStop = false;
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
			   this->SplitContainer2->Panel1->Controls->Add(this->bNextPhoto);
			   this->SplitContainer2->Panel1->Controls->Add(this->bPreviousPhoto);
			   this->SplitContainer2->Panel2Collapsed = true;
			   this->SplitContainer2->Size = System::Drawing::Size(449, 46);
			   this->SplitContainer2->SplitterDistance = 28;
			   this->SplitContainer2->SplitterWidth = 1;
			   this->SplitContainer2->TabIndex = 0;
			   this->SplitContainer2->TabStop = false;
			   // 
			   // bNextPhoto
			   // 
			   this->bNextPhoto->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bNextPhoto->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->bNextPhoto->Location = System::Drawing::Point(230, 17);
			   this->bNextPhoto->Name = L"bNextPhoto";
			   this->bNextPhoto->Size = System::Drawing::Size(75, 23);
			   this->bNextPhoto->TabIndex = 1;
			   this->bNextPhoto->Text = L">";
			   this->bNextPhoto->UseVisualStyleBackColor = true;
			   // 
			   // bPreviousPhoto
			   // 
			   this->bPreviousPhoto->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->bPreviousPhoto->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->bPreviousPhoto->Location = System::Drawing::Point(118, 17);
			   this->bPreviousPhoto->Name = L"bPreviousPhoto";
			   this->bPreviousPhoto->Size = System::Drawing::Size(75, 23);
			   this->bPreviousPhoto->TabIndex = 1;
			   this->bPreviousPhoto->Text = L"<";
			   this->bPreviousPhoto->UseVisualStyleBackColor = true;
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(449, 402);
			   this->Controls->Add(this->SplitContainer);
			   this->MinimumSize = System::Drawing::Size(340, 404);
			   this->Name = L"MainForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			   this->Text = L"Photo-Viewer";
			   this->SplitContainer->Panel1->ResumeLayout(false);
			   this->SplitContainer->Panel2->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer))->EndInit();
			   this->SplitContainer->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->PictureBox))->EndInit();
			   this->SplitContainer2->Panel1->ResumeLayout(false);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->SplitContainer2))->EndInit();
			   this->SplitContainer2->ResumeLayout(false);
			   this->ResumeLayout(false);

		   }
#pragma endregion
	};
}
