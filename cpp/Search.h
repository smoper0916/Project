#pragma once

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//����ȭ
	double extern formOp;
    int extern stateCount;
	static double searchOp = 0;
	
	/// <summary>
	/// Search�� ���� ����Դϴ�.
	/// </summary>
	public ref class Search : public System::Windows::Forms::Form
	{
	public:
		Search(void)
		{
			InitializeComponent();
			array < String^>^ cities = gcnew array<String^>(168);
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
			cbSearch->AutoCompleteCustomSource->AddRange(cities);
		}

	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
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
			this->cbSearch->Font = (gcnew System::Drawing::Font(L"�������", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
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
