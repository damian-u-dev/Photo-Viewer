#pragma once

namespace PhotoViewer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class AboutPVForm : public System::Windows::Forms::Form
	{
	public:
		AboutPVForm();
		~AboutPVForm();
		void SetColorForm(Color FormColor, Color FontColor);
		void AboutPVForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		String^ GitHubLink = "https://github.com/damian-u-dev";


	private: System::Windows::Forms::Label^ l_NameOfProgramm;
	private: System::Windows::Forms::Label^ l_Copyrights;

	private: System::Windows::Forms::LinkLabel^ link_GitHub;

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->l_NameOfProgramm = (gcnew System::Windows::Forms::Label());
			this->l_Copyrights = (gcnew System::Windows::Forms::Label());
			this->link_GitHub = (gcnew System::Windows::Forms::LinkLabel());
			this->SuspendLayout();
			// 
			// l_NameOfProgramm
			// 
			this->l_NameOfProgramm->AutoSize = true;
			this->l_NameOfProgramm->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->l_NameOfProgramm->Location = System::Drawing::Point(91, 9);
			this->l_NameOfProgramm->Name = L"l_NameOfProgramm";
			this->l_NameOfProgramm->Size = System::Drawing::Size(83, 14);
			this->l_NameOfProgramm->TabIndex = 1;
			this->l_NameOfProgramm->Text = L"Photo-Viewer";
			// 
			// l_Copyrights
			// 
			this->l_Copyrights->AutoSize = true;
			this->l_Copyrights->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->l_Copyrights->Location = System::Drawing::Point(91, 33);
			this->l_Copyrights->Name = L"l_Copyrights";
			this->l_Copyrights->Size = System::Drawing::Size(115, 14);
			this->l_Copyrights->TabIndex = 2;
			this->l_Copyrights->Text = L"All Rights Reserved";
			// 
			// link_GitHub
			// 
			this->link_GitHub->AutoSize = true;
			this->link_GitHub->LinkArea = System::Windows::Forms::LinkArea(0, 2811);
			this->link_GitHub->LinkBehavior = System::Windows::Forms::LinkBehavior::HoverUnderline;
			this->link_GitHub->Location = System::Drawing::Point(91, 57);
			this->link_GitHub->Name = L"link_GitHub";
			this->link_GitHub->Size = System::Drawing::Size(39, 17);
			this->link_GitHub->TabIndex = 4;
			this->link_GitHub->TabStop = true;
			this->link_GitHub->Text = L"GitHub";
			this->link_GitHub->UseCompatibleTextRendering = true;
			this->link_GitHub->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &AboutPVForm::link_GitHub_LinkClicked);
			// 
			// AboutPVForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(264, 167);
			this->Controls->Add(this->link_GitHub);
			this->Controls->Add(this->l_Copyrights);
			this->Controls->Add(this->l_NameOfProgramm);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"AboutPVForm";
			this->ShowIcon = false;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"About Photo-Viewer";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &AboutPVForm::AboutPVForm_KeyDown);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void link_GitHub_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e);
	};
}
