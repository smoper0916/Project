#pragma once

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//투명화
	double extern formOp;
    int extern stateCount;
	static double searchOp = 0;
	
	/// <summary>
	/// Search에 대한 요약입니다.
	/// </summary>
	public ref class Search : public System::Windows::Forms::Form
	{
	public:
		Search(void)
		{
			InitializeComponent();
			array < String^>^ cities = gcnew array<String^>(168);
			cities[0] = "강원도 춘천시";
			cities[1] = "강원도 강릉시";
			cities[2] = "강원도 원주시";
			cities[3] = "강원도 동해시";
			cities[4] = "강원도 삼척시";
			cities[5] = "강원도 속초시";
			cities[6] = "강원도 태백시";
			cities[7] = "강원도 홍천시";
			cities[8] = "강원도 화천군";
			cities[9] = "강원도 횡성군";
			cities[10] = "강원도 양구군";
			cities[11] = "강원도 영월군";
			cities[12] = "강원도 인제군";
			cities[13] = "강원도 평창군";
			cities[14] = "강원도 고성군";
			cities[15] = "강원도 정선군";
			cities[16] = "강원도 양양군";
			cities[17] = "강원도 철원군";
			cities[18] = "경기도 수원시";
			cities[19] = "경기도 성남시";
			cities[20] = "경기도 의정부시";
			cities[21] = "경기도 안양시";
			cities[22] = "경기도 부천시";
			cities[23] = "경기도 광명시";
			cities[24] = "경기도 동두천시";
			cities[25] = "경기도 안산시";
			cities[26] = "경기도 고양시";
			cities[27] = "경기도 과천시";
			cities[28] = "경기도 구리시";
			cities[29] = "경기도 평택시";
			cities[30] = "경기도 남양주시";
			cities[31] = "경기도 오산시";
			cities[32] = "경기도 시흥시";
			cities[33] = "경기도 군포시";
			cities[34] = "경기도 의왕시";
			cities[35] = "경기도 하남시";
			cities[36] = "경기도 파주시";
			cities[37] = "경기도 이천시";
			cities[38] = "경기도 용인시";
			cities[39] = "경기도 안성시";
			cities[40] = "경기도 김포시";
			cities[41] = "경기도 화성시";
			cities[42] = "경기도 광주시";
			cities[43] = "경기도 양주시";
			cities[44] = "경기도 포천시";
			cities[45] = "경기도 여주군";
			cities[46] = "경기도 가평군";
			cities[47] = "경기도 양평군";
			cities[48] = "경기도 연천군";
			cities[49] = "경상북도 포항시";
			cities[50] = "경상북도 경주시";
			cities[51] = "경상북도 김천시";
			cities[52] = "경상북도 안동시";
			cities[53] = "경상북도 구미시";
			cities[54] = "경상북도 영주시";
			cities[55] = "경상북도 영천시";
			cities[56] = "경상북도 상주시";
			cities[57] = "경상북도 문경시";
			cities[58] = "경상북도 경산시";
			cities[59] = "경상북도 군위군";
			cities[60] = "경상북도 의성군";
			cities[61] = "경상북도 청송군";
			cities[62] = "경상북도 영양군";
			cities[63] = "경상북도 영덕군";
			cities[64] = "경상북도 청도군";
			cities[65] = "경상북도 고령군";
			cities[66] = "경상북도 칠곡군";
			cities[67] = "경상북도 예천군";
			cities[68] = "경상북도 봉화군";
			cities[69] = "경상북도 울진군";
			cities[70] = "경상북도 울릉군";
			cities[71] = "경상북도 성주군";
			cities[72] = "경상남도 창원시";
			cities[73] = "경상남도 마산시";
			cities[74] = "경상남도 진주시";
			cities[75] = "경상남도 진해시";
			cities[76] = "경상남도 통영시";
			cities[77] = "경상남도 사천시";
			cities[78] = "경상남도 김해시";
			cities[79] = "경상남도 밀양시";
			cities[80] = "경상남도 양산시";
			cities[81] = "경상남도 거제시";
			cities[82] = "경상남도 의령군";
			cities[83] = "경상남도 함안군";
			cities[84] = "경상남도 창녕군";
			cities[85] = "경상남도 고성군";
			cities[86] = "경상남도 남해군";
			cities[87] = "경상남도 하동군";
			cities[88] = "경상남도 산청군";
			cities[89] = "경상남도 거창군";
			cities[90] = "경상남도 함양군";
			cities[91] = "경상남도 합천군";
			cities[92] = "충청북도 청주시";
			cities[93] = "충청북도 충주시";
			cities[94] = "충청북도 제천시";
			cities[95] = "충청북도 청원군";
			cities[96] = "충청북도 보은군";
			cities[97] = "충청북도 옥천군";
			cities[98] = "충청북도 진천군";
			cities[99] = "충청북도 음성군";
			cities[100] = "충청북도 영동군";
			cities[101] = "충청북도 괴산군";
			cities[102] = "충청북도 단양군";
			cities[103] = "충청남도 천안시";
			cities[104] = "충청남도 공주시";
			cities[105] = "충청남도 보령시";
			cities[106] = "충청남도 아산시";
			cities[107] = "충청남도 서산시";
			cities[108] = "충청남도 논산시";
			cities[109] = "충청남도 서천군";
			cities[110] = "충청남도 홍성군";
			cities[111] = "충청남도 태안군";
			cities[112] = "충청남도 금산군";
			cities[113] = "충청남도 연기군";
			cities[114] = "충청남도 부여군";
			cities[115] = "충청남도 청양군";
			cities[116] = "충청남도 예산군";
			cities[117] = "충청남도 당진군";
			cities[118] = "전라북도 전주시";
			cities[119] = "전라북도 군산시";
			cities[120] = "전라북도 익산시";
			cities[121] = "전라북도 정읍시";
			cities[122] = "전라북도 남원시";
			cities[123] = "전라북도 김제시";
			cities[124] = "전라북도 무주군";
			cities[125] = "전라북도 임실군";
			cities[126] = "전라북도 고창군";
			cities[127] = "전라북도 진안군";
			cities[128] = "전라북도 장수군";
			cities[129] = "전라북도 순창군";
			cities[130] = "전라북도 부안군";
			cities[131] = "전라남도 목포시";
			cities[132] = "전라남도 여수시";
			cities[133] = "전라남도 순천시";
			cities[134] = "전라남도 나주시";
			cities[135] = "전라남도 광양시";
			cities[136] = "전라남도 담양군";
			cities[137] = "전라남도 구례군";
			cities[138] = "전라남도 장흥군";
			cities[139] = "전라남도 영암군";
			cities[140] = "전라남도 영광군";
			cities[141] = "전라남도 진도군";
			cities[142] = "전라남도 곡성군";
			cities[143] = "전라남도 고흥군";
			cities[144] = "전라남도 강진군";
			cities[145] = "전라남도 무안군";
			cities[146] = "전라남도 장성군";
			cities[147] = "전라남도 신안군";
			cities[148] = "전라남도 보성군";
			cities[149] = "전라남도 화순군";
			cities[150] = "전라남도 해남군";
			cities[151] = "전라남도 함평군";
			cities[152] = "전라남도 완도군";
			cities[153] = "제주특별자치도 서귀포시";
			cities[154] = "제주특별자치도 제주시";
			cities[155] = "제주특별자치도 북제주군";
			cities[156] = "제주특별자치도 남제주군";
			cities[157] = "서울특별시";
			cities[158] = "인천광역시";
			cities[159] = "대전광역시";
			cities[160] = "광주광역시";
			cities[161] = "대구광역시";
			cities[162] = "부산광역시";
			cities[163] = "울산광역시";
			cities[164] = "울산광역시 울주군";
			cities[165] = "부산광역시 기장군";
			cities[166] = "인천광역시 옹진군";
			cities[167] = "인천광역시 강화군";
			cbSearch->AutoCompleteCustomSource->AddRange(cities);
		}

	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~Search()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^  SearchOp;
	private: System::Windows::Forms::Button^  btnSearch;


	private: System::Windows::Forms::PictureBox^  pbSearch;
	private: System::Windows::Forms::ComboBox^  cbSearch;









	protected: 
	private: System::ComponentModel::IContainer^  components;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Search::typeid));
			this->SearchOp = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnSearch = (gcnew System::Windows::Forms::Button());
			this->pbSearch = (gcnew System::Windows::Forms::PictureBox());
			this->cbSearch = (gcnew System::Windows::Forms::ComboBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSearch))->BeginInit();
			this->SuspendLayout();
			// 
			// SearchOp
			// 
			this->SearchOp->Interval = 50;
			this->SearchOp->Tick += gcnew System::EventHandler(this, &Search::SearchOp_Tick);
			// 
			// btnSearch
			// 
			this->btnSearch->BackColor = System::Drawing::Color::Transparent;
			this->btnSearch->Cursor = System::Windows::Forms::Cursors::Hand;
			this->btnSearch->FlatAppearance->BorderSize = 0;
			this->btnSearch->FlatAppearance->MouseDownBackColor = System::Drawing::Color::Silver;
			this->btnSearch->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Transparent;
			this->btnSearch->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnSearch->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->btnSearch->ForeColor = System::Drawing::Color::Transparent;
			this->btnSearch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btnSearch.Image")));
			this->btnSearch->Location = System::Drawing::Point(590, 12);
			this->btnSearch->Name = L"btnSearch";
			this->btnSearch->Size = System::Drawing::Size(80, 80);
			this->btnSearch->TabIndex = 0;
			this->btnSearch->UseVisualStyleBackColor = false;
			this->btnSearch->Click += gcnew System::EventHandler(this, &Search::btnSearch_Click);
			// 
			// pbSearch
			// 
			this->pbSearch->BackColor = System::Drawing::Color::Transparent;
			this->pbSearch->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbSearch.Image")));
			this->pbSearch->Location = System::Drawing::Point(0, 0);
			this->pbSearch->Name = L"pbSearch";
			this->pbSearch->Size = System::Drawing::Size(700, 100);
			this->pbSearch->TabIndex = 2;
			this->pbSearch->TabStop = false;
			// 
			// cbSearch
			// 
			this->cbSearch->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->cbSearch->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->cbSearch->BackColor = System::Drawing::Color::Snow;
			this->cbSearch->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->cbSearch->Font = (gcnew System::Drawing::Font(L"나눔고딕", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->cbSearch->FormattingEnabled = true;
			this->cbSearch->Location = System::Drawing::Point(55, 26);
			this->cbSearch->Name = L"cbSearch";
			this->cbSearch->Size = System::Drawing::Size(508, 54);
			this->cbSearch->TabIndex = 3;
			// 
			// Search
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(700, 100);
			this->Controls->Add(this->cbSearch);
			this->Controls->Add(this->btnSearch);
			this->Controls->Add(this->pbSearch);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Location = System::Drawing::Point(100, 100);
			this->Name = L"Search";
			this->Opacity = 0;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Search";
			this->TransparencyKey = System::Drawing::Color::White;
			this->Load += gcnew System::EventHandler(this, &Search::Search_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbSearch))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void SearchOp_Tick(System::Object^  sender, System::EventArgs^  e) {

				this->Opacity = searchOp;
				searchOp += 0.05;
				
				if(searchOp>1)
				{
					SearchOp->Stop();
				}
			 }
	private: System::Void Search_Load(System::Object^  sender, System::EventArgs^  e) {

				 SearchOp->Start();
			 }
	private: System::Void btnSearch_Click(System::Object^  sender, System::EventArgs^  e) {

				 searchLocation = cbSearch->Text;
				 searchOp = 0;
				 formOp = 1;
				 stateCount = 1;
				 this->Close();
			 }

	String^ searchLocation;

	public: String^ getLocationName()
	{
		return searchLocation;
	}


};
}
