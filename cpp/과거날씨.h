#pragma once

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;

	extern int menubarState;
	extern int pastCloseCount;
	
	//menubar Location
	extern int menubarPosition;


	/// <summary>
	/// 과거날씨에 대한 요약입니다.
	/// </summary>
	public ref class 과거날씨 : public System::Windows::Forms::Form
	{
		array< String^ >^ pastFormMonth = gcnew array< String^ >(12);
		array< String^ >^ pastFormMax = gcnew array< String^ >(12);
		array< String^ >^ pastFormMin = gcnew array< String^ >(12);
		array< String^ >^ pastFormRain = gcnew array< String^ >(12);

	private:

		int monthText;

	public:


		과거날씨(void)
		{
			InitializeComponent();

			//과거날씨 파씽
			XmlTextReader^ reder = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/make_xml_table.php?table=se_past_weather&filename=transaction_past_weather");
			
			int pastdataCount = 0;
			int pastmonthCount = 0;
			int pastmaxCount = 0;
			int pastminCount = 0;
			int pastrainCount = 0;

			while (reder->Read())
			{
				switch (reder->NodeType)
				{
				case XmlNodeType::Text:

					if (pastdataCount == 0 || pastdataCount == 4 || pastdataCount == 8 || pastdataCount == 12 || pastdataCount == 16 || pastdataCount == 20 || pastdataCount == 24 || pastdataCount == 28 || pastdataCount == 32 || pastdataCount == 36 || pastdataCount == 40 || pastdataCount == 44)
					{
						pastFormMonth[pastmonthCount] = reder->Value;
						pastmonthCount++;
					}
					else if (pastdataCount == 1 || pastdataCount == 5 || pastdataCount == 9 || pastdataCount == 13 || pastdataCount == 17 || pastdataCount == 21 || pastdataCount == 25 || pastdataCount == 29 || pastdataCount == 33 || pastdataCount == 37 || pastdataCount == 41 || pastdataCount == 45)
					{
						pastFormMax[pastmaxCount] = reder->Value;
						pastmaxCount++;
					}
					else if (pastdataCount == 2 || pastdataCount == 6 || pastdataCount == 10 || pastdataCount == 14 || pastdataCount == 18 || pastdataCount == 22 || pastdataCount == 26 || pastdataCount == 30 || pastdataCount == 34 || pastdataCount == 38 || pastdataCount == 42 || pastdataCount == 46)
					{
						pastFormMin[pastminCount] = reder->Value;
						pastminCount++;
					}
					else if (pastdataCount == 3 || pastdataCount == 7 || pastdataCount == 11 || pastdataCount == 15 || pastdataCount == 19 || pastdataCount == 23 || pastdataCount == 27 || pastdataCount == 31 || pastdataCount == 35 || pastdataCount == 39 || pastdataCount == 43 || pastdataCount == 47)
					{
						pastFormRain[pastrainCount] = reder->Value;
						pastrainCount++;
					}
					pastdataCount++;
					
					break;
				}
			}
			pastdataCount = 0;
			pastmonthCount = 0;
			pastmaxCount = 0;
			pastminCount = 0;
			pastrainCount = 0;

			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			monthText = System::DateTime::Now.Month;
			lbLocation->Text = monthText + "월";

			pb1월강수량->Visible = false;
			pb2월강수량->Visible = false;
			pb3월강수량->Visible = false;
			pb4월강수량->Visible = false;
			pb5월강수량->Visible = false;
			pb6월강수량->Visible = false;
			pb7월강수량->Visible = false;
			pb8월강수량->Visible = false;
			pb9월강수량->Visible = false;
			pb10월강수량->Visible = false;
			pb11월강수량->Visible = false;
			pb12월강수량->Visible = false;

			pb1월온도->Visible = true;
			pb2월온도->Visible = true;
			pb3월온도->Visible = true;
			pb4월온도->Visible = true;
			pb5월온도->Visible = true;
			pb6월온도->Visible = true;
			pb7월온도->Visible = true;
			pb8월온도->Visible = true;
			pb9월온도->Visible = true;
			pb10월온도->Visible = true;
			pb11월온도->Visible = true;
			pb12월온도->Visible = true;
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~과거날씨()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^  pictureBox1;


	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Label^  lbRain;

	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
private: System::Windows::Forms::Label^  lbminTemp;

private: System::Windows::Forms::Label^  lbmaxTemp;


	private: System::Windows::Forms::PictureBox^  pb1월강수량;
	private: System::Windows::Forms::PictureBox^  pb2월강수량;
	private: System::Windows::Forms::PictureBox^  pb3월강수량;
	private: System::Windows::Forms::PictureBox^  pb4월강수량;
	private: System::Windows::Forms::PictureBox^  pb5월강수량;
	private: System::Windows::Forms::PictureBox^  pb6월강수량;
	private: System::Windows::Forms::PictureBox^  pb7월강수량;
	private: System::Windows::Forms::PictureBox^  pb8월강수량;
	private: System::Windows::Forms::PictureBox^  pb9월강수량;
	private: System::Windows::Forms::PictureBox^  pb10월강수량;
	private: System::Windows::Forms::PictureBox^  pb11월강수량;
	private: System::Windows::Forms::PictureBox^  pb12월강수량;
	private: System::Windows::Forms::Timer^  pastCloseTimer;
	private: System::Windows::Forms::Button^  btn강수량;
	private: System::Windows::Forms::Button^  btn기온;
	private: System::Windows::Forms::PictureBox^  pb1월온도;
	private: System::Windows::Forms::PictureBox^  pb2월온도;
	private: System::Windows::Forms::PictureBox^  pb3월온도;
	private: System::Windows::Forms::PictureBox^  pb4월온도;
	private: System::Windows::Forms::PictureBox^  pb5월온도;
	private: System::Windows::Forms::PictureBox^  pb6월온도;
	private: System::Windows::Forms::PictureBox^  pb7월온도;
	private: System::Windows::Forms::PictureBox^  pb8월온도;
	private: System::Windows::Forms::PictureBox^  pb9월온도;
	private: System::Windows::Forms::PictureBox^  pb10월온도;
	private: System::Windows::Forms::PictureBox^  pb11월온도;
	private: System::Windows::Forms::PictureBox^  pb12월온도;
	private: System::Windows::Forms::Button^  btnRight;
	private: System::Windows::Forms::Button^  btnLeft;
	private: System::Windows::Forms::Label^  lbLocation;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(과거날씨::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->lbRain = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->lbminTemp = (gcnew System::Windows::Forms::Label());
			this->lbmaxTemp = (gcnew System::Windows::Forms::Label());
			this->pb1월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb2월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb3월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb4월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb5월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb6월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb7월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb8월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb9월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb10월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb11월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pb12월강수량 = (gcnew System::Windows::Forms::PictureBox());
			this->pastCloseTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->btn강수량 = (gcnew System::Windows::Forms::Button());
			this->btn기온 = (gcnew System::Windows::Forms::Button());
			this->pb1월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb2월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb3월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb4월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb5월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb6월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb7월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb8월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb9월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb10월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb11월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->pb12월온도 = (gcnew System::Windows::Forms::PictureBox());
			this->btnRight = (gcnew System::Windows::Forms::Button());
			this->btnLeft = (gcnew System::Windows::Forms::Button());
			this->lbLocation = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12월강수량))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11월온도))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12월온도))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1417, 708);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 67;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &과거날씨::pictureBox1_MouseDown);
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label18->ForeColor = System::Drawing::Color::SteelBlue;
			this->label18->Location = System::Drawing::Point(1341, 580);
			this->label18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(36, 25);
			this->label18->TabIndex = 77;
			this->label18->Text = L"21";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label17->ForeColor = System::Drawing::Color::SteelBlue;
			this->label17->Location = System::Drawing::Point(1323, 472);
			this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(57, 25);
			this->label17->TabIndex = 76;
			this->label17->Text = L"10일";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label16->ForeColor = System::Drawing::Color::SteelBlue;
			this->label16->Location = System::Drawing::Point(1281, 532);
			this->label16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(94, 25);
			this->label16->TabIndex = 75;
			this->label16->Text = L"6시간/일";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label15->ForeColor = System::Drawing::Color::SteelBlue;
			this->label15->Location = System::Drawing::Point(1339, 418);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(45, 25);
			this->label15->TabIndex = 74;
			this->label15->Text = L"0일";
			// 
			// lbRain
			// 
			this->lbRain->AutoSize = true;
			this->lbRain->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->lbRain->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->lbRain->ForeColor = System::Drawing::Color::SteelBlue;
			this->lbRain->Location = System::Drawing::Point(1310, 370);
			this->lbRain->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbRain->Name = L"lbRain";
			this->lbRain->Size = System::Drawing::Size(66, 25);
			this->lbRain->TabIndex = 73;
			this->lbRain->Text = L"168.5";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label13->ForeColor = System::Drawing::Color::SteelBlue;
			this->label13->Location = System::Drawing::Point(1241, 309);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(133, 25);
			this->label13->TabIndex = 72;
			this->label13->Text = L"6.7 (2005년)";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->label12->ForeColor = System::Drawing::Color::SteelBlue;
			this->label12->Location = System::Drawing::Point(1225, 254);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(145, 25);
			this->label12->TabIndex = 71;
			this->label12->Text = L"37.5 (1994년)";
			// 
			// lbminTemp
			// 
			this->lbminTemp->AutoSize = true;
			this->lbminTemp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->lbminTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->lbminTemp->ForeColor = System::Drawing::Color::SteelBlue;
			this->lbminTemp->Location = System::Drawing::Point(1327, 200);
			this->lbminTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbminTemp->Name = L"lbminTemp";
			this->lbminTemp->Size = System::Drawing::Size(54, 25);
			this->lbminTemp->TabIndex = 70;
			this->lbminTemp->Text = L"17.1";
			// 
			// lbmaxTemp
			// 
			this->lbmaxTemp->AutoSize = true;
			this->lbmaxTemp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->lbmaxTemp->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->lbmaxTemp->ForeColor = System::Drawing::Color::SteelBlue;
			this->lbmaxTemp->Location = System::Drawing::Point(1327, 136);
			this->lbmaxTemp->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbmaxTemp->Name = L"lbmaxTemp";
			this->lbmaxTemp->Size = System::Drawing::Size(54, 25);
			this->lbmaxTemp->TabIndex = 69;
			this->lbmaxTemp->Text = L"26.8";
			// 
			// pb1월강수량
			// 
			this->pb1월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb1월강수량.Image")));
			this->pb1월강수량->Location = System::Drawing::Point(103, 495);
			this->pb1월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb1월강수량->Name = L"pb1월강수량";
			this->pb1월강수량->Size = System::Drawing::Size(59, 120);
			this->pb1월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb1월강수량->TabIndex = 80;
			this->pb1월강수량->TabStop = false;
			// 
			// pb2월강수량
			// 
			this->pb2월강수량->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pb2월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb2월강수량.Image")));
			this->pb2월강수량->Location = System::Drawing::Point(183, 495);
			this->pb2월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb2월강수량->Name = L"pb2월강수량";
			this->pb2월강수량->Size = System::Drawing::Size(59, 118);
			this->pb2월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb2월강수량->TabIndex = 81;
			this->pb2월강수량->TabStop = false;
			// 
			// pb3월강수량
			// 
			this->pb3월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb3월강수량.Image")));
			this->pb3월강수량->Location = System::Drawing::Point(261, 495);
			this->pb3월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb3월강수량->Name = L"pb3월강수량";
			this->pb3월강수량->Size = System::Drawing::Size(59, 118);
			this->pb3월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb3월강수량->TabIndex = 82;
			this->pb3월강수량->TabStop = false;
			// 
			// pb4월강수량
			// 
			this->pb4월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb4월강수량.Image")));
			this->pb4월강수량->Location = System::Drawing::Point(340, 495);
			this->pb4월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb4월강수량->Name = L"pb4월강수량";
			this->pb4월강수량->Size = System::Drawing::Size(59, 118);
			this->pb4월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb4월강수량->TabIndex = 83;
			this->pb4월강수량->TabStop = false;
			// 
			// pb5월강수량
			// 
			this->pb5월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb5월강수량.Image")));
			this->pb5월강수량->Location = System::Drawing::Point(419, 495);
			this->pb5월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb5월강수량->Name = L"pb5월강수량";
			this->pb5월강수량->Size = System::Drawing::Size(59, 118);
			this->pb5월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb5월강수량->TabIndex = 84;
			this->pb5월강수량->TabStop = false;
			// 
			// pb6월강수량
			// 
			this->pb6월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb6월강수량.Image")));
			this->pb6월강수량->Location = System::Drawing::Point(499, 495);
			this->pb6월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb6월강수량->Name = L"pb6월강수량";
			this->pb6월강수량->Size = System::Drawing::Size(59, 118);
			this->pb6월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb6월강수량->TabIndex = 85;
			this->pb6월강수량->TabStop = false;
			// 
			// pb7월강수량
			// 
			this->pb7월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb7월강수량.Image")));
			this->pb7월강수량->Location = System::Drawing::Point(577, 495);
			this->pb7월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb7월강수량->Name = L"pb7월강수량";
			this->pb7월강수량->Size = System::Drawing::Size(59, 118);
			this->pb7월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb7월강수량->TabIndex = 86;
			this->pb7월강수량->TabStop = false;
			// 
			// pb8월강수량
			// 
			this->pb8월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb8월강수량.Image")));
			this->pb8월강수량->Location = System::Drawing::Point(656, 495);
			this->pb8월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb8월강수량->Name = L"pb8월강수량";
			this->pb8월강수량->Size = System::Drawing::Size(59, 118);
			this->pb8월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb8월강수량->TabIndex = 87;
			this->pb8월강수량->TabStop = false;
			// 
			// pb9월강수량
			// 
			this->pb9월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb9월강수량.Image")));
			this->pb9월강수량->Location = System::Drawing::Point(736, 495);
			this->pb9월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb9월강수량->Name = L"pb9월강수량";
			this->pb9월강수량->Size = System::Drawing::Size(59, 118);
			this->pb9월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb9월강수량->TabIndex = 88;
			this->pb9월강수량->TabStop = false;
			// 
			// pb10월강수량
			// 
			this->pb10월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb10월강수량.Image")));
			this->pb10월강수량->Location = System::Drawing::Point(817, 495);
			this->pb10월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb10월강수량->Name = L"pb10월강수량";
			this->pb10월강수량->Size = System::Drawing::Size(59, 118);
			this->pb10월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb10월강수량->TabIndex = 89;
			this->pb10월강수량->TabStop = false;
			// 
			// pb11월강수량
			// 
			this->pb11월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb11월강수량.Image")));
			this->pb11월강수량->Location = System::Drawing::Point(897, 495);
			this->pb11월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb11월강수량->Name = L"pb11월강수량";
			this->pb11월강수량->Size = System::Drawing::Size(59, 118);
			this->pb11월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb11월강수량->TabIndex = 90;
			this->pb11월강수량->TabStop = false;
			// 
			// pb12월강수량
			// 
			this->pb12월강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb12월강수량.Image")));
			this->pb12월강수량->Location = System::Drawing::Point(976, 495);
			this->pb12월강수량->Margin = System::Windows::Forms::Padding(4);
			this->pb12월강수량->Name = L"pb12월강수량";
			this->pb12월강수량->Size = System::Drawing::Size(59, 118);
			this->pb12월강수량->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb12월강수량->TabIndex = 91;
			this->pb12월강수량->TabStop = false;
			// 
			// pastCloseTimer
			// 
			this->pastCloseTimer->Enabled = true;
			this->pastCloseTimer->Interval = 1000;
			this->pastCloseTimer->Tick += gcnew System::EventHandler(this, &과거날씨::pastCloseTimer_Tick);
			// 
			// btn강수량
			// 
			this->btn강수량->BackColor = System::Drawing::Color::Transparent;
			this->btn강수량->FlatAppearance->BorderSize = 0;
			this->btn강수량->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btn강수량->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btn강수량->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn강수량->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn강수량.Image")));
			this->btn강수량->Location = System::Drawing::Point(27, 652);
			this->btn강수량->Margin = System::Windows::Forms::Padding(4);
			this->btn강수량->Name = L"btn강수량";
			this->btn강수량->Size = System::Drawing::Size(43, 45);
			this->btn강수량->TabIndex = 92;
			this->btn강수량->TabStop = false;
			this->btn강수량->UseVisualStyleBackColor = false;
			this->btn강수량->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &과거날씨::btn강수량_MouseDown);
			// 
			// btn기온
			// 
			this->btn기온->BackColor = System::Drawing::Color::Transparent;
			this->btn기온->FlatAppearance->BorderSize = 0;
			this->btn기온->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btn기온->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btn기온->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn기온->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn기온.Image")));
			this->btn기온->Location = System::Drawing::Point(86, 652);
			this->btn기온->Margin = System::Windows::Forms::Padding(4);
			this->btn기온->Name = L"btn기온";
			this->btn기온->Size = System::Drawing::Size(43, 45);
			this->btn기온->TabIndex = 93;
			this->btn기온->TabStop = false;
			this->btn기온->UseVisualStyleBackColor = false;
			this->btn기온->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &과거날씨::btn기온_MouseDown);
			// 
			// pb1월온도
			// 
			this->pb1월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb1월온도.Image")));
			this->pb1월온도->Location = System::Drawing::Point(103, 446);
			this->pb1월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb1월온도->Name = L"pb1월온도";
			this->pb1월온도->Size = System::Drawing::Size(59, 111);
			this->pb1월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb1월온도->TabIndex = 94;
			this->pb1월온도->TabStop = false;
			// 
			// pb2월온도
			// 
			this->pb2월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb2월온도.Image")));
			this->pb2월온도->Location = System::Drawing::Point(183, 418);
			this->pb2월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb2월온도->Name = L"pb2월온도";
			this->pb2월온도->Size = System::Drawing::Size(59, 118);
			this->pb2월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb2월온도->TabIndex = 95;
			this->pb2월온도->TabStop = false;
			// 
			// pb3월온도
			// 
			this->pb3월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb3월온도.Image")));
			this->pb3월온도->Location = System::Drawing::Point(261, 357);
			this->pb3월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb3월온도->Name = L"pb3월온도";
			this->pb3월온도->Size = System::Drawing::Size(59, 129);
			this->pb3월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb3월온도->TabIndex = 96;
			this->pb3월온도->TabStop = false;
			// 
			// pb4월온도
			// 
			this->pb4월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb4월온도.Image")));
			this->pb4월온도->Location = System::Drawing::Point(340, 266);
			this->pb4월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb4월온도->Name = L"pb4월온도";
			this->pb4월온도->Size = System::Drawing::Size(59, 129);
			this->pb4월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb4월온도->TabIndex = 97;
			this->pb4월온도->TabStop = false;
			// 
			// pb5월온도
			// 
			this->pb5월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb5월온도.Image")));
			this->pb5월온도->Location = System::Drawing::Point(419, 195);
			this->pb5월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb5월온도->Name = L"pb5월온도";
			this->pb5월온도->Size = System::Drawing::Size(59, 129);
			this->pb5월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb5월온도->TabIndex = 98;
			this->pb5월온도->TabStop = false;
			// 
			// pb6월온도
			// 
			this->pb6월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb6월온도.Image")));
			this->pb6월온도->Location = System::Drawing::Point(499, 136);
			this->pb6월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb6월온도->Name = L"pb6월온도";
			this->pb6월온도->Size = System::Drawing::Size(59, 129);
			this->pb6월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb6월온도->TabIndex = 99;
			this->pb6월온도->TabStop = false;
			// 
			// pb7월온도
			// 
			this->pb7월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb7월온도.Image")));
			this->pb7월온도->Location = System::Drawing::Point(577, 136);
			this->pb7월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb7월온도->Name = L"pb7월온도";
			this->pb7월온도->Size = System::Drawing::Size(59, 88);
			this->pb7월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb7월온도->TabIndex = 100;
			this->pb7월온도->TabStop = false;
			// 
			// pb8월온도
			// 
			this->pb8월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb8월온도.Image")));
			this->pb8월온도->Location = System::Drawing::Point(656, 126);
			this->pb8월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb8월온도->Name = L"pb8월온도";
			this->pb8월온도->Size = System::Drawing::Size(59, 99);
			this->pb8월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb8월온도->TabIndex = 101;
			this->pb8월온도->TabStop = false;
			// 
			// pb9월온도
			// 
			this->pb9월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb9월온도.Image")));
			this->pb9월온도->Location = System::Drawing::Point(736, 150);
			this->pb9월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb9월온도->Name = L"pb9월온도";
			this->pb9월온도->Size = System::Drawing::Size(59, 134);
			this->pb9월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb9월온도->TabIndex = 102;
			this->pb9월온도->TabStop = false;
			// 
			// pb10월온도
			// 
			this->pb10월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb10월온도.Image")));
			this->pb10월온도->Location = System::Drawing::Point(817, 243);
			this->pb10월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb10월온도->Name = L"pb10월온도";
			this->pb10월온도->Size = System::Drawing::Size(59, 126);
			this->pb10월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb10월온도->TabIndex = 103;
			this->pb10월온도->TabStop = false;
			// 
			// pb11월온도
			// 
			this->pb11월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb11월온도.Image")));
			this->pb11월온도->Location = System::Drawing::Point(897, 345);
			this->pb11월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb11월온도->Name = L"pb11월온도";
			this->pb11월온도->Size = System::Drawing::Size(59, 80);
			this->pb11월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb11월온도->TabIndex = 104;
			this->pb11월온도->TabStop = false;
			// 
			// pb12월온도
			// 
			this->pb12월온도->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb12월온도.Image")));
			this->pb12월온도->Location = System::Drawing::Point(976, 472);
			this->pb12월온도->Margin = System::Windows::Forms::Padding(4);
			this->pb12월온도->Name = L"pb12월온도";
			this->pb12월온도->Size = System::Drawing::Size(59, 105);
			this->pb12월온도->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb12월온도->TabIndex = 105;
			this->pb12월온도->TabStop = false;
			// 
			// btnRight
			// 
			this->btnRight->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->btnRight->FlatAppearance->BorderSize = 0;
			this->btnRight->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnRight->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnRight->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnRight->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnRight.Image")));
			this->btnRight->Location = System::Drawing::Point(1294, 17);
			this->btnRight->Margin = System::Windows::Forms::Padding(4);
			this->btnRight->Name = L"btnRight";
			this->btnRight->Size = System::Drawing::Size(81, 94);
			this->btnRight->TabIndex = 108;
			this->btnRight->TabStop = false;
			this->btnRight->UseVisualStyleBackColor = false;
			this->btnRight->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &과거날씨::btnRight_MouseDown);
			// 
			// btnLeft
			// 
			this->btnLeft->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->btnLeft->FlatAppearance->BorderSize = 0;
			this->btnLeft->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btnLeft->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnLeft->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnLeft->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnLeft.Image")));
			this->btnLeft->Location = System::Drawing::Point(1100, 17);
			this->btnLeft->Margin = System::Windows::Forms::Padding(4);
			this->btnLeft->Name = L"btnLeft";
			this->btnLeft->Size = System::Drawing::Size(81, 94);
			this->btnLeft->TabIndex = 107;
			this->btnLeft->TabStop = false;
			this->btnLeft->UseVisualStyleBackColor = false;
			this->btnLeft->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &과거날씨::btnLeft_MouseDown);
			// 
			// lbLocation
			// 
			this->lbLocation->AutoSize = true;
			this->lbLocation->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->lbLocation->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbLocation->ForeColor = System::Drawing::Color::Black;
			this->lbLocation->Location = System::Drawing::Point(1173, 37);
			this->lbLocation->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbLocation->Name = L"lbLocation";
			this->lbLocation->Size = System::Drawing::Size(106, 46);
			this->lbLocation->TabIndex = 106;
			this->lbLocation->Text = L"12월";
			// 
			// 과거날씨
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(1417, 708);
			this->Controls->Add(this->btnRight);
			this->Controls->Add(this->btnLeft);
			this->Controls->Add(this->lbLocation);
			this->Controls->Add(this->pb12월온도);
			this->Controls->Add(this->pb11월온도);
			this->Controls->Add(this->pb10월온도);
			this->Controls->Add(this->pb9월온도);
			this->Controls->Add(this->pb8월온도);
			this->Controls->Add(this->pb7월온도);
			this->Controls->Add(this->pb6월온도);
			this->Controls->Add(this->pb5월온도);
			this->Controls->Add(this->pb4월온도);
			this->Controls->Add(this->pb3월온도);
			this->Controls->Add(this->pb2월온도);
			this->Controls->Add(this->pb1월온도);
			this->Controls->Add(this->btn기온);
			this->Controls->Add(this->btn강수량);
			this->Controls->Add(this->pb12월강수량);
			this->Controls->Add(this->pb11월강수량);
			this->Controls->Add(this->pb10월강수량);
			this->Controls->Add(this->pb9월강수량);
			this->Controls->Add(this->pb8월강수량);
			this->Controls->Add(this->pb7월강수량);
			this->Controls->Add(this->pb6월강수량);
			this->Controls->Add(this->pb5월강수량);
			this->Controls->Add(this->pb4월강수량);
			this->Controls->Add(this->pb3월강수량);
			this->Controls->Add(this->pb2월강수량);
			this->Controls->Add(this->pb1월강수량);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->lbRain);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->lbminTemp);
			this->Controls->Add(this->lbmaxTemp);
			this->Controls->Add(this->pictureBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"과거날씨";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"과거날씨";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12월강수량))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11월온도))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12월온도))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void btnLeft_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		monthText -= 1;

		if (monthText == 0)
		{
			monthText = 12;
		}

		if (monthText<10)
		{
			lbLocation->Text = " " + monthText + "월";
		}
		else
		{
			lbLocation->Text = monthText + "월";
		}
		passingData();

	}
	private: System::Void btnRight_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		monthText += 1;

		if (monthText == 13)
		{
			monthText = 1;
		}

		if (monthText<10)
		{
			lbLocation->Text = " " + monthText + "월";
		}
		else
		{
			lbLocation->Text = monthText + "월";
		}
		passingData();

	}


		void view1(int water)
		{
			int startPoint = 614;
			int locationX = 103;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb1월강수량->Location = Point(locationX, locationY);
			pb1월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view2(int water)
		{
			int startPoint = 614;
			int locationX = 188;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb2월강수량->Location = Point(locationX, locationY);
			pb2월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view3(int water)
		{
			int startPoint = 614;
			int locationX = 266;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb3월강수량->Location = Point(locationX, locationY);
			pb3월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view4(int water)
		{
			int startPoint = 614;
			int locationX = 345;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb4월강수량->Location = Point(locationX, locationY);
			pb4월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view5(int water)
		{
			int startPoint = 614;
			int locationX = 424;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb5월강수량->Location = Point(locationX, locationY);
			pb5월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view6(int water)
		{
			int startPoint = 614;
			int locationX = 504;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb6월강수량->Location = Point(locationX, locationY);
			pb6월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view7(int water)
		{
			int startPoint = 614;
			int locationX = 582;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb7월강수량->Location = Point(locationX, locationY);
			pb7월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view8(int water)
		{
			int startPoint = 614;
			int locationX = 661;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb8월강수량->Location = Point(locationX, locationY);
			pb8월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view9(int water)
		{
			int startPoint = 614;
			int locationX = 741;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb9월강수량->Location = Point(locationX, locationY);
			pb9월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view10(int water)
		{
			int startPoint = 614;
			int locationX = 817;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb10월강수량->Location = Point(locationX, locationY);
			pb10월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view11(int water)
		{
			int startPoint = 614;
			int locationX = 897;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb11월강수량->Location = Point(locationX, locationY);
			pb11월강수량->Size = System::Drawing::Size(41, SizeY);
		}
		void view12(int water)
		{
			int startPoint = 614;
			int locationX = 976;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb12월강수량->Location = Point(locationX, locationY);
			pb12월강수량->Size = System::Drawing::Size(41, SizeY);
		}

		void passingData()
		{
			switch (monthText)
			{
			case 1:
				lbmaxTemp->Text = pastFormMax[0];
				lbminTemp->Text = pastFormMax[0];
				lbRain->Text = pastFormRain[0];
				break;
			case 2:
				lbmaxTemp->Text = pastFormMax[1];
				lbminTemp->Text = pastFormMin[1];
				lbRain->Text = pastFormRain[1];
				break;
			case 3:
				lbmaxTemp->Text = pastFormMax[2];
				lbminTemp->Text = pastFormMin[2];
				lbRain->Text = pastFormRain[2];
				break;
			case 4:
				lbmaxTemp->Text = pastFormMax[3];
				lbminTemp->Text = pastFormMin[3];
				lbRain->Text = pastFormRain[3];
				break;
			case 5:
				lbmaxTemp->Text = pastFormMax[4];
				lbminTemp->Text = pastFormMin[4];
				lbRain->Text = pastFormRain[4];
				break;
			case 6:
				lbmaxTemp->Text = pastFormMax[5];
				lbminTemp->Text = pastFormMin[5];
				lbRain->Text = pastFormRain[5];
				break;
			case 7:
				lbmaxTemp->Text = pastFormMax[6];
				lbminTemp->Text = pastFormMin[6];
				lbRain->Text = pastFormRain[6];
				break;
			case 8:
				lbmaxTemp->Text = pastFormMax[7];
				lbminTemp->Text = pastFormMin[7];
				lbRain->Text = pastFormRain[7];
				break;
			case 9:
				lbmaxTemp->Text = pastFormMax[8];
				lbminTemp->Text = pastFormMin[8];
				lbRain->Text = pastFormRain[8];
				break;
			case 10:
				lbmaxTemp->Text = pastFormMax[9];
				lbminTemp->Text = pastFormMin[9];
				lbRain->Text = pastFormRain[9];
				break;
			case 11:
				lbmaxTemp->Text = pastFormMax[10];
				lbminTemp->Text = pastFormMin[10];
				lbRain->Text = pastFormRain[10];
				break;
			case 12:
				lbmaxTemp->Text = pastFormMax[11];
				lbminTemp->Text = pastFormMin[11];
				lbRain->Text = pastFormRain[11];
				break;

			}
		}
	private: System::Void pictureBox1_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			menubarPosition = 1;
			menubarState = 1;
		}
	}
	private: System::Void pastCloseTimer_Tick(System::Object^  sender, System::EventArgs^  e) {

		if (pastCloseCount == 1)
		{
			this->Close();
			pastCloseCount = 0;
		}
		else if (pastCloseCount == 2)
		{
			this->Show();
			pastCloseCount = 0;
		}
	}
	private: System::Void btn강수량_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		pictureBox1->Load("./img/그래프.jpg");

		view1(11);
		view2(23);
		view3(10);
		view4(81);
		view5(29);
		view6(99);
		view7(226);
		view8(73);
		view9(26);
		view10(82);
		view11(105);
		view12(18);

		pb1월강수량->Visible = true;
		pb2월강수량->Visible = true;
		pb3월강수량->Visible = true;
		pb4월강수량->Visible = true;
		pb5월강수량->Visible = true;
		pb6월강수량->Visible = true;
		pb7월강수량->Visible = true;
		pb8월강수량->Visible = true;
		pb9월강수량->Visible = true;
		pb10월강수량->Visible = true;
		pb11월강수량->Visible = true;
		pb12월강수량->Visible = true;

		pb1월온도->Visible = false;
		pb2월온도->Visible = false;
		pb3월온도->Visible = false;
		pb4월온도->Visible = false;
		pb5월온도->Visible = false;
		pb6월온도->Visible = false;
		pb7월온도->Visible = false;
		pb8월온도->Visible = false;
		pb9월온도->Visible = false;
		pb10월온도->Visible = false;
		pb11월온도->Visible = false;
		pb12월온도->Visible = false;
	}
	private: System::Void btn기온_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		pictureBox1->Load("./img/그래프온도.jpg");
		pb1월강수량->Visible = false;
		pb2월강수량->Visible = false;
		pb3월강수량->Visible = false;
		pb4월강수량->Visible = false;
		pb5월강수량->Visible = false;
		pb6월강수량->Visible = false;
		pb7월강수량->Visible = false;
		pb8월강수량->Visible = false;
		pb9월강수량->Visible = false;
		pb10월강수량->Visible = false;
		pb11월강수량->Visible = false;
		pb12월강수량->Visible = false;

		pb1월온도->Visible = true;
		pb2월온도->Visible = true;
		pb3월온도->Visible = true;
		pb4월온도->Visible = true;
		pb5월온도->Visible = true;
		pb6월온도->Visible = true;
		pb7월온도->Visible = true;
		pb8월온도->Visible = true;
		pb9월온도->Visible = true;
		pb10월온도->Visible = true;
		pb11월온도->Visible = true;
		pb12월온도->Visible = true;
	}
	};
}
