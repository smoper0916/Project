#pragma once

#include "Alarm.h"
#include "Search.h"
#include "TopMenuBar.h"

namespace newCLR {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	using namespace System::Threading;
	using namespace System::Timers;

	int Hour = System::DateTime::Now.Hour;
	int Minute = System::DateTime::Now.Minute;

	int temp;
	int moningLow = 10;
	int moningHigh = 10;
	int afterLow = 10;
	int afterHigh = 10;
	int nightLow = 10;
	int nightHigh = 10;
	int dwanLow = 10;
	int dwanHigh = 10;
	int tommorowLow = 10;
	int tommorowHigh = 10;
	int todayMax;
	int todayMin;


	int nameCount = 0;
	int valueCount = 0;
	int btnCount = 0;

	//투명화
	double formOp = 1;
	int stateCount = 0;
	int bottomFormClose = 0;

	//menubar
	int menubarState = 0;

	//Close
	int mainCloseCount;
	int countryCloseCount;
	int pastCloseCount;
	int weekCloseCount;
	int alarmCloseCount;

	//Position
	int menubarPosition = 0;

	int applicationClose = 0;
	/// <summary>
	/// Form1에 대한 요약입니다.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		String^ location;
		String^ todayWeather;
		String^ sHour;
		String^ sMinute;
	private: System::Windows::Forms::Timer^  nowtimeTimer;
	private: System::Windows::Forms::Timer^  backgroundTimer;
	private: System::Windows::Forms::Button^  btnFavorite3;
	private: System::Windows::Forms::Button^  btnFavorite2;
	private: System::Windows::Forms::Button^  btnFavorite1;

	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Timer^  FormOp;
	private: System::Windows::Forms::Timer^  stateTimer;
			 String^ ipParserURL;
			 String^ latitude, ^longitude; // 위도, 경도 값
	public: String^ A_Location, ^B_Location, ^C_Location, ^LSN = "";
			int LSC, LSC_Weather;
			int fullMax = 3481;
			array<String^>^ totalArr = nullptr;
			bool currentPlace = true;
			String^ otherCityCode = "";

			ref class Info
			{
			public:
				String^ big, ^mid, ^small;

				Info(String^ big, String^ mid, String^ small)
				{
					this->big = big;
					this->mid = mid;
					this->small = small;
				}
			};

	public:

	public:

		array<String^>^ favoriteList = gcnew array<String^>(3);
		int favoriteCnt = 0;
		String^ selectFavorite;
	private: System::Windows::Forms::Button^  btnNowLocation;
	public:

	public:
		///////////////////////////////////////////////////////////////
		String^ data;
		String^ getData()
		{
			return data;
		}

		Form1(String^ data)
		{
			this->data = data;
		}
		/////////////////////////////////////////////////////////////////

		Form1(void)
		{
			InitializeComponent();

			// ip를 통해 현재위치를 알려주는 site
			ipParserURL = "http://ipinfodb.com/";

			// ip를 통해 현재 위도, 경도를 얻고 그것을 이용해 근처 지역을 찾는다.
			findLocation(ipParserURL);
			findNearLocation();

			ReadFullRegion();
			nowTemp(A_Location, B_Location, C_Location);
			backgroundAuto();
			btnView();
			loadFavorite();
		}
		void saveFavorite(String^ cityName)
		{
			String^ fileName = "favorite.dat";

			FileStream^ fs = gcnew FileStream(fileName, FileMode::Append, FileAccess::Write);
			// append 이어쓰기
			StreamWriter^ sw = gcnew StreamWriter(fs, System::Text::Encoding::UTF8);

			sw->WriteLine("{0}", cityName);
			favoriteList[favoriteCnt++] = cityName;

			sw->Flush();
			sw->Close();
			fs->Close();
			fs = nullptr;
			sw = nullptr;
		}
		void deleteFavorite(String^ cityName, int index)
		{
			String^ fileName = "favorite.dat";

			favoriteList[index] = "DELETE";

			FileStream^ fs = gcnew FileStream(fileName, FileMode::Create, FileAccess::Write);
			StreamWriter^ sw = gcnew StreamWriter(fs, System::Text::Encoding::UTF8);

			for (int i = 0; i < favoriteCnt; i++)
			{
				if (favoriteList[i] == "DELETE")
				{
				}
				else if (favoriteList[i] == nullptr)
				{

				}
				else
				{
					sw->WriteLine("{0}", favoriteList[i]);
				}
			}
			favoriteCnt--;

			sw->Flush();
			sw->Close();
			fs->Close();
			fs = nullptr;
			sw = nullptr;

		}
		void loadFavorite()
		{
			String^ fileName = "favorite.dat";
			favoriteCnt = 0;

			FileStream^ fs = gcnew FileStream(fileName, FileMode::OpenOrCreate, FileAccess::Read);
			StreamReader^ st = gcnew StreamReader(fs, System::Text::Encoding::UTF8);
			st->BaseStream->Seek(0, SeekOrigin::Begin);
			while (st->Peek() > -1)
			{
				String^ temp = st->ReadLine();
				favoriteList[btnCount++] = temp;
				favoriteCnt++;
				if (favoriteCnt == 1)
				{
					btnFavorite1->Show();
					btnFavorite1->Text = temp;

					btnAdd->Left = 228;
					btnAdd->Top = 14;
				}
				else if (favoriteCnt == 2)
				{
					btnFavorite2->Show();
					btnFavorite2->Text = temp;

					btnFavorite2->Left = 241;
					btnFavorite2->Top = 14;

					btnAdd->Left = 342;
					btnAdd->Top = 14;

				}
				else if (favoriteCnt == 3)
				{
					btnFavorite3->Show();
					btnFavorite3->Text = temp;


					btnFavorite1->Left = 127;
					btnFavorite1->Top = 14;

					btnFavorite2->Left = 241;
					btnFavorite2->Top = 14;

					btnFavorite3->Left = 362;
					btnFavorite3->Top = 14;

					btnAdd->Left = 486;
					btnAdd->Top = 14;

				}
			}
			st->Close();
			fs->Close();
		}
	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pb01;
	protected:

	private: System::Windows::Forms::Label^  lbtempNow;
	private: System::Windows::Forms::Label^  lbTommorowHigh;
	private: System::Windows::Forms::Label^  lbTommorowLow;

	private: System::Windows::Forms::Label^  lbDwanLow;

	private: System::Windows::Forms::Label^  lbNightLow;

	private: System::Windows::Forms::Label^  lbAfterLow;

	private: System::Windows::Forms::Label^  lbMoningLow;
	private: System::Windows::Forms::Label^  lbTommorow;
	private: System::Windows::Forms::Label^  lbDawn;
	private: System::Windows::Forms::Label^  lbNight;
	private: System::Windows::Forms::Label^  lbAfternoon;
	private: System::Windows::Forms::Label^  lbMonig;
	private: System::Windows::Forms::PictureBox^  pbTommorow;
	private: System::Windows::Forms::PictureBox^  pbDawn;
	private: System::Windows::Forms::PictureBox^  pbNight;
	private: System::Windows::Forms::PictureBox^  pbAfternoon;
	private: System::Windows::Forms::PictureBox^  pbMoning;
	private: System::Windows::Forms::Label^  lbLocation;
	private: System::Windows::Forms::Label^  lbNowtime;
	private: System::Windows::Forms::Button^  btnAlarm;
	private: System::Windows::Forms::Label^  lbTodayMin;

	private: System::Windows::Forms::Label^  lbTodayMax;

	private: System::Windows::Forms::Label^  lbToday;
	private: System::Windows::Forms::PictureBox^  pbToday;
	private: System::ComponentModel::IContainer^  components;




	protected:

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->pb01 = (gcnew System::Windows::Forms::PictureBox());
			this->lbtempNow = (gcnew System::Windows::Forms::Label());
			this->lbTommorowHigh = (gcnew System::Windows::Forms::Label());
			this->lbTommorowLow = (gcnew System::Windows::Forms::Label());
			this->lbDwanLow = (gcnew System::Windows::Forms::Label());
			this->lbNightLow = (gcnew System::Windows::Forms::Label());
			this->lbAfterLow = (gcnew System::Windows::Forms::Label());
			this->lbMoningLow = (gcnew System::Windows::Forms::Label());
			this->lbTommorow = (gcnew System::Windows::Forms::Label());
			this->lbDawn = (gcnew System::Windows::Forms::Label());
			this->lbNight = (gcnew System::Windows::Forms::Label());
			this->lbAfternoon = (gcnew System::Windows::Forms::Label());
			this->lbMonig = (gcnew System::Windows::Forms::Label());
			this->pbTommorow = (gcnew System::Windows::Forms::PictureBox());
			this->pbDawn = (gcnew System::Windows::Forms::PictureBox());
			this->pbNight = (gcnew System::Windows::Forms::PictureBox());
			this->pbAfternoon = (gcnew System::Windows::Forms::PictureBox());
			this->pbMoning = (gcnew System::Windows::Forms::PictureBox());
			this->lbLocation = (gcnew System::Windows::Forms::Label());
			this->lbNowtime = (gcnew System::Windows::Forms::Label());
			this->btnAlarm = (gcnew System::Windows::Forms::Button());
			this->lbTodayMin = (gcnew System::Windows::Forms::Label());
			this->lbTodayMax = (gcnew System::Windows::Forms::Label());
			this->lbToday = (gcnew System::Windows::Forms::Label());
			this->pbToday = (gcnew System::Windows::Forms::PictureBox());
			this->nowtimeTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->backgroundTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnFavorite3 = (gcnew System::Windows::Forms::Button());
			this->btnFavorite2 = (gcnew System::Windows::Forms::Button());
			this->btnFavorite1 = (gcnew System::Windows::Forms::Button());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->FormOp = (gcnew System::Windows::Forms::Timer(this->components));
			this->stateTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnNowLocation = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb01))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTommorow))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDawn))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbNight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbAfternoon))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMoning))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbToday))->BeginInit();
			this->SuspendLayout();
			// 
			// pb01
			// 
			this->pb01->Location = System::Drawing::Point(-10, -2);
			this->pb01->Margin = System::Windows::Forms::Padding(4);
			this->pb01->Name = L"pb01";
			this->pb01->Size = System::Drawing::Size(1429, 710);
			this->pb01->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb01->TabIndex = 0;
			this->pb01->TabStop = false;
			this->pb01->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::pb01_MouseDown);
			// 
			// lbtempNow
			// 
			this->lbtempNow->AutoSize = true;
			this->lbtempNow->BackColor = System::Drawing::Color::Transparent;
			this->lbtempNow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 110.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbtempNow->ForeColor = System::Drawing::Color::White;
			this->lbtempNow->Location = System::Drawing::Point(2, 494);
			this->lbtempNow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbtempNow->Name = L"lbtempNow";
			this->lbtempNow->Size = System::Drawing::Size(436, 166);
			this->lbtempNow->TabIndex = 3;
			this->lbtempNow->Text = L"Label";
			// 
			// lbTommorowHigh
			// 
			this->lbTommorowHigh->AutoSize = true;
			this->lbTommorowHigh->BackColor = System::Drawing::Color::Transparent;
			this->lbTommorowHigh->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbTommorowHigh->ForeColor = System::Drawing::Color::DodgerBlue;
			this->lbTommorowHigh->Location = System::Drawing::Point(1221, 660);
			this->lbTommorowHigh->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbTommorowHigh->Name = L"lbTommorowHigh";
			this->lbTommorowHigh->Size = System::Drawing::Size(24, 25);
			this->lbTommorowHigh->TabIndex = 42;
			this->lbTommorowHigh->Text = L"0";
			// 
			// lbTommorowLow
			// 
			this->lbTommorowLow->AutoSize = true;
			this->lbTommorowLow->BackColor = System::Drawing::Color::Transparent;
			this->lbTommorowLow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbTommorowLow->ForeColor = System::Drawing::Color::White;
			this->lbTommorowLow->Location = System::Drawing::Point(1144, 660);
			this->lbTommorowLow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbTommorowLow->Name = L"lbTommorowLow";
			this->lbTommorowLow->Size = System::Drawing::Size(24, 25);
			this->lbTommorowLow->TabIndex = 41;
			this->lbTommorowLow->Text = L"0";
			// 
			// lbDwanLow
			// 
			this->lbDwanLow->AutoSize = true;
			this->lbDwanLow->BackColor = System::Drawing::Color::Transparent;
			this->lbDwanLow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbDwanLow->ForeColor = System::Drawing::Color::White;
			this->lbDwanLow->Location = System::Drawing::Point(1039, 662);
			this->lbDwanLow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbDwanLow->Name = L"lbDwanLow";
			this->lbDwanLow->Size = System::Drawing::Size(24, 25);
			this->lbDwanLow->TabIndex = 39;
			this->lbDwanLow->Text = L"0";
			// 
			// lbNightLow
			// 
			this->lbNightLow->AutoSize = true;
			this->lbNightLow->BackColor = System::Drawing::Color::Transparent;
			this->lbNightLow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbNightLow->ForeColor = System::Drawing::Color::White;
			this->lbNightLow->Location = System::Drawing::Point(885, 662);
			this->lbNightLow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbNightLow->Name = L"lbNightLow";
			this->lbNightLow->Size = System::Drawing::Size(24, 25);
			this->lbNightLow->TabIndex = 37;
			this->lbNightLow->Text = L"0";
			// 
			// lbAfterLow
			// 
			this->lbAfterLow->AutoSize = true;
			this->lbAfterLow->BackColor = System::Drawing::Color::Transparent;
			this->lbAfterLow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbAfterLow->ForeColor = System::Drawing::Color::White;
			this->lbAfterLow->Location = System::Drawing::Point(729, 660);
			this->lbAfterLow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbAfterLow->Name = L"lbAfterLow";
			this->lbAfterLow->Size = System::Drawing::Size(24, 25);
			this->lbAfterLow->TabIndex = 35;
			this->lbAfterLow->Text = L"0";
			// 
			// lbMoningLow
			// 
			this->lbMoningLow->AutoSize = true;
			this->lbMoningLow->BackColor = System::Drawing::Color::Transparent;
			this->lbMoningLow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbMoningLow->ForeColor = System::Drawing::Color::White;
			this->lbMoningLow->Location = System::Drawing::Point(571, 662);
			this->lbMoningLow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbMoningLow->Name = L"lbMoningLow";
			this->lbMoningLow->Size = System::Drawing::Size(24, 25);
			this->lbMoningLow->TabIndex = 33;
			this->lbMoningLow->Text = L"0";
			// 
			// lbTommorow
			// 
			this->lbTommorow->AutoSize = true;
			this->lbTommorow->BackColor = System::Drawing::Color::Transparent;
			this->lbTommorow->Font = (gcnew System::Drawing::Font(L"나눔고딕", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbTommorow->ForeColor = System::Drawing::Color::White;
			this->lbTommorow->Location = System::Drawing::Point(1154, 514);
			this->lbTommorow->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbTommorow->Name = L"lbTommorow";
			this->lbTommorow->Size = System::Drawing::Size(79, 38);
			this->lbTommorow->TabIndex = 32;
			this->lbTommorow->Text = L"내일";
			// 
			// lbDawn
			// 
			this->lbDawn->AutoSize = true;
			this->lbDawn->BackColor = System::Drawing::Color::Transparent;
			this->lbDawn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbDawn->ForeColor = System::Drawing::Color::White;
			this->lbDawn->Location = System::Drawing::Point(1004, 514);
			this->lbDawn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbDawn->Name = L"lbDawn";
			this->lbDawn->Size = System::Drawing::Size(79, 38);
			this->lbDawn->TabIndex = 31;
			this->lbDawn->Text = L"새벽";
			// 
			// lbNight
			// 
			this->lbNight->AutoSize = true;
			this->lbNight->BackColor = System::Drawing::Color::Transparent;
			this->lbNight->Font = (gcnew System::Drawing::Font(L"나눔고딕", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbNight->ForeColor = System::Drawing::Color::White;
			this->lbNight->Location = System::Drawing::Point(849, 514);
			this->lbNight->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbNight->Name = L"lbNight";
			this->lbNight->Size = System::Drawing::Size(79, 38);
			this->lbNight->TabIndex = 30;
			this->lbNight->Text = L"저녁";
			// 
			// lbAfternoon
			// 
			this->lbAfternoon->AutoSize = true;
			this->lbAfternoon->BackColor = System::Drawing::Color::Transparent;
			this->lbAfternoon->Font = (gcnew System::Drawing::Font(L"나눔고딕", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbAfternoon->ForeColor = System::Drawing::Color::White;
			this->lbAfternoon->Location = System::Drawing::Point(693, 514);
			this->lbAfternoon->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbAfternoon->Name = L"lbAfternoon";
			this->lbAfternoon->Size = System::Drawing::Size(79, 38);
			this->lbAfternoon->TabIndex = 29;
			this->lbAfternoon->Text = L"점심";
			// 
			// lbMonig
			// 
			this->lbMonig->AutoSize = true;
			this->lbMonig->BackColor = System::Drawing::Color::Transparent;
			this->lbMonig->Font = (gcnew System::Drawing::Font(L"나눔고딕", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbMonig->ForeColor = System::Drawing::Color::White;
			this->lbMonig->Location = System::Drawing::Point(534, 514);
			this->lbMonig->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbMonig->Name = L"lbMonig";
			this->lbMonig->Size = System::Drawing::Size(79, 38);
			this->lbMonig->TabIndex = 28;
			this->lbMonig->Text = L"아침";
			// 
			// pbTommorow
			// 
			this->pbTommorow->BackColor = System::Drawing::Color::Transparent;
			this->pbTommorow->Location = System::Drawing::Point(1154, 566);
			this->pbTommorow->Margin = System::Windows::Forms::Padding(4);
			this->pbTommorow->Name = L"pbTommorow";
			this->pbTommorow->Size = System::Drawing::Size(111, 92);
			this->pbTommorow->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbTommorow->TabIndex = 27;
			this->pbTommorow->TabStop = false;
			// 
			// pbDawn
			// 
			this->pbDawn->BackColor = System::Drawing::Color::Transparent;
			this->pbDawn->Location = System::Drawing::Point(1004, 566);
			this->pbDawn->Margin = System::Windows::Forms::Padding(4);
			this->pbDawn->Name = L"pbDawn";
			this->pbDawn->Size = System::Drawing::Size(111, 92);
			this->pbDawn->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbDawn->TabIndex = 26;
			this->pbDawn->TabStop = false;
			// 
			// pbNight
			// 
			this->pbNight->BackColor = System::Drawing::Color::Transparent;
			this->pbNight->Location = System::Drawing::Point(849, 566);
			this->pbNight->Margin = System::Windows::Forms::Padding(4);
			this->pbNight->Name = L"pbNight";
			this->pbNight->Size = System::Drawing::Size(111, 92);
			this->pbNight->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbNight->TabIndex = 25;
			this->pbNight->TabStop = false;
			// 
			// pbAfternoon
			// 
			this->pbAfternoon->BackColor = System::Drawing::Color::Transparent;
			this->pbAfternoon->Location = System::Drawing::Point(693, 566);
			this->pbAfternoon->Margin = System::Windows::Forms::Padding(4);
			this->pbAfternoon->Name = L"pbAfternoon";
			this->pbAfternoon->Size = System::Drawing::Size(111, 92);
			this->pbAfternoon->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbAfternoon->TabIndex = 24;
			this->pbAfternoon->TabStop = false;
			// 
			// pbMoning
			// 
			this->pbMoning->BackColor = System::Drawing::Color::Transparent;
			this->pbMoning->Location = System::Drawing::Point(530, 566);
			this->pbMoning->Margin = System::Windows::Forms::Padding(4);
			this->pbMoning->Name = L"pbMoning";
			this->pbMoning->Size = System::Drawing::Size(111, 92);
			this->pbMoning->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbMoning->TabIndex = 23;
			this->pbMoning->TabStop = false;
			// 
			// lbLocation
			// 
			this->lbLocation->AutoSize = true;
			this->lbLocation->BackColor = System::Drawing::Color::Transparent;
			this->lbLocation->Dock = System::Windows::Forms::DockStyle::Right;
			this->lbLocation->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbLocation->ForeColor = System::Drawing::Color::Transparent;
			this->lbLocation->Location = System::Drawing::Point(1260, 0);
			this->lbLocation->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbLocation->Name = L"lbLocation";
			this->lbLocation->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->lbLocation->Size = System::Drawing::Size(147, 38);
			this->lbLocation->TabIndex = 43;
			this->lbLocation->Text = L"Location";
			// 
			// lbNowtime
			// 
			this->lbNowtime->AutoSize = true;
			this->lbNowtime->BackColor = System::Drawing::Color::Transparent;
			this->lbNowtime->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbNowtime->ForeColor = System::Drawing::Color::Transparent;
			this->lbNowtime->Location = System::Drawing::Point(601, 13);
			this->lbNowtime->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbNowtime->Name = L"lbNowtime";
			this->lbNowtime->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->lbNowtime->Size = System::Drawing::Size(178, 38);
			this->lbNowtime->TabIndex = 44;
			this->lbNowtime->Text = L"오후 12:00";
			// 
			// btnAlarm
			// 
			this->btnAlarm->BackColor = System::Drawing::Color::Transparent;
			this->btnAlarm->FlatAppearance->BorderSize = 0;
			this->btnAlarm->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnAlarm->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnAlarm->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnAlarm->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnAlarm.Image")));
			this->btnAlarm->Location = System::Drawing::Point(799, -9);
			this->btnAlarm->Margin = System::Windows::Forms::Padding(4);
			this->btnAlarm->Name = L"btnAlarm";
			this->btnAlarm->Size = System::Drawing::Size(81, 94);
			this->btnAlarm->TabIndex = 45;
			this->btnAlarm->TabStop = false;
			this->btnAlarm->UseVisualStyleBackColor = false;
			this->btnAlarm->Click += gcnew System::EventHandler(this, &Form1::btnAlarm_Click);
			// 
			// lbTodayMin
			// 
			this->lbTodayMin->AutoSize = true;
			this->lbTodayMin->BackColor = System::Drawing::Color::Transparent;
			this->lbTodayMin->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->lbTodayMin->ForeColor = System::Drawing::Color::DodgerBlue;
			this->lbTodayMin->Location = System::Drawing::Point(189, 453);
			this->lbTodayMin->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbTodayMin->Name = L"lbTodayMin";
			this->lbTodayMin->Size = System::Drawing::Size(29, 31);
			this->lbTodayMin->TabIndex = 49;
			this->lbTodayMin->Text = L"0";
			// 
			// lbTodayMax
			// 
			this->lbTodayMax->AutoSize = true;
			this->lbTodayMax->BackColor = System::Drawing::Color::Transparent;
			this->lbTodayMax->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->lbTodayMax->ForeColor = System::Drawing::Color::White;
			this->lbTodayMax->Location = System::Drawing::Point(71, 453);
			this->lbTodayMax->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbTodayMax->Name = L"lbTodayMax";
			this->lbTodayMax->Size = System::Drawing::Size(29, 31);
			this->lbTodayMax->TabIndex = 48;
			this->lbTodayMax->Text = L"0";
			// 
			// lbToday
			// 
			this->lbToday->AutoSize = true;
			this->lbToday->BackColor = System::Drawing::Color::Transparent;
			this->lbToday->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 24.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbToday->ForeColor = System::Drawing::Color::White;
			this->lbToday->Location = System::Drawing::Point(190, 378);
			this->lbToday->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbToday->Name = L"lbToday";
			this->lbToday->Size = System::Drawing::Size(79, 38);
			this->lbToday->TabIndex = 47;
			this->lbToday->Text = L"오늘";
			// 
			// pbToday
			// 
			this->pbToday->BackColor = System::Drawing::Color::Transparent;
			this->pbToday->Location = System::Drawing::Point(54, 315);
			this->pbToday->Margin = System::Windows::Forms::Padding(4);
			this->pbToday->Name = L"pbToday";
			this->pbToday->Size = System::Drawing::Size(128, 117);
			this->pbToday->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbToday->TabIndex = 46;
			this->pbToday->TabStop = false;
			// 
			// nowtimeTimer
			// 
			this->nowtimeTimer->Enabled = true;
			this->nowtimeTimer->Interval = 1000;
			this->nowtimeTimer->Tick += gcnew System::EventHandler(this, &Form1::nowtimeTimer_Tick);
			// 
			// backgroundTimer
			// 
			this->backgroundTimer->Enabled = true;
			this->backgroundTimer->Interval = 10000;
			this->backgroundTimer->Tick += gcnew System::EventHandler(this, &Form1::backgroundTimer_Tick);
			// 
			// btnFavorite3
			// 
			this->btnFavorite3->BackColor = System::Drawing::Color::Transparent;
			this->btnFavorite3->FlatAppearance->BorderSize = 0;
			this->btnFavorite3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnFavorite3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnFavorite3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnFavorite3->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnFavorite3->ForeColor = System::Drawing::Color::White;
			this->btnFavorite3->Location = System::Drawing::Point(362, 14);
			this->btnFavorite3->Margin = System::Windows::Forms::Padding(4);
			this->btnFavorite3->Name = L"btnFavorite3";
			this->btnFavorite3->Size = System::Drawing::Size(93, 58);
			this->btnFavorite3->TabIndex = 54;
			this->btnFavorite3->TabStop = false;
			this->btnFavorite3->Text = L"추가3";
			this->btnFavorite3->UseVisualStyleBackColor = false;
			this->btnFavorite3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnFavorite3_MouseClick);
			this->btnFavorite3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnFavorite3_MouseDown);
			// 
			// btnFavorite2
			// 
			this->btnFavorite2->BackColor = System::Drawing::Color::Transparent;
			this->btnFavorite2->FlatAppearance->BorderSize = 0;
			this->btnFavorite2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnFavorite2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnFavorite2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnFavorite2->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnFavorite2->ForeColor = System::Drawing::Color::White;
			this->btnFavorite2->Location = System::Drawing::Point(241, 14);
			this->btnFavorite2->Margin = System::Windows::Forms::Padding(4);
			this->btnFavorite2->Name = L"btnFavorite2";
			this->btnFavorite2->Size = System::Drawing::Size(93, 58);
			this->btnFavorite2->TabIndex = 53;
			this->btnFavorite2->TabStop = false;
			this->btnFavorite2->Text = L"추가2";
			this->btnFavorite2->UseVisualStyleBackColor = false;
			this->btnFavorite2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnFavorite2_MouseClick);
			this->btnFavorite2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnFavorite2_MouseDown);
			// 
			// btnFavorite1
			// 
			this->btnFavorite1->BackColor = System::Drawing::Color::Transparent;
			this->btnFavorite1->FlatAppearance->BorderSize = 0;
			this->btnFavorite1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnFavorite1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnFavorite1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnFavorite1->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnFavorite1->ForeColor = System::Drawing::Color::White;
			this->btnFavorite1->Location = System::Drawing::Point(127, 14);
			this->btnFavorite1->Margin = System::Windows::Forms::Padding(4);
			this->btnFavorite1->Name = L"btnFavorite1";
			this->btnFavorite1->Size = System::Drawing::Size(93, 58);
			this->btnFavorite1->TabIndex = 52;
			this->btnFavorite1->TabStop = false;
			this->btnFavorite1->Text = L"추가1";
			this->btnFavorite1->UseVisualStyleBackColor = false;
			this->btnFavorite1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnFavorite1_MouseClick);
			this->btnFavorite1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnFavorite1_MouseDown);
			// 
			// btnAdd
			// 
			this->btnAdd->BackColor = System::Drawing::Color::Transparent;
			this->btnAdd->FlatAppearance->BorderSize = 0;
			this->btnAdd->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnAdd->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnAdd->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->btnAdd->ForeColor = System::Drawing::Color::White;
			this->btnAdd->Location = System::Drawing::Point(127, 14);
			this->btnAdd->Margin = System::Windows::Forms::Padding(4);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(59, 54);
			this->btnAdd->TabIndex = 50;
			this->btnAdd->TabStop = false;
			this->btnAdd->Text = L"+";
			this->btnAdd->UseVisualStyleBackColor = false;
			this->btnAdd->Click += gcnew System::EventHandler(this, &Form1::btnAdd_Click);
			// 
			// FormOp
			// 
			this->FormOp->Interval = 50;
			this->FormOp->Tick += gcnew System::EventHandler(this, &Form1::FormOp_Tick);
			// 
			// stateTimer
			// 
			this->stateTimer->Interval = 50;
			this->stateTimer->Tick += gcnew System::EventHandler(this, &Form1::stateTimer_Tick);
			// 
			// btnNowLocation
			// 
			this->btnNowLocation->BackColor = System::Drawing::Color::Transparent;
			this->btnNowLocation->FlatAppearance->BorderSize = 0;
			this->btnNowLocation->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnNowLocation->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnNowLocation->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnNowLocation->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnNowLocation->ForeColor = System::Drawing::Color::White;
			this->btnNowLocation->Location = System::Drawing::Point(13, 14);
			this->btnNowLocation->Margin = System::Windows::Forms::Padding(4);
			this->btnNowLocation->Name = L"btnNowLocation";
			this->btnNowLocation->Size = System::Drawing::Size(93, 58);
			this->btnNowLocation->TabIndex = 51;
			this->btnNowLocation->TabStop = false;
			this->btnNowLocation->Text = L"현위치";
			this->btnNowLocation->UseVisualStyleBackColor = false;
			this->btnNowLocation->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::btnNowLocation_MouseClick);
			// 
			// Form1
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(1407, 708);
			this->Controls->Add(this->btnFavorite3);
			this->Controls->Add(this->btnFavorite2);
			this->Controls->Add(this->btnFavorite1);
			this->Controls->Add(this->btnNowLocation);
			this->Controls->Add(this->btnAdd);
			this->Controls->Add(this->lbTodayMin);
			this->Controls->Add(this->lbTodayMax);
			this->Controls->Add(this->lbToday);
			this->Controls->Add(this->pbToday);
			this->Controls->Add(this->btnAlarm);
			this->Controls->Add(this->lbNowtime);
			this->Controls->Add(this->lbLocation);
			this->Controls->Add(this->lbTommorowHigh);
			this->Controls->Add(this->lbTommorowLow);
			this->Controls->Add(this->lbDwanLow);
			this->Controls->Add(this->lbNightLow);
			this->Controls->Add(this->lbAfterLow);
			this->Controls->Add(this->lbMoningLow);
			this->Controls->Add(this->lbTommorow);
			this->Controls->Add(this->lbDawn);
			this->Controls->Add(this->lbNight);
			this->Controls->Add(this->lbAfternoon);
			this->Controls->Add(this->lbMonig);
			this->Controls->Add(this->pbTommorow);
			this->Controls->Add(this->pbDawn);
			this->Controls->Add(this->pbNight);
			this->Controls->Add(this->pbAfternoon);
			this->Controls->Add(this->pbMoning);
			this->Controls->Add(this->lbtempNow);
			this->Controls->Add(this->pb01);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"날씨 정보 소프트웨어";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb01))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbTommorow))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbDawn))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbNight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbAfternoon))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMoning))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbToday))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		void time();
		void nowTemp(String^ A_Loc, String^ B_Loc, String^ C_Loc);
		void backgroundAuto();
		void backgroundAuto(String^ LSC);
		void afternoon();
		void night();
		void btnView();

	private: System::Void nowtimeTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		/// 위치조정
		
		Hour = System::DateTime::Now.Hour;
		Minute = System::DateTime::Now.Minute;
		time();

		if (applicationClose == 1)
		{
			this->Close();
		}
		if (mainCloseCount == 1)
		{
			this->Hide();
			mainCloseCount = 0;
		}
		else if (mainCloseCount == 2)
		{
			this->Show();
			mainCloseCount = 0;
		}

		if (menubarState == 1)
		{
			if (menubarPosition == 0)
			{
				TopMenuBar^ topmenubar = gcnew TopMenuBar();
				topmenubar->Location = System::Drawing::Point(this->Location.X, this->Location.Y);
				topmenubar->Show();
				BottomMenuBar^ bottomMenubar = gcnew BottomMenuBar();
				bottomMenubar->Width = this->Width;
				bottomMenubar->Location = System::Drawing::Point(this->Location.X, 690);
				bottomMenubar->Show();
			}

			else
			{
				TopMenuBar^ topmenubar = gcnew TopMenuBar();
				topmenubar->Location = System::Drawing::Point(250, 160);
				topmenubar->Show();
				BottomMenuBar^ bottomMenubar = gcnew BottomMenuBar();
				bottomMenubar->Width = this->Width;
				bottomMenubar->Location = System::Drawing::Point(250, 690);
				bottomMenubar->Show();
			}

			menubarState = 0;
		}

	}
	private: System::Void backgroundTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		backgroundAuto();
	}

	private: System::Void btnAdd_Click(System::Object^  sender, System::EventArgs^  e) {

		btnCount++;

		stateCount = 0;
		FormOp->Start();
		stateTimer->Start();
		Search^ search = gcnew Search();
		search->ShowDialog();

		if (btnCount == 1)
		{
			btnFavorite1->Show();
			btnFavorite1->Text = search->getLocationName();
			saveFavorite(search->getLocationName());

			if (btnFavorite2->Visible == true && btnFavorite3->Visible == false)
			{
				btnAdd->Left = 327;
				btnAdd->Top = 14;

				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite2->Left = 241;
				btnFavorite2->Top = 14;

				btnCount = 2;
			}
			else if (btnFavorite2->Visible == false && btnFavorite3->Visible == true)
			{
				btnAdd->Left = 327;
				btnAdd->Top = 16;

				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite3->Left = 241;
				btnFavorite3->Top = 14;
			}
			else if (btnFavorite2->Visible == true && btnFavorite3->Visible == true)
			{
				btnAdd->Left = 486;
				btnAdd->Top = 14;

				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite2->Left = 241;
				btnFavorite2->Top = 14;

				btnFavorite3->Left = 362;
				btnFavorite3->Top = 14;
			}
			else
			{
				btnAdd->Left = 228;
				btnAdd->Top = 14;
			}
		}
		else if (btnCount == 2)
		{
			btnFavorite2->Show();
			btnFavorite2->Text = search->getLocationName();
			saveFavorite(search->getLocationName());

			if (btnFavorite1->Visible == true && btnFavorite3->Visible == false)
			{
				btnFavorite2->Left = 241;
				btnFavorite2->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else if (btnFavorite1->Visible == false && btnFavorite3->Visible == true)
			{
				btnFavorite2->Left = 127;
				btnFavorite2->Top = 14;

				btnFavorite3->Left = 241;
				btnFavorite3->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else if (btnFavorite1->Visible == true && btnFavorite3->Visible == true)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite2->Left = 241;
				btnFavorite2->Top = 14;

				btnFavorite3->Left = 362;
				btnFavorite3->Top = 14;

				btnAdd->Left = 486;
				btnAdd->Top = 14;
			}
			else
			{
				btnFavorite2->Left = 127;
				btnFavorite2->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
			}


		}
		else if (btnCount == 3)
		{
			btnFavorite3->Show();
			btnFavorite3->Text = search->getLocationName();
			saveFavorite(search->getLocationName());

			if (btnFavorite1->Visible == true && btnFavorite2->Visible == false)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite3->Left = 241;
				btnFavorite3->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else if (btnFavorite1->Visible == false && btnFavorite2->Visible == true)
			{
				btnFavorite2->Left = 127;
				btnFavorite2->Top = 14;

				btnFavorite3->Left = 241;
				btnFavorite3->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else if (btnFavorite1->Visible == true && btnFavorite2->Visible == true)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite2->Left = 241;
				btnFavorite2->Top = 14;

				btnFavorite3->Left = 362;
				btnFavorite3->Top = 14;

				btnAdd->Left = 486;
				btnAdd->Top = 14;
			}
			else
			{
				btnFavorite3->Left = 127;
				btnFavorite3->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
			}
		}
	}
	private: System::Void btnFavorite1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right && (btnCount == 1))
		{
			btnCount--;
			btnFavorite1->Hide();
			deleteFavorite(btnFavorite1->Text, btnCount);

			if (btnFavorite2->Visible == true && btnFavorite3->Visible == false)
			{
				btnFavorite2->Left = 127;
				btnFavorite2->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
			}
			else if (btnFavorite2->Visible == false && btnFavorite3->Visible == true)
			{
				btnFavorite3->Left = 127;
				btnFavorite3->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
			}
			else if (btnFavorite2->Visible == true && btnFavorite3->Visible == true)
			{
				btnFavorite2->Left = 127;
				btnFavorite2->Top = 14;

				btnFavorite3->Left = 241;
				btnFavorite3->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else
			{
				btnAdd->Left = 127;
				btnAdd->Top = 14;
			}
		}
	}

	private: System::Void btnFavorite2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right && (btnCount == 2))
		{
			btnCount--;
			btnFavorite2->Hide();
			deleteFavorite(btnFavorite2->Text, btnCount);

			if (btnFavorite1->Visible == true && btnFavorite3->Visible == false)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
			}
			else if (btnFavorite1->Visible == false && btnFavorite3->Visible == true)
			{
				btnFavorite3->Left = 127;
				btnFavorite3->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
				btnCount = 0;
			}
			else if (btnFavorite1->Visible == true && btnFavorite3->Visible == true)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite3->Left = 241;
				btnFavorite3->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else
			{
				btnAdd->Left = 127;
				btnAdd->Top = 14;
				btnCount = 0;
			}
		}
	}
	private: System::Void btnFavorite3_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right && (btnCount == 3))
		{
			btnCount--;
			btnFavorite3->Hide();
			deleteFavorite(btnFavorite3->Text, btnCount);

			if (btnFavorite1->Visible == true && btnFavorite2->Visible == false)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
				btnCount = 1;
			}
			else if (btnFavorite1->Visible == false && btnFavorite2->Visible == true)
			{
				btnFavorite2->Left = 127;
				btnFavorite2->Top = 14;

				btnAdd->Left = 228;
				btnAdd->Top = 14;
				btnCount = 0;
			}
			else if (btnFavorite1->Visible == true && btnFavorite2->Visible == true)
			{
				btnFavorite1->Left = 127;
				btnFavorite1->Top = 14;

				btnFavorite2->Left = 241;
				btnFavorite2->Top = 14;

				btnAdd->Left = 342;
				btnAdd->Top = 14;
			}
			else
			{
				btnAdd->Left = 127;
				btnAdd->Top = 14;
				btnCount = 0;
			}
		}
	}

	private: System::Void btnAlarm_Click(System::Object^  sender, System::EventArgs^  e) {

		stateCount = 0;
		FormOp->Start();
		stateTimer->Start();
		Alarm^ alarm = gcnew Alarm();
		alarm->ShowDialog();

	}
	private: System::Void FormOp_Tick(System::Object^  sender, System::EventArgs^  e) {

		this->Opacity = formOp;
		formOp -= 0.015;

		if (formOp <= 0.8)
		{
			FormOp->Stop();
		}
	}
	private: System::Void stateTimer_Tick(System::Object^  sender, System::EventArgs^  e) {

		if (stateCount == 1)
		{
			this->Opacity = 1;
			stateTimer->Stop();
		}
	}
	private: System::Void pb01_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			stateCount = 0;
			FormOp->Start();
			stateTimer->Start();
			menubarPosition = 0;
			menubarState = 1;

		}

	}
			 ref class position
			 {
			 public:
				 int^ code;
				 double lat;
				 double lon;
				 double min;

				 String^ pData;
				 String^ getpData()
				 {
					 return pData;
				 }

				 position(String^ pData)
				 {
					 this->pData = pData;
				 }
			 };

			 ref class locationData
			 {
			 public:
				 int^ code;
				 String^ F_lo;
				 String^ S_lo;

				 String^ lData;
				 String^ getlData()
				 {
					 return lData;
				 }

				 locationData(String^ lData)
				 {
					 this->lData = lData;
				 }
			 };

			 Void findLocation(String^ url)
			 {
				 HtmlAgilityPack::HtmlWeb^ web = gcnew HtmlAgilityPack::HtmlWeb();
				 HtmlAgilityPack::HtmlDocument^ doc = web->Load(url);


				 int count = 0;
				 for each(HtmlAgilityPack::HtmlNode^ node in doc->DocumentNode->SelectNodes("//div[@class]"))
				 {
					 HtmlAgilityPack::HtmlAttributeCollection^ arr = node->Attributes;

					 if (arr->Count == 0) {
						 continue;
					 }
					 else {
						 if (arr[0]->OriginalName == "class" && arr[0]->Value == "section") {
							 count++;
							 if (count == 3)
							 {
								 //MessageBox::Show(node->InnerHtml);

								 //MessageBox::Show(node->Attributes[0]->Value);
								 //continue;
								 for each(HtmlAgilityPack::HtmlNode^ i in node->SelectNodes("//li"))
								 {
									 if (i->InnerText->Contains("Latitude") || i->InnerText->Contains("Longitude")) {

										 array<String^, 1>^ splittedData = i->InnerText->Split(':');
										 if (splittedData[0]->Contains("Latitude")) {
											 latitude = splittedData[1]->Trim();
										 }
										 else {
											 longitude = splittedData[1]->Trim();
										 }
									 }
								 }
							 }
						 }
					 }





				 }
			 }
	private:  System::Void findNearLocation()
	{

		int^ code;
		double lat;
		double lon;
		double mylat;
		double mylon;

		double min;
		bool isFirst = true;

		mylat = Convert::ToDouble(latitude);
		mylon = Convert::ToDouble(longitude);

		int valueCount = 0;
		XmlTextReader^ reder = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/visit_search_result.php?lat=" + latitude + "&lon=" + longitude);
		array< position^ >^ baseData = gcnew array< position^ >(3);


		while (reder->Read())
		{
			switch (reder->NodeType)
			{
			case XmlNodeType::Text:

				baseData[valueCount] = gcnew position(reder->Value);

				if (valueCount == 2)
				{
					double result = 0;

					if (isFirst)
					{
						code = Convert::ToInt32(baseData[0]->getpData());
						lat = Convert::ToDouble(baseData[1]->getpData());
						lon = Convert::ToDouble(baseData[2]->getpData());
						min = Math::Sqrt((mylat - lat)*(mylat - lat) + (mylon - lon)*(mylon - lon)); // 최소

						isFirst = false;

						valueCount = 0;
						continue;
					}

					result = Math::Sqrt((mylat - Convert::ToDouble(baseData[1]->getpData()))*(mylat - Convert::ToDouble(baseData[1]->getpData())) +
						(mylon - Convert::ToDouble(baseData[2]->getpData()))*(mylon - Convert::ToDouble(baseData[2]->getpData())));

					if (result < min)
					{
						code = Convert::ToInt32(baseData[0]->getpData());
						lat = Convert::ToDouble(baseData[1]->getpData());
						lon = Convert::ToDouble(baseData[2]->getpData());

						min = result;
					}
					valueCount = 0;
					continue;
				}
				valueCount++;

				break;
			}
		}

		//MessageBox::Show("" + code);

		int testCount = 0;
		XmlTextReader^ loReader = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/xml/specified_region_result.xml");
		array<locationData^>^ loData = gcnew array<locationData^>(10);

		bool isSecond = true;

		int^ loCode;
		String^ Big_Location;
		String^ Mid_Location;
		String^ Small_Location;

		while (loReader->Read())
		{
			switch (loReader->NodeType)
			{
			case XmlNodeType::Text:

				loData[testCount] = gcnew locationData(loReader->Value);

				if (testCount == 7)
				{
					if (isSecond)
					{
						loCode = Convert::ToInt32(loData[0]->getlData());
						A_Location = loData[1]->getlData();
						B_Location = loData[2]->getlData();
						C_Location = loData[3]->getlData();

						isSecond = false;

						testCount = 0;
						continue;
					}

					loCode = Convert::ToInt32(loData[0]->getlData());
					A_Location = loData[1]->getlData();
					B_Location = loData[2]->getlData();
					C_Location = loData[3]->getlData();

					if (code->Equals(loCode))
					{
						break;
					}

					testCount = 0;
					continue;
				}
				testCount++;
				break;
			}
			if (code->Equals(loCode))
				break;
		}
		location = A_Location + " " + B_Location + " " + C_Location;


		XmlTextReader^ standardCode = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/xml/total_cities.xml");
		array< String^ >^ nowLocationStandardCode = gcnew array< String^ >(5);
		int valueCount3 = 0;

		while (standardCode->Read())
		{
			switch (standardCode->NodeType)
			{
			case XmlNodeType::Text:

				nowLocationStandardCode[valueCount3] = standardCode->Value;

				if (valueCount3 == 3)
				{
					LSC = Convert::ToInt32(nowLocationStandardCode[0]);
					LSN = Convert::ToString(nowLocationStandardCode[2]);
					LSC_Weather = Convert::ToInt32(nowLocationStandardCode[3]);
					if (LSN->Equals(B_Location))
						break;

					valueCount3 = 0;
					continue;
				}
				valueCount3++;
				break;
			}
			if (LSN->Equals(B_Location))
				break;
		}

	}
	Void resetData() {
		nowTemp(A_Location, B_Location, C_Location);
		backgroundAuto();
		lbLocation->Text = A_Location + " " + B_Location + " " + C_Location;
	}
	private: System::Void btnFavorite1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		selectFavorite = btnFavorite1->Text;
		findFirst(btnFavorite1->Text);
	}
	private: System::Void btnFavorite2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		selectFavorite = btnFavorite2->Text;
		findFirst(btnFavorite2->Text);
	}
	private: System::Void btnFavorite3_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		selectFavorite = btnFavorite3->Text;
		findFirst(btnFavorite3->Text);
	}
	private: System::Void btnNowLocation_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		// 현재위치
		resetData();
		currentPlace = true;
		backgroundAuto();
	}

			 ref class IOHandler
			 {
			 private:
				 String^ fileName = "동네예보_동네별위경도_오픈API용.csv";

			 public:
				 array<Info^>^ read(int max)
				 {

					 array<Info^>^ pArr = gcnew array<Info^>(max);
					 int count = 0;
					 FileInfo^ FI = gcnew FileInfo(fileName);
					 if (FI->Exists)
					 {
						 StreamReader^ sr = gcnew StreamReader(fileName);
						 while (sr->Peek() >= 0)
						 {
							 if (count == max)
								 break;
							 array<String^>^ arr = sr->ReadLine()->Split(',');
							 pArr[count++] = gcnew Info(arr[0], arr[1], arr[2]);
						 }
						 sr->Close();
					 }
					 else
						 MessageBox::Show("File Not Found! - File Name : " + fileName);
					 return pArr;
				 }
			 };
			 Void ReadFullRegion() {
				 IOHandler^ io = gcnew IOHandler();
				 array<Info^>^ arr = io->read(fullMax);
				 totalArr = gcnew array<String^>(fullMax);

				 // 전체 string 값을 조합
				 for (int i = 0; i < fullMax; i++)
				 {
					 totalArr[i] = arr[i]->big + " " + arr[i]->mid + " " + arr[i]->small;
				 }
			 }
			 Void findFirst(String^ subject) {

				 String^ selected = "";
				 for (int i = 0; i < fullMax; i++) {
					 if (totalArr[i]->Contains(subject))
					 {
						 selected = totalArr[i];
						 break;
					 }
				 }
				 if (selected == "")
					 return;
				 array<String^>^ arr = selected->Split(' ');
				 nowTemp(arr[0], arr[1], arr[2]);
				 String^ gu = "";
				 if ((!arr[0]->Contains("광역시") && !arr[0]->Contains("특별시")) && arr[1]->Length >= 5) {
					 int pos = arr[1]->IndexOf("시");
					 String^ result = arr[1]->Substring(0, pos + 1);
					 gu = arr[1]->Substring(pos + 1);
					 arr[1] = result;
				 }
				 lbLocation->Text = arr[0] + " " + arr[1] + " " + gu;

				 XmlTextReader^ standardCode = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/xml/total_cities.xml");
				 array< String^ >^ nowLocationStandardCode = gcnew array< String^ >(5);
				 int valueCount3 = 0;
				 String^ lsCode, ^lsName, ^lsStd;

				 while (standardCode->Read())
				 {
					 switch (standardCode->NodeType)
					 {
					 case XmlNodeType::Text:

						 nowLocationStandardCode[valueCount3] = standardCode->Value;

						 if (valueCount3 == 3)
						 {
							 lsCode = nowLocationStandardCode[0];
							 lsName = nowLocationStandardCode[2];
							 lsStd = nowLocationStandardCode[3];
							 valueCount3 = 0;
							 continue;
						 }
						 valueCount3++;
						 break;
					 }
					 if (arr[0]->Contains("광역시") || arr[0]->Contains("특별시")) {
						 if (lsName != nullptr && lsName->Equals(arr[0]))
							 break;
					 }
					 else {
						 if (lsName != nullptr && lsName->Equals(arr[1]))
							 break;
					 }
				 }
				 backgroundAuto(lsCode);
				 otherCityCode = lsCode;
				 currentPlace = false;
			 }
};
}

