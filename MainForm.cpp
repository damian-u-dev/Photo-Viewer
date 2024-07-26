#include "MainForm.h"

PhotoViewer::MainForm::MainForm()
{
	InitializeComponent();
}

PhotoViewer::MainForm::~MainForm()
{
	if (components)
	{
		delete components;
	}
}
