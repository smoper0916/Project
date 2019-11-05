#pragma once
#include "BottomMenuBar.h"
#include "전국날씨.h"
#include "과거날씨.h"
#include "AlarmPage.h"
#include "Week.h"

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	double extern formOp;
	int extern stateCount;
	int extern bottomFormClose;
	static double topmenuOp = 0;

	int extern mainCloseCount;
	int extern countryCloseCount;
	int extern alarmCloseCount;


	/// <summary>
	/// TopMenuBar에 대한 요약입니다.
	/// </summary>
	public ref class TopMenuBar : public System::Windows::Forms::Form
	{
	public:
		TopMenuBar(void)
		{
			InitializeComponent();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~TopMenuBar()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnHome;
	private: System::Windows::Forms::Button^  btnWeek;
	private: System::Windows::Forms::Button^  btnCountry;
	private: System::Windows::Forms::Button^  btnPast;
	private: System::Windows::Forms::Button^  btnAlarm;
	private: System::Windows::Forms::Timer^  TopMenuTimer;


	private: System::ComponentModel::IContainer^  components;



	protected:





	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다.
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(TopMenuBar::typeid));
			this->btnHome = (gcnew System::Windows::Forms::Button());
			this->btnWeek = (gcnew System::Windows::Forms::Button());
			this->btnCountry = (gcnew System::Windows::Forms::Button());
			this->btnPast = (gcnew System::Windows::Forms::Button());
			this->btnAlarm = (gcnew System::Windows::Forms::Button());
			this->TopMenuTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// btnHome
			// 
			this->btnHome->BackColor = System::Drawing::Color::Transparent;
			this->btnHome->FlatAppearance->BorderSize = 0;
			this->btnHome->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnHome.Image")));
			this->btnHome->Location = System::Drawing::Point(155, 60);
			this->btnHome->Margin = System::Windows::Forms::Padding(4);
			this->btnHome->Name = L"btnHome";
			this->btnHome->Size = System::Drawing::Size(207, 87);
			this->btnHome->TabIndex = 0;
			this->btnHome->UseVisualStyleBackColor = false;
			this->btnHome->Click += gcnew System::EventHandler(this, &TopMenuBar::btnHome_Click);
			// 
			// btnWeek
			// 
			this->btnWeek->BackColor = System::Drawing::Color::Transparent;
			this->btnWeek->FlatAppearance->BorderSize = 0;
			this->btnWeek->Font = (gcnew System::Drawing::Font(L"서울남산체 B", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->btnWeek->ForeColor = System::Drawing::Color::White;
			this->btnWeek->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnWeek.Image")));
			this->btnWeek->Location = System::Drawing::Point(370, 60);
			this->btnWeek->Margin = System::Windows::Forms::Padding(4);
			this->btnWeek->Name = L"btnWeek";
			this->btnWeek->Size = System::Drawing::Size(206, 87);
			this->btnWeek->TabIndex = 1;
			this->btnWeek->UseVisualStyleBackColor = false;
			this->btnWeek->Click += gcnew System::EventHandler(this, &TopMenuBar::btnWeek_Click);
			// 
			// btnCountry
			// 
			this->btnCountry->BackColor = System::Drawing::Color::Transparent;
			this->btnCountry->FlatAppearance->BorderSize = 0;
			this->btnCountry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnCountry.Image")));
			this->btnCountry->Location = System::Drawing::Point(584, 60);
			this->btnCountry->Margin = System::Windows::Forms::Padding(4);
			this->btnCountry->Name = L"btnCountry";
			this->btnCountry->Size = System::Drawing::Size(207, 87);
			this->btnCountry->TabIndex = 2;
			this->btnCountry->UseVisualStyleBackColor = false;
			this->btnCountry->Click += gcnew System::EventHandler(this, &TopMenuBar::btnCountry_Click);
			// 
			// btnPast
			// 
			this->btnPast->BackColor = System::Drawing::Color::Transparent;
			this->btnPast->FlatAppearance->BorderSize = 0;
			this->btnPast->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnPast.Image")));
			this->btnPast->Location = System::Drawing::Point(798, 60);
			this->btnPast->Margin = System::Windows::Forms::Padding(4);
			this->btnPast->Name = L"btnPast";
			this->btnPast->Size = System::Drawing::Size(207, 87);
			this->btnPast->TabIndex = 3;
			this->btnPast->UseVisualStyleBackColor = false;
			this->btnPast->Click += gcnew System::EventHandler(this, &TopMenuBar::btnPast_Click);
			// 
			// btnAlarm
			// 
			this->btnAlarm->BackColor = System::Drawing::Color::Transparent;
			this->btnAlarm->FlatAppearance->BorderSize = 0;
			this->btnAlarm->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAlarm.Image")));
			this->btnAlarm->Location = System::Drawing::Point(1013, 60);
			this->btnAlarm->Margin = System::Windows::Forms::Padding(4);
			this->btnAlarm->Name = L"btnAlarm";
			this->btnAlarm->Size = System::Drawing::Size(207, 87);
			this->btnAlarm->TabIndex = 4;
			this->btnAlarm->UseVisualStyleBackColor = false;
			this->btnAlarm->Click += gcnew System::EventHandler(this, &TopMenuBar::btnAlarm_Click);
			// 
			// TopMenuTimer
			// 
			this->TopMenuTimer->Interval = 50;
			this->TopMenuTimer->Tick += gcnew System::EventHandler(this, &TopMenuBar::TopMenuTimer_Tick);
			// 
			// TopMenuBar
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::DimGray;
			this->ClientSize = System::Drawing::Size(1417, 180);
			this->Controls->Add(this->btnAlarm);
			this->Controls->Add(this->btnPast);
			this->Controls->Add(this->btnCountry);
			this->Controls->Add(this->btnWeek);
			this->Controls->Add(this->btnHome);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(186, 106);
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"TopMenuBar";
			this->Opacity = 0;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"TopMenuBar";
			this->Load += gcnew System::EventHandler(this, &TopMenuBar::TopMenuBar_Load);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &TopMenuBar::TopMenuBar_MouseDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void TopMenuTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		this->Opacity = topmenuOp;
		topmenuOp += 0.05;

		if (topmenuOp>0.95)
		{
			TopMenuTimer->Stop();
		}
	}



	private: System::Void TopMenuBar_Load(System::Object^  sender, System::EventArgs^  e) {

		TopMenuTimer->Start();
	}

	private: System::Void TopMenuBar_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			bottomFormClose = 1;
			topmenuOp = 0;
			formOp = 1;
			stateCount = 1;
			this->Close();
		}
	}
	private: System::Void btnWeek_Click(System::Object^  sender, System::EventArgs^  e) {
		Week^ week = gcnew Week();
		week->Show();

		topmenuOp = 0;
		formOp = 1;
		stateCount = 1;

		weekCloseCount = 2;
		alarmCloseCount = 1;
		countryCloseCount = 1;
		pastCloseCount = 1;
		mainCloseCount = 1;
		bottomFormClose = 1;

		this->Close();
	}
	private: System::Void btnCountry_Click(System::Object^  sender, System::EventArgs^  e) {
		전국날씨^ korea = gcnew 전국날씨();
		korea->Show();

		countryCloseCount = 2;
		alarmCloseCount = 1;
		weekCloseCount = 1;
		pastCloseCount = 1;
		mainCloseCount = 1;
		bottomFormClose = 1;

		topmenuOp = 0;
		formOp = 1;
		stateCount = 1;



		this->Close();
	}
	private: System::Void btnPast_Click(System::Object^  sender, System::EventArgs^  e) {
		과거날씨^ past = gcnew 과거날씨();
		past->Show();

		pastCloseCount = 2;
		alarmCloseCount = 1;
		weekCloseCount = 1;
		mainCloseCount = 1;
		countryCloseCount = 1;
		bottomFormClose = 1;

		formOp = 1;
		topmenuOp = 0;
		this->Close();
	}
	private: System::Void btnHome_Click(System::Object^  sender, System::EventArgs^  e) {


		formOp = 1;
		topmenuOp = 0;
		stateCount = 1;

		mainCloseCount = 2;
		alarmCloseCount = 1;
		weekCloseCount = 1;
		bottomFormClose = 1;
		countryCloseCount = 1;
		pastCloseCount = 1;
		this->Close();
	}
	private: System::Void btnAlarm_Click(System::Object^  sender, System::EventArgs^  e) {
		AlarmPage^ alarm = gcnew AlarmPage();
		alarm->Show();

		topmenuOp = 0;
		formOp = 1;
		stateCount = 1;

		alarmCloseCount = 2;
		weekCloseCount = 1;
		countryCloseCount = 1;
		pastCloseCount = 1;
		mainCloseCount = 1;
		bottomFormClose = 1;

		this->Close();
	}
};
}
