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
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;

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
		int flag;

	private: System::Windows::Forms::PictureBox^  pictureBox3;

	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::Label^  E;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::ToolStripMenuItem^  operationsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  yIntesityToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  digitalZoomToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  histogramToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart1;
	private: System::Windows::Forms::ToolStripMenuItem^  stretchToolStripMenuItem;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label12;






			 /// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->operationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->yIntesityToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->digitalZoomToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->histogramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stretchToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->E = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ControlLight;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->operationsToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1057, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->openToolStripMenuItem,
					this->exitToolStripMenuItem
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
					this->digitalZoomToolStripMenuItem, this->histogramToolStripMenuItem, this->stretchToolStripMenuItem
			});
			this->operationsToolStripMenuItem->Name = L"operationsToolStripMenuItem";
			this->operationsToolStripMenuItem->Size = System::Drawing::Size(112, 20);
			this->operationsToolStripMenuItem->Text = L"Image Processing";
			// 
			// yIntesityToolStripMenuItem
			// 
			this->yIntesityToolStripMenuItem->Name = L"yIntesityToolStripMenuItem";
			this->yIntesityToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->yIntesityToolStripMenuItem->Text = L"Y-Intesity";
			this->yIntesityToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::yIntesityToolStripMenuItem_Click);
			// 
			// digitalZoomToolStripMenuItem
			// 
			this->digitalZoomToolStripMenuItem->Name = L"digitalZoomToolStripMenuItem";
			this->digitalZoomToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->digitalZoomToolStripMenuItem->Text = L"Digital Zoom";
			this->digitalZoomToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::digitalZoomToolStripMenuItem_Click);
			// 
			// histogramToolStripMenuItem
			// 
			this->histogramToolStripMenuItem->Name = L"histogramToolStripMenuItem";
			this->histogramToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->histogramToolStripMenuItem->Text = L"Histogram";
			this->histogramToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::histogramToolStripMenuItem_Click);
			// 
			// stretchToolStripMenuItem
			// 
			this->stretchToolStripMenuItem->Name = L"stretchToolStripMenuItem";
			this->stretchToolStripMenuItem->Size = System::Drawing::Size(143, 22);
			this->stretchToolStripMenuItem->Text = L"Stretch";
			this->stretchToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::stretchToolStripMenuItem_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox1->Location = System::Drawing::Point(12, 45);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(140, 140);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// pictureBox2
			// 
			this->pictureBox2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox2->Location = System::Drawing::Point(171, 45);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(140, 140);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseDown);
			this->pictureBox2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseMove);
			this->pictureBox2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox2_MouseUp);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label1->Location = System::Drawing::Point(2, 88);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(23, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"X : ";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label2->Location = System::Drawing::Point(2, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(20, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Y: ";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label3->Location = System::Drawing::Point(2, 142);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(38, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"boxW:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->label4->Location = System::Drawing::Point(3, 167);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"boxH:";
			// 
			// pictureBox3
			// 
			this->pictureBox3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox3->Location = System::Drawing::Point(329, 45);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(140, 140);
			this->pictureBox3->TabIndex = 7;
			this->pictureBox3->TabStop = false;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(54, 29);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(53, 13);
			this->label5->TabIndex = 9;
			this->label5->Text = L"*BUFFER";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(186, 29);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(100, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"*RAW_INTENSITY";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(378, 29);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(41, 13);
			this->label7->TabIndex = 11;
			this->label7->Text = L"*CROP";
			// 
			// pictureBox4
			// 
			this->pictureBox4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox4->Location = System::Drawing::Point(641, 45);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(281, 281);
			this->pictureBox4->TabIndex = 12;
			this->pictureBox4->TabStop = false;
			// 
			// E
			// 
			this->E->AutoSize = true;
			this->E->Location = System::Drawing::Point(730, 29);
			this->E->Name = L"E";
			this->E->Size = System::Drawing::Size(88, 13);
			this->E->TabIndex = 13;
			this->E->Text = L"*DIGITAL ZOOM";
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::SystemColors::Info;
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->label4);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->label10);
			this->panel2->Controls->Add(this->label9);
			this->panel2->Controls->Add(this->label8);
			this->panel2->Location = System::Drawing::Point(945, 45);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(101, 281);
			this->panel2->TabIndex = 14;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(2, 64);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(30, 13);
			this->label10->TabIndex = 2;
			this->label10->Text = L"Size:";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(2, 39);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(41, 13);
			this->label9->TabIndex = 1;
			this->label9->Text = L"Height:";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 14);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(38, 13);
			this->label8->TabIndex = 0;
			this->label8->Text = L"Width:";
			// 
			// chart1
			// 
			this->chart1->AllowDrop = true;
			chartArea3->Name = L"ChartArea1";
			this->chart1->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->chart1->Legends->Add(legend3);
			this->chart1->Location = System::Drawing::Point(12, 213);
			this->chart1->Name = L"chart1";
			this->chart1->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::SemiTransparent;
			series3->ChartArea = L"ChartArea1";
			series3->Legend = L"Legend1";
			series3->Name = L"Number Of Pixel";
			this->chart1->Series->Add(series3);
			this->chart1->Size = System::Drawing::Size(299, 252);
			this->chart1->TabIndex = 15;
			this->chart1->Text = L"chart1";
			// 
			// chart2
			// 
			chartArea4->Name = L"ChartArea1";
			this->chart2->ChartAreas->Add(chartArea4);
			legend4->Name = L"Legend1";
			this->chart2->Legends->Add(legend4);
			this->chart2->Location = System::Drawing::Point(329, 213);
			this->chart2->Name = L"chart2";
			this->chart2->Palette = System::Windows::Forms::DataVisualization::Charting::ChartColorPalette::SemiTransparent;
			series4->ChartArea = L"ChartArea1";
			series4->Legend = L"Legend1";
			series4->Name = L"Number Of Pixel";
			this->chart2->Series->Add(series4);
			this->chart2->Size = System::Drawing::Size(301, 252);
			this->chart2->TabIndex = 16;
			this->chart2->Text = L"chart2";
			// 
			// pictureBox5
			// 
			this->pictureBox5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pictureBox5->Location = System::Drawing::Point(490, 45);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(140, 140);
			this->pictureBox5->TabIndex = 17;
			this->pictureBox5->TabStop = false;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(531, 29);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(62, 13);
			this->label11->TabIndex = 18;
			this->label11->Text = L"*STRETCH";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(964, 29);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(60, 13);
			this->label12->TabIndex = 19;
			this->label12->Text = L"Bitmap Info";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->ClientSize = System::Drawing::Size(1057, 481);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->chart1);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->E);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->pictureBox3);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
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

			label8->Text = "Width: " + width + " px";
			label9->Text = "Height: " + height + " px";
			label10->Text = "Size: " + size + " byte";
		}
	}

	private: System::Void yIntesityToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		BYTE* raw_intensity = ConvertBMPToIntensity(buffer, width, height);

		Bitmap^ img = gcnew Bitmap(pictureBox2->Width, pictureBox2->Height);
		pictureBox2->Image = img;
		Color c;
		int temp;

		for (unsigned int row = 0; row <height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(raw_intensity[temp], raw_intensity[temp], raw_intensity[temp]);
				img->SetPixel(column, row, c);
			}
		delete[]raw_intensity;
	}
	private: System::Void pictureBox2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		
		if (pictureBox2->Image)
		{
			flag = 1;
			x = e->X;
			y = e->Y;
			label1->Text = "X: " + e->X;
			label2->Text = "Y: " + e->Y;
		}
		
	}
	private: System::Void pictureBox2_MouseMove(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		try
		{		
			if (pictureBox2->Image && flag == 1)
			{
				box_W = e->X;
				box_H = e->Y;
				BYTE* crop = ConvertBMPToIntensity(buffer, width, height);

				Bitmap^ imgCrop = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
				pictureBox3->Image = imgCrop;
				Color c;
				int temp;

				for (unsigned int row = y; row <box_H; row++)
					for (unsigned int column = x; column < box_W; column++)
					{
						temp = row * width + column;
						c = Color::FromArgb(crop[temp], crop[temp], crop[temp]);
						imgCrop->SetPixel(column, row, c);

					}
				delete[]crop;
			}
		}
		catch (const System::ArgumentOutOfRangeException^ e)
		{
			flag = 0;
			MessageBox::Show("Hata");
		}
		
	}
	private: System::Void pictureBox2_MouseUp(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		try
		{	
			if (pictureBox2->Image)
			{
				flag = 0;
				box_W = e->X;
				box_H = e->Y;
				label3->Text = "boxW: " + e->X;
				label4->Text = "boxH: " + e->Y;
				BYTE* crop = ConvertBMPToIntensity(buffer, width, height);

				Bitmap^ imgCrop = gcnew Bitmap(pictureBox3->Width, pictureBox3->Height);
				pictureBox3->Image = imgCrop;
				Color c;
				int temp;

				for (unsigned int row = y; row <box_H; row++)
					for (unsigned int column = x; column < box_W; column++)
					{
						temp = row * width + column;
						c = Color::FromArgb(crop[temp], crop[temp], crop[temp]);
						imgCrop->SetPixel(column, row, c);
					}

				delete[]crop;
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
	
		BYTE* raw_intensity = ConvertBMPToIntensity(buffer, width, height);
		BYTE* zoom = DigitalZoom(raw_intensity, width, height);
		
		Bitmap^ imgZoom = gcnew Bitmap(pictureBox4->Width, pictureBox4->Height);
		pictureBox4->Image = imgZoom;
		Color c;
		int temp;

		for (unsigned int row = 0; row <2*height+1; row++)
			for (unsigned int column = 0; column <2 * width + 1; column++)
			{
				temp = row * (2 * width + 1) + column;
				c = Color::FromArgb(zoom[temp], zoom[temp], zoom[temp]);
				imgZoom->SetPixel(column, row, c);
			}
		delete[] zoom;
		
		
	}
		
	private: System::Void histogramToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		chart1->Titles->Clear();
		chart1->Series->Clear();
		chart1->Series->Add("Number Of Pixel");

		BYTE* raw_intensity = ConvertBMPToIntensity(buffer, width, height);
		/*int *histogram = new int[256];

		for (unsigned int i = 0; i < 256; i++)
			histogram[i] = 0;

		for(unsigned int pos = 0; pos <width*height; pos++)
		{
			int t = raw_intensity[pos];
			histogram[t]++;
		}*/
		int *hist = Histogram(raw_intensity, width, height);
		for (unsigned int i = 0; i < 256; i++)
		{
			chart1->Series["Number Of Pixel"]->Points->AddXY(i, hist[i]);
		}

		chart1->Titles->Add("Histogram");
		delete[]hist;
		delete[]raw_intensity;
		
	}

	private: System::Void stretchToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		chart2->Titles->Clear();
		chart2->Series->Clear();
		chart2->Series->Add("Number Of Pixel");

		BYTE* raw_intensity = ConvertBMPToIntensity(buffer, width, height); // rgb to Y intensity
		BYTE* new_intensity = Stretch(raw_intensity, width, height);
		int *tempHistogram = Histogram(new_intensity, width, height); // Yayma(Stretch) histogramý

		for (unsigned int i = 0; i < 256; i++)
		{
			chart2->Series["Number Of Pixel"]->Points->AddXY(i, tempHistogram[i]);
		}
		chart2->Titles->Add("Histogram(Stretch)");

		Bitmap^ a = gcnew Bitmap(pictureBox5->Width, pictureBox5->Height);
		pictureBox5->Image = a;
		Color c;
		int temp;

		for (unsigned int row = 0; row <height; row++)
			for (unsigned int column = 0; column < width; column++)
			{
				temp = row * width + column;
				c = Color::FromArgb(new_intensity[temp], new_intensity[temp], new_intensity[temp]);
				a->SetPixel(column, row, c);
			}
		
		delete[]tempHistogram;
		delete[]new_intensity;
	}

};
}
