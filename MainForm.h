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


		ArrayList Pictures;

	protected:
		~MainForm();
	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Name = L"MainForm";
			this->Text = L"Photo-Viewer";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
