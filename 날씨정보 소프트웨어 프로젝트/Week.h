#pragma once

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;
	using namespace System::Threading;
	using namespace System::IO;

	extern int menubarState;
	extern int pastCloseCount;
	extern int weekCloseCount;
	extern int menubarPosition;

	public ref class Week : public System::Windows::Forms::Form
	{
	public:

		String^ ipParserURL;
		String^ latitude, ^longitude; // ����, �浵 ��
		String^ bigLocatation, ^tmplocation; // = F_lo // ex) ���̽�

		DateTime^ toDay = gcnew DateTime(System::DateTime::Now.Year, System::DateTime::Now.Month, System::DateTime::Now.Day);
		int nowMonth = (int)System::DateTime::Now.Month;
		int nowDay = (int)System::DateTime::Now.Day;
	private: System::Windows::Forms::Button^  btnFavorite3;
	public:
	private: System::Windows::Forms::Button^  btnFavorite2;
	private: System::Windows::Forms::Button^  btnFavorite1;
	private:
		System::Windows::Forms::Timer^  closeTimer;
		array < String^>^ cities = nullptr;
	public:
		String^ selectFavorite;
		Week(void)
		{
			InitializeComponent();

			/////////////////////////////���ã��κ� Hide //////////////////////
			btnFavorite1->Hide();
			btnFavorite2->Hide();
			btnFavorite3->Hide();
			loadFavorite();
			/////////////////////////////////////////////////////////////////////

			ipParserURL = "http://ipinfodb.com/";

			// ip�� ���� ���� ����, �浵�� ��� �װ��� �̿��� ��ó ������ ã�´�.
			findLocation(ipParserURL);
			findNearLocation();

			String^ weekUrl = "";
			if (bigLocatation->Contains("������") || bigLocatation->Contains("Ư����")) {
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + bigLocatation;
			}
			else {
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + bigLocatation + "&mid=" + tmplocation;
			}
			XmlTextReader^ reder = gcnew XmlTextReader(weekUrl);
			array< String^ >^ week_Weather = gcnew array< String^ >(100);
			int valueCount = 0;

			while (reder->Read())
			{
				switch (reder->NodeType)
				{
				case XmlNodeType::Text:

					week_Weather[valueCount] = reder->Value;
					valueCount++;
					break;
				}
			}

			// ������ġ Ȯ���� �����Ͱ� ����ֱ�
			String^ cityName = textBox1->Text;
			cityNamelb->Text = tmplocation;

			String^ weatherInfo = Convert::ToString(week_Weather[4]);

			//��������
			ddayStat->Text = Convert::ToString(week_Weather[3]);
			ddayStat1->Text = Convert::ToString(week_Weather[8]);
			ddayStat2->Text = Convert::ToString(week_Weather[13]);
			ddayStat3->Text = Convert::ToString(week_Weather[18]);
			ddayStat4->Text = Convert::ToString(week_Weather[23]);
			ddayStat5->Text = Convert::ToString(week_Weather[28]);

			//////////////////////////////////////////////////////////////////////////////////////////
			////////////////////// ���� ��� /////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////
			DateTime toDay = System::DateTime::Now;
			int nowMonth = toDay.Date.Month;
			int nowDay = toDay.Date.Day;

			dday->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay.ToString("ddd"));
			toDay = toDay.AddDays(1);
			nowMonth = toDay.Date.Month;
			nowDay = toDay.Date.Day;
			dday1->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay.ToString("ddd"));
			toDay = toDay.AddDays(1);
			nowMonth = toDay.Date.Month;
			nowDay = toDay.Date.Day;
			dday2->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay.ToString("ddd"));
			toDay = toDay.AddDays(1);
			nowMonth = toDay.Date.Month;
			nowDay = toDay.Date.Day;
			dday3->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay.ToString("ddd"));
			toDay = toDay.AddDays(1);
			nowMonth = toDay.Date.Month;
			nowDay = toDay.Date.Day;
			dday4->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay.ToString("ddd"));
			toDay = toDay.AddDays(1);
			nowMonth = toDay.Date.Month;
			nowDay = toDay.Date.Day;
			dday5->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay.ToString("ddd"));

			//////////////////////////////////////////////////////////////////////////////////////////
			////////////////////// ���� ��� /////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////

			//�ְ�µ� , ����
			ddayTemp->Text = Math::Round(Convert::ToInt32(week_Weather[1])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[2])) + "��";
			ddayTemp1->Text = Math::Round(Convert::ToInt32(week_Weather[6])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[7])) + "��";
			ddayTemp2->Text = Math::Round(Convert::ToInt32(week_Weather[11])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[12])) + "��";
			ddayTemp3->Text = Math::Round(Convert::ToInt32(week_Weather[16])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[17])) + "��";
			ddayTemp4->Text = Math::Round(Convert::ToInt32(week_Weather[21])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[22])) + "��";
			ddayTemp5->Text = Math::Round(Convert::ToInt32(week_Weather[26])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[27])) + "��";

			// ���� ����â
			ddayIm->Load("./������/" + Convert::ToString(week_Weather[3]) + ".png");
			ddayIm1->Load("./������/" + Convert::ToString(week_Weather[8]) + ".png");
			ddayIm2->Load("./������/" + Convert::ToString(week_Weather[13]) + ".png");
			ddayIm3->Load("./������/" + Convert::ToString(week_Weather[18]) + ".png");
			ddayIm4->Load("./������/" + Convert::ToString(week_Weather[23]) + ".png");
			ddayIm5->Load("./������/" + Convert::ToString(week_Weather[28]) + ".png");

			// ���� ����
			textBox2->Text = weatherInfo;

			// �ܾ� ��õ ���
			addCities();
		}
		void loadFavorite()
		{
			String^ fileName = "favorite.dat";
			int favoriteCnt = 0;
			array<String^>^ favoriteList = gcnew array<String^>(3);

			FileStream^ fs = gcnew FileStream(fileName, FileMode::OpenOrCreate, FileAccess::Read);
			StreamReader^ st = gcnew StreamReader(fs, System::Text::Encoding::UTF8);
			st->BaseStream->Seek(0, SeekOrigin::Begin);
			while (st->Peek() > -1)
			{
				String^ temp = st->ReadLine();
				favoriteList[favoriteCnt++] = temp;
				if (favoriteCnt == 1)
				{
					btnFavorite1->Show();
					btnFavorite1->Text = temp;
				}
				else if (favoriteCnt == 2)
				{
					btnFavorite2->Show();
					btnFavorite2->Text = temp;

					btnFavorite2->Left = 241;
					btnFavorite2->Top = 14;
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
				}
			}
			st->Close();
			fs->Close();
		}
	protected:
		~Week()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ImageList^  imageList1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::ComboBox^  textBox1;
	private: System::Windows::Forms::Label^  cityNamelb;
	private: System::Windows::Forms::Label^  ddayTemp5;
	private: System::Windows::Forms::Label^  ddayTemp4;
	private: System::Windows::Forms::Label^  ddayTemp3;
	private: System::Windows::Forms::Label^  ddayTemp2;
	private: System::Windows::Forms::Label^  ddayTemp1;
	private: System::Windows::Forms::Label^  ddayStat5;
	private: System::Windows::Forms::Label^  ddayStat4;
	private: System::Windows::Forms::Label^  ddayStat3;
	private: System::Windows::Forms::Label^  ddayStat2;
	private: System::Windows::Forms::Label^  ddayStat1;
	private: System::Windows::Forms::Label^  ddayStat;
	private: System::Windows::Forms::Label^  ddayTemp;
	private: System::Windows::Forms::PictureBox^  ddayIm5;
	private: System::Windows::Forms::PictureBox^  ddayIm4;
	private: System::Windows::Forms::PictureBox^  ddayIm3;
	private: System::Windows::Forms::PictureBox^  ddayIm2;
	private: System::Windows::Forms::PictureBox^  ddayIm1;
	private: System::Windows::Forms::PictureBox^  ddayIm;
	private: System::Windows::Forms::Label^  dday5;
	private: System::Windows::Forms::Label^  dday4;
	private: System::Windows::Forms::Label^  dday3;
	private: System::Windows::Forms::Label^  dday2;
	private: System::Windows::Forms::Label^  dday1;
	private: System::Windows::Forms::Label^  dday;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Timer^  stateTimer;
	private: System::ComponentModel::IContainer^  components;

#pragma region Windows Form Designer generated code
			 /// <summary>
			 /// �����̳� ������ �ʿ��� �޼����Դϴ�.
			 /// �� �޼����� ������ �ڵ� ������� �������� ���ʽÿ�.
			 /// </summary>
			 void InitializeComponent(void)
			 {
				 this->components = (gcnew System::ComponentModel::Container());
				 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Week::typeid));
				 this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
				 this->textBox2 = (gcnew System::Windows::Forms::TextBox());
				 this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
				 this->textBox1 = (gcnew System::Windows::Forms::ComboBox());
				 this->cityNamelb = (gcnew System::Windows::Forms::Label());
				 this->ddayTemp5 = (gcnew System::Windows::Forms::Label());
				 this->ddayTemp4 = (gcnew System::Windows::Forms::Label());
				 this->ddayTemp3 = (gcnew System::Windows::Forms::Label());
				 this->ddayTemp2 = (gcnew System::Windows::Forms::Label());
				 this->ddayTemp1 = (gcnew System::Windows::Forms::Label());
				 this->ddayStat5 = (gcnew System::Windows::Forms::Label());
				 this->ddayStat4 = (gcnew System::Windows::Forms::Label());
				 this->ddayStat3 = (gcnew System::Windows::Forms::Label());
				 this->ddayStat2 = (gcnew System::Windows::Forms::Label());
				 this->ddayStat1 = (gcnew System::Windows::Forms::Label());
				 this->ddayStat = (gcnew System::Windows::Forms::Label());
				 this->ddayTemp = (gcnew System::Windows::Forms::Label());
				 this->ddayIm5 = (gcnew System::Windows::Forms::PictureBox());
				 this->ddayIm4 = (gcnew System::Windows::Forms::PictureBox());
				 this->ddayIm3 = (gcnew System::Windows::Forms::PictureBox());
				 this->ddayIm2 = (gcnew System::Windows::Forms::PictureBox());
				 this->ddayIm1 = (gcnew System::Windows::Forms::PictureBox());
				 this->ddayIm = (gcnew System::Windows::Forms::PictureBox());
				 this->dday5 = (gcnew System::Windows::Forms::Label());
				 this->dday4 = (gcnew System::Windows::Forms::Label());
				 this->dday3 = (gcnew System::Windows::Forms::Label());
				 this->dday2 = (gcnew System::Windows::Forms::Label());
				 this->dday1 = (gcnew System::Windows::Forms::Label());
				 this->dday = (gcnew System::Windows::Forms::Label());
				 this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
				 this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
				 this->stateTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->closeTimer = (gcnew System::Windows::Forms::Timer(this->components));
				 this->btnFavorite3 = (gcnew System::Windows::Forms::Button());
				 this->btnFavorite2 = (gcnew System::Windows::Forms::Button());
				 this->btnFavorite1 = (gcnew System::Windows::Forms::Button());
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm5))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm4))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm3))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm2))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm1))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
				 this->SuspendLayout();
				 // 
				 // imageList1
				 // 
				 this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^>(resources->GetObject(L"imageList1.ImageStream")));
				 this->imageList1->TransparentColor = System::Drawing::Color::Transparent;
				 this->imageList1->Images->SetKeyName(0, L"��������.jpg");
				 this->imageList1->Images->SetKeyName(1, L"������.jpg");
				 this->imageList1->Images->SetKeyName(2, L"�����ع�¦.jpg");
				 this->imageList1->Images->SetKeyName(3, L"��.jpg");
				 this->imageList1->Images->SetKeyName(4, L"��.jpg");
				 // 
				 // textBox2
				 // 
				 this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
				 this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->textBox2->Location = System::Drawing::Point(129, 573);
				 this->textBox2->Multiline = true;
				 this->textBox2->Name = L"textBox2";
				 this->textBox2->Size = System::Drawing::Size(1031, 82);
				 this->textBox2->TabIndex = 76;
				 // 
				 // pictureBox7
				 // 
				 this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
				 this->pictureBox7->Location = System::Drawing::Point(104, 552);
				 this->pictureBox7->Name = L"pictureBox7";
				 this->pictureBox7->Size = System::Drawing::Size(1100, 118);
				 this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox7->TabIndex = 75;
				 this->pictureBox7->TabStop = false;
				 // 
				 // pictureBox6
				 // 
				 this->pictureBox6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox6.Image")));
				 this->pictureBox6->Location = System::Drawing::Point(1220, 566);
				 this->pictureBox6->Name = L"pictureBox6";
				 this->pictureBox6->Size = System::Drawing::Size(90, 92);
				 this->pictureBox6->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox6->TabIndex = 74;
				 this->pictureBox6->TabStop = false;
				 // 
				 // textBox1
				 // 
				 this->textBox1->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
				 this->textBox1->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
				 this->textBox1->BackColor = System::Drawing::Color::Silver;
				 this->textBox1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
				 this->textBox1->Font = (gcnew System::Drawing::Font(L"�������", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->textBox1->FormattingEnabled = true;
				 this->textBox1->Location = System::Drawing::Point(949, 86);
				 this->textBox1->Name = L"textBox1";
				 this->textBox1->Size = System::Drawing::Size(275, 39);
				 this->textBox1->TabIndex = 73;
				 // 
				 // cityNamelb
				 // 
				 this->cityNamelb->AutoSize = true;
				 this->cityNamelb->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(166)), static_cast<System::Int32>(static_cast<System::Byte>(166)),
					 static_cast<System::Int32>(static_cast<System::Byte>(166)));
				 this->cityNamelb->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->cityNamelb->ForeColor = System::Drawing::Color::White;
				 this->cityNamelb->Location = System::Drawing::Point(641, 98);
				 this->cityNamelb->Name = L"cityNamelb";
				 this->cityNamelb->Size = System::Drawing::Size(116, 40);
				 this->cityNamelb->TabIndex = 72;
				 this->cityNamelb->Text = L"���̽�";
				 // 
				 // ddayTemp5
				 // 
				 this->ddayTemp5->AutoSize = true;
				 this->ddayTemp5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayTemp5->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayTemp5->ForeColor = System::Drawing::Color::White;
				 this->ddayTemp5->Location = System::Drawing::Point(1108, 464);
				 this->ddayTemp5->Name = L"ddayTemp5";
				 this->ddayTemp5->Size = System::Drawing::Size(133, 28);
				 this->ddayTemp5->TabIndex = 71;
				 this->ddayTemp5->Text = L"17�� / 13��";
				 // 
				 // ddayTemp4
				 // 
				 this->ddayTemp4->AutoSize = true;
				 this->ddayTemp4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayTemp4->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayTemp4->ForeColor = System::Drawing::Color::White;
				 this->ddayTemp4->Location = System::Drawing::Point(913, 464);
				 this->ddayTemp4->Name = L"ddayTemp4";
				 this->ddayTemp4->Size = System::Drawing::Size(118, 28);
				 this->ddayTemp4->TabIndex = 70;
				 this->ddayTemp4->Text = L"18�� / 9��";
				 // 
				 // ddayTemp3
				 // 
				 this->ddayTemp3->AutoSize = true;
				 this->ddayTemp3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayTemp3->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayTemp3->ForeColor = System::Drawing::Color::White;
				 this->ddayTemp3->Location = System::Drawing::Point(714, 464);
				 this->ddayTemp3->Name = L"ddayTemp3";
				 this->ddayTemp3->Size = System::Drawing::Size(133, 28);
				 this->ddayTemp3->TabIndex = 69;
				 this->ddayTemp3->Text = L"24�� / 17��";
				 // 
				 // ddayTemp2
				 // 
				 this->ddayTemp2->AutoSize = true;
				 this->ddayTemp2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayTemp2->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayTemp2->ForeColor = System::Drawing::Color::White;
				 this->ddayTemp2->Location = System::Drawing::Point(514, 464);
				 this->ddayTemp2->Name = L"ddayTemp2";
				 this->ddayTemp2->Size = System::Drawing::Size(133, 28);
				 this->ddayTemp2->TabIndex = 68;
				 this->ddayTemp2->Text = L"20�� / 11��";
				 // 
				 // ddayTemp1
				 // 
				 this->ddayTemp1->AutoSize = true;
				 this->ddayTemp1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayTemp1->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayTemp1->ForeColor = System::Drawing::Color::White;
				 this->ddayTemp1->Location = System::Drawing::Point(314, 464);
				 this->ddayTemp1->Name = L"ddayTemp1";
				 this->ddayTemp1->Size = System::Drawing::Size(133, 28);
				 this->ddayTemp1->TabIndex = 67;
				 this->ddayTemp1->Text = L"15�� / 13��";
				 // 
				 // ddayStat5
				 // 
				 this->ddayStat5->AutoSize = true;
				 this->ddayStat5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayStat5->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayStat5->ForeColor = System::Drawing::Color::White;
				 this->ddayStat5->Location = System::Drawing::Point(1117, 398);
				 this->ddayStat5->Name = L"ddayStat5";
				 this->ddayStat5->Size = System::Drawing::Size(58, 28);
				 this->ddayStat5->TabIndex = 66;
				 this->ddayStat5->Text = L"�帲";
				 // 
				 // ddayStat4
				 // 
				 this->ddayStat4->AutoSize = true;
				 this->ddayStat4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayStat4->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayStat4->ForeColor = System::Drawing::Color::White;
				 this->ddayStat4->Location = System::Drawing::Point(913, 398);
				 this->ddayStat4->Name = L"ddayStat4";
				 this->ddayStat4->Size = System::Drawing::Size(58, 28);
				 this->ddayStat4->TabIndex = 65;
				 this->ddayStat4->Text = L"�帲";
				 // 
				 // ddayStat3
				 // 
				 this->ddayStat3->AutoSize = true;
				 this->ddayStat3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayStat3->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayStat3->ForeColor = System::Drawing::Color::White;
				 this->ddayStat3->Location = System::Drawing::Point(722, 398);
				 this->ddayStat3->Name = L"ddayStat3";
				 this->ddayStat3->Size = System::Drawing::Size(58, 28);
				 this->ddayStat3->TabIndex = 64;
				 this->ddayStat3->Text = L"�帲";
				 // 
				 // ddayStat2
				 // 
				 this->ddayStat2->AutoSize = true;
				 this->ddayStat2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayStat2->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayStat2->ForeColor = System::Drawing::Color::White;
				 this->ddayStat2->Location = System::Drawing::Point(526, 398);
				 this->ddayStat2->Name = L"ddayStat2";
				 this->ddayStat2->Size = System::Drawing::Size(58, 28);
				 this->ddayStat2->TabIndex = 63;
				 this->ddayStat2->Text = L"�帲";
				 // 
				 // ddayStat1
				 // 
				 this->ddayStat1->AutoSize = true;
				 this->ddayStat1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayStat1->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayStat1->ForeColor = System::Drawing::Color::White;
				 this->ddayStat1->Location = System::Drawing::Point(326, 398);
				 this->ddayStat1->Name = L"ddayStat1";
				 this->ddayStat1->Size = System::Drawing::Size(58, 28);
				 this->ddayStat1->TabIndex = 62;
				 this->ddayStat1->Text = L"�帲";
				 // 
				 // ddayStat
				 // 
				 this->ddayStat->AutoSize = true;
				 this->ddayStat->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayStat->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayStat->ForeColor = System::Drawing::Color::White;
				 this->ddayStat->Location = System::Drawing::Point(130, 398);
				 this->ddayStat->Name = L"ddayStat";
				 this->ddayStat->Size = System::Drawing::Size(58, 28);
				 this->ddayStat->TabIndex = 61;
				 this->ddayStat->Text = L"�帲";
				 // 
				 // ddayTemp
				 // 
				 this->ddayTemp->AutoSize = true;
				 this->ddayTemp->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayTemp->Font = (gcnew System::Drawing::Font(L"�������", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->ddayTemp->ForeColor = System::Drawing::Color::White;
				 this->ddayTemp->Location = System::Drawing::Point(121, 464);
				 this->ddayTemp->Name = L"ddayTemp";
				 this->ddayTemp->Size = System::Drawing::Size(133, 28);
				 this->ddayTemp->TabIndex = 60;
				 this->ddayTemp->Text = L"17�� / 10��";
				 // 
				 // ddayIm5
				 // 
				 this->ddayIm5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayIm5->Location = System::Drawing::Point(1116, 250);
				 this->ddayIm5->Name = L"ddayIm5";
				 this->ddayIm5->Size = System::Drawing::Size(137, 130);
				 this->ddayIm5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->ddayIm5->TabIndex = 59;
				 this->ddayIm5->TabStop = false;
				 // 
				 // ddayIm4
				 // 
				 this->ddayIm4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayIm4->Location = System::Drawing::Point(919, 250);
				 this->ddayIm4->Name = L"ddayIm4";
				 this->ddayIm4->Size = System::Drawing::Size(137, 130);
				 this->ddayIm4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->ddayIm4->TabIndex = 58;
				 this->ddayIm4->TabStop = false;
				 // 
				 // ddayIm3
				 // 
				 this->ddayIm3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayIm3->Location = System::Drawing::Point(726, 250);
				 this->ddayIm3->Name = L"ddayIm3";
				 this->ddayIm3->Size = System::Drawing::Size(137, 130);
				 this->ddayIm3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->ddayIm3->TabIndex = 57;
				 this->ddayIm3->TabStop = false;
				 // 
				 // ddayIm2
				 // 
				 this->ddayIm2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayIm2->Location = System::Drawing::Point(527, 250);
				 this->ddayIm2->Name = L"ddayIm2";
				 this->ddayIm2->Size = System::Drawing::Size(137, 130);
				 this->ddayIm2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->ddayIm2->TabIndex = 56;
				 this->ddayIm2->TabStop = false;
				 // 
				 // ddayIm1
				 // 
				 this->ddayIm1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayIm1->Location = System::Drawing::Point(331, 250);
				 this->ddayIm1->Name = L"ddayIm1";
				 this->ddayIm1->Size = System::Drawing::Size(137, 130);
				 this->ddayIm1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->ddayIm1->TabIndex = 55;
				 this->ddayIm1->TabStop = false;
				 // 
				 // ddayIm
				 // 
				 this->ddayIm->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->ddayIm->Location = System::Drawing::Point(133, 250);
				 this->ddayIm->Name = L"ddayIm";
				 this->ddayIm->Size = System::Drawing::Size(137, 130);
				 this->ddayIm->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->ddayIm->TabIndex = 54;
				 this->ddayIm->TabStop = false;
				 // 
				 // dday5
				 // 
				 this->dday5->AutoSize = true;
				 this->dday5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->dday5->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dday5->ForeColor = System::Drawing::Color::White;
				 this->dday5->Location = System::Drawing::Point(1111, 183);
				 this->dday5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->dday5->Name = L"dday5";
				 this->dday5->Size = System::Drawing::Size(103, 31);
				 this->dday5->TabIndex = 53;
				 this->dday5->Text = L"10.6 ȭ";
				 // 
				 // dday4
				 // 
				 this->dday4->AutoSize = true;
				 this->dday4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->dday4->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dday4->ForeColor = System::Drawing::Color::White;
				 this->dday4->Location = System::Drawing::Point(914, 183);
				 this->dday4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->dday4->Name = L"dday4";
				 this->dday4->Size = System::Drawing::Size(103, 31);
				 this->dday4->TabIndex = 52;
				 this->dday4->Text = L"10.5 ��";
				 // 
				 // dday3
				 // 
				 this->dday3->AutoSize = true;
				 this->dday3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->dday3->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dday3->ForeColor = System::Drawing::Color::White;
				 this->dday3->Location = System::Drawing::Point(711, 183);
				 this->dday3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->dday3->Name = L"dday3";
				 this->dday3->Size = System::Drawing::Size(103, 31);
				 this->dday3->TabIndex = 51;
				 this->dday3->Text = L"10.4 ��";
				 // 
				 // dday2
				 // 
				 this->dday2->AutoSize = true;
				 this->dday2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->dday2->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dday2->ForeColor = System::Drawing::Color::White;
				 this->dday2->Location = System::Drawing::Point(524, 183);
				 this->dday2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->dday2->Name = L"dday2";
				 this->dday2->Size = System::Drawing::Size(103, 31);
				 this->dday2->TabIndex = 50;
				 this->dday2->Text = L"10.3 ��";
				 // 
				 // dday1
				 // 
				 this->dday1->AutoSize = true;
				 this->dday1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->dday1->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dday1->ForeColor = System::Drawing::Color::White;
				 this->dday1->Location = System::Drawing::Point(324, 183);
				 this->dday1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->dday1->Name = L"dday1";
				 this->dday1->Size = System::Drawing::Size(103, 31);
				 this->dday1->TabIndex = 49;
				 this->dday1->Text = L"10.2 ��";
				 // 
				 // dday
				 // 
				 this->dday->AutoSize = true;
				 this->dday->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(89)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
					 static_cast<System::Int32>(static_cast<System::Byte>(89)));
				 this->dday->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->dday->ForeColor = System::Drawing::Color::White;
				 this->dday->Location = System::Drawing::Point(126, 183);
				 this->dday->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
				 this->dday->Name = L"dday";
				 this->dday->Size = System::Drawing::Size(103, 31);
				 this->dday->TabIndex = 48;
				 this->dday->Text = L"10.1 ��";
				 // 
				 // pictureBox5
				 // 
				 this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
				 this->pictureBox5->Location = System::Drawing::Point(68, 26);
				 this->pictureBox5->Name = L"pictureBox5";
				 this->pictureBox5->Size = System::Drawing::Size(52, 46);
				 this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox5->TabIndex = 47;
				 this->pictureBox5->TabStop = false;
				 this->pictureBox5->Click += gcnew System::EventHandler(this, &Week::pictureBox5_Click);
				 // 
				 // pictureBox4
				 // 
				 this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
				 this->pictureBox4->Location = System::Drawing::Point(1244, 81);
				 this->pictureBox4->Name = L"pictureBox4";
				 this->pictureBox4->Size = System::Drawing::Size(56, 57);
				 this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox4->TabIndex = 46;
				 this->pictureBox4->TabStop = false;
				 this->pictureBox4->Click += gcnew System::EventHandler(this, &Week::pictureBox4_Click);
				 // 
				 // pictureBox3
				 // 
				 this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
				 this->pictureBox3->Location = System::Drawing::Point(944, 81);
				 this->pictureBox3->Name = L"pictureBox3";
				 this->pictureBox3->Size = System::Drawing::Size(284, 57);
				 this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox3->TabIndex = 45;
				 this->pictureBox3->TabStop = false;
				 // 
				 // pictureBox2
				 // 
				 this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
				 this->pictureBox2->Location = System::Drawing::Point(99, 164);
				 this->pictureBox2->Name = L"pictureBox2";
				 this->pictureBox2->Size = System::Drawing::Size(1199, 369);
				 this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox2->TabIndex = 44;
				 this->pictureBox2->TabStop = false;
				 this->pictureBox2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Week::pictureBox2_MouseDown_1);
				 // 
				 // pictureBox1
				 // 
				 this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
				 this->pictureBox1->Location = System::Drawing::Point(523, 72);
				 this->pictureBox1->Name = L"pictureBox1";
				 this->pictureBox1->Size = System::Drawing::Size(347, 105);
				 this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				 this->pictureBox1->TabIndex = 43;
				 this->pictureBox1->TabStop = false;
				 // 
				 // stateTimer
				 // 
				 this->stateTimer->Interval = 50;
				 // 
				 // closeTimer
				 // 
				 this->closeTimer->Enabled = true;
				 this->closeTimer->Interval = 1000;
				 this->closeTimer->Tick += gcnew System::EventHandler(this, &Week::closeTimer_Tick);
				 // 
				 // btnFavorite3
				 // 
				 this->btnFavorite3->BackColor = System::Drawing::Color::Transparent;
				 this->btnFavorite3->FlatAppearance->BorderSize = 0;
				 this->btnFavorite3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
				 this->btnFavorite3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
				 this->btnFavorite3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnFavorite3->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnFavorite3->ForeColor = System::Drawing::Color::White;
				 this->btnFavorite3->Location = System::Drawing::Point(362, 14);
				 this->btnFavorite3->Margin = System::Windows::Forms::Padding(4);
				 this->btnFavorite3->Name = L"btnFavorite3";
				 this->btnFavorite3->Size = System::Drawing::Size(93, 58);
				 this->btnFavorite3->TabIndex = 79;
				 this->btnFavorite3->TabStop = false;
				 this->btnFavorite3->Text = L"�߰�3";
				 this->btnFavorite3->UseVisualStyleBackColor = false;
				 this->btnFavorite3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Week::btnFavorite3_MouseClick);
				 // 
				 // btnFavorite2
				 // 
				 this->btnFavorite2->BackColor = System::Drawing::Color::Transparent;
				 this->btnFavorite2->FlatAppearance->BorderSize = 0;
				 this->btnFavorite2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
				 this->btnFavorite2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
				 this->btnFavorite2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnFavorite2->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnFavorite2->ForeColor = System::Drawing::Color::White;
				 this->btnFavorite2->Location = System::Drawing::Point(241, 14);
				 this->btnFavorite2->Margin = System::Windows::Forms::Padding(4);
				 this->btnFavorite2->Name = L"btnFavorite2";
				 this->btnFavorite2->Size = System::Drawing::Size(93, 58);
				 this->btnFavorite2->TabIndex = 78;
				 this->btnFavorite2->TabStop = false;
				 this->btnFavorite2->Text = L"�߰�2";
				 this->btnFavorite2->UseVisualStyleBackColor = false;
				 this->btnFavorite2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Week::btnFavorite2_MouseClick);
				 // 
				 // btnFavorite1
				 // 
				 this->btnFavorite1->BackColor = System::Drawing::Color::Transparent;
				 this->btnFavorite1->FlatAppearance->BorderSize = 0;
				 this->btnFavorite1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::GreenYellow;
				 this->btnFavorite1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
				 this->btnFavorite1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
				 this->btnFavorite1->Font = (gcnew System::Drawing::Font(L"������� ExtraBold", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
					 static_cast<System::Byte>(0)));
				 this->btnFavorite1->ForeColor = System::Drawing::Color::White;
				 this->btnFavorite1->Location = System::Drawing::Point(127, 14);
				 this->btnFavorite1->Margin = System::Windows::Forms::Padding(4);
				 this->btnFavorite1->Name = L"btnFavorite1";
				 this->btnFavorite1->Size = System::Drawing::Size(93, 58);
				 this->btnFavorite1->TabIndex = 77;
				 this->btnFavorite1->TabStop = false;
				 this->btnFavorite1->Text = L"�߰�1";
				 this->btnFavorite1->UseVisualStyleBackColor = false;
				 this->btnFavorite1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &Week::btnFavorite1_MouseClick);
				 // 
				 // Week
				 // 
				 this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
				 this->BackColor = System::Drawing::Color::Silver;
				 this->ClientSize = System::Drawing::Size(1417, 708);
				 this->Controls->Add(this->btnFavorite3);
				 this->Controls->Add(this->btnFavorite2);
				 this->Controls->Add(this->btnFavorite1);
				 this->Controls->Add(this->textBox2);
				 this->Controls->Add(this->pictureBox7);
				 this->Controls->Add(this->pictureBox6);
				 this->Controls->Add(this->textBox1);
				 this->Controls->Add(this->cityNamelb);
				 this->Controls->Add(this->ddayTemp5);
				 this->Controls->Add(this->ddayTemp4);
				 this->Controls->Add(this->ddayTemp3);
				 this->Controls->Add(this->ddayTemp2);
				 this->Controls->Add(this->ddayTemp1);
				 this->Controls->Add(this->ddayStat5);
				 this->Controls->Add(this->ddayStat4);
				 this->Controls->Add(this->ddayStat3);
				 this->Controls->Add(this->ddayStat2);
				 this->Controls->Add(this->ddayStat1);
				 this->Controls->Add(this->ddayStat);
				 this->Controls->Add(this->ddayTemp);
				 this->Controls->Add(this->ddayIm5);
				 this->Controls->Add(this->ddayIm4);
				 this->Controls->Add(this->ddayIm3);
				 this->Controls->Add(this->ddayIm2);
				 this->Controls->Add(this->ddayIm1);
				 this->Controls->Add(this->ddayIm);
				 this->Controls->Add(this->dday5);
				 this->Controls->Add(this->dday4);
				 this->Controls->Add(this->dday3);
				 this->Controls->Add(this->dday2);
				 this->Controls->Add(this->dday1);
				 this->Controls->Add(this->dday);
				 this->Controls->Add(this->pictureBox5);
				 this->Controls->Add(this->pictureBox4);
				 this->Controls->Add(this->pictureBox3);
				 this->Controls->Add(this->pictureBox2);
				 this->Controls->Add(this->pictureBox1);
				 this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
				 this->Margin = System::Windows::Forms::Padding(4);
				 this->Name = L"Week";
				 this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
				 this->Text = L"Week";
				 this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Week::Week_MouseDown_1);
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm5))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm4))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm3))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm2))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm1))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ddayIm))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
				 (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
				 this->ResumeLayout(false);
				 this->PerformLayout();

			 }
#pragma endregion
	private: System::Void pictureBox4_Click(System::Object^  sender, System::EventArgs^  e) {

		String^ locationInfo = textBox1->Text;
		String^ weekUrl = "";
		String^ cityName = "";
		if (locationInfo->Contains("������") || locationInfo->Contains("Ư����")) {
			weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + locationInfo->Trim();
			cityName = locationInfo->Trim();
		}
		else {
			array<String^>^ result = locationInfo->Split(' ');
			if (result->Length == 2) {
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result[0] + "&mid=" + result[1];
				cityName = result[1];
			}
			else {
				String^ pick = "";
				for (int i = 0; i < cities->Length; i++) {
					pick = cities[i];
					if (pick->Contains(locationInfo))
						break;
				}
				array<String^>^ result2 = pick->Split(' ');
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result2[0] + "&mid=" + result2[1];
				cityName = result2[1];
			}
		}

		XmlTextReader^ reder = gcnew XmlTextReader(weekUrl);
		array< String^ >^ week_Weather = gcnew array< String^ >(100);
		int valueCount = 0;

		while (reder->Read())
		{
			switch (reder->NodeType)
			{
			case XmlNodeType::Text:

				week_Weather[valueCount] = reder->Value;
				valueCount++;
				break;
			}
		}

		//String^ cityName = textBox1->Text;
		cityNamelb->Text = cityName;
		String^ weatherInfo = Convert::ToString(week_Weather[4]);

		//��������
		ddayStat->Text = Convert::ToString(week_Weather[3]);
		ddayStat1->Text = Convert::ToString(week_Weather[8]);
		ddayStat2->Text = Convert::ToString(week_Weather[13]);
		ddayStat3->Text = Convert::ToString(week_Weather[18]);
		ddayStat4->Text = Convert::ToString(week_Weather[23]);
		ddayStat5->Text = Convert::ToString(week_Weather[28]);

		toDay = System::DateTime::Now;
		nowMonth = toDay->Date.Month;
		nowDay = toDay->Date.Day;
		//��¥         
		dday->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
		toDay = toDay->AddDays(1);
		nowMonth = toDay->Date.Month;
		nowDay = toDay->Date.Day;
		dday1->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
		toDay = toDay->AddDays(1);
		nowMonth = toDay->Date.Month;
		nowDay = toDay->Date.Day;
		dday2->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
		toDay = toDay->AddDays(1);
		nowMonth = toDay->Date.Month;
		nowDay = toDay->Date.Day;
		dday3->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
		toDay = toDay->AddDays(1);
		nowMonth = toDay->Date.Month;
		nowDay = toDay->Date.Day;
		dday4->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
		toDay = toDay->AddDays(1);
		nowMonth = toDay->Date.Month;
		nowDay = toDay->Date.Day;
		dday5->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));

		//�ְ�µ� , ����
		ddayTemp->Text = Math::Round(Convert::ToInt32(week_Weather[1])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[2])) + "��";
		ddayTemp1->Text = Math::Round(Convert::ToInt32(week_Weather[6])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[7])) + "��";
		ddayTemp2->Text = Math::Round(Convert::ToInt32(week_Weather[11])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[12])) + "��";
		ddayTemp3->Text = Math::Round(Convert::ToInt32(week_Weather[16])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[17])) + "��";
		ddayTemp4->Text = Math::Round(Convert::ToInt32(week_Weather[21])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[22])) + "��";
		ddayTemp5->Text = Math::Round(Convert::ToInt32(week_Weather[26])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[27])) + "��";

		// ���� ����â
		ddayIm->Load("./������/" + Convert::ToString(week_Weather[3]) + ".png");
		ddayIm1->Load("./������/" + Convert::ToString(week_Weather[8]) + ".png");
		ddayIm2->Load("./������/" + Convert::ToString(week_Weather[13]) + ".png");
		ddayIm3->Load("./������/" + Convert::ToString(week_Weather[18]) + ".png");
		ddayIm4->Load("./������/" + Convert::ToString(week_Weather[23]) + ".png");
		ddayIm5->Load("./������/" + Convert::ToString(week_Weather[28]) + ".png");

		// ���� ����
		textBox2->Text = weatherInfo;
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
						min = Math::Sqrt((mylat - lat)*(mylat - lat) + (mylon - lon)*(mylon - lon)); // �ּ�

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

		int testCount = 0;
		XmlTextReader^ loreder = gcnew XmlTextReader("http://jaehyeok.kr/programming_design/xml/specified_region_result.xml");
		array<locationData^>^ loData = gcnew array<locationData^>(10);

		bool isSecond = true;

		int^ loCode;
		String^ F_lo;
		String^ S_lo;
		String^ A_lo;

		while (loreder->Read())
		{
			switch (loreder->NodeType)
			{
			case XmlNodeType::Text:

				loData[testCount] = gcnew locationData(loreder->Value);

				if (testCount == 7)
				{
					if (isSecond)
					{
						loCode = Convert::ToInt32(loData[0]->getlData());
						F_lo = Convert::ToString(loData[2]->getlData());
						A_lo = Convert::ToString(loData[1]->getlData());
						isSecond = false;

						testCount = 0;
						continue;
					}

					loCode = Convert::ToInt32(loData[0]->getlData());
					F_lo = Convert::ToString(loData[2]->getlData());
					A_lo = Convert::ToString(loData[1]->getlData());

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
		tmplocation = F_lo; // +" " + S_lo;
		bigLocatation = A_lo;
	}
	private: System::Void pictureBox2_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			menubarState = 1;
		}
	}
	private: System::Void Week_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			menubarState = 1;
		}
	}
	private: System::Void closeTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (weekCloseCount == 1)
		{
			this->Close();
			weekCloseCount = 0;
		}
		else if (weekCloseCount == 2)
		{
			this->Show();
			weekCloseCount = 0;
		}
	}
	private: System::Void Week_MouseDown_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			menubarPosition = 1;
			menubarState = 1;
		}
	}
private: System::Void pictureBox2_MouseDown_1(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	if (e->Button == System::Windows::Forms::MouseButtons::Right)
	{
		menubarPosition = 1;
		menubarState = 1;
	}
}
private: System::Void btnFavorite1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	selectFavorite = btnFavorite1->Text;
	cityNamelb->Text = selectFavorite; // �Ľ̵Ǵ� �����̸�

	for (int i = 0; i < textBox1->AutoCompleteCustomSource->Count; i++) {
		if (textBox1->AutoCompleteCustomSource[i]->Contains(selectFavorite)) {
			String^ locationInfo = selectFavorite;
			String^ weekUrl = "";
			String^ cityName = "";
			if (locationInfo->Contains("������") || locationInfo->Contains("Ư����")) {
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + locationInfo->Trim();
				cityName = locationInfo->Trim();
			}
			else {
				array<String^>^ result = locationInfo->Split(' ');
				if (result->Length == 2) {
					weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result[0] + "&mid=" + result[1];
					cityName = result[1];
				}
				else {
					String^ pick = "";
					for (int i = 0; i < cities->Length; i++) {
						pick = cities[i];
						if (pick->Contains(locationInfo))
							break;
					}
					array<String^>^ result2 = pick->Split(' ');
					weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result2[0] + "&mid=" + result2[1];
					cityName = result2[1];
				}
			}

			XmlTextReader^ reder = gcnew XmlTextReader(weekUrl);
			array< String^ >^ week_Weather = gcnew array< String^ >(100);
			int valueCount = 0;

			while (reder->Read())
			{
				switch (reder->NodeType)
				{
				case XmlNodeType::Text:

					week_Weather[valueCount] = reder->Value;
					valueCount++;
					break;
				}
			}

			//String^ cityName = textBox1->Text;
			cityNamelb->Text = cityName;
			String^ weatherInfo = Convert::ToString(week_Weather[4]);

			//��������
			ddayStat->Text = Convert::ToString(week_Weather[3]);
			ddayStat1->Text = Convert::ToString(week_Weather[8]);
			ddayStat2->Text = Convert::ToString(week_Weather[13]);
			ddayStat3->Text = Convert::ToString(week_Weather[18]);
			ddayStat4->Text = Convert::ToString(week_Weather[23]);
			ddayStat5->Text = Convert::ToString(week_Weather[28]);

			toDay = System::DateTime::Now;
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			//��¥         
			dday->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday1->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday2->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday3->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday4->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday5->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));

			//�ְ�µ� , ����
			ddayTemp->Text = Math::Round(Convert::ToInt32(week_Weather[1])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[2])) + "��";
			ddayTemp1->Text = Math::Round(Convert::ToInt32(week_Weather[6])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[7])) + "��";
			ddayTemp2->Text = Math::Round(Convert::ToInt32(week_Weather[11])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[12])) + "��";
			ddayTemp3->Text = Math::Round(Convert::ToInt32(week_Weather[16])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[17])) + "��";
			ddayTemp4->Text = Math::Round(Convert::ToInt32(week_Weather[21])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[22])) + "��";
			ddayTemp5->Text = Math::Round(Convert::ToInt32(week_Weather[26])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[27])) + "��";

			// ���� ����â
			ddayIm->Load("./������/" + Convert::ToString(week_Weather[3]) + ".png");
			ddayIm1->Load("./������/" + Convert::ToString(week_Weather[8]) + ".png");
			ddayIm2->Load("./������/" + Convert::ToString(week_Weather[13]) + ".png");
			ddayIm3->Load("./������/" + Convert::ToString(week_Weather[18]) + ".png");
			ddayIm4->Load("./������/" + Convert::ToString(week_Weather[23]) + ".png");
			ddayIm5->Load("./������/" + Convert::ToString(week_Weather[28]) + ".png");

			// ���� ����
			textBox2->Text = weatherInfo;
			break;
		}
	}
	
}
private: System::Void btnFavorite2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	selectFavorite = btnFavorite2->Text;
	cityNamelb->Text = selectFavorite; // �Ľ̵Ǵ� �����̸�

	for (int i = 0; i < textBox1->AutoCompleteCustomSource->Count; i++) {
		if (textBox1->AutoCompleteCustomSource[i]->Contains(selectFavorite)) {
			String^ locationInfo = selectFavorite;
			String^ weekUrl = "";
			String^ cityName = "";
			if (locationInfo->Contains("������") || locationInfo->Contains("Ư����")) {
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + locationInfo->Trim();
				cityName = locationInfo->Trim();
			}
			else {
				array<String^>^ result = locationInfo->Split(' ');
				if (result->Length == 2) {
					weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result[0] + "&mid=" + result[1];
					cityName = result[1];
				}
				else {
					String^ pick = "";
					for (int i = 0; i < cities->Length; i++) {
						pick = cities[i];
						if (pick->Contains(locationInfo))
							break;
					}
					array<String^>^ result2 = pick->Split(' ');
					weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result2[0] + "&mid=" + result2[1];
					cityName = result2[1];
				}
			}

			XmlTextReader^ reder = gcnew XmlTextReader(weekUrl);
			array< String^ >^ week_Weather = gcnew array< String^ >(100);
			int valueCount = 0;

			while (reder->Read())
			{
				switch (reder->NodeType)
				{
				case XmlNodeType::Text:

					week_Weather[valueCount] = reder->Value;
					valueCount++;
					break;
				}
			}

			//String^ cityName = textBox1->Text;
			cityNamelb->Text = cityName;
			String^ weatherInfo = Convert::ToString(week_Weather[4]);

			//��������
			ddayStat->Text = Convert::ToString(week_Weather[3]);
			ddayStat1->Text = Convert::ToString(week_Weather[8]);
			ddayStat2->Text = Convert::ToString(week_Weather[13]);
			ddayStat3->Text = Convert::ToString(week_Weather[18]);
			ddayStat4->Text = Convert::ToString(week_Weather[23]);
			ddayStat5->Text = Convert::ToString(week_Weather[28]);

			toDay = System::DateTime::Now;
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			//��¥         
			dday->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday1->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday2->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday3->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday4->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday5->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));

			//�ְ�µ� , ����
			ddayTemp->Text = Math::Round(Convert::ToInt32(week_Weather[1])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[2])) + "��";
			ddayTemp1->Text = Math::Round(Convert::ToInt32(week_Weather[6])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[7])) + "��";
			ddayTemp2->Text = Math::Round(Convert::ToInt32(week_Weather[11])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[12])) + "��";
			ddayTemp3->Text = Math::Round(Convert::ToInt32(week_Weather[16])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[17])) + "��";
			ddayTemp4->Text = Math::Round(Convert::ToInt32(week_Weather[21])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[22])) + "��";
			ddayTemp5->Text = Math::Round(Convert::ToInt32(week_Weather[26])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[27])) + "��";

			// ���� ����â
			ddayIm->Load("./������/" + Convert::ToString(week_Weather[3]) + ".png");
			ddayIm1->Load("./������/" + Convert::ToString(week_Weather[8]) + ".png");
			ddayIm2->Load("./������/" + Convert::ToString(week_Weather[13]) + ".png");
			ddayIm3->Load("./������/" + Convert::ToString(week_Weather[18]) + ".png");
			ddayIm4->Load("./������/" + Convert::ToString(week_Weather[23]) + ".png");
			ddayIm5->Load("./������/" + Convert::ToString(week_Weather[28]) + ".png");

			// ���� ����
			textBox2->Text = weatherInfo;
			break;
		}
	}
}
private: System::Void btnFavorite3_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
	selectFavorite = btnFavorite3->Text;
	cityNamelb->Text = selectFavorite; // �Ľ̵Ǵ� �����̸�

	for (int i = 0; i < textBox1->AutoCompleteCustomSource->Count; i++) {
		if (textBox1->AutoCompleteCustomSource[i]->Contains(selectFavorite)) {
			String^ locationInfo = selectFavorite;
			String^ weekUrl = "";
			String^ cityName = "";
			if (locationInfo->Contains("������") || locationInfo->Contains("Ư����")) {
				weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + locationInfo->Trim();
				cityName = locationInfo->Trim();
			}
			else {
				array<String^>^ result = locationInfo->Split(' ');
				if (result->Length == 2) {
					weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result[0] + "&mid=" + result[1];
					cityName = result[1];
				}
				else {
					String^ pick = "";
					for (int i = 0; i < cities->Length; i++) {
						pick = cities[i];
						if (pick->Contains(locationInfo))
							break;
					}
					array<String^>^ result2 = pick->Split(' ');
					weekUrl = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + result2[0] + "&mid=" + result2[1];
					cityName = result2[1];
				}
			}

			XmlTextReader^ reder = gcnew XmlTextReader(weekUrl);
			array< String^ >^ week_Weather = gcnew array< String^ >(100);
			int valueCount = 0;

			while (reder->Read())
			{
				switch (reder->NodeType)
				{
				case XmlNodeType::Text:

					week_Weather[valueCount] = reder->Value;
					valueCount++;
					break;
				}
			}

			//String^ cityName = textBox1->Text;
			cityNamelb->Text = cityName;
			String^ weatherInfo = Convert::ToString(week_Weather[4]);

			//��������
			ddayStat->Text = Convert::ToString(week_Weather[3]);
			ddayStat1->Text = Convert::ToString(week_Weather[8]);
			ddayStat2->Text = Convert::ToString(week_Weather[13]);
			ddayStat3->Text = Convert::ToString(week_Weather[18]);
			ddayStat4->Text = Convert::ToString(week_Weather[23]);
			ddayStat5->Text = Convert::ToString(week_Weather[28]);

			toDay = System::DateTime::Now;
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			//��¥         
			dday->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday1->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday2->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday3->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday4->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));
			toDay = toDay->AddDays(1);
			nowMonth = toDay->Date.Month;
			nowDay = toDay->Date.Day;
			dday5->Text = gcnew String(nowMonth + "." + nowDay + " " + toDay->ToString("ddd"));

			//�ְ�µ� , ����
			ddayTemp->Text = Math::Round(Convert::ToInt32(week_Weather[1])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[2])) + "��";
			ddayTemp1->Text = Math::Round(Convert::ToInt32(week_Weather[6])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[7])) + "��";
			ddayTemp2->Text = Math::Round(Convert::ToInt32(week_Weather[11])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[12])) + "��";
			ddayTemp3->Text = Math::Round(Convert::ToInt32(week_Weather[16])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[17])) + "��";
			ddayTemp4->Text = Math::Round(Convert::ToInt32(week_Weather[21])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[22])) + "��";
			ddayTemp5->Text = Math::Round(Convert::ToInt32(week_Weather[26])) + "�� / " + Math::Round(Convert::ToInt32(week_Weather[27])) + "��";

			// ���� ����â
			ddayIm->Load("./������/" + Convert::ToString(week_Weather[3]) + ".png");
			ddayIm1->Load("./������/" + Convert::ToString(week_Weather[8]) + ".png");
			ddayIm2->Load("./������/" + Convert::ToString(week_Weather[13]) + ".png");
			ddayIm3->Load("./������/" + Convert::ToString(week_Weather[18]) + ".png");
			ddayIm4->Load("./������/" + Convert::ToString(week_Weather[23]) + ".png");
			ddayIm5->Load("./������/" + Convert::ToString(week_Weather[28]) + ".png");

			// ���� ����
			textBox2->Text = weatherInfo;
			break;
		}
	}
}


		 Void addCities() {
			 cities = gcnew array<String^>(168);
			 cities[0] = "������ ��õ��";
			 cities[1] = "������ ������";
			 cities[2] = "������ ���ֽ�";
			 cities[3] = "������ ���ؽ�";
			 cities[4] = "������ ��ô��";
			 cities[5] = "������ ���ʽ�";
			 cities[6] = "������ �¹��";
			 cities[7] = "������ ȫõ��";
			 cities[8] = "������ ȭõ��";
			 cities[9] = "������ Ⱦ����";
			 cities[10] = "������ �籸��";
			 cities[11] = "������ ������";
			 cities[12] = "������ ������";
			 cities[13] = "������ ��â��";
			 cities[14] = "������ ����";
			 cities[15] = "������ ������";
			 cities[16] = "������ ��籺";
			 cities[17] = "������ ö����";
			 cities[18] = "��⵵ ������";
			 cities[19] = "��⵵ ������";
			 cities[20] = "��⵵ �����ν�";
			 cities[21] = "��⵵ �Ⱦ��";
			 cities[22] = "��⵵ ��õ��";
			 cities[23] = "��⵵ �����";
			 cities[24] = "��⵵ ����õ��";
			 cities[25] = "��⵵ �Ȼ��";
			 cities[26] = "��⵵ ����";
			 cities[27] = "��⵵ ��õ��";
			 cities[28] = "��⵵ ������";
			 cities[29] = "��⵵ ���ý�";
			 cities[30] = "��⵵ �����ֽ�";
			 cities[31] = "��⵵ �����";
			 cities[32] = "��⵵ �����";
			 cities[33] = "��⵵ ������";
			 cities[34] = "��⵵ �ǿս�";
			 cities[35] = "��⵵ �ϳ���";
			 cities[36] = "��⵵ ���ֽ�";
			 cities[37] = "��⵵ ��õ��";
			 cities[38] = "��⵵ ���ν�";
			 cities[39] = "��⵵ �ȼ���";
			 cities[40] = "��⵵ ������";
			 cities[41] = "��⵵ ȭ����";
			 cities[42] = "��⵵ ���ֽ�";
			 cities[43] = "��⵵ ���ֽ�";
			 cities[44] = "��⵵ ��õ��";
			 cities[45] = "��⵵ ���ֱ�";
			 cities[46] = "��⵵ ����";
			 cities[47] = "��⵵ ����";
			 cities[48] = "��⵵ ��õ��";
			 cities[49] = "���ϵ� ���׽�";
			 cities[50] = "���ϵ� ���ֽ�";
			 cities[51] = "���ϵ� ��õ��";
			 cities[52] = "���ϵ� �ȵ���";
			 cities[53] = "���ϵ� ���̽�";
			 cities[54] = "���ϵ� ���ֽ�";
			 cities[55] = "���ϵ� ��õ��";
			 cities[56] = "���ϵ� ���ֽ�";
			 cities[57] = "���ϵ� �����";
			 cities[58] = "���ϵ� ����";
			 cities[59] = "���ϵ� ������";
			 cities[60] = "���ϵ� �Ǽ���";
			 cities[61] = "���ϵ� û�۱�";
			 cities[62] = "���ϵ� ���籺";
			 cities[63] = "���ϵ� ������";
			 cities[64] = "���ϵ� û����";
			 cities[65] = "���ϵ� ��ɱ�";
			 cities[66] = "���ϵ� ĥ�";
			 cities[67] = "���ϵ� ��õ��";
			 cities[68] = "���ϵ� ��ȭ��";
			 cities[69] = "���ϵ� ������";
			 cities[70] = "���ϵ� �︪��";
			 cities[71] = "���ϵ� ���ֱ�";
			 cities[72] = "��󳲵� â����";
			 cities[73] = "��󳲵� �����";
			 cities[74] = "��󳲵� ���ֽ�";
			 cities[75] = "��󳲵� ���ؽ�";
			 cities[76] = "��󳲵� �뿵��";
			 cities[77] = "��󳲵� ��õ��";
			 cities[78] = "��󳲵� ���ؽ�";
			 cities[79] = "��󳲵� �о��";
			 cities[80] = "��󳲵� ����";
			 cities[81] = "��󳲵� ������";
			 cities[82] = "��󳲵� �Ƿɱ�";
			 cities[83] = "��󳲵� �Ծȱ�";
			 cities[84] = "��󳲵� â�籺";
			 cities[85] = "��󳲵� ����";
			 cities[86] = "��󳲵� ���ر�";
			 cities[87] = "��󳲵� �ϵ���";
			 cities[88] = "��󳲵� ��û��";
			 cities[89] = "��󳲵� ��â��";
			 cities[90] = "��󳲵� �Ծ籺";
			 cities[91] = "��󳲵� ��õ��";
			 cities[92] = "��û�ϵ� û�ֽ�";
			 cities[93] = "��û�ϵ� ���ֽ�";
			 cities[94] = "��û�ϵ� ��õ��";
			 cities[95] = "��û�ϵ� û����";
			 cities[96] = "��û�ϵ� ������";
			 cities[97] = "��û�ϵ� ��õ��";
			 cities[98] = "��û�ϵ� ��õ��";
			 cities[99] = "��û�ϵ� ������";
			 cities[100] = "��û�ϵ� ������";
			 cities[101] = "��û�ϵ� ���걺";
			 cities[102] = "��û�ϵ� �ܾ籺";
			 cities[103] = "��û���� õ�Ƚ�";
			 cities[104] = "��û���� ���ֽ�";
			 cities[105] = "��û���� ���ɽ�";
			 cities[106] = "��û���� �ƻ��";
			 cities[107] = "��û���� �����";
			 cities[108] = "��û���� ����";
			 cities[109] = "��û���� ��õ��";
			 cities[110] = "��û���� ȫ����";
			 cities[111] = "��û���� �¾ȱ�";
			 cities[112] = "��û���� �ݻ걺";
			 cities[113] = "��û���� ���ⱺ";
			 cities[114] = "��û���� �ο���";
			 cities[115] = "��û���� û�籺";
			 cities[116] = "��û���� ���걺";
			 cities[117] = "��û���� ������";
			 cities[118] = "����ϵ� ���ֽ�";
			 cities[119] = "����ϵ� �����";
			 cities[120] = "����ϵ� �ͻ��";
			 cities[121] = "����ϵ� ������";
			 cities[122] = "����ϵ� ������";
			 cities[123] = "����ϵ� ������";
			 cities[124] = "����ϵ� ���ֱ�";
			 cities[125] = "����ϵ� �ӽǱ�";
			 cities[126] = "����ϵ� ��â��";
			 cities[127] = "����ϵ� ���ȱ�";
			 cities[128] = "����ϵ� �����";
			 cities[129] = "����ϵ� ��â��";
			 cities[130] = "����ϵ� �ξȱ�";
			 cities[131] = "���󳲵� ������";
			 cities[132] = "���󳲵� ������";
			 cities[133] = "���󳲵� ��õ��";
			 cities[134] = "���󳲵� ���ֽ�";
			 cities[135] = "���󳲵� �����";
			 cities[136] = "���󳲵� ��籺";
			 cities[137] = "���󳲵� ���ʱ�";
			 cities[138] = "���󳲵� ���ﱺ";
			 cities[139] = "���󳲵� ���ϱ�";
			 cities[140] = "���󳲵� ������";
			 cities[141] = "���󳲵� ������";
			 cities[142] = "���󳲵� ���";
			 cities[143] = "���󳲵� ���ﱺ";
			 cities[144] = "���󳲵� ������";
			 cities[145] = "���󳲵� ���ȱ�";
			 cities[146] = "���󳲵� �强��";
			 cities[147] = "���󳲵� �žȱ�";
			 cities[148] = "���󳲵� ������";
			 cities[149] = "���󳲵� ȭ����";
			 cities[150] = "���󳲵� �س���";
			 cities[151] = "���󳲵� ����";
			 cities[152] = "���󳲵� �ϵ���";
			 cities[153] = "����Ư����ġ�� ��������";
			 cities[154] = "����Ư����ġ�� ���ֽ�";
			 cities[155] = "����Ư����ġ�� �����ֱ�";
			 cities[156] = "����Ư����ġ�� �����ֱ�";
			 cities[157] = "����Ư����";
			 cities[158] = "��õ������";
			 cities[159] = "����������";
			 cities[160] = "���ֱ�����";
			 cities[161] = "�뱸������";
			 cities[162] = "�λ걤����";
			 cities[163] = "��걤����";
			 cities[164] = "��걤���� ���ֱ�";
			 cities[165] = "�λ걤���� ���屺";
			 cities[166] = "��õ������ ������";
			 cities[167] = "��õ������ ��ȭ��";
			 textBox1->AutoCompleteCustomSource->AddRange(cities);
		 }
private: System::Void pictureBox5_Click(System::Object^  sender, System::EventArgs^  e) {


}
};
}