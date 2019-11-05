#pragma once

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;

	extern int countryCloseCount;
	extern int menubarState;

	extern int menubarPosition;

	public ref class 전국날씨 : public System::Windows::Forms::Form
	{

	public:
		array<String^>^ nation_Weather = gcnew array<String^>(50);

		전국날씨(void)
		{
			InitializeComponent();
			XmlTextReader^ reder = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/show_national_weather.php");

			int valueCount = 0;

			while (reder->Read())
			{
				switch (reder->NodeType)
				{
				case XmlNodeType::Text:

					nation_Weather[valueCount] = reder->Value;
					valueCount++;
					break;
				}
			}
			seoul_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[0])) + "℃";
			seoul_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[1])) + "℃";
			daegu_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[18])) + "℃";
			daegu_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[19])) + "℃";
			busan_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[36])) + "℃";
			busan_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[37])) + "℃";
			daejeon_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[12])) + "℃";
			daejeon_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[13])) + "℃";
			incheon_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[6])) + "℃";
			incheon_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[7])) + "℃";
			ulsan_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[30])) + "℃";
			ulsan_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[31])) + "℃";
			kwangju_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[24])) + "℃";
			kwangju_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[25])) + "℃";
			jeju_tmx->Text = Math::Round(Convert::ToSingle(nation_Weather[42])) + "℃";
			jeju_tmn->Text = Math::Round(Convert::ToSingle(nation_Weather[43])) + "℃";
		}

	protected:

		~전국날씨()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:

	private: System::Windows::Forms::PictureBox^  pb전국지도;
	private: System::Windows::Forms::Button^  btnSeoul;

	private: System::Windows::Forms::PictureBox^  pb설명;
	private: System::Windows::Forms::Label^  lbName;
	private: System::Windows::Forms::Label^  lb날씨;
	private: System::Windows::Forms::Label^  lbState;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  lb최고기온;
	private: System::Windows::Forms::Label^  lb최저기온;
	private: System::Windows::Forms::Label^  lb강수확률;
	private: System::Windows::Forms::Label^  lb습도;
	private: System::Windows::Forms::Button^  btnBusan;
	private: System::Windows::Forms::Button^  btnUlsan;


	private: System::Windows::Forms::Button^  btnKwangju;

	private: System::Windows::Forms::Button^  btnDaegu;
	private: System::Windows::Forms::Button^  btnJeju;


	private: System::Windows::Forms::Button^  btnDaejeon;

	private: System::Windows::Forms::Button^  btnIncheon;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::Label^  seoul_tmn;

	private: System::Windows::Forms::Label^  seoul_tmx;

	private: System::Windows::Forms::Label^  daejeon_tmn;

	private: System::Windows::Forms::Label^  daejeon_tmx;

	private: System::Windows::Forms::Label^  daegu_tmn;

	private: System::Windows::Forms::Label^  daegu_tmx;
	private: System::Windows::Forms::Label^  ulsan_tmn;


	private: System::Windows::Forms::Label^  ulsan_tmx;
	private: System::Windows::Forms::Label^  busan_tmn;


	private: System::Windows::Forms::Label^  busan_tmx;
	private: System::Windows::Forms::Label^  jeju_tmn;


	private: System::Windows::Forms::Label^  jeju_tmx;
	private: System::Windows::Forms::Label^  incheon_tmn;


	private: System::Windows::Forms::Label^  incheon_tmx;

	private: System::Windows::Forms::Label^  kwangju_tmn;

	private: System::Windows::Forms::Label^  kwangju_tmx;

	private: System::Windows::Forms::PictureBox^  pictureBox8;
private: System::Windows::Forms::Timer^  closeTimer;
	private: System::ComponentModel::IContainer^  components;




	private:



#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(전국날씨::typeid));
			this->pb전국지도 = (gcnew System::Windows::Forms::PictureBox());
			this->btnSeoul = (gcnew System::Windows::Forms::Button());
			this->pb설명 = (gcnew System::Windows::Forms::PictureBox());
			this->lbName = (gcnew System::Windows::Forms::Label());
			this->lb날씨 = (gcnew System::Windows::Forms::Label());
			this->lbState = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->lb최고기온 = (gcnew System::Windows::Forms::Label());
			this->lb최저기온 = (gcnew System::Windows::Forms::Label());
			this->lb강수확률 = (gcnew System::Windows::Forms::Label());
			this->lb습도 = (gcnew System::Windows::Forms::Label());
			this->btnBusan = (gcnew System::Windows::Forms::Button());
			this->btnUlsan = (gcnew System::Windows::Forms::Button());
			this->btnKwangju = (gcnew System::Windows::Forms::Button());
			this->btnDaegu = (gcnew System::Windows::Forms::Button());
			this->btnJeju = (gcnew System::Windows::Forms::Button());
			this->btnDaejeon = (gcnew System::Windows::Forms::Button());
			this->btnIncheon = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->seoul_tmn = (gcnew System::Windows::Forms::Label());
			this->seoul_tmx = (gcnew System::Windows::Forms::Label());
			this->daejeon_tmn = (gcnew System::Windows::Forms::Label());
			this->daejeon_tmx = (gcnew System::Windows::Forms::Label());
			this->daegu_tmn = (gcnew System::Windows::Forms::Label());
			this->daegu_tmx = (gcnew System::Windows::Forms::Label());
			this->ulsan_tmn = (gcnew System::Windows::Forms::Label());
			this->ulsan_tmx = (gcnew System::Windows::Forms::Label());
			this->busan_tmn = (gcnew System::Windows::Forms::Label());
			this->busan_tmx = (gcnew System::Windows::Forms::Label());
			this->jeju_tmn = (gcnew System::Windows::Forms::Label());
			this->jeju_tmx = (gcnew System::Windows::Forms::Label());
			this->incheon_tmn = (gcnew System::Windows::Forms::Label());
			this->incheon_tmx = (gcnew System::Windows::Forms::Label());
			this->kwangju_tmn = (gcnew System::Windows::Forms::Label());
			this->kwangju_tmx = (gcnew System::Windows::Forms::Label());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->closeTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb전국지도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb설명))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			this->SuspendLayout();
			// 
			// pb전국지도
			// 
			this->pb전국지도->BackColor = System::Drawing::Color::Transparent;
			this->pb전국지도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb전국지도.Image")));
			this->pb전국지도->Location = System::Drawing::Point(177, 59);
			this->pb전국지도->Margin = System::Windows::Forms::Padding(4);
			this->pb전국지도->Name = L"pb전국지도";
			this->pb전국지도->Size = System::Drawing::Size(500, 616);
			this->pb전국지도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb전국지도->TabIndex = 47;
			this->pb전국지도->TabStop = false;
			// 
			// btnSeoul
			// 
			this->btnSeoul->BackColor = System::Drawing::Color::White;
			this->btnSeoul->FlatAppearance->BorderSize = 0;
			this->btnSeoul->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnSeoul->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnSeoul->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSeoul->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSeoul.Image")));
			this->btnSeoul->Location = System::Drawing::Point(306, 127);
			this->btnSeoul->Margin = System::Windows::Forms::Padding(4);
			this->btnSeoul->Name = L"btnSeoul";
			this->btnSeoul->Size = System::Drawing::Size(50, 30);
			this->btnSeoul->TabIndex = 48;
			this->btnSeoul->TabStop = false;
			this->btnSeoul->UseVisualStyleBackColor = false;
			this->btnSeoul->Click += gcnew System::EventHandler(this, &전국날씨::btnSeoul_Click);
			// 
			// pb설명
			// 
			this->pb설명->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb설명.Image")));
			this->pb설명->Location = System::Drawing::Point(905, 102);
			this->pb설명->Margin = System::Windows::Forms::Padding(4);
			this->pb설명->Name = L"pb설명";
			this->pb설명->Size = System::Drawing::Size(427, 540);
			this->pb설명->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb설명->TabIndex = 50;
			this->pb설명->TabStop = false;
			// 
			// lbName
			// 
			this->lbName->AutoSize = true;
			this->lbName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lbName->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbName->ForeColor = System::Drawing::Color::White;
			this->lbName->Location = System::Drawing::Point(1017, 134);
			this->lbName->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbName->Name = L"lbName";
			this->lbName->Size = System::Drawing::Size(96, 46);
			this->lbName->TabIndex = 51;
			this->lbName->Text = L"지역";
			// 
			// lb날씨
			// 
			this->lb날씨->AutoSize = true;
			this->lb날씨->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lb날씨->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb날씨->ForeColor = System::Drawing::Color::White;
			this->lb날씨->Location = System::Drawing::Point(971, 234);
			this->lb날씨->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb날씨->Name = L"lb날씨";
			this->lb날씨->Size = System::Drawing::Size(81, 31);
			this->lb날씨->TabIndex = 52;
			this->lb날씨->Text = L"날씨 :";
			// 
			// lbState
			// 
			this->lbState->AutoSize = true;
			this->lbState->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lbState->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbState->ForeColor = System::Drawing::Color::White;
			this->lbState->Location = System::Drawing::Point(1100, 234);
			this->lbState->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbState->Name = L"lbState";
			this->lbState->Size = System::Drawing::Size(64, 31);
			this->lbState->TabIndex = 53;
			this->lbState->Text = L"상태";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->label1->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::White;
			this->label1->Location = System::Drawing::Point(939, 302);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(139, 31);
			this->label1->TabIndex = 54;
			this->label1->Text = L"최고 기온 :";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->label2->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label2->Location = System::Drawing::Point(939, 385);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(139, 31);
			this->label2->TabIndex = 55;
			this->label2->Text = L"최저 기온 :";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->label3->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(939, 468);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(139, 31);
			this->label3->TabIndex = 56;
			this->label3->Text = L"강수 확률 :";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->label4->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(971, 547);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(81, 31);
			this->label4->TabIndex = 57;
			this->label4->Text = L"습도 :";
			// 
			// lb최고기온
			// 
			this->lb최고기온->AutoSize = true;
			this->lb최고기온->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lb최고기온->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb최고기온->ForeColor = System::Drawing::Color::White;
			this->lb최고기온->Location = System::Drawing::Point(1148, 302);
			this->lb최고기온->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb최고기온->Name = L"lb최고기온";
			this->lb최고기온->Size = System::Drawing::Size(64, 31);
			this->lb최고기온->TabIndex = 58;
			this->lb최고기온->Text = L"기온";
			// 
			// lb최저기온
			// 
			this->lb최저기온->AutoSize = true;
			this->lb최저기온->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lb최저기온->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb최저기온->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->lb최저기온->Location = System::Drawing::Point(1148, 385);
			this->lb최저기온->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb최저기온->Name = L"lb최저기온";
			this->lb최저기온->Size = System::Drawing::Size(64, 31);
			this->lb최저기온->TabIndex = 59;
			this->lb최저기온->Text = L"기온";
			// 
			// lb강수확률
			// 
			this->lb강수확률->AutoSize = true;
			this->lb강수확률->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lb강수확률->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb강수확률->ForeColor = System::Drawing::Color::White;
			this->lb강수확률->Location = System::Drawing::Point(1150, 468);
			this->lb강수확률->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb강수확률->Name = L"lb강수확률";
			this->lb강수확률->Size = System::Drawing::Size(64, 31);
			this->lb강수확률->TabIndex = 60;
			this->lb강수확률->Text = L"확률";
			// 
			// lb습도
			// 
			this->lb습도->AutoSize = true;
			this->lb습도->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->lb습도->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb습도->ForeColor = System::Drawing::Color::White;
			this->lb습도->Location = System::Drawing::Point(1148, 547);
			this->lb습도->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb습도->Name = L"lb습도";
			this->lb습도->Size = System::Drawing::Size(64, 31);
			this->lb습도->TabIndex = 61;
			this->lb습도->Text = L"습도";
			// 
			// btnBusan
			// 
			this->btnBusan->BackColor = System::Drawing::Color::White;
			this->btnBusan->FlatAppearance->BorderSize = 0;
			this->btnBusan->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnBusan->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnBusan->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnBusan->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnBusan.Image")));
			this->btnBusan->Location = System::Drawing::Point(438, 491);
			this->btnBusan->Margin = System::Windows::Forms::Padding(4);
			this->btnBusan->Name = L"btnBusan";
			this->btnBusan->Size = System::Drawing::Size(50, 30);
			this->btnBusan->TabIndex = 62;
			this->btnBusan->TabStop = false;
			this->btnBusan->UseVisualStyleBackColor = false;
			this->btnBusan->Click += gcnew System::EventHandler(this, &전국날씨::button1_Click);
			// 
			// btnUlsan
			// 
			this->btnUlsan->BackColor = System::Drawing::Color::White;
			this->btnUlsan->FlatAppearance->BorderSize = 0;
			this->btnUlsan->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnUlsan->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnUlsan->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnUlsan->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnUlsan.Image")));
			this->btnUlsan->Location = System::Drawing::Point(501, 442);
			this->btnUlsan->Margin = System::Windows::Forms::Padding(4);
			this->btnUlsan->Name = L"btnUlsan";
			this->btnUlsan->Size = System::Drawing::Size(50, 30);
			this->btnUlsan->TabIndex = 63;
			this->btnUlsan->TabStop = false;
			this->btnUlsan->UseVisualStyleBackColor = false;
			this->btnUlsan->Click += gcnew System::EventHandler(this, &전국날씨::button2_Click);
			// 
			// btnKwangju
			// 
			this->btnKwangju->BackColor = System::Drawing::Color::White;
			this->btnKwangju->FlatAppearance->BorderSize = 0;
			this->btnKwangju->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnKwangju->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnKwangju->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnKwangju->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnKwangju.Image")));
			this->btnKwangju->Location = System::Drawing::Point(271, 506);
			this->btnKwangju->Margin = System::Windows::Forms::Padding(4);
			this->btnKwangju->Name = L"btnKwangju";
			this->btnKwangju->Size = System::Drawing::Size(50, 30);
			this->btnKwangju->TabIndex = 64;
			this->btnKwangju->TabStop = false;
			this->btnKwangju->UseVisualStyleBackColor = false;
			this->btnKwangju->Click += gcnew System::EventHandler(this, &전국날씨::btnKwangju_Click);
			// 
			// btnDaegu
			// 
			this->btnDaegu->BackColor = System::Drawing::Color::White;
			this->btnDaegu->FlatAppearance->BorderSize = 0;
			this->btnDaegu->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnDaegu->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnDaegu->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnDaegu->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnDaegu.Image")));
			this->btnDaegu->Location = System::Drawing::Point(483, 347);
			this->btnDaegu->Margin = System::Windows::Forms::Padding(4);
			this->btnDaegu->Name = L"btnDaegu";
			this->btnDaegu->Size = System::Drawing::Size(50, 30);
			this->btnDaegu->TabIndex = 65;
			this->btnDaegu->TabStop = false;
			this->btnDaegu->UseVisualStyleBackColor = false;
			this->btnDaegu->Click += gcnew System::EventHandler(this, &전국날씨::button4_Click);
			// 
			// btnJeju
			// 
			this->btnJeju->BackColor = System::Drawing::Color::White;
			this->btnJeju->FlatAppearance->BorderSize = 0;
			this->btnJeju->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnJeju->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnJeju->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnJeju->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnJeju.Image")));
			this->btnJeju->Location = System::Drawing::Point(244, 635);
			this->btnJeju->Margin = System::Windows::Forms::Padding(4);
			this->btnJeju->Name = L"btnJeju";
			this->btnJeju->Size = System::Drawing::Size(50, 30);
			this->btnJeju->TabIndex = 66;
			this->btnJeju->TabStop = false;
			this->btnJeju->UseVisualStyleBackColor = false;
			this->btnJeju->Click += gcnew System::EventHandler(this, &전국날씨::btnJeju_Click);
			// 
			// btnDaejeon
			// 
			this->btnDaejeon->BackColor = System::Drawing::Color::White;
			this->btnDaejeon->FlatAppearance->BorderSize = 0;
			this->btnDaejeon->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnDaejeon->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnDaejeon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnDaejeon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnDaejeon.Image")));
			this->btnDaejeon->Location = System::Drawing::Point(298, 307);
			this->btnDaejeon->Margin = System::Windows::Forms::Padding(4);
			this->btnDaejeon->Name = L"btnDaejeon";
			this->btnDaejeon->Size = System::Drawing::Size(50, 30);
			this->btnDaejeon->TabIndex = 67;
			this->btnDaejeon->TabStop = false;
			this->btnDaejeon->UseVisualStyleBackColor = false;
			this->btnDaejeon->Click += gcnew System::EventHandler(this, &전국날씨::button6_Click);
			// 
			// btnIncheon
			// 
			this->btnIncheon->BackColor = System::Drawing::Color::White;
			this->btnIncheon->FlatAppearance->BorderSize = 0;
			this->btnIncheon->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnIncheon->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnIncheon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnIncheon->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnIncheon.Image")));
			this->btnIncheon->Location = System::Drawing::Point(288, 207);
			this->btnIncheon->Margin = System::Windows::Forms::Padding(4);
			this->btnIncheon->Name = L"btnIncheon";
			this->btnIncheon->Size = System::Drawing::Size(50, 30);
			this->btnIncheon->TabIndex = 68;
			this->btnIncheon->TabStop = false;
			this->btnIncheon->UseVisualStyleBackColor = false;
			this->btnIncheon->Click += gcnew System::EventHandler(this, &전국날씨::button7_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Silver;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(219, 15);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(150, 87);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 69;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(22, 147);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(199, 70);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 70;
			this->pictureBox2->TabStop = false;
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::White;
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(103, 296);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(201, 70);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 71;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(627, 318);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(211, 70);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 72;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(625, 414);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(211, 70);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 73;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
			this->pictureBox6->Location = System::Drawing::Point(325, 615);
			this->pictureBox6->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(229, 70);
			this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox6->TabIndex = 74;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(540, 522);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(226, 70);
			this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox7->TabIndex = 75;
			this->pictureBox7->TabStop = false;
			// 
			// seoul_tmn
			// 
			this->seoul_tmn->AutoSize = true;
			this->seoul_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->seoul_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->seoul_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->seoul_tmn->Location = System::Drawing::Point(302, 36);
			this->seoul_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->seoul_tmn->Name = L"seoul_tmn";
			this->seoul_tmn->Size = System::Drawing::Size(45, 23);
			this->seoul_tmn->TabIndex = 77;
			this->seoul_tmn->Text = L"-1℃";
			// 
			// seoul_tmx
			// 
			this->seoul_tmx->AutoSize = true;
			this->seoul_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->seoul_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->seoul_tmx->ForeColor = System::Drawing::Color::White;
			this->seoul_tmx->Location = System::Drawing::Point(241, 36);
			this->seoul_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->seoul_tmx->Name = L"seoul_tmx";
			this->seoul_tmx->Size = System::Drawing::Size(38, 23);
			this->seoul_tmx->TabIndex = 76;
			this->seoul_tmx->Text = L"1℃";
			// 
			// daejeon_tmn
			// 
			this->daejeon_tmn->AutoSize = true;
			this->daejeon_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->daejeon_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->daejeon_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->daejeon_tmn->Location = System::Drawing::Point(209, 318);
			this->daejeon_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->daejeon_tmn->Name = L"daejeon_tmn";
			this->daejeon_tmn->Size = System::Drawing::Size(38, 23);
			this->daejeon_tmn->TabIndex = 89;
			this->daejeon_tmn->Text = L"0℃";
			// 
			// daejeon_tmx
			// 
			this->daejeon_tmx->AutoSize = true;
			this->daejeon_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->daejeon_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->daejeon_tmx->ForeColor = System::Drawing::Color::White;
			this->daejeon_tmx->Location = System::Drawing::Point(129, 318);
			this->daejeon_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->daejeon_tmx->Name = L"daejeon_tmx";
			this->daejeon_tmx->Size = System::Drawing::Size(38, 23);
			this->daejeon_tmx->TabIndex = 88;
			this->daejeon_tmx->Text = L"3℃";
			// 
			// daegu_tmn
			// 
			this->daegu_tmn->AutoSize = true;
			this->daegu_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->daegu_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->daegu_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->daegu_tmn->Location = System::Drawing::Point(770, 341);
			this->daegu_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->daegu_tmn->Name = L"daegu_tmn";
			this->daegu_tmn->Size = System::Drawing::Size(38, 23);
			this->daegu_tmn->TabIndex = 91;
			this->daegu_tmn->Text = L"2℃";
			// 
			// daegu_tmx
			// 
			this->daegu_tmx->AutoSize = true;
			this->daegu_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->daegu_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->daegu_tmx->ForeColor = System::Drawing::Color::White;
			this->daegu_tmx->Location = System::Drawing::Point(696, 341);
			this->daegu_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->daegu_tmx->Name = L"daegu_tmx";
			this->daegu_tmx->Size = System::Drawing::Size(38, 23);
			this->daegu_tmx->TabIndex = 90;
			this->daegu_tmx->Text = L"5℃";
			// 
			// ulsan_tmn
			// 
			this->ulsan_tmn->AutoSize = true;
			this->ulsan_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->ulsan_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ulsan_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->ulsan_tmn->Location = System::Drawing::Point(770, 443);
			this->ulsan_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->ulsan_tmn->Name = L"ulsan_tmn";
			this->ulsan_tmn->Size = System::Drawing::Size(38, 23);
			this->ulsan_tmn->TabIndex = 93;
			this->ulsan_tmn->Text = L"2℃";
			// 
			// ulsan_tmx
			// 
			this->ulsan_tmx->AutoSize = true;
			this->ulsan_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->ulsan_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->ulsan_tmx->ForeColor = System::Drawing::Color::White;
			this->ulsan_tmx->Location = System::Drawing::Point(696, 443);
			this->ulsan_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->ulsan_tmx->Name = L"ulsan_tmx";
			this->ulsan_tmx->Size = System::Drawing::Size(38, 23);
			this->ulsan_tmx->TabIndex = 92;
			this->ulsan_tmx->Text = L"7℃";
			// 
			// busan_tmn
			// 
			this->busan_tmn->AutoSize = true;
			this->busan_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->busan_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->busan_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->busan_tmn->Location = System::Drawing::Point(682, 545);
			this->busan_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->busan_tmn->Name = L"busan_tmn";
			this->busan_tmn->Size = System::Drawing::Size(38, 23);
			this->busan_tmn->TabIndex = 95;
			this->busan_tmn->Text = L"4℃";
			// 
			// busan_tmx
			// 
			this->busan_tmx->AutoSize = true;
			this->busan_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->busan_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->busan_tmx->ForeColor = System::Drawing::Color::White;
			this->busan_tmx->Location = System::Drawing::Point(604, 545);
			this->busan_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->busan_tmx->Name = L"busan_tmx";
			this->busan_tmx->Size = System::Drawing::Size(38, 23);
			this->busan_tmx->TabIndex = 94;
			this->busan_tmx->Text = L"8℃";
			// 
			// jeju_tmn
			// 
			this->jeju_tmn->AutoSize = true;
			this->jeju_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->jeju_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->jeju_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->jeju_tmn->Location = System::Drawing::Point(483, 640);
			this->jeju_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->jeju_tmn->Name = L"jeju_tmn";
			this->jeju_tmn->Size = System::Drawing::Size(38, 23);
			this->jeju_tmn->TabIndex = 97;
			this->jeju_tmn->Text = L"6℃";
			// 
			// jeju_tmx
			// 
			this->jeju_tmx->AutoSize = true;
			this->jeju_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->jeju_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->jeju_tmx->ForeColor = System::Drawing::Color::White;
			this->jeju_tmx->Location = System::Drawing::Point(405, 640);
			this->jeju_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->jeju_tmx->Name = L"jeju_tmx";
			this->jeju_tmx->Size = System::Drawing::Size(38, 23);
			this->jeju_tmx->TabIndex = 96;
			this->jeju_tmx->Text = L"6℃";
			// 
			// incheon_tmn
			// 
			this->incheon_tmn->AutoSize = true;
			this->incheon_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->incheon_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->incheon_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->incheon_tmn->Location = System::Drawing::Point(115, 169);
			this->incheon_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->incheon_tmn->Name = L"incheon_tmn";
			this->incheon_tmn->Size = System::Drawing::Size(45, 23);
			this->incheon_tmn->TabIndex = 99;
			this->incheon_tmn->Text = L"-2℃";
			// 
			// incheon_tmx
			// 
			this->incheon_tmx->AutoSize = true;
			this->incheon_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->incheon_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->incheon_tmx->ForeColor = System::Drawing::Color::White;
			this->incheon_tmx->Location = System::Drawing::Point(48, 169);
			this->incheon_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->incheon_tmx->Name = L"incheon_tmx";
			this->incheon_tmx->Size = System::Drawing::Size(38, 23);
			this->incheon_tmx->TabIndex = 98;
			this->incheon_tmx->Text = L"1℃";
			// 
			// kwangju_tmn
			// 
			this->kwangju_tmn->AutoSize = true;
			this->kwangju_tmn->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->kwangju_tmn->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->kwangju_tmn->ForeColor = System::Drawing::Color::DodgerBlue;
			this->kwangju_tmn->Location = System::Drawing::Point(180, 488);
			this->kwangju_tmn->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->kwangju_tmn->Name = L"kwangju_tmn";
			this->kwangju_tmn->Size = System::Drawing::Size(38, 23);
			this->kwangju_tmn->TabIndex = 102;
			this->kwangju_tmn->Text = L"0℃";
			// 
			// kwangju_tmx
			// 
			this->kwangju_tmx->AutoSize = true;
			this->kwangju_tmx->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(89)));
			this->kwangju_tmx->Font = (gcnew System::Drawing::Font(L"나눔고딕", 15, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->kwangju_tmx->ForeColor = System::Drawing::Color::White;
			this->kwangju_tmx->Location = System::Drawing::Point(90, 488);
			this->kwangju_tmx->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->kwangju_tmx->Name = L"kwangju_tmx";
			this->kwangju_tmx->Size = System::Drawing::Size(38, 23);
			this->kwangju_tmx->TabIndex = 101;
			this->kwangju_tmx->Text = L"3℃";
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::White;
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->InitialImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.InitialImage")));
			this->pictureBox8->Location = System::Drawing::Point(70, 463);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(201, 70);
			this->pictureBox8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox8->TabIndex = 100;
			this->pictureBox8->TabStop = false;
			// 
			// closeTimer
			// 
			this->closeTimer->Enabled = true;
			this->closeTimer->Interval = 1000;
			this->closeTimer->Tick += gcnew System::EventHandler(this, &전국날씨::closeTimer_Tick);
			// 
			// 전국날씨
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::Silver;
			this->ClientSize = System::Drawing::Size(1417, 708);
			this->Controls->Add(this->kwangju_tmn);
			this->Controls->Add(this->kwangju_tmx);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->incheon_tmn);
			this->Controls->Add(this->incheon_tmx);
			this->Controls->Add(this->jeju_tmn);
			this->Controls->Add(this->jeju_tmx);
			this->Controls->Add(this->busan_tmn);
			this->Controls->Add(this->busan_tmx);
			this->Controls->Add(this->ulsan_tmn);
			this->Controls->Add(this->ulsan_tmx);
			this->Controls->Add(this->daegu_tmn);
			this->Controls->Add(this->daegu_tmx);
			this->Controls->Add(this->daejeon_tmn);
			this->Controls->Add(this->daejeon_tmx);
			this->Controls->Add(this->seoul_tmn);
			this->Controls->Add(this->seoul_tmx);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->btnIncheon);
			this->Controls->Add(this->btnDaejeon);
			this->Controls->Add(this->btnJeju);
			this->Controls->Add(this->btnDaegu);
			this->Controls->Add(this->btnKwangju);
			this->Controls->Add(this->btnUlsan);
			this->Controls->Add(this->btnBusan);
			this->Controls->Add(this->lb습도);
			this->Controls->Add(this->lb강수확률);
			this->Controls->Add(this->lb최저기온);
			this->Controls->Add(this->lb최고기온);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->lbState);
			this->Controls->Add(this->lb날씨);
			this->Controls->Add(this->lbName);
			this->Controls->Add(this->pb설명);
			this->Controls->Add(this->btnSeoul);
			this->Controls->Add(this->pb전국지도);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"전국날씨";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"전국날씨";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &전국날씨::전국날씨_MouseDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb전국지도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb설명))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void btnSeoul_Click(System::Object^  sender, System::EventArgs^  e) {

		lbName->Text = "서울";
		lbState->Text = Convert::ToString(nation_Weather[3]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[0])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[1])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[5]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[4]) + "%";
	}
	private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {

		lbName->Text = "대구";
		lbState->Text = Convert::ToString(nation_Weather[21]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[18])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[19])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[23]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[22]) + "%";
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		lbName->Text = "부산";
		lbState->Text = Convert::ToString(nation_Weather[39]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[36])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[37])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[41]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[40]) + "%";
	}
	private: System::Void button6_Click(System::Object^  sender, System::EventArgs^  e) {
		lbName->Text = "대전";
		lbState->Text = Convert::ToString(nation_Weather[15]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[12])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[13])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[17]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[16]) + "%";
	}
	private: System::Void button7_Click(System::Object^  sender, System::EventArgs^  e) {
		lbName->Text = "인천";
		lbState->Text = Convert::ToString(nation_Weather[9]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[6])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[7])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[11]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[10]) + "%";
	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
		lbName->Text = "울산";
		lbState->Text = Convert::ToString(nation_Weather[33]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[30])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[31])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[35]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[34]) + "%";
	}
	private: System::Void btnKwangju_Click(System::Object^  sender, System::EventArgs^  e) {
		lbName->Text = "광주";
		lbState->Text = Convert::ToString(nation_Weather[27]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[24])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[25])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[29]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[28]) + "%";
	}
	private: System::Void btnJeju_Click(System::Object^  sender, System::EventArgs^  e) {
		lbName->Text = "제주";
		lbState->Text = Convert::ToString(nation_Weather[45]);
		lb최고기온->Text = Math::Round(Convert::ToSingle(nation_Weather[42])) + "℃";
		lb최저기온->Text = Math::Round(Convert::ToSingle(nation_Weather[43])) + "℃";
		lb습도->Text = Convert::ToSingle(nation_Weather[47]) + "%";
		lb강수확률->Text = Convert::ToSingle(nation_Weather[46]) + "%";
	}
	private: System::Void closeTimer_Tick(System::Object^  sender, System::EventArgs^  e) {

		if (countryCloseCount == 1)
		{
			this->Close();
			countryCloseCount = 0;
		}
		else if (countryCloseCount == 2)
		{
			this->Show();
			countryCloseCount = 0;
		}

	}
private: System::Void 전국날씨_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		menubarPosition = 1;
		menubarState = 1;
	}

}
};
}
