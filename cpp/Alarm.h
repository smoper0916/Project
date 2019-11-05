#pragma once

namespace newCLR {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Threading;
	using namespace System::Text;
	using namespace System::Xml;

	//�迭

	//����ȭ
	double extern formOp;
	int extern stateCount;
	static double alarmOp = 0;

	static int Count = 0;
	static int readCount = 0;

	/// <summary>
	/// Alarm�� ���� ����Դϴ�.
	/// </summary>
	public ref class Alarm : public System::Windows::Forms::Form
	{
	public:

		Alarm(void)
		{
			InitializeComponent();
			Count = 0;
			btnClose->Parent = this;
			weatherIm1->Parent = this;
			weatherIm2->Parent = this;
			weatherIm3->Parent = this;
			weatherIm4->Parent = this;
			weatherIm5->Parent = this;
			//
			//TODO: ������ �ڵ带 ���⿡ �߰��մϴ�.
			//
			int tmpYear;
			int tmpMonth;
			int tmpDay;

			array<String^>^ tmpCityName = gcnew array<String^>(43); // ���� �̸� �迭
			array<int>^ dDayInfo = gcnew array<int>(5); //D-day �迭
			DateTime toDay = System::DateTime::Now;

			int nowYear = toDay.Date.Year;
			int nowMonth = toDay.Date.Month;
			int nowDay = toDay.Date.Day;

			StreamReader^ st = gcnew StreamReader("alarm.dat", System::Text::Encoding::Default);
			array<String^>^ strList = gcnew array<String^>(10);
			array<String^>^ value = gcnew array<String^>(732); // 366�������� �˶����尡��


			while (st->Peek() >= 0)
			{
				String^ tmp = st->ReadLine();
				
				strList = tmp->Split(' ');


				if (Convert::ToInt16(strList[1]) < 10)
				{
					strList[1] = "0" + strList[1];
				}
				if (Convert::ToInt16(strList[2]) < 10)
				{
					strList[2] = "0" + strList[2];
				}

				value[readCount] = strList[0] + strList[1] + strList[2];

				String^ strTmp;
				if(strList->Length == 5)
					strTmp = strList[3] + " " + strList[4];

				if(strList[3] == "���ϵ�")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "��󳲵�")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "��û�ϵ�")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "��û����")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "����ϵ�")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "���󳲵�")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "��⵵")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "������")
					value[readCount + 1] = strList[4];
				else if (strList[3] == "����Ư����ġ��")
					value[readCount + 1] = strList[4];
				
				else if (strTmp == "��걤���� ���ֱ�")
					value[readCount + 1] = strList[4];
				else if (strTmp == "�λ걤���� ���屺")
					value[readCount + 1] = strList[4];
				else if (strTmp == "��õ������ ������")
					value[readCount + 1] = strList[4];
				else if (strTmp == "��õ������ ��ȭ��")
					value[readCount + 1] = strList[4];
				else
					value[readCount + 1] = strList[3];
				
				readCount += 2;
			}


			int nowDate = (nowYear * 10000) + (nowMonth * 100) + (nowDay);

			int A = nowDate - Convert::ToInt32(value[0]);
			int B = nowDate - Convert::ToInt32(value[2]);
			int C = nowDate - Convert::ToInt32(value[4]);
			int D = nowDate - Convert::ToInt32(value[6]);
			int E = nowDate - Convert::ToInt32(value[8]);

			if (A > -6 && A < 1)
			{
				alarmday1->Text = value[0]; // ��¥
				dDay1->Text = "Day" + (nowDate - Convert::ToInt32(value[0])); //D-Day
				area1->Text = value[1]; // ������
			}

			if (B > -6 && B < 1)
			{
				alarmday2->Text = value[2];
				dDay2->Text = "Day" + (nowDate - Convert::ToInt32(value[2]));
				area2->Text = value[3];
			}

			if (C > -6 && C < 1)
			{
				alarmday3->Text = value[4];
				dDay3->Text = "Day" + (nowDate - Convert::ToInt32(value[4]));
				area3->Text = value[5];
			}

			if (D > -6 && D < 1)
			{
				alarmday4->Text = value[6];
				dDay4->Text = "Day" + (nowDate - Convert::ToInt32(value[6]));
				area4->Text = value[7];
			}

			if (E > -6 && E < 1)
			{
				alarmday5->Text = value[8];
				dDay5->Text = "Day" + (nowDate - Convert::ToInt32(value[8]));
				area5->Text = value[9];
			}

			readCount = 0;

			for (int z = 0; z < 10; z = z + 2)
			{
				if (nowDate - Convert::ToInt32(value[z]) > -6 && nowDate - Convert::ToInt32(value[z]) < 1)
					Count++;
			}


			st->Close();

			String^ B_L;
			String^ S_L;

			array < alarmLocation^ >^ find_Location = gcnew array < alarmLocation^ >(170);
			for (int i = 0; i < 170; i++)
				find_Location[i] = gcnew alarmLocation;

			find_Location[0]->big_Loction = "������";   find_Location[0]->small_Loction = "��õ��";
			find_Location[1]->big_Loction = "������";   find_Location[1]->small_Loction = "������";
			find_Location[2]->big_Loction = "������";   find_Location[2]->small_Loction = "���ֽ�";
			find_Location[3]->big_Loction = "������";   find_Location[3]->small_Loction = "���ؽ�";
			find_Location[4]->big_Loction = "������";   find_Location[4]->small_Loction = "��ô��";
			find_Location[5]->big_Loction = "������";   find_Location[5]->small_Loction = "���ʽ�";
			find_Location[6]->big_Loction = "������";   find_Location[6]->small_Loction = "�¹��";
			find_Location[7]->big_Loction = "������";   find_Location[7]->small_Loction = "ȫõ��";
			find_Location[8]->big_Loction = "������";   find_Location[8]->small_Loction = "ȭõ��";
			find_Location[9]->big_Loction = "������";   find_Location[9]->small_Loction = "Ⱦ����";
			find_Location[10]->big_Loction = "������";   find_Location[10]->small_Loction = "�籸��";
			find_Location[11]->big_Loction = "������";   find_Location[11]->small_Loction = "������";
			find_Location[12]->big_Loction = "������";   find_Location[12]->small_Loction = "������";
			find_Location[13]->big_Loction = "������";   find_Location[13]->small_Loction = "��â��";
			find_Location[14]->big_Loction = "������";   find_Location[14]->small_Loction = "����";
			find_Location[15]->big_Loction = "������";   find_Location[15]->small_Loction = "������";
			find_Location[16]->big_Loction = "������";   find_Location[16]->small_Loction = "��籺";
			find_Location[17]->big_Loction = "������";   find_Location[17]->small_Loction = "ö����";
			find_Location[18]->big_Loction = "��⵵";   find_Location[18]->small_Loction = "������";
			find_Location[19]->big_Loction = "��⵵";   find_Location[19]->small_Loction = "������";
			find_Location[20]->big_Loction = "��⵵";   find_Location[20]->small_Loction = "�����ν�";
			find_Location[21]->big_Loction = "��⵵";   find_Location[21]->small_Loction = "�Ⱦ��";
			find_Location[22]->big_Loction = "��⵵";   find_Location[22]->small_Loction = "��õ��";
			find_Location[23]->big_Loction = "��⵵";   find_Location[23]->small_Loction = "�����";
			find_Location[24]->big_Loction = "��⵵";   find_Location[24]->small_Loction = "����õ��";
			find_Location[25]->big_Loction = "��⵵";   find_Location[25]->small_Loction = "�Ȼ��";
			find_Location[26]->big_Loction = "��⵵";   find_Location[26]->small_Loction = "����";
			find_Location[27]->big_Loction = "��⵵";   find_Location[27]->small_Loction = "��õ��";
			find_Location[28]->big_Loction = "��⵵";   find_Location[28]->small_Loction = "������";
			find_Location[29]->big_Loction = "��⵵";   find_Location[29]->small_Loction = "���ý�";
			find_Location[30]->big_Loction = "��⵵";   find_Location[30]->small_Loction = "�����ֽ�";
			find_Location[31]->big_Loction = "��⵵";   find_Location[31]->small_Loction = "�����";
			find_Location[32]->big_Loction = "��⵵";   find_Location[32]->small_Loction = "�����";
			find_Location[33]->big_Loction = "��⵵";   find_Location[33]->small_Loction = "������";
			find_Location[34]->big_Loction = "��⵵";   find_Location[34]->small_Loction = "�ǿս�";
			find_Location[35]->big_Loction = "��⵵";   find_Location[35]->small_Loction = "�ϳ���";
			find_Location[36]->big_Loction = "��⵵";   find_Location[36]->small_Loction = "���ֽ�";
			find_Location[37]->big_Loction = "��⵵";   find_Location[37]->small_Loction = "��õ��";
			find_Location[38]->big_Loction = "��⵵";   find_Location[38]->small_Loction = "���ν�";
			find_Location[39]->big_Loction = "��⵵";   find_Location[39]->small_Loction = "�ȼ���";
			find_Location[40]->big_Loction = "��⵵";   find_Location[40]->small_Loction = "������";
			find_Location[41]->big_Loction = "��⵵";   find_Location[41]->small_Loction = "ȭ����";
			find_Location[42]->big_Loction = "��⵵";   find_Location[42]->small_Loction = "���ֽ�";
			find_Location[43]->big_Loction = "��⵵";   find_Location[43]->small_Loction = "���ֽ�";
			find_Location[44]->big_Loction = "��⵵";   find_Location[44]->small_Loction = "��õ��";
			find_Location[45]->big_Loction = "��⵵";   find_Location[45]->small_Loction = "���ֱ�";
			find_Location[46]->big_Loction = "��⵵";   find_Location[46]->small_Loction = "����";
			find_Location[47]->big_Loction = "��⵵";   find_Location[47]->small_Loction = "����";
			find_Location[48]->big_Loction = "��⵵";   find_Location[48]->small_Loction = "��õ��";
			find_Location[49]->big_Loction = "���ϵ�";   find_Location[49]->small_Loction = "���׽�";
			find_Location[50]->big_Loction = "���ϵ�";   find_Location[50]->small_Loction = "���ֽ�";
			find_Location[51]->big_Loction = "���ϵ�";   find_Location[51]->small_Loction = "��õ��";
			find_Location[52]->big_Loction = "���ϵ�";   find_Location[52]->small_Loction = "�ȵ���";
			find_Location[53]->big_Loction = "���ϵ�";   find_Location[53]->small_Loction = "���̽�";
			find_Location[54]->big_Loction = "���ϵ�";   find_Location[54]->small_Loction = "���ֽ�";
			find_Location[55]->big_Loction = "���ϵ�";   find_Location[55]->small_Loction = "��õ��";
			find_Location[56]->big_Loction = "���ϵ�";   find_Location[56]->small_Loction = "���ֽ�";
			find_Location[57]->big_Loction = "���ϵ�";   find_Location[57]->small_Loction = "�����";
			find_Location[58]->big_Loction = "���ϵ�";   find_Location[58]->small_Loction = "����";
			find_Location[59]->big_Loction = "���ϵ�";   find_Location[59]->small_Loction = "������";
			find_Location[60]->big_Loction = "���ϵ�";   find_Location[60]->small_Loction = "�Ǽ���";
			find_Location[61]->big_Loction = "���ϵ�";   find_Location[61]->small_Loction = "û�۱�";
			find_Location[62]->big_Loction = "���ϵ�";   find_Location[62]->small_Loction = "���籺";
			find_Location[63]->big_Loction = "���ϵ�";   find_Location[63]->small_Loction = "������";
			find_Location[64]->big_Loction = "���ϵ�";   find_Location[64]->small_Loction = "û����";
			find_Location[65]->big_Loction = "���ϵ�";   find_Location[65]->small_Loction = "��ɱ�";
			find_Location[66]->big_Loction = "���ϵ�";   find_Location[66]->small_Loction = "ĥ�";
			find_Location[67]->big_Loction = "���ϵ�";   find_Location[67]->small_Loction = "��õ��";
			find_Location[68]->big_Loction = "���ϵ�";   find_Location[68]->small_Loction = "��ȭ��";
			find_Location[69]->big_Loction = "���ϵ�";   find_Location[69]->small_Loction = "������";
			find_Location[70]->big_Loction = "���ϵ�";   find_Location[70]->small_Loction = "�︪��";
			find_Location[71]->big_Loction = "���ϵ�";   find_Location[71]->small_Loction = "���ֱ�";
			find_Location[72]->big_Loction = "��󳲵�";   find_Location[72]->small_Loction = "â����";
			find_Location[73]->big_Loction = "��󳲵�";   find_Location[73]->small_Loction = "�����";
			find_Location[74]->big_Loction = "��󳲵�";   find_Location[74]->small_Loction = "���ֽ�";
			find_Location[75]->big_Loction = "��󳲵�";   find_Location[75]->small_Loction = "���ؽ�";
			find_Location[76]->big_Loction = "��󳲵�";   find_Location[76]->small_Loction = "�뿵��";
			find_Location[77]->big_Loction = "��󳲵�";   find_Location[77]->small_Loction = "��õ��";
			find_Location[78]->big_Loction = "��󳲵�";   find_Location[78]->small_Loction = "���ؽ�";
			find_Location[79]->big_Loction = "��󳲵�";   find_Location[79]->small_Loction = "�о��";
			find_Location[80]->big_Loction = "��󳲵�";   find_Location[80]->small_Loction = "����";
			find_Location[81]->big_Loction = "��󳲵�";   find_Location[81]->small_Loction = "������";
			find_Location[82]->big_Loction = "��󳲵�";   find_Location[82]->small_Loction = "�Ƿɱ�";
			find_Location[83]->big_Loction = "��󳲵�";   find_Location[83]->small_Loction = "�Ծȱ�";
			find_Location[84]->big_Loction = "��󳲵�";   find_Location[84]->small_Loction = "â�籺";
			find_Location[85]->big_Loction = "��󳲵�";   find_Location[85]->small_Loction = "����";
			find_Location[86]->big_Loction = "��󳲵�";   find_Location[86]->small_Loction = "���ر�";
			find_Location[87]->big_Loction = "��󳲵�";   find_Location[87]->small_Loction = "�ϵ���";
			find_Location[88]->big_Loction = "��󳲵�";   find_Location[88]->small_Loction = "��û��";
			find_Location[89]->big_Loction = "��󳲵�";   find_Location[89]->small_Loction = "��â��";
			find_Location[90]->big_Loction = "��󳲵�";   find_Location[90]->small_Loction = "�Ծ籺";
			find_Location[91]->big_Loction = "��󳲵�";   find_Location[91]->small_Loction = "��õ��";
			find_Location[92]->big_Loction = "��û�ϵ�";   find_Location[92]->small_Loction = "û�ֽ�";
			find_Location[93]->big_Loction = "��û�ϵ�";   find_Location[93]->small_Loction = "���ֽ�";
			find_Location[94]->big_Loction = "��û�ϵ�";   find_Location[94]->small_Loction = "��õ��";
			find_Location[95]->big_Loction = "��û�ϵ�";   find_Location[95]->small_Loction = "û����";
			find_Location[96]->big_Loction = "��û�ϵ�";   find_Location[96]->small_Loction = "������";
			find_Location[97]->big_Loction = "��û�ϵ�";   find_Location[97]->small_Loction = "��õ��";
			find_Location[98]->big_Loction = "��û�ϵ�";   find_Location[98]->small_Loction = "��õ��";
			find_Location[99]->big_Loction = "��û�ϵ�";   find_Location[99]->small_Loction = "������";
			find_Location[100]->big_Loction = "��û�ϵ�";   find_Location[100]->small_Loction = "������";
			find_Location[101]->big_Loction = "��û�ϵ�";   find_Location[101]->small_Loction = "���걺";
			find_Location[102]->big_Loction = "��û�ϵ�";   find_Location[102]->small_Loction = "�ܾ籺";
			find_Location[103]->big_Loction = "��û����";   find_Location[103]->small_Loction = "õ�Ƚ�";
			find_Location[104]->big_Loction = "��û����";   find_Location[104]->small_Loction = "���ֽ�";
			find_Location[105]->big_Loction = "��û����";   find_Location[105]->small_Loction = "���ɽ�";
			find_Location[106]->big_Loction = "��û����";   find_Location[106]->small_Loction = "�ƻ��";
			find_Location[107]->big_Loction = "��û����";   find_Location[107]->small_Loction = "�����";
			find_Location[108]->big_Loction = "��û����";   find_Location[108]->small_Loction = "����";
			find_Location[109]->big_Loction = "��û����";   find_Location[109]->small_Loction = "��õ��";
			find_Location[110]->big_Loction = "��û����";   find_Location[110]->small_Loction = "ȫ����";
			find_Location[111]->big_Loction = "��û����";   find_Location[111]->small_Loction = "�¾ȱ�";
			find_Location[112]->big_Loction = "��û����";   find_Location[112]->small_Loction = "�ݻ걺";
			find_Location[113]->big_Loction = "��û����";   find_Location[113]->small_Loction = "���ⱺ";
			find_Location[114]->big_Loction = "��û����";   find_Location[114]->small_Loction = "�ο���";
			find_Location[115]->big_Loction = "��û����";   find_Location[115]->small_Loction = "û�籺";
			find_Location[116]->big_Loction = "��û����";   find_Location[116]->small_Loction = "���걺";
			find_Location[117]->big_Loction = "��û����";   find_Location[117]->small_Loction = "������";
			find_Location[118]->big_Loction = "����ϵ�";   find_Location[118]->small_Loction = "���ֽ�";
			find_Location[119]->big_Loction = "����ϵ�";   find_Location[119]->small_Loction = "�����";
			find_Location[120]->big_Loction = "����ϵ�";   find_Location[120]->small_Loction = "�ͻ��";
			find_Location[121]->big_Loction = "����ϵ�";   find_Location[121]->small_Loction = "������";
			find_Location[122]->big_Loction = "����ϵ�";   find_Location[122]->small_Loction = "������";
			find_Location[123]->big_Loction = "����ϵ�";   find_Location[123]->small_Loction = "������";
			find_Location[124]->big_Loction = "����ϵ�";   find_Location[124]->small_Loction = "���ֱ�";
			find_Location[125]->big_Loction = "����ϵ�";   find_Location[125]->small_Loction = "�ӽǱ�";
			find_Location[126]->big_Loction = "����ϵ�";   find_Location[126]->small_Loction = "��â��";
			find_Location[127]->big_Loction = "����ϵ�";   find_Location[127]->small_Loction = "���ȱ�";
			find_Location[128]->big_Loction = "����ϵ�";   find_Location[128]->small_Loction = "�����";
			find_Location[129]->big_Loction = "����ϵ�";   find_Location[129]->small_Loction = "��â��";
			find_Location[130]->big_Loction = "����ϵ�";   find_Location[130]->small_Loction = "�ξȱ�";
			find_Location[131]->big_Loction = "���󳲵�";   find_Location[131]->small_Loction = "������";
			find_Location[132]->big_Loction = "���󳲵�";   find_Location[132]->small_Loction = "������";
			find_Location[133]->big_Loction = "���󳲵�";   find_Location[133]->small_Loction = "��õ��";
			find_Location[134]->big_Loction = "���󳲵�";   find_Location[134]->small_Loction = "���ֽ�";
			find_Location[135]->big_Loction = "���󳲵�";   find_Location[135]->small_Loction = "�����";
			find_Location[136]->big_Loction = "���󳲵�";   find_Location[136]->small_Loction = "��籺";
			find_Location[137]->big_Loction = "���󳲵�";   find_Location[137]->small_Loction = "���ʱ�";
			find_Location[138]->big_Loction = "���󳲵�";   find_Location[138]->small_Loction = "���ﱺ";
			find_Location[139]->big_Loction = "���󳲵�";   find_Location[139]->small_Loction = "���ϱ�";
			find_Location[140]->big_Loction = "���󳲵�";   find_Location[140]->small_Loction = "������";
			find_Location[141]->big_Loction = "���󳲵�";   find_Location[141]->small_Loction = "������";
			find_Location[142]->big_Loction = "���󳲵�";   find_Location[142]->small_Loction = "���";
			find_Location[143]->big_Loction = "���󳲵�";   find_Location[143]->small_Loction = "���ﱺ";
			find_Location[144]->big_Loction = "���󳲵�";   find_Location[144]->small_Loction = "������";
			find_Location[145]->big_Loction = "���󳲵�";   find_Location[145]->small_Loction = "���ȱ�";
			find_Location[146]->big_Loction = "���󳲵�";   find_Location[146]->small_Loction = "�强��";
			find_Location[147]->big_Loction = "���󳲵�";   find_Location[147]->small_Loction = "�žȱ�";
			find_Location[148]->big_Loction = "���󳲵�";   find_Location[148]->small_Loction = "������";
			find_Location[149]->big_Loction = "���󳲵�";   find_Location[149]->small_Loction = "ȭ����";
			find_Location[150]->big_Loction = "���󳲵�";   find_Location[150]->small_Loction = "�س���";
			find_Location[151]->big_Loction = "���󳲵�";   find_Location[151]->small_Loction = "����";
			find_Location[152]->big_Loction = "���󳲵�";   find_Location[152]->small_Loction = "�ϵ���";
			find_Location[153]->big_Loction = "����Ư����ġ��";   find_Location[153]->small_Loction = "��������";
			find_Location[154]->big_Loction = "����Ư����ġ��";   find_Location[154]->small_Loction = "���ֽ�";
			find_Location[155]->big_Loction = "����Ư����ġ��";   find_Location[155]->small_Loction = "�����ֱ�";
			find_Location[156]->big_Loction = "����Ư����ġ��";   find_Location[156]->small_Loction = "�����ֱ�";
			find_Location[157]->big_Loction = "";   find_Location[157]->small_Loction = "����Ư����";
			find_Location[158]->big_Loction = "";   find_Location[158]->small_Loction = "�뱸������";
			find_Location[159]->big_Loction = "";   find_Location[159]->small_Loction = "���ֱ�����";
			find_Location[160]->big_Loction = "";   find_Location[160]->small_Loction = "��õ������";
			find_Location[161]->big_Loction = "";   find_Location[161]->small_Loction = "��걤����";
			find_Location[162]->big_Loction = "";   find_Location[162]->small_Loction = "����������";
			find_Location[163]->big_Loction = "";   find_Location[163]->small_Loction = "�λ걤����";
			find_Location[164]->big_Loction = "��걤����";   find_Location[164]->small_Loction = "���ֱ�";
			find_Location[165]->big_Loction = "�λ걤����";   find_Location[165]->small_Loction = "���屺";
			find_Location[166]->big_Loction = "��õ������";   find_Location[166]->small_Loction = "������";
			find_Location[167]->big_Loction = "��õ������";   find_Location[167]->small_Loction = "��ȭ��";

			for (int i = 0; i < Count; i++) // Count = �˶�����
			{
				for (int j = 0; j < 168; j++)
				{
					if (find_Location[j]->small_Loction == value[2 * i + 1]) // value // 1,3,5,7,9
					{
						B_L = find_Location[j]->big_Loction;
						S_L = find_Location[j]->small_Loction;

						break;
					}
				}

				String^ url = "";
				if (B_L->Length == 0) {
					url = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + S_L;
				}
				else {
					url = "http://jaehyeok.kr/programming_design/show_week_weather.php?big=" + B_L + "&mid=" + S_L;
				}
				XmlTextReader^ reder = gcnew XmlTextReader(url);
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

				array< TextBox^ >^ ddayStat = gcnew array < TextBox^ >(5);
				ddayStat[0] = weatherInfo1;
				ddayStat[1] = weatherInfo2;
				ddayStat[2] = weatherInfo3;
				ddayStat[3] = weatherInfo4;
				ddayStat[4] = weatherInfo5;

				array< PictureBox^ >^ ddayIm = gcnew array < PictureBox^ >(5);
				ddayIm[0] = weatherIm1;
				ddayIm[1] = weatherIm2;
				ddayIm[2] = weatherIm3;
				ddayIm[3] = weatherIm4;
				ddayIm[4] = weatherIm5;

				//�������� & ����������
				if (dDayInfo[i] == 0) // day - 0
				{
					ddayStat[i]->Text = Convert::ToString(week_Weather[3]);
					ddayIm[i]->Load("./������2/" + Convert::ToString(week_Weather[3]) + ".png");
				}
				else if (dDayInfo[i] == 1) // day - 1
				{
					ddayStat[i]->Text = Convert::ToString(week_Weather[8]);
					ddayIm[i]->Load("./������2/" + Convert::ToString(week_Weather[8]) + ".png");
				}
				else if (dDayInfo[i] == 2) // day - 2
				{
					ddayStat[i]->Text = Convert::ToString(week_Weather[13]);
					ddayIm[i]->Load("./������2/" + Convert::ToString(week_Weather[13]) + ".png");
				}
				else if (dDayInfo[i] == 3) // day - 3
				{
					ddayStat[i]->Text = Convert::ToString(week_Weather[18]);
					ddayIm[i]->Load("./������2/" + Convert::ToString(week_Weather[18]) + ".png");
				}
				else if (dDayInfo[i] == 4) // day - 4
				{
					ddayStat[i]->Text = Convert::ToString(week_Weather[23]);
					ddayIm[i]->Load("./������2/" + Convert::ToString(week_Weather[23]) + ".png");
				}
				else if (dDayInfo[i] == 5) // day - 5
				{
					ddayStat[i]->Text = Convert::ToString(week_Weather[28]);
					ddayIm[i]->Load("./������2/" + Convert::ToString(week_Weather[28]) + ".png");
				}
			}

		}

		ref class alarmLocation
		{
		public:
			String^ big_Loction;
			String^ small_Loction;

			String^ getBig_Loction()
			{
				return big_Loction;
			}
			String^ getSmall_Location()
			{
				return small_Loction;
			}
		};

	protected:
		/// <summary>
		/// ��� ���� ��� ���ҽ��� �����մϴ�.
		/// </summary>
		~Alarm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Timer^  AlarmOp;
	private: System::Windows::Forms::Button^  btnClose;
	private: System::Windows::Forms::TextBox^  alarmday1;
	private: System::Windows::Forms::TextBox^  alarmday2;
	private: System::Windows::Forms::TextBox^  alarmday3;
	private: System::Windows::Forms::TextBox^  dDay2;
	private: System::Windows::Forms::TextBox^  dDay1;
	private: System::Windows::Forms::TextBox^  dDay3;
	private: System::Windows::Forms::TextBox^  area4;
	private: System::Windows::Forms::TextBox^  area1;
	private: System::Windows::Forms::TextBox^  area3;
	private: System::Windows::Forms::TextBox^  area2;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::TextBox^  dDay4;
	private: System::Windows::Forms::TextBox^  alarmday4;
	private: System::Windows::Forms::TextBox^  area5;
	private: System::Windows::Forms::TextBox^  dDay5;
	private: System::Windows::Forms::TextBox^  alarmday5;
	private: System::Windows::Forms::TextBox^  weatherInfo5;
	private: System::Windows::Forms::TextBox^  weatherInfo4;
	private: System::Windows::Forms::TextBox^  weatherInfo3;
	private: System::Windows::Forms::TextBox^  weatherInfo2;
	private: System::Windows::Forms::TextBox^  weatherInfo1;
	private: System::Windows::Forms::PictureBox^  weatherIm1;
	private: System::Windows::Forms::PictureBox^  weatherIm5;
	private: System::Windows::Forms::PictureBox^  weatherIm4;
	private: System::Windows::Forms::PictureBox^  weatherIm3;
	private: System::Windows::Forms::PictureBox^  weatherIm2;

	private: System::ComponentModel::IContainer^  components;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Alarm::typeid));
			this->AlarmOp = (gcnew System::Windows::Forms::Timer(this->components));
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->alarmday1 = (gcnew System::Windows::Forms::TextBox());
			this->alarmday2 = (gcnew System::Windows::Forms::TextBox());
			this->alarmday3 = (gcnew System::Windows::Forms::TextBox());
			this->dDay2 = (gcnew System::Windows::Forms::TextBox());
			this->dDay1 = (gcnew System::Windows::Forms::TextBox());
			this->dDay3 = (gcnew System::Windows::Forms::TextBox());
			this->area4 = (gcnew System::Windows::Forms::TextBox());
			this->area1 = (gcnew System::Windows::Forms::TextBox());
			this->area3 = (gcnew System::Windows::Forms::TextBox());
			this->area2 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->dDay4 = (gcnew System::Windows::Forms::TextBox());
			this->alarmday4 = (gcnew System::Windows::Forms::TextBox());
			this->area5 = (gcnew System::Windows::Forms::TextBox());
			this->dDay5 = (gcnew System::Windows::Forms::TextBox());
			this->alarmday5 = (gcnew System::Windows::Forms::TextBox());
			this->weatherInfo5 = (gcnew System::Windows::Forms::TextBox());
			this->weatherInfo4 = (gcnew System::Windows::Forms::TextBox());
			this->weatherInfo3 = (gcnew System::Windows::Forms::TextBox());
			this->weatherInfo2 = (gcnew System::Windows::Forms::TextBox());
			this->weatherInfo1 = (gcnew System::Windows::Forms::TextBox());
			this->weatherIm1 = (gcnew System::Windows::Forms::PictureBox());
			this->weatherIm5 = (gcnew System::Windows::Forms::PictureBox());
			this->weatherIm4 = (gcnew System::Windows::Forms::PictureBox());
			this->weatherIm3 = (gcnew System::Windows::Forms::PictureBox());
			this->weatherIm2 = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm2))->BeginInit();
			this->SuspendLayout();
			// 
			// AlarmOp
			// 
			this->AlarmOp->Interval = 50;
			this->AlarmOp->Tick += gcnew System::EventHandler(this, &Alarm::AlarmOp_Tick);
			// 
			// btnClose
			// 
			this->btnClose->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			resources->ApplyResources(this->btnClose, L"btnClose");
			this->btnClose->Name = L"btnClose";
			this->btnClose->UseVisualStyleBackColor = false;
			this->btnClose->Click += gcnew System::EventHandler(this, &Alarm::btnClose_Click);
			// 
			// alarmday1
			// 
			this->alarmday1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->alarmday1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->alarmday1, L"alarmday1");
			this->alarmday1->Name = L"alarmday1";
			this->alarmday1->TextChanged += gcnew System::EventHandler(this, &Alarm::alarmday1_TextChanged);
			// 
			// alarmday2
			// 
			this->alarmday2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->alarmday2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->alarmday2, L"alarmday2");
			this->alarmday2->Name = L"alarmday2";
			this->alarmday2->TextChanged += gcnew System::EventHandler(this, &Alarm::alarmday2_TextChanged);
			// 
			// alarmday3
			// 
			this->alarmday3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->alarmday3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->alarmday3, L"alarmday3");
			this->alarmday3->Name = L"alarmday3";
			this->alarmday3->TextChanged += gcnew System::EventHandler(this, &Alarm::alarmday3_TextChanged);
			// 
			// dDay2
			// 
			this->dDay2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->dDay2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->dDay2, L"dDay2");
			this->dDay2->ForeColor = System::Drawing::Color::Red;
			this->dDay2->Name = L"dDay2";
			this->dDay2->TextChanged += gcnew System::EventHandler(this, &Alarm::dDay2_TextChanged);
			// 
			// dDay1
			// 
			this->dDay1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->dDay1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->dDay1, L"dDay1");
			this->dDay1->ForeColor = System::Drawing::Color::Red;
			this->dDay1->Name = L"dDay1";
			this->dDay1->TextChanged += gcnew System::EventHandler(this, &Alarm::dDay1_TextChanged);
			// 
			// dDay3
			// 
			this->dDay3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->dDay3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->dDay3, L"dDay3");
			this->dDay3->ForeColor = System::Drawing::Color::Red;
			this->dDay3->Name = L"dDay3";
			this->dDay3->TextChanged += gcnew System::EventHandler(this, &Alarm::dDay3_TextChanged);
			// 
			// area4
			// 
			this->area4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->area4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->area4, L"area4");
			this->area4->Name = L"area4";
			this->area4->TextChanged += gcnew System::EventHandler(this, &Alarm::area4_TextChanged);
			// 
			// area1
			// 
			this->area1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->area1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->area1, L"area1");
			this->area1->Name = L"area1";
			this->area1->TextChanged += gcnew System::EventHandler(this, &Alarm::area1_TextChanged);
			// 
			// area3
			// 
			this->area3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->area3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->area3, L"area3");
			this->area3->Name = L"area3";
			this->area3->TextChanged += gcnew System::EventHandler(this, &Alarm::area3_TextChanged);
			// 
			// area2
			// 
			this->area2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->area2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->area2, L"area2");
			this->area2->Name = L"area2";
			this->area2->TextChanged += gcnew System::EventHandler(this, &Alarm::area2_TextChanged);
			// 
			// pictureBox7
			// 
			resources->ApplyResources(this->pictureBox7, L"pictureBox7");
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox6
			// 
			resources->ApplyResources(this->pictureBox6, L"pictureBox6");
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox5
			// 
			resources->ApplyResources(this->pictureBox5, L"pictureBox5");
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox4
			// 
			resources->ApplyResources(this->pictureBox4, L"pictureBox4");
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->TabStop = false;
			// 
			// dDay4
			// 
			this->dDay4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->dDay4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->dDay4, L"dDay4");
			this->dDay4->ForeColor = System::Drawing::Color::Red;
			this->dDay4->Name = L"dDay4";
			this->dDay4->TextChanged += gcnew System::EventHandler(this, &Alarm::dDay4_TextChanged);
			// 
			// alarmday4
			// 
			this->alarmday4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->alarmday4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->alarmday4, L"alarmday4");
			this->alarmday4->Name = L"alarmday4";
			this->alarmday4->TextChanged += gcnew System::EventHandler(this, &Alarm::alarmday4_TextChanged);
			// 
			// area5
			// 
			this->area5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->area5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->area5, L"area5");
			this->area5->Name = L"area5";
			this->area5->TextChanged += gcnew System::EventHandler(this, &Alarm::area5_TextChanged);
			// 
			// dDay5
			// 
			this->dDay5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->dDay5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->dDay5, L"dDay5");
			this->dDay5->ForeColor = System::Drawing::Color::Red;
			this->dDay5->Name = L"dDay5";
			this->dDay5->TextChanged += gcnew System::EventHandler(this, &Alarm::dDay5_TextChanged);
			// 
			// alarmday5
			// 
			this->alarmday5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->alarmday5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->alarmday5, L"alarmday5");
			this->alarmday5->Name = L"alarmday5";
			this->alarmday5->TextChanged += gcnew System::EventHandler(this, &Alarm::alarmday5_TextChanged);
			// 
			// weatherInfo5
			// 
			this->weatherInfo5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->weatherInfo5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->weatherInfo5, L"weatherInfo5");
			this->weatherInfo5->ForeColor = System::Drawing::Color::Black;
			this->weatherInfo5->Name = L"weatherInfo5";
			this->weatherInfo5->TextChanged += gcnew System::EventHandler(this, &Alarm::textBox2_TextChanged);
			// 
			// weatherInfo4
			// 
			this->weatherInfo4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->weatherInfo4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->weatherInfo4, L"weatherInfo4");
			this->weatherInfo4->ForeColor = System::Drawing::Color::Black;
			this->weatherInfo4->Name = L"weatherInfo4";
			this->weatherInfo4->TextChanged += gcnew System::EventHandler(this, &Alarm::textBox10_TextChanged);
			// 
			// weatherInfo3
			// 
			this->weatherInfo3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->weatherInfo3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->weatherInfo3, L"weatherInfo3");
			this->weatherInfo3->ForeColor = System::Drawing::Color::Black;
			this->weatherInfo3->Name = L"weatherInfo3";
			this->weatherInfo3->TextChanged += gcnew System::EventHandler(this, &Alarm::textBox13_TextChanged);
			// 
			// weatherInfo2
			// 
			this->weatherInfo2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->weatherInfo2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->weatherInfo2, L"weatherInfo2");
			this->weatherInfo2->ForeColor = System::Drawing::Color::Black;
			this->weatherInfo2->Name = L"weatherInfo2";
			this->weatherInfo2->TextChanged += gcnew System::EventHandler(this, &Alarm::textBox11_TextChanged);
			// 
			// weatherInfo1
			// 
			this->weatherInfo1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			this->weatherInfo1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			resources->ApplyResources(this->weatherInfo1, L"weatherInfo1");
			this->weatherInfo1->ForeColor = System::Drawing::Color::Black;
			this->weatherInfo1->Name = L"weatherInfo1";
			this->weatherInfo1->TextChanged += gcnew System::EventHandler(this, &Alarm::textBox12_TextChanged);
			// 
			// weatherIm1
			// 
			this->weatherIm1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			resources->ApplyResources(this->weatherIm1, L"weatherIm1");
			this->weatherIm1->Name = L"weatherIm1";
			this->weatherIm1->TabStop = false;
			// 
			// weatherIm5
			// 
			this->weatherIm5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			resources->ApplyResources(this->weatherIm5, L"weatherIm5");
			this->weatherIm5->Name = L"weatherIm5";
			this->weatherIm5->TabStop = false;
			// 
			// weatherIm4
			// 
			this->weatherIm4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			resources->ApplyResources(this->weatherIm4, L"weatherIm4");
			this->weatherIm4->Name = L"weatherIm4";
			this->weatherIm4->TabStop = false;
			// 
			// weatherIm3
			// 
			this->weatherIm3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			resources->ApplyResources(this->weatherIm3, L"weatherIm3");
			this->weatherIm3->Name = L"weatherIm3";
			this->weatherIm3->TabStop = false;
			// 
			// weatherIm2
			// 
			this->weatherIm2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(217)), static_cast<System::Int32>(static_cast<System::Byte>(217)),
				static_cast<System::Int32>(static_cast<System::Byte>(217)));
			resources->ApplyResources(this->weatherIm2, L"weatherIm2");
			this->weatherIm2->Name = L"weatherIm2";
			this->weatherIm2->TabStop = false;
			// 
			// Alarm
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Control;
			this->Controls->Add(this->weatherIm2);
			this->Controls->Add(this->weatherIm3);
			this->Controls->Add(this->weatherIm4);
			this->Controls->Add(this->weatherIm5);
			this->Controls->Add(this->weatherIm1);
			this->Controls->Add(this->area5);
			this->Controls->Add(this->weatherInfo5);
			this->Controls->Add(this->dDay5);
			this->Controls->Add(this->alarmday5);
			this->Controls->Add(this->alarmday1);
			this->Controls->Add(this->alarmday2);
			this->Controls->Add(this->alarmday3);
			this->Controls->Add(this->dDay2);
			this->Controls->Add(this->dDay1);
			this->Controls->Add(this->dDay3);
			this->Controls->Add(this->area4);
			this->Controls->Add(this->area1);
			this->Controls->Add(this->area3);
			this->Controls->Add(this->area2);
			this->Controls->Add(this->weatherInfo3);
			this->Controls->Add(this->weatherInfo1);
			this->Controls->Add(this->weatherInfo2);
			this->Controls->Add(this->weatherInfo4);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->dDay4);
			this->Controls->Add(this->alarmday4);
			this->Controls->Add(this->btnClose);
			this->DoubleBuffered = true;
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"Alarm";
			this->TransparencyKey = System::Drawing::Color::White;
			this->Load += gcnew System::EventHandler(this, &Alarm::Alarm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->weatherIm2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion
	private: System::Void AlarmOp_Tick(System::Object^  sender, System::EventArgs^  e) {

		this->Opacity = alarmOp;
		alarmOp += 0.05;

		if (alarmOp > 1)
		{
		AlarmOp->Stop();
		}

		

	}
	private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) {
		alarmOp = 0;
		formOp = 1;
		stateCount = 1;
		this->Close();
	}
	private: System::Void Alarm_Load(System::Object^  sender, System::EventArgs^  e) {
		AlarmOp->Start();

	}
	private: System::Void alarmday1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void alarmday2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void alarmday3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void dDay2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void dDay1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void dDay3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void area4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void area1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void area3_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void area2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox13_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox12_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox11_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox10_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void alarmday4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void dDay5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void area5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void alarmday5_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	private: System::Void dDay4_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
	};
}
