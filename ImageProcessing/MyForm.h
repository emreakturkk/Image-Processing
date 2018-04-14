#pragma once
#include <Windows.h>
#include <atlstr.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "MyImage.h"

namespace ImageProcessing {

	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  exitToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;





	private:
		/// <summary>
		/// Required designer variable.
		int x;
		int y;
		int box_W;
		int box_H;

		LPCTSTR input;
		int width, height;
		long size;

		BYTE* buffer;
		BYTE* raw_intensity;
		BYTE* dCrop;
		int flag;


	private: System::Windows::Forms::ToolStripMenuItem^  operationsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  yIntesityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  digitalZoomToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::ToolStripMenuItem^  stretchToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  clearToolStripMenuItem;


	private: System::Windows::Forms::ToolStripMenuItem^  kMeansToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeansClustering1DToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  kMeansClusteringNDToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  ýmageMorphologyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dilationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  erosionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  closingToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  boundaryToolStripMenuItem;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown4;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;



			 /// </summary>
			 System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// Required method for Designer support - do not modify
			 /// the contents of this method with the code editor.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
				 System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
				 System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
				 this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
				 this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->clearToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->operationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->yIntesityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->stretchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->digitalZoomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->kMeansToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->kMeansClustering1DToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->kMeansClusteringNDToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->ýmageMorphologyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->openingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->closingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->boundaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
				 this->label1 = (gcnew System::Windows::Forms::Label());
				 this->label2 = (gcnew System::Windows::Forms::Label());
				 this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->panel1 = (gcnew System::Windows::Forms::Panel());
				 this->numericUpDown4 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->numericUpDown3 = (gcnew System::Windows::Forms::NumericUpDown());
				 this->label4 = (gcnew System::Windows::Forms::Label());
				 this->label3 = (gcnew System::Windows::Forms::Label());
				 this->menuStrip1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->BeginInit();
				 this->panel1->SuspendLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // menuStrip1
				 // 
				 this->menuStrip1->BackColor = System::Drawing::SystemColors::ControlLight;
				 this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->fileToolStripMenuItem,
						 this->operationsToolStripMenuItem, this->kMeansToolStripMenuItem, this->ýmageMorphologyToolStripMenuItem
				 });
				 this->menuStrip1->Location = System::Drawing::Point(0, 0);
				 this->menuStrip1->Name = L"menuStrip1";
				 this->menuStrip1->Size = System::Drawing::Size(1277, 24);
				 this->menuStrip1->TabIndex = 0;
				 this->menuStrip1->Text = L"menuStrip1";
				 // 
				 // fileToolStripMenuItem
				 // 
				 this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
					 this->openToolStripMenuItem,
						 this->clearToolStripMenuItem, this->exitToolStripMenuItem
				 });
				 this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
				 this->fileToolStripMenuItem->Size = System::Drawing::Size(37, 20);
				 this->fileToolStripMenuItem->Text = L"File";
				 // 
				 // openToolStripMenuItem
				 // 
				 this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
				 this->openToolStripMenuItem->Size = System::Drawing::Size(103, 22);
				 this->openToolStripMenuItem->Text = L"Open";
				 this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
				 // 
				 // clearToolStripMenuItem
				 // 
				 this->clearToolStripMenuItem->Name = L"clearToolStripMenuItem";
				 this->clearToolStripMenuItem->Size = System::Drawing::Size(103, 22);
				 this->clearToolStripMenuItem->Text = L"Clear";
				 this->clearToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::clearToolStripMenuItem_Click);
				 // 
				 // exitToolStripMenuItem
				 // 
				 this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
				 this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
				 this->exitToolStripMenuItem->Text = L"Exit";
				 this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::exitToolStripMenuItem_Click);
				 // 
				 // operationsToolStripMenuItem
				 // 
				 this->operationsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
					 this->yIntesityToolStripMenuItem,
						 this->histogramToolStripMenuItem, this->stretchToolStripMenuItem, this->digitalZoomToolStripMenuItem
				 });
				 this->operationsToolStripMenuItem->Name = L"operationsToolStripMenuItem";
				 this->operationsToolStripMenuItem->Size = System::Drawing::Size(112, 20);
				 this->operationsToolStripMenuItem->Text = L"Image Processing";
				 // 
				 // yIntesityToolStripMenuItem
				 // 
				 this->yIntesityToolStripMenuItem->Name = L"yIntesityToolStripMenuItem";
				 this->yIntesityToolStripMenuItem->Size = System::Drawing::Size(194, 22);
				 this->yIntesityToolStripMenuItem->Text = L"Y-Intesity";
				 this->yIntesityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::yIntesityToolStripMenuItem_Click);
				 // 
				 // histogramToolStripMenuItem
				 // 
				 this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
				 this->histogramToolStripMenuItem->Size = System::Drawing::Size(194, 22);
				 this->histogramToolStripMenuItem->Text = L"Histogram";
				 this->histogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramToolStripMenuItem_Click);
				 // 
				 // stretchToolStripMenuItem
				 // 
				 this->stretchToolStripMenuItem->Name = L"stretchToolStripMenuItem";
				 this->stretchToolStripMenuItem->Size = System::Drawing::Size(194, 22);
				 this->stretchToolStripMenuItem->Text = L"HistogramEqualization";
				 this->stretchToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::stretchToolStripMenuItem_Click);
				 // 
				 // digitalZoomToolStripMenuItem
				 // 
				 this->digitalZoomToolStripMenuItem->Name = L"digitalZoomToolStripMenuItem";
				 this->digitalZoomToolStripMenuItem->Size = System::Drawing::Size(194, 22);
				 this->digitalZoomToolStripMenuItem->Text = L"Digital Zoom";
				 this->digitalZoomToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::digitalZoomToolStripMenuItem_Click);
				 // 
				 // kMeansToolStripMenuItem
				 // 
				 this->kMeansToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
					 this->kMeansClustering1DToolStripMenuItem,
						 this->kMeansClusteringNDToolStripMenuItem1
				 });
				 this->kMeansToolStripMenuItem->Name = L"kMeansToolStripMenuItem";
				 this->kMeansToolStripMenuItem->Size = System::Drawing::Size(66, 20);
				 this->kMeansToolStripMenuItem->Text = L"K-Means";
				 // 
				 // kMeansClustering1DToolStripMenuItem
				 // 
				 this->kMeansClustering1DToolStripMenuItem->Name = L"kMeansClustering1DToolStripMenuItem";
				 this->kMeansClustering1DToolStripMenuItem->Size = System::Drawing::Size(187, 22);
				 this->kMeansClustering1DToolStripMenuItem->Text = L"KMeansClustering1D";
				 this->kMeansClustering1DToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansClustering1DToolStripMenuItem_Click);
				 // 
				 // kMeansClusteringNDToolStripMenuItem1
				 // 
				 this->kMeansClusteringNDToolStripMenuItem1->Name = L"kMeansClusteringNDToolStripMenuItem1";
				 this->kMeansClusteringNDToolStripMenuItem1->Size = System::Drawing::Size(187, 22);
				 this->kMeansClusteringNDToolStripMenuItem1->Text = L"KMeansClusteringND";
				 this->kMeansClusteringNDToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::kMeansClusteringNDToolStripMenuItem1_Click);
				 // 
				 // ýmageMorphologyToolStripMenuItem
				 // 
				 this->ýmageMorphologyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
					 this->dilationToolStripMenuItem,
						 this->erosionToolStripMenuItem, this->openingToolStripMenuItem, this->closingToolStripMenuItem, this->boundaryToolStripMenuItem
				 });
				 this->ýmageMorphologyToolStripMenuItem->Name = L"ýmageMorphologyToolStripMenuItem";
				 this->ýmageMorphologyToolStripMenuItem->Size = System::Drawing::Size(121, 20);
				 this->ýmageMorphologyToolStripMenuItem->Text = L"Image Morphology";
				 // 
				 // dilationToolStripMenuItem
				 // 
				 this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
				 this->dilationToolStripMenuItem->Size = System::Drawing::Size(125, 22);
				 this->dilationToolStripMenuItem->Text = L"Dilation";
				 this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
				 // 
				 // erosionToolStripMenuItem
				 // 
				 this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
				 this->erosionToolStripMenuItem->Size = System::Drawing::Size(125, 22);
				 this->erosionToolStripMenuItem->Text = L"Erosion";
				 this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
				 // 
				 // openingToolStripMenuItem
				 // 
				 this->openingToolStripMenuItem->Name = L"openingToolStripMenuItem";
				 this->openingToolStripMenuItem->Size = System::Drawing::Size(125, 22);
				 this->openingToolStripMenuItem->Text = L"Opening";
				 this->openingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openingToolStripMenuItem_Click);
				 // 
				 // closingToolStripMenuItem
				 // 
				 this->closingToolStripMenuItem->Name = L"closingToolStripMenuItem";
				 this->closingToolStripMenuItem->Size = System::Drawing::Size(125, 22);
				 this->closingToolStripMenuItem->Text = L"Closing";
				 this->closingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::closingToolStripMenuItem_Click);
				 // 
				 // boundaryToolStripMenuItem
				 // 
				 this->boundaryToolStripMenuItem->Name = L"boundaryToolStripMenuItem";
				 this->boundaryToolStripMenuItem->Size = System::Drawing::Size(125, 22);
				 this->boundaryToolStripMenuItem->Text = L"Boundary";
				 this->boundaryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::boundaryToolStripMenuItem_Click);
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Location = System::Drawing::Point(23, 58);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(450, 450);
				 this->pictureBox1->TabIndex = 1;
				 this->pictureBox1->TabStop = false;
				 this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
				 this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
				 this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
				 // 
				 // openFileDialog1
				 // 
				 this->openFileDialog1->FileName = L"openFileDialog1";
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Location = System::Drawing::Point(500, 58);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(450, 450);
				 this->pictureBox2->TabIndex = 2;
				 this->pictureBox2->TabStop = false;
				 // 
				 // chart1
				 // 
				 this->chart1->AllowDrop = true;
				 chartArea1->Name = L"ChartArea1";
				 this->chart1->ChartAreas->Add(chartArea1);
				 legend1->Name = L"Legend1";
				 this->chart1->Legends->Add(legend1);
				 this->chart1->Location = System::Drawing::Point(965, 212);
				 this->chart1->Name = L"chart1";
				 this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::SemiTransparent;
				 series1->ChartArea = L"ChartArea1";
				 series1->Legend = L"Legend1";
				 series1->Name = L"Number Of Pixel";
				 this->chart1->Series->Add(series1);
				 this->chart1->Size = System::Drawing::Size(299, 252);
				 this->chart1->TabIndex = 15;
				 this->chart1->Text = L"chart1";
				 // 
				 // label1
				 // 
				 this->label1->AutoSize = true;
				 this->label1->Location = System::Drawing::Point(3, 15);
				 this->label1->Name = L"label1";
				 this->label1->Size = System::Drawing::Size(42, 13);
				 this->label1->TabIndex = 16;
				 this->label1->Text = L"Dilation";
				 // 
				 // label2
				 // 
				 this->label2->AutoSize = true;
				 this->label2->Location = System::Drawing::Point(3, 41);
				 this->label2->Name = L"label2";
				 this->label2->Size = System::Drawing::Size(42, 13);
				 this->label2->TabIndex = 17;
				 this->label2->Text = L"Erosion";
				 // 
				 // numericUpDown1
				 // 
				 this->numericUpDown1->Location = System::Drawing::Point(64, 13);
				 this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numericUpDown1->Name = L"numericUpDown1";
				 this->numericUpDown1->Size = System::Drawing::Size(44, 20);
				 this->numericUpDown1->TabIndex = 19;
				 this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // numericUpDown2
				 // 
				 this->numericUpDown2->Location = System::Drawing::Point(64, 39);
				 this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numericUpDown2->Name = L"numericUpDown2";
				 this->numericUpDown2->Size = System::Drawing::Size(44, 20);
				 this->numericUpDown2->TabIndex = 20;
				 this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // panel1
				 // 
				 this->panel1->Controls->Add(this->numericUpDown4);
				 this->panel1->Controls->Add(this->numericUpDown3);
				 this->panel1->Controls->Add(this->label4);
				 this->panel1->Controls->Add(this->label3);
				 this->panel1->Controls->Add(this->label1);
				 this->panel1->Controls->Add(this->numericUpDown2);
				 this->panel1->Controls->Add(this->label2);
				 this->panel1->Controls->Add(this->numericUpDown1);
				 this->panel1->Location = System::Drawing::Point(965, 58);
				 this->panel1->Name = L"panel1";
				 this->panel1->Size = System::Drawing::Size(123, 136);
				 this->panel1->TabIndex = 21;
				 // 
				 // numericUpDown4
				 // 
				 this->numericUpDown4->Location = System::Drawing::Point(64, 93);
				 this->numericUpDown4->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numericUpDown4->Name = L"numericUpDown4";
				 this->numericUpDown4->Size = System::Drawing::Size(44, 20);
				 this->numericUpDown4->TabIndex = 24;
				 this->numericUpDown4->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // numericUpDown3
				 // 
				 this->numericUpDown3->Location = System::Drawing::Point(64, 67);
				 this->numericUpDown3->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 this->numericUpDown3->Name = L"numericUpDown3";
				 this->numericUpDown3->Size = System::Drawing::Size(44, 20);
				 this->numericUpDown3->TabIndex = 23;
				 this->numericUpDown3->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 0 });
				 // 
				 // label4
				 // 
				 this->label4->AutoSize = true;
				 this->label4->Location = System::Drawing::Point(4, 100);
				 this->label4->Name = L"label4";
				 this->label4->Size = System::Drawing::Size(41, 13);
				 this->label4->TabIndex = 22;
				 this->label4->Text = L"Closing";
				 // 
				 // label3
				 // 
				 this->label3->AutoSize = true;
				 this->label3->Location = System::Drawing::Point(3, 69);
				 this->label3->Name = L"label3";
				 this->label3->Size = System::Drawing::Size(47, 13);
				 this->label3->TabIndex = 21;
				 this->label3->Text = L"Opening";
				 // 
				 // MyForm
				 // 
				 this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
				 this->BackColor = System::Drawing::SystemColors::Control;
				 this->ClientSize = System::Drawing::Size(1277, 530);
				 this->Controls->Add(this->panel1);
				 this->Controls->Add(this->chart1);
				 this->Controls->Add(this->pictureBox2);
				 this->Controls->Add(this->pictureBox1);
				 this->Controls->Add(this->menuStrip1);
				 this->MainMenuStrip = this->menuStrip1;
				 this->Name = L"MyForm";
				 this->Text = L"MyForm";
				 this->menuStrip1->ResumeLayout(false);
				 this->menuStrip1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown2))->EndInit();
				 this->panel1->ResumeLayout(false);
				 this->panel1->PerformLayout();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown4))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown3))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion

	private: System::Void exitToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		this->Close();
	}
	private: System::Void openToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		openFileDialog1->Filter = "|*.bmp";
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			pictureBox1->ImageLocation = openFileDialog1->FileName;
			CString path;
			path = openFileDialog1->FileName;
			input = (LPCTSTR)path;

			buffer = LoadBMP(width, height, size, input);
			BYTE *tBuffer = new BYTE[width*height * 3];

			for (int i = 0; i < width*height * 3; i++)
				tBuffer[i] = buffer[i];

			raw_intensity = ConvertBMPToIntensity(tBuffer, width, height);
			
		}
	}

	private: System::Void yIntesityToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		BYTE* t_intensity = new BYTE[width*height];

		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		Bitmap^ img = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		pictureBox1->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(t_intensity[temp], t_intensity[temp], t_intensity[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]t_intensity;
	
	}

	private: System::Void clearToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		pictureBox2->Image = nullptr;
		pictureBox2->Width = 450;
		pictureBox2->Height = 450;
	}

	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (pictureBox1->Image)
		{
			pictureBox2->Width = 450;
			pictureBox2->Height = 450;
			flag = 1;
			x = e->X;
			y = e->Y;
		}
	}

	private: System::Void pictureBox1_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		try
		{
			if (pictureBox1->Image && flag == 1)
			{
				BYTE* t_intensity = new BYTE[width*height];

				for (unsigned int i = 0; i < height*width; i++)
					t_intensity[i] = raw_intensity[i];

				box_W = e->X;
				box_H = e->Y;
			
				Bitmap^ imgCrop = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
				pictureBox2->Image = imgCrop;
				Color c;
				int temp;

				for (unsigned int row = y; row < box_H; row++)
				{
					for (unsigned int column = x; column < box_W; column++)
					{
						temp = row * width + column;
						c = Color::FromArgb(t_intensity[temp], t_intensity[temp], t_intensity[temp]);
						imgCrop->SetPixel(column, row, c);

					}
					
				}
				pictureBox2->Refresh();
				delete[]t_intensity;
			
			}
			
		}
		catch (const System::ArgumentOutOfRangeException^ e)
		{
			flag = 0;
			MessageBox::Show("Hata");
		}
	}
	private: System::Void pictureBox1_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		try
		{
			if (pictureBox1->Image)
			{
				flag = 0;
				box_W = e->X;
				box_H = e->Y;

				BYTE* t_intensity = new BYTE[width*height];
				for (unsigned int i = 0; i < height*width; i++)
					t_intensity[i] = raw_intensity[i];

				dCrop = new BYTE[(box_H - y)*(box_W - x)];
				int pos = 0;
				for (unsigned int row = y; row <box_H; row++)
					for (unsigned int column = x; column < box_W; column++)
					{
						dCrop[pos++] = t_intensity[row*width + column];
					}
				delete[]t_intensity;
				
			}
			
		}
		catch (const System::ArgumentOutOfRangeException^ e)
		{
			flag = 0;
			MessageBox::Show("Hata");
		}
	}

	private: System::Void digitalZoomToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (dCrop)
		{
			BYTE* zoom = DigitalZoom(dCrop, (box_W - x), (box_H - y));

			Bitmap^ imgZoom = gcnew Bitmap(2 * (box_W - x) - 1, 2 * (box_H - y) - 1);
			pictureBox2->Width = 2 * (box_W - x) - 1;
			pictureBox2->Height = 2 * (box_H - y) - 1;
			pictureBox2->Image = imgZoom;
			Color c;
			int temp;

			for (unsigned int row = 0; row < 2 * (box_H - y) - 1; row++)
				for (unsigned int column = 0; column < 2 * (box_W - x) - 1; column++)
				{
					temp = row * (2 * (box_W - x) - 1) + column;
					c = Color::FromArgb(zoom[temp], zoom[temp], zoom[temp]);
					imgZoom->SetPixel(column, row, c);
				}
			delete[] zoom;
			delete[] dCrop;
		}
		
	}
	
	private: System::Void histogramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		chart1->Titles->Clear();
		chart1->Series->Clear();
		chart1->Series->Add("Number Of Pixel");


		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];
		
		int *hist = Histogram(t_intensity, width, height);
		for (unsigned int i = 0; i < 256; i++)
		{
			chart1->Series["Number Of Pixel"]->Points->AddXY(i, hist[i]);
		}

		chart1->Titles->Add("Histogram");
		delete[]hist;
		delete[]t_intensity;

	}

	private: System::Void stretchToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		chart1->Titles->Clear();
		chart1->Series->Clear();
		chart1->Series->Add("Number Of Pixel");

		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		BYTE* new_intensity = HistogramEqualization(t_intensity, width, height);

		int *tempHistogram = Histogram(new_intensity, width, height);

		for (unsigned int i = 0; i < 256; i++)
		{
			chart1->Series["Number Of Pixel"]->Points->AddXY(i, tempHistogram[i]);
		}
		chart1->Titles->Add("Histogram(Stretch)");

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(new_intensity[temp], new_intensity[temp], new_intensity[temp]);
				img->SetPixel(column, row, c);
			}

		delete[]tempHistogram;
		delete[]new_intensity;
	}

	private: System::Void kMeansClustering1DToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		BYTE* k_means = KMeansClustering(t_intensity, width, height, 0);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(k_means[temp], k_means[temp], k_means[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]k_means;
	}

	private: System::Void kMeansClusteringNDToolStripMenuItem1_Click(System::Object^  sender, System::EventArgs^  e) {

		BYTE* tBuffer = new BYTE[width*height * 3];

		for (int i = 0; i < height*width * 3; i++)
			tBuffer[i] = buffer[i];

		BYTE* k_means = KMeansClusteringN(tBuffer, width, height);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp = 0;

		for (int row = 0; row < height; row++)
		{
			for (int column = 0; column < width; column++)
			{
				temp = row * width*3 + column*3;
				c = Color::FromArgb(k_means[temp], k_means[temp+1], k_means[temp+2]);
				img->SetPixel(column, row, c);
			}
		}

		delete[]k_means;
	}

	private: System::Void dilationToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		int iteration = (int)numericUpDown1->Value;
		BYTE* binary = KMeansClustering(t_intensity, width, height, 0);
		BYTE* dilation = Dilation(binary, width, height, iteration);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(dilation[temp], dilation[temp], dilation[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]dilation;
	}
	private: System::Void erosionToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		int iteration = (int)numericUpDown2->Value;
		BYTE* binary = KMeansClustering(t_intensity, width, height, 0);
		BYTE* erosion = Erosion(binary, width, height, iteration);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(erosion[temp], erosion[temp], erosion[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]erosion;
	}
	private: System::Void openingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		int iteration = (int)numericUpDown3->Value;
		BYTE* binary = KMeansClustering(t_intensity, width, height, 0);
		BYTE* opening = Opening(binary, width, height, iteration);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(opening[temp], opening[temp], opening[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]opening;
	}

	private: System::Void closingToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		int iteration = (int)numericUpDown4->Value;
		BYTE* binary = KMeansClustering(t_intensity, width, height, 0);
		
		BYTE* closing = Closinng(binary, width, height, iteration);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(closing[temp], closing[temp], closing[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]closing;
	}
	private: System::Void boundaryToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {

		BYTE* t_intensity = new BYTE[width*height];
		for (unsigned int i = 0; i < height*width; i++)
			t_intensity[i] = raw_intensity[i];

		BYTE* binary = KMeansClustering(t_intensity, width, height, 0);
		BYTE* boundary = Boundary(binary, width, height);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row < height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(boundary[temp], boundary[temp], boundary[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]boundary;
	}
	
};
}
