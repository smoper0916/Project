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
	/// ���ų����� ���� ����Դϴ�.
	/// </summary>
	public ref class ���ų��� : public System::Windows::Forms::Form
	{
		array< String^ >^ pastFormMonth = gcnew array< String^ >(12);
		array< String^ >^ pastFormMax = gcnew array< String^ >(12);
		array< String^ >^ pastFormMin = gcnew array< String^ >(12);
		array< String^ >^ pastFormRain = gcnew array< String^ >(12);

	private:

		int monthText;

	public:


		���ų���(void)
		{
			InitializeComponent();

			//���ų��� �ľ�
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
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//
			monthText = System::DateTime::Now.Month;
			lbLocation->Text = monthText + "��";

			pb1��������->Visible = false;
			pb2��������->Visible = false;
			pb3��������->Visible = false;
			pb4��������->Visible = false;
			pb5��������->Visible = false;
			pb6��������->Visible = false;
			pb7��������->Visible = false;
			pb8��������->Visible = false;
			pb9��������->Visible = false;
			pb10��������->Visible = false;
			pb11��������->Visible = false;
			pb12��������->Visible = false;

			pb1���µ�->Visible = true;
			pb2���µ�->Visible = true;
			pb3���µ�->Visible = true;
			pb4���µ�->Visible = true;
			pb5���µ�->Visible = true;
			pb6���µ�->Visible = true;
			pb7���µ�->Visible = true;
			pb8���µ�->Visible = true;
			pb9���µ�->Visible = true;
			pb10���µ�->Visible = true;
			pb11���µ�->Visible = true;
			pb12���µ�->Visible = true;
		}

	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
		/// </summary>
		~���ų���()
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


	private: System::Windows::Forms::PictureBox^  pb1��������;
	private: System::Windows::Forms::PictureBox^  pb2��������;
	private: System::Windows::Forms::PictureBox^  pb3��������;
	private: System::Windows::Forms::PictureBox^  pb4��������;
	private: System::Windows::Forms::PictureBox^  pb5��������;
	private: System::Windows::Forms::PictureBox^  pb6��������;
	private: System::Windows::Forms::PictureBox^  pb7��������;
	private: System::Windows::Forms::PictureBox^  pb8��������;
	private: System::Windows::Forms::PictureBox^  pb9��������;
	private: System::Windows::Forms::PictureBox^  pb10��������;
	private: System::Windows::Forms::PictureBox^  pb11��������;
	private: System::Windows::Forms::PictureBox^  pb12��������;
	private: System::Windows::Forms::Timer^  pastCloseTimer;
	private: System::Windows::Forms::Button^  btn������;
	private: System::Windows::Forms::Button^  btn���;
	private: System::Windows::Forms::PictureBox^  pb1���µ�;
	private: System::Windows::Forms::PictureBox^  pb2���µ�;
	private: System::Windows::Forms::PictureBox^  pb3���µ�;
	private: System::Windows::Forms::PictureBox^  pb4���µ�;
	private: System::Windows::Forms::PictureBox^  pb5���µ�;
	private: System::Windows::Forms::PictureBox^  pb6���µ�;
	private: System::Windows::Forms::PictureBox^  pb7���µ�;
	private: System::Windows::Forms::PictureBox^  pb8���µ�;
	private: System::Windows::Forms::PictureBox^  pb9���µ�;
	private: System::Windows::Forms::PictureBox^  pb10���µ�;
	private: System::Windows::Forms::PictureBox^  pb11���µ�;
	private: System::Windows::Forms::PictureBox^  pb12���µ�;
	private: System::Windows::Forms::Button^  btnRight;
	private: System::Windows::Forms::Button^  btnLeft;
	private: System::Windows::Forms::Label^  lbLocation;
	private: System::ComponentModel::IContainer^  components;













	protected:

	protected:

	private:
		/// <summary>
		/// �ʼ� �����̳� �����Դϴ�.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// �����̳� ������ �ʿ��� �޼����Դϴ�.
		/// �� �޼����� ������ �ڵ� ������� �������� ���ʽÿ�.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(���ų���::typeid));
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
			this->pb1�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb2�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb3�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb4�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb5�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb6�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb7�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb8�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb9�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb10�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb11�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pb12�������� = (gcnew System::Windows::Forms::PictureBox());
			this->pastCloseTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->btn������ = (gcnew System::Windows::Forms::Button());
			this->btn��� = (gcnew System::Windows::Forms::Button());
			this->pb1���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb2���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb3���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb4���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb5���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb6���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb7���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb8���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb9���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb10���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb11���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->pb12���µ� = (gcnew System::Windows::Forms::PictureBox());
			this->btnRight = (gcnew System::Windows::Forms::Button());
			this->btnLeft = (gcnew System::Windows::Forms::Button());
			this->lbLocation = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12��������))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11���µ�))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12���µ�))->BeginInit();
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
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &���ų���::pictureBox1_MouseDown);
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
			this->label17->Text = L"10��";
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
			this->label16->Text = L"6�ð�/��";
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
			this->label15->Text = L"0��";
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
			this->label13->Text = L"6.7 (2005��)";
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
			this->label12->Text = L"37.5 (1994��)";
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
			// pb1��������
			// 
			this->pb1��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb1��������.Image")));
			this->pb1��������->Location = System::Drawing::Point(103, 495);
			this->pb1��������->Margin = System::Windows::Forms::Padding(4);
			this->pb1��������->Name = L"pb1��������";
			this->pb1��������->Size = System::Drawing::Size(59, 120);
			this->pb1��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb1��������->TabIndex = 80;
			this->pb1��������->TabStop = false;
			// 
			// pb2��������
			// 
			this->pb2��������->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->pb2��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb2��������.Image")));
			this->pb2��������->Location = System::Drawing::Point(183, 495);
			this->pb2��������->Margin = System::Windows::Forms::Padding(4);
			this->pb2��������->Name = L"pb2��������";
			this->pb2��������->Size = System::Drawing::Size(59, 118);
			this->pb2��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb2��������->TabIndex = 81;
			this->pb2��������->TabStop = false;
			// 
			// pb3��������
			// 
			this->pb3��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb3��������.Image")));
			this->pb3��������->Location = System::Drawing::Point(261, 495);
			this->pb3��������->Margin = System::Windows::Forms::Padding(4);
			this->pb3��������->Name = L"pb3��������";
			this->pb3��������->Size = System::Drawing::Size(59, 118);
			this->pb3��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb3��������->TabIndex = 82;
			this->pb3��������->TabStop = false;
			// 
			// pb4��������
			// 
			this->pb4��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb4��������.Image")));
			this->pb4��������->Location = System::Drawing::Point(340, 495);
			this->pb4��������->Margin = System::Windows::Forms::Padding(4);
			this->pb4��������->Name = L"pb4��������";
			this->pb4��������->Size = System::Drawing::Size(59, 118);
			this->pb4��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb4��������->TabIndex = 83;
			this->pb4��������->TabStop = false;
			// 
			// pb5��������
			// 
			this->pb5��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb5��������.Image")));
			this->pb5��������->Location = System::Drawing::Point(419, 495);
			this->pb5��������->Margin = System::Windows::Forms::Padding(4);
			this->pb5��������->Name = L"pb5��������";
			this->pb5��������->Size = System::Drawing::Size(59, 118);
			this->pb5��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb5��������->TabIndex = 84;
			this->pb5��������->TabStop = false;
			// 
			// pb6��������
			// 
			this->pb6��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb6��������.Image")));
			this->pb6��������->Location = System::Drawing::Point(499, 495);
			this->pb6��������->Margin = System::Windows::Forms::Padding(4);
			this->pb6��������->Name = L"pb6��������";
			this->pb6��������->Size = System::Drawing::Size(59, 118);
			this->pb6��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb6��������->TabIndex = 85;
			this->pb6��������->TabStop = false;
			// 
			// pb7��������
			// 
			this->pb7��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb7��������.Image")));
			this->pb7��������->Location = System::Drawing::Point(577, 495);
			this->pb7��������->Margin = System::Windows::Forms::Padding(4);
			this->pb7��������->Name = L"pb7��������";
			this->pb7��������->Size = System::Drawing::Size(59, 118);
			this->pb7��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb7��������->TabIndex = 86;
			this->pb7��������->TabStop = false;
			// 
			// pb8��������
			// 
			this->pb8��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb8��������.Image")));
			this->pb8��������->Location = System::Drawing::Point(656, 495);
			this->pb8��������->Margin = System::Windows::Forms::Padding(4);
			this->pb8��������->Name = L"pb8��������";
			this->pb8��������->Size = System::Drawing::Size(59, 118);
			this->pb8��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb8��������->TabIndex = 87;
			this->pb8��������->TabStop = false;
			// 
			// pb9��������
			// 
			this->pb9��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb9��������.Image")));
			this->pb9��������->Location = System::Drawing::Point(736, 495);
			this->pb9��������->Margin = System::Windows::Forms::Padding(4);
			this->pb9��������->Name = L"pb9��������";
			this->pb9��������->Size = System::Drawing::Size(59, 118);
			this->pb9��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb9��������->TabIndex = 88;
			this->pb9��������->TabStop = false;
			// 
			// pb10��������
			// 
			this->pb10��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb10��������.Image")));
			this->pb10��������->Location = System::Drawing::Point(817, 495);
			this->pb10��������->Margin = System::Windows::Forms::Padding(4);
			this->pb10��������->Name = L"pb10��������";
			this->pb10��������->Size = System::Drawing::Size(59, 118);
			this->pb10��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb10��������->TabIndex = 89;
			this->pb10��������->TabStop = false;
			// 
			// pb11��������
			// 
			this->pb11��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb11��������.Image")));
			this->pb11��������->Location = System::Drawing::Point(897, 495);
			this->pb11��������->Margin = System::Windows::Forms::Padding(4);
			this->pb11��������->Name = L"pb11��������";
			this->pb11��������->Size = System::Drawing::Size(59, 118);
			this->pb11��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb11��������->TabIndex = 90;
			this->pb11��������->TabStop = false;
			// 
			// pb12��������
			// 
			this->pb12��������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb12��������.Image")));
			this->pb12��������->Location = System::Drawing::Point(976, 495);
			this->pb12��������->Margin = System::Windows::Forms::Padding(4);
			this->pb12��������->Name = L"pb12��������";
			this->pb12��������->Size = System::Drawing::Size(59, 118);
			this->pb12��������->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb12��������->TabIndex = 91;
			this->pb12��������->TabStop = false;
			// 
			// pastCloseTimer
			// 
			this->pastCloseTimer->Enabled = true;
			this->pastCloseTimer->Interval = 1000;
			this->pastCloseTimer->Tick += gcnew System::EventHandler(this, &���ų���::pastCloseTimer_Tick);
			// 
			// btn������
			// 
			this->btn������->BackColor = System::Drawing::Color::Transparent;
			this->btn������->FlatAppearance->BorderSize = 0;
			this->btn������->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btn������->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btn������->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn������->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn������.Image")));
			this->btn������->Location = System::Drawing::Point(27, 652);
			this->btn������->Margin = System::Windows::Forms::Padding(4);
			this->btn������->Name = L"btn������";
			this->btn������->Size = System::Drawing::Size(43, 45);
			this->btn������->TabIndex = 92;
			this->btn������->TabStop = false;
			this->btn������->UseVisualStyleBackColor = false;
			this->btn������->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &���ų���::btn������_MouseDown);
			// 
			// btn���
			// 
			this->btn���->BackColor = System::Drawing::Color::Transparent;
			this->btn���->FlatAppearance->BorderSize = 0;
			this->btn���->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
			this->btn���->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btn���->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn���->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn���.Image")));
			this->btn���->Location = System::Drawing::Point(86, 652);
			this->btn���->Margin = System::Windows::Forms::Padding(4);
			this->btn���->Name = L"btn���";
			this->btn���->Size = System::Drawing::Size(43, 45);
			this->btn���->TabIndex = 93;
			this->btn���->TabStop = false;
			this->btn���->UseVisualStyleBackColor = false;
			this->btn���->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &���ų���::btn���_MouseDown);
			// 
			// pb1���µ�
			// 
			this->pb1���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb1���µ�.Image")));
			this->pb1���µ�->Location = System::Drawing::Point(103, 446);
			this->pb1���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb1���µ�->Name = L"pb1���µ�";
			this->pb1���µ�->Size = System::Drawing::Size(59, 111);
			this->pb1���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb1���µ�->TabIndex = 94;
			this->pb1���µ�->TabStop = false;
			// 
			// pb2���µ�
			// 
			this->pb2���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb2���µ�.Image")));
			this->pb2���µ�->Location = System::Drawing::Point(183, 418);
			this->pb2���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb2���µ�->Name = L"pb2���µ�";
			this->pb2���µ�->Size = System::Drawing::Size(59, 118);
			this->pb2���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb2���µ�->TabIndex = 95;
			this->pb2���µ�->TabStop = false;
			// 
			// pb3���µ�
			// 
			this->pb3���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb3���µ�.Image")));
			this->pb3���µ�->Location = System::Drawing::Point(261, 357);
			this->pb3���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb3���µ�->Name = L"pb3���µ�";
			this->pb3���µ�->Size = System::Drawing::Size(59, 129);
			this->pb3���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb3���µ�->TabIndex = 96;
			this->pb3���µ�->TabStop = false;
			// 
			// pb4���µ�
			// 
			this->pb4���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb4���µ�.Image")));
			this->pb4���µ�->Location = System::Drawing::Point(340, 266);
			this->pb4���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb4���µ�->Name = L"pb4���µ�";
			this->pb4���µ�->Size = System::Drawing::Size(59, 129);
			this->pb4���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb4���µ�->TabIndex = 97;
			this->pb4���µ�->TabStop = false;
			// 
			// pb5���µ�
			// 
			this->pb5���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb5���µ�.Image")));
			this->pb5���µ�->Location = System::Drawing::Point(419, 195);
			this->pb5���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb5���µ�->Name = L"pb5���µ�";
			this->pb5���µ�->Size = System::Drawing::Size(59, 129);
			this->pb5���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb5���µ�->TabIndex = 98;
			this->pb5���µ�->TabStop = false;
			// 
			// pb6���µ�
			// 
			this->pb6���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb6���µ�.Image")));
			this->pb6���µ�->Location = System::Drawing::Point(499, 136);
			this->pb6���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb6���µ�->Name = L"pb6���µ�";
			this->pb6���µ�->Size = System::Drawing::Size(59, 129);
			this->pb6���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb6���µ�->TabIndex = 99;
			this->pb6���µ�->TabStop = false;
			// 
			// pb7���µ�
			// 
			this->pb7���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb7���µ�.Image")));
			this->pb7���µ�->Location = System::Drawing::Point(577, 136);
			this->pb7���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb7���µ�->Name = L"pb7���µ�";
			this->pb7���µ�->Size = System::Drawing::Size(59, 88);
			this->pb7���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb7���µ�->TabIndex = 100;
			this->pb7���µ�->TabStop = false;
			// 
			// pb8���µ�
			// 
			this->pb8���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb8���µ�.Image")));
			this->pb8���µ�->Location = System::Drawing::Point(656, 126);
			this->pb8���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb8���µ�->Name = L"pb8���µ�";
			this->pb8���µ�->Size = System::Drawing::Size(59, 99);
			this->pb8���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb8���µ�->TabIndex = 101;
			this->pb8���µ�->TabStop = false;
			// 
			// pb9���µ�
			// 
			this->pb9���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb9���µ�.Image")));
			this->pb9���µ�->Location = System::Drawing::Point(736, 150);
			this->pb9���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb9���µ�->Name = L"pb9���µ�";
			this->pb9���µ�->Size = System::Drawing::Size(59, 134);
			this->pb9���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb9���µ�->TabIndex = 102;
			this->pb9���µ�->TabStop = false;
			// 
			// pb10���µ�
			// 
			this->pb10���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb10���µ�.Image")));
			this->pb10���µ�->Location = System::Drawing::Point(817, 243);
			this->pb10���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb10���µ�->Name = L"pb10���µ�";
			this->pb10���µ�->Size = System::Drawing::Size(59, 126);
			this->pb10���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb10���µ�->TabIndex = 103;
			this->pb10���µ�->TabStop = false;
			// 
			// pb11���µ�
			// 
			this->pb11���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb11���µ�.Image")));
			this->pb11���µ�->Location = System::Drawing::Point(897, 345);
			this->pb11���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb11���µ�->Name = L"pb11���µ�";
			this->pb11���µ�->Size = System::Drawing::Size(59, 80);
			this->pb11���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb11���µ�->TabIndex = 104;
			this->pb11���µ�->TabStop = false;
			// 
			// pb12���µ�
			// 
			this->pb12���µ�->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb12���µ�.Image")));
			this->pb12���µ�->Location = System::Drawing::Point(976, 472);
			this->pb12���µ�->Margin = System::Windows::Forms::Padding(4);
			this->pb12���µ�->Name = L"pb12���µ�";
			this->pb12���µ�->Size = System::Drawing::Size(59, 105);
			this->pb12���µ�->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb12���µ�->TabIndex = 105;
			this->pb12���µ�->TabStop = false;
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
			this->btnRight->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &���ų���::btnRight_MouseDown);
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
			this->btnLeft->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &���ų���::btnLeft_MouseDown);
			// 
			// lbLocation
			// 
			this->lbLocation->AutoSize = true;
			this->lbLocation->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->lbLocation->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbLocation->ForeColor = System::Drawing::Color::Black;
			this->lbLocation->Location = System::Drawing::Point(1173, 37);
			this->lbLocation->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lbLocation->Name = L"lbLocation";
			this->lbLocation->Size = System::Drawing::Size(106, 46);
			this->lbLocation->TabIndex = 106;
			this->lbLocation->Text = L"12��";
			// 
			// ���ų���
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::LightGray;
			this->ClientSize = System::Drawing::Size(1417, 708);
			this->Controls->Add(this->btnRight);
			this->Controls->Add(this->btnLeft);
			this->Controls->Add(this->lbLocation);
			this->Controls->Add(this->pb12���µ�);
			this->Controls->Add(this->pb11���µ�);
			this->Controls->Add(this->pb10���µ�);
			this->Controls->Add(this->pb9���µ�);
			this->Controls->Add(this->pb8���µ�);
			this->Controls->Add(this->pb7���µ�);
			this->Controls->Add(this->pb6���µ�);
			this->Controls->Add(this->pb5���µ�);
			this->Controls->Add(this->pb4���µ�);
			this->Controls->Add(this->pb3���µ�);
			this->Controls->Add(this->pb2���µ�);
			this->Controls->Add(this->pb1���µ�);
			this->Controls->Add(this->btn���);
			this->Controls->Add(this->btn������);
			this->Controls->Add(this->pb12��������);
			this->Controls->Add(this->pb11��������);
			this->Controls->Add(this->pb10��������);
			this->Controls->Add(this->pb9��������);
			this->Controls->Add(this->pb8��������);
			this->Controls->Add(this->pb7��������);
			this->Controls->Add(this->pb6��������);
			this->Controls->Add(this->pb5��������);
			this->Controls->Add(this->pb4��������);
			this->Controls->Add(this->pb3��������);
			this->Controls->Add(this->pb2��������);
			this->Controls->Add(this->pb1��������);
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
			this->Name = L"���ų���";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"���ų���";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12��������))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb1���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb2���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb3���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb4���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb5���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb6���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb7���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb8���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb9���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb10���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb11���µ�))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb12���µ�))->EndInit();
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
			lbLocation->Text = " " + monthText + "��";
		}
		else
		{
			lbLocation->Text = monthText + "��";
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
			lbLocation->Text = " " + monthText + "��";
		}
		else
		{
			lbLocation->Text = monthText + "��";
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
			pb1��������->Location = Point(locationX, locationY);
			pb1��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view2(int water)
		{
			int startPoint = 614;
			int locationX = 188;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb2��������->Location = Point(locationX, locationY);
			pb2��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view3(int water)
		{
			int startPoint = 614;
			int locationX = 266;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb3��������->Location = Point(locationX, locationY);
			pb3��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view4(int water)
		{
			int startPoint = 614;
			int locationX = 345;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb4��������->Location = Point(locationX, locationY);
			pb4��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view5(int water)
		{
			int startPoint = 614;
			int locationX = 424;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb5��������->Location = Point(locationX, locationY);
			pb5��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view6(int water)
		{
			int startPoint = 614;
			int locationX = 504;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb6��������->Location = Point(locationX, locationY);
			pb6��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view7(int water)
		{
			int startPoint = 614;
			int locationX = 582;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb7��������->Location = Point(locationX, locationY);
			pb7��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view8(int water)
		{
			int startPoint = 614;
			int locationX = 661;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb8��������->Location = Point(locationX, locationY);
			pb8��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view9(int water)
		{
			int startPoint = 614;
			int locationX = 741;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb9��������->Location = Point(locationX, locationY);
			pb9��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view10(int water)
		{
			int startPoint = 614;
			int locationX = 817;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.77);
			pb10��������->Location = Point(locationX, locationY);
			pb10��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view11(int water)
		{
			int startPoint = 614;
			int locationX = 897;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb11��������->Location = Point(locationX, locationY);
			pb11��������->Size = System::Drawing::Size(41, SizeY);
		}
		void view12(int water)
		{
			int startPoint = 614;
			int locationX = 976;
			int locationY = (int)(startPoint - (water*0.78));
			int SizeX = 41;
			int SizeY = (int)(water*0.78);
			pb12��������->Location = Point(locationX, locationY);
			pb12��������->Size = System::Drawing::Size(41, SizeY);
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
	private: System::Void btn������_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		pictureBox1->Load("./img/�׷���.jpg");

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

		pb1��������->Visible = true;
		pb2��������->Visible = true;
		pb3��������->Visible = true;
		pb4��������->Visible = true;
		pb5��������->Visible = true;
		pb6��������->Visible = true;
		pb7��������->Visible = true;
		pb8��������->Visible = true;
		pb9��������->Visible = true;
		pb10��������->Visible = true;
		pb11��������->Visible = true;
		pb12��������->Visible = true;

		pb1���µ�->Visible = false;
		pb2���µ�->Visible = false;
		pb3���µ�->Visible = false;
		pb4���µ�->Visible = false;
		pb5���µ�->Visible = false;
		pb6���µ�->Visible = false;
		pb7���µ�->Visible = false;
		pb8���µ�->Visible = false;
		pb9���µ�->Visible = false;
		pb10���µ�->Visible = false;
		pb11���µ�->Visible = false;
		pb12���µ�->Visible = false;
	}
	private: System::Void btn���_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		pictureBox1->Load("./img/�׷����µ�.jpg");
		pb1��������->Visible = false;
		pb2��������->Visible = false;
		pb3��������->Visible = false;
		pb4��������->Visible = false;
		pb5��������->Visible = false;
		pb6��������->Visible = false;
		pb7��������->Visible = false;
		pb8��������->Visible = false;
		pb9��������->Visible = false;
		pb10��������->Visible = false;
		pb11��������->Visible = false;
		pb12��������->Visible = false;

		pb1���µ�->Visible = true;
		pb2���µ�->Visible = true;
		pb3���µ�->Visible = true;
		pb4���µ�->Visible = true;
		pb5���µ�->Visible = true;
		pb6���µ�->Visible = true;
		pb7���µ�->Visible = true;
		pb8���µ�->Visible = true;
		pb9���µ�->Visible = true;
		pb10���µ�->Visible = true;
		pb11���µ�->Visible = true;
		pb12���µ�->Visible = true;
	}
	};
}
