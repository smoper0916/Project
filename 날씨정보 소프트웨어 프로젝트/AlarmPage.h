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

	extern int menubarState;
	extern int alarmCloseCount;

	static int yearVal;
	static int monthVal;

	static int nowYearVal; // 현재이전의 데이터를 삭제시키기 위한 변수
	static int nowMonthVal; // 현재이전의 데이터를 삭제시키기 위한 변수
	static int nowDayVal; // 현재이전의 데이터를 삭제시키기 위한 변수

	const int sevenDays = 7;		//달력의 요일 개수
	const int week = 6;				//달력에 나타날수있는 최대 행의 개수
	const int monthSize = 12;
	static int selectDay; // 달력에서 선택한 날짜

	/// <summary>
	/// AlarmPage에 대한 요약입니다.
	/// </summary>
	public ref class AlarmPage : public System::Windows::Forms::Form
	{
	public:

		array<String^>^ tmpCityName = gcnew array<String^>(43);
		array<int^, 2>^ dayList = gcnew array<int^, 2>(6, 7); // Day 값을 입력받는 배열
	private: System::Windows::Forms::Timer^  tableReset;
	private: System::Windows::Forms::Timer^  totalReset;
	private: System::Windows::Forms::Timer^  CloseTimer;
	public:
		array<int^, 2>^ privDayList = gcnew array<int^, 2>(6, 7); // privDay 값을 입력받는 배열

		AlarmPage(void)
		{
			InitializeComponent();
			addCities();
			//
			//TODO: 생성자 코드를 여기에 추가합니다.
			//
			yearVal = System::DateTime::Now.Year;
			monthVal = System::DateTime::Now.Month;

			nowYearVal = System::DateTime::Now.Year;
			nowMonthVal = System::DateTime::Now.Month;
			nowDayVal = System::DateTime::Now.Day;

			year->Text = yearVal + "년";
			month->Text = monthVal + "월";

			if (monthVal <= 1)
			{
				insertDate(yearVal, monthVal, dayList);
				insertDate(yearVal - 1, 12, privDayList);
			}
			else
			{
				insertDate(yearVal, monthVal, dayList);
				insertDate(yearVal, monthVal - 1, privDayList);
			}
			ChangeDayList(dayList); // 현재달값
			ChangePrivDayList(privDayList); // 이전달값
			updateAlarm(); // 현재날짜 이전 스케쥴 삭제
			//////////////////////////////////////////////////////////
			// day 값 입력부분 END ///////////////////////////////////
			tableReset->Start();
			totalReset->Start();
		}
		int selectPosition(array<int^, 2>^ dayList, int day)
		{
			int returnIndex = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (dayList[i, j]->Equals(day))
						return returnIndex + 1;
					returnIndex++;
				}
			}
			return -999;
		}
		void updateAlarm()
		{
			String^ fileName = "alarm.dat";
			int tmpYear;
			int tmpMonth;
			int tmpDay;

			array<int>^ yearRecord = gcnew array<int>(365); // 값저장배열
			array<int>^ monthRecord = gcnew array<int>(365); // 값저장배열
			array<int>^ daysRecord = gcnew array<int>(365); // 값저장배열
			array<String^>^ cityRecord = gcnew array<String^>(365); // 값저장배열
			int count = 0;

			FileStream^ fs = gcnew FileStream(fileName, FileMode::OpenOrCreate, FileAccess::Read);
			StreamReader^ st = gcnew StreamReader(fs, System::Text::Encoding::UTF8);
			st->BaseStream->Seek(0, SeekOrigin::Begin);
			while (st->Peek() > -1)
			{
				String^ temp = st->ReadLine();
				String^ tmpStr;
				tmpYear = (temp[0] - '0') * 1000 + (temp[1] - '0') * 100 + (temp[2] - '0') * 10 + (temp[3] - '0');
				if (temp[6].Equals(' '))
				{
					tmpMonth = (temp[5] - '0');
					if (temp[8].Equals(' ')) // xxxx x x sssss
					{
						tmpDay = (temp[7] - '0');
						for (int i = 9; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}
					else // xxxx x xx sssss
					{
						tmpDay = (temp[7] - '0') * 10 + (temp[8] - '0');
						for (int i = 10; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}
				}
				else
				{
					tmpMonth = (temp[5] - '0') * 10 + (temp[6] - '0');
					if (temp[9].Equals(' ')) // xxxx xx x ssssss
					{
						tmpDay = (temp[8] - '0');
						for (int i = 10; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}
					else // xxxx xx xx sssssssss
					{
						tmpDay = (temp[8] - '0') * 10 + (temp[9] - '0');
						for (int i = 11; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}

				}
				if (tmpYear <= nowYearVal && tmpMonth <= nowMonthVal && tmpDay < nowDayVal)
				{
					continue;
				}
				else
				{
					yearRecord[count] = tmpYear;
					monthRecord[count] = tmpMonth;
					daysRecord[count] = tmpDay;
					cityRecord[count++] = String::Copy(tmpStr);
				}
			}
			st->Close();
			fs->Close();
			///////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////정렬부분/////////
			for (int i = 0; i < count - 1; i++)
			{
				for (int j = 0; j < count - 1; j++)
				{
					if (daysRecord[j] > daysRecord[j + 1])
					{
						int tempYear;
						int tempMonth;
						int tempDay;
						String^ tempCityName;

						tempYear = yearRecord[j];
						tempMonth = monthRecord[j];
						tempDay = daysRecord[j];
						tempCityName = cityRecord[j];
						yearRecord[j] = yearRecord[j + 1];
						monthRecord[j] = monthRecord[j + 1];
						daysRecord[j] = daysRecord[j + 1];
						cityRecord[j] = cityRecord[j + 1];
						yearRecord[j + 1] = tempYear;
						monthRecord[j + 1] = tempMonth;
						daysRecord[j + 1] = tempDay;
						cityRecord[j + 1] = tempCityName;
					}
				}
			}
			for (int i = 0; i < count - 1; i++)
			{
				for (int j = 0; j < count - 1; j++)
				{
					if (monthRecord[j] > monthRecord[j + 1])
					{
						int tempYear;
						int tempMonth;
						int tempDay;
						String^ tempCityName;

						tempYear = yearRecord[j];
						tempMonth = monthRecord[j];
						tempDay = daysRecord[j];
						tempCityName = cityRecord[j];
						yearRecord[j] = yearRecord[j + 1];
						monthRecord[j] = monthRecord[j + 1];
						daysRecord[j] = daysRecord[j + 1];
						cityRecord[j] = cityRecord[j + 1];
						yearRecord[j + 1] = tempYear;
						monthRecord[j + 1] = tempMonth;
						daysRecord[j + 1] = tempDay;
						cityRecord[j + 1] = tempCityName;
					}
				}
			}
			for (int i = 0; i < count - 1; i++)
			{
				for (int j = 0; j < count - 1; j++)
				{
					if (yearRecord[j] > yearRecord[j + 1])
					{
						int tempYear;
						int tempMonth;
						int tempDay;
						String^ tempCityName;

						tempYear = yearRecord[j];
						tempMonth = monthRecord[j];
						tempDay = daysRecord[j];
						tempCityName = cityRecord[j];
						yearRecord[j] = yearRecord[j + 1];
						monthRecord[j] = monthRecord[j + 1];
						daysRecord[j] = daysRecord[j + 1];
						cityRecord[j] = cityRecord[j + 1];
						yearRecord[j + 1] = tempYear;
						monthRecord[j + 1] = tempMonth;
						daysRecord[j + 1] = tempDay;
						cityRecord[j + 1] = tempCityName;
					}
				}
			}
			///////////////////////////////////////////////////////////////////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////

			fs = gcnew FileStream(fileName, FileMode::Create, FileAccess::Write);
			StreamWriter^ sw = gcnew StreamWriter(fs, System::Text::Encoding::UTF8);
			for (int i = 0; i < count; i++)
			{
				sw->WriteLine("{0} {1} {2} {3}", yearRecord[i], monthRecord[i], daysRecord[i], cityRecord[i]);
			}

			sw->Flush();
			sw->Close();
			fs->Close();
		}
		void deleteAlarm(int inputYear, int inputMonth, int inputDay, String^ cityName)
		{
			String^ fileName = "alarm.dat";
			int tmpYear;
			int tmpMonth;
			int tmpDay;

			array<int^, 2>^ dayRecord = gcnew array<int^, 2>(365, 3); // 값저장 배열
			array<String^>^ cityRecord = gcnew array<String^>(365);
			int count = 0;

			FileStream^ fs = gcnew FileStream(fileName, FileMode::OpenOrCreate, FileAccess::Read);
			StreamReader^ st = gcnew StreamReader(fs, System::Text::Encoding::UTF8);
			st->BaseStream->Seek(0, SeekOrigin::Begin);
			while (st->Peek() > -1)
			{
				String^ temp = st->ReadLine();
				String^ tmpStr;
				tmpYear = (temp[0] - '0') * 1000 + (temp[1] - '0') * 100 + (temp[2] - '0') * 10 + (temp[3] - '0');
				if (temp[6].Equals(' '))
				{
					tmpMonth = (temp[5] - '0');
					if (temp[8].Equals(' ')) // xxxx x x sssss
					{
						tmpDay = (temp[7] - '0');
						for (int i = 9; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}
					else // xxxx x xx sssss
					{
						tmpDay = (temp[7] - '0') * 10 + (temp[8] - '0');
						for (int i = 10; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}
				}
				else
				{
					tmpMonth = (temp[5] - '0') * 10 + (temp[6] - '0');
					if (temp[9].Equals(' ')) // xxxx xx x ssssss
					{
						tmpDay = (temp[8] - '0');
						for (int i = 10; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}
					else // xxxx xx xx sssssssss
					{
						tmpDay = (temp[8] - '0') * 10 + (temp[9] - '0');
						for (int i = 11; i < temp->Length; i++)
						{
							tmpStr += (temp[i]);
						}
					}

				}
				if (tmpYear == inputYear && tmpMonth == inputMonth && tmpDay == inputDay) // 삭제해야할 년,월,일이라면
				{
					continue;
				}
				else
				{
					dayRecord[count, 0] = tmpYear;
					dayRecord[count, 1] = tmpMonth;
					dayRecord[count, 2] = tmpDay;
					cityRecord[count++] = String::Copy(tmpStr);
				}
			}
			st->Close();
			fs->Close();

			fs = gcnew FileStream(fileName, FileMode::Create, FileAccess::Write);
			StreamWriter^ sw = gcnew StreamWriter(fs, System::Text::Encoding::UTF8);
			for (int i = 0; i < count; i++)
			{
				sw->WriteLine("{0} {1} {2} {3}", dayRecord[i, 0], dayRecord[i, 1], dayRecord[i, 2], cityRecord[i]);
			}

			sw->Flush();
			sw->Close();
			fs->Close();
		}
		void saveAlarm(int inputYear, int inputMonth, int inputDay, String^ cityName)
		{
			String^ fileName = "alarm.dat";
			FileStream^ fs = gcnew FileStream(fileName, FileMode::Append, FileAccess::Write);
			// append 이어쓰기
			StreamWriter^ sw = gcnew StreamWriter(fs, System::Text::Encoding::UTF8);

			sw->WriteLine("{0} {1} {2} {3}", inputYear, inputMonth, inputDay, cityName);
			sw->Flush();
			sw->Close();
			fs->Close();
		}
		void loadAlarm(array<int^, 2>^ dayList)
		{
			String^ fileName = "alarm.dat";
			int tmpYear;
			int tmpMonth;
			int tmpDay;

			FileStream^ fs = gcnew FileStream(fileName, FileMode::OpenOrCreate, FileAccess::Read);
			StreamReader^ st = gcnew StreamReader(fs, System::Text::Encoding::UTF8);
			st->BaseStream->Seek(0, SeekOrigin::Begin);
			while (st->Peek() > -1)
			{
				String^ temp = st->ReadLine();
				// 로드해서 해당 년 월 일의 값을 설정해줘야함
				tmpYear = (temp[0] - '0') * 1000 + (temp[1] - '0') * 100 + (temp[2] - '0') * 10 + (temp[3] - '0');
				if (temp[6].Equals(' '))
				{
					tmpMonth = (temp[5] - '0');
					if (temp[8].Equals(' ')) // xxxx x x sssss
					{
						tmpDay = (temp[7] - '0');
					}
					else // xxxx x xx sssss
					{
						tmpDay = (temp[7] - '0') * 10 + (temp[8] - '0');
					}
				}
				else
				{
					tmpMonth = (temp[5] - '0') * 10 + (temp[6] - '0');
					if (temp[9].Equals(' ')) // xxxx xx x ssssss
					{
						tmpDay = (temp[8] - '0');
					}
					else // xxxx xx xx sssssssss
					{
						tmpDay = (temp[8] - '0') * 10 + (temp[9] - '0');
					}

				}
				///////////////////////////////////////////////////////////////////////
				//달력선택부분/////////////////////////////////////////////////////////
				if (yearVal == tmpYear)
				{
					if (monthVal == tmpMonth)
					{
						ChangeChooseDayColor(selectPosition(dayList, tmpDay));
					}
				}
			}
			st->Close();
			fs->Close();
		}
		void selectCityName()
		{
			String^ fileName = "alarm.dat";
			int tmpYear;
			int tmpMonth;
			int tmpDay;
			for (int i = 0; i < tmpCityName->Length; i++)
			{
				tmpCityName[i] = "";
			}
			FileStream^ fs = gcnew FileStream(fileName, FileMode::OpenOrCreate, FileAccess::Read);
			StreamReader^ st = gcnew StreamReader(fs, System::Text::Encoding::UTF8);
			st->BaseStream->Seek(0, SeekOrigin::Begin);
			while (st->Peek() > -1)
			{
				String^ temp = st->ReadLine();
				// 로드해서 해당 년 월 일의 값을 설정해줘야함
				tmpYear = (temp[0] - '0') * 1000 + (temp[1] - '0') * 100 + (temp[2] - '0') * 10 + (temp[3] - '0');
				if (yearVal == tmpYear)
					if (temp[6].Equals(' '))
					{
						tmpMonth = (temp[5] - '0');
						if (monthVal == tmpMonth)
							if (temp[8].Equals(' ')) // xxxx x x sssss
							{
								tmpDay = (temp[7] - '0');
								for (int j = 0; j < 6; j++)
								{
									for (int k = 0; k < 7; k++)
									{
										if (dayList[j, k]->Equals(tmpDay))
										{
											String^ tmpStr;
											for (int i = 9; i < temp->Length; i++)
											{
												tmpStr += (temp[i]);
											}
											tmpCityName[j * 7 + k + 1] = String::Copy(tmpStr);
										}
									}
								}
							}
							else // xxxx x xx sssss
							{
								tmpDay = (temp[7] - '0') * 10 + (temp[8] - '0');
								for (int j = 0; j < 6; j++)
								{
									for (int k = 0; k < 7; k++)
									{
										if (dayList[j, k]->Equals(tmpDay))
										{
											String^ tmpStr;
											for (int i = 10; i < temp->Length; i++)
											{
												tmpStr += (temp[i]);
											}
											tmpCityName[j * 7 + k + 1] = String::Copy(tmpStr);
										}
									}
								}
							}
					}
					else
					{
						tmpMonth = (temp[5] - '0') * 10 + (temp[6] - '0');
						if (monthVal == tmpMonth)
							if (temp[9].Equals(' ')) // xxxx xx x ssssss
							{
								tmpDay = (temp[8] - '0');
								for (int j = 0; j < 6; j++)
								{
									for (int k = 0; k < 7; k++)
									{
										if (dayList[j, k]->Equals(tmpDay))
										{
											String^ tmpStr;
											for (int i = 10; i < temp->Length; i++)
											{
												tmpStr += (temp[i]);
											}
											tmpCityName[j * 7 + k + 1] = String::Copy(tmpStr);
										}
									}
								}
							}
							else // xxxx xx xx sssssssss
							{
								tmpDay = (temp[8] - '0') * 10 + (temp[9] - '0');
								for (int j = 0; j < 6; j++)
								{
									for (int k = 0; k < 7; k++)
									{
										if (dayList[j, k]->Equals(tmpDay))
										{
											String^ tmpStr;
											for (int i = 11; i < temp->Length; i++)
											{
												tmpStr += (temp[i]);
											}
											tmpCityName[j * 7 + k + 1] = String::Copy(tmpStr);
										}
									}
								}
							}

					}
			}
			st->Close();
			fs->Close();
		}
		void changeCityName(int index)
		{
			switch (index)
			{
			default:
				break;
			}
		}
		void insertDate(int inputYear, int inputMonth, array<int^, 2>^ dayList)
		{
			int month[2][monthSize];

			month[0][0] = 31;		//1월의 마지막 날
			//2월은 윤년일때 체크하기위해
			month[0][2] = 31;
			month[0][3] = 30;
			month[0][4] = 31;
			month[0][5] = 30;
			month[0][6] = 31;
			month[0][7] = 31;
			month[0][8] = 30;
			month[0][9] = 31;
			month[0][10] = 30;
			month[0][11] = 31;		//12월의 마지막 날


			int totalDay;

			totalDay = (inputYear - 1) * 365 + 1;												//1년 1월 1일부터 지나온 날짜(1월1일은 월요일)
			totalDay += ((inputYear - 1) / 4) - ((inputYear - 1) / 100) + ((inputYear - 1) / 400);			//윤년

			if (((inputYear % 4 == 0) && (inputYear % 100 != 0)) || (inputYear % 400 == 0))		//입력된 년도가 윤년일때
			{
				month[0][1] = 29;
			}
			else
			{
				month[0][1] = 28;
			}


			month[1][0] = totalDay % sevenDays;						//1월의 시작요일


			for (int i = 1; i < monthSize; ++i)										//2월부터 12월까지 시작요일
			{
				int lastDay;
				lastDay = month[0][i];

				month[1][i] = (month[0][i - 1] + month[1][i - 1]) % sevenDays;
				//이번달 시작요일 = (전달 마지막날 + 시작하는요일) % sevenDays
			}


			int dateArr[week][sevenDays];

			int date = 1;


			for (int i = 0; i < month[1][inputMonth - 1]; ++i)		//첫주에 나타나는 날짜
			{
				dayList[0, i] = -999;
			}

			for (int i = month[1][inputMonth - 1]; i < sevenDays; ++i)		//첫주에 나타나는 날짜
			{
				dayList[0, i] = date;
				++date;
			}


			for (int i = 1; i < week; ++i)					//두번째주부터 마지막까지 나타나는 날짜
			{
				for (int j = 0; j < sevenDays; ++j)
				{

					if (date > month[0][inputMonth - 1])
					{
						dayList[i, j] = -999;
					}
					else
					{
						dayList[i, j] = date;
					}
					++date;
				}
			}
		}
		void ChangeDayColor(int selectday)
		{
			switch (selectday)
			{
			case -999:
				day1->ForeColor = Color::White;
				day2->ForeColor = Color::White;
				day3->ForeColor = Color::White;
				day4->ForeColor = Color::White;
				day5->ForeColor = Color::White;
				day6->ForeColor = Color::White;
				day7->ForeColor = Color::White;
				day8->ForeColor = Color::White;
				day9->ForeColor = Color::White;
				day10->ForeColor = Color::White;
				day11->ForeColor = Color::White;
				day12->ForeColor = Color::White;
				day13->ForeColor = Color::White;
				day14->ForeColor = Color::White;
				day15->ForeColor = Color::White;
				day16->ForeColor = Color::White;
				day17->ForeColor = Color::White;
				day18->ForeColor = Color::White;
				day19->ForeColor = Color::White;
				day20->ForeColor = Color::White;
				day21->ForeColor = Color::White;
				day22->ForeColor = Color::White;
				day23->ForeColor = Color::White;
				day24->ForeColor = Color::White;
				day25->ForeColor = Color::White;
				day26->ForeColor = Color::White;
				day27->ForeColor = Color::White;
				day28->ForeColor = Color::White;
				day29->ForeColor = Color::White;
				day30->ForeColor = Color::White;
				day31->ForeColor = Color::White;
				day32->ForeColor = Color::White;
				day33->ForeColor = Color::White;
				day34->ForeColor = Color::White;
				day35->ForeColor = Color::White;
				day36->ForeColor = Color::White;
				day37->ForeColor = Color::White;
				day38->ForeColor = Color::White;
				day39->ForeColor = Color::White;
				day40->ForeColor = Color::White;
				day41->ForeColor = Color::White;
				day42->ForeColor = Color::White;
				break;
			default:
				break;
			}
		}
		void ChangeChooseDayColor(int selectday)
		{
			switch (selectday)
			{
			case 1:
				day1->ForeColor = Color::PaleVioletRed;
				break;
			case 2:
				day2->ForeColor = Color::PaleVioletRed;
				break;
			case 3:
				day3->ForeColor = Color::PaleVioletRed;
				break;
			case 4:
				day4->ForeColor = Color::PaleVioletRed;
				break;
			case 5:
				day5->ForeColor = Color::PaleVioletRed;
				break;
			case 6:
				day6->ForeColor = Color::PaleVioletRed;
				break;
			case 7:
				day7->ForeColor = Color::PaleVioletRed;
				break;
			case 8:
				day8->ForeColor = Color::PaleVioletRed;
				break;
			case 9:
				day9->ForeColor = Color::PaleVioletRed;
				break;
			case 10:
				day10->ForeColor = Color::PaleVioletRed;
				break;
			case 11:
				day11->ForeColor = Color::PaleVioletRed;
				break;
			case 12:
				day12->ForeColor = Color::PaleVioletRed;
				break;
			case 13:
				day13->ForeColor = Color::PaleVioletRed;
				break;
			case 14:
				day14->ForeColor = Color::PaleVioletRed;
				break;
			case 15:
				day15->ForeColor = Color::PaleVioletRed;
				break;
			case 16:
				day16->ForeColor = Color::PaleVioletRed;
				break;
			case 17:
				day17->ForeColor = Color::PaleVioletRed;
				break;
			case 18:
				day18->ForeColor = Color::PaleVioletRed;
				break;
			case 19:
				day19->ForeColor = Color::PaleVioletRed;
				break;
			case 20:
				day20->ForeColor = Color::PaleVioletRed;
				break;
			case 21:
				day21->ForeColor = Color::PaleVioletRed;
				break;
			case 22:
				day22->ForeColor = Color::PaleVioletRed;
				break;
			case 23:
				day23->ForeColor = Color::PaleVioletRed;
				break;
			case 24:
				day24->ForeColor = Color::PaleVioletRed;
				break;
			case 25:
				day25->ForeColor = Color::PaleVioletRed;
				break;
			case 26:
				day26->ForeColor = Color::PaleVioletRed;
				break;
			case 27:
				day27->ForeColor = Color::PaleVioletRed;
				break;
			case 28:
				day28->ForeColor = Color::PaleVioletRed;
				break;
			case 29:
				day29->ForeColor = Color::PaleVioletRed;
				break;
			case 30:
				day30->ForeColor = Color::PaleVioletRed;
				break;
			case 31:
				day31->ForeColor = Color::PaleVioletRed;
				break;
			case 32:
				day32->ForeColor = Color::PaleVioletRed;
				break;
			case 33:
				day33->ForeColor = Color::PaleVioletRed;
				break;
			case 34:
				day34->ForeColor = Color::PaleVioletRed;
				break;
			case 35:
				day35->ForeColor = Color::PaleVioletRed;
				break;
			case 36:
				day36->ForeColor = Color::PaleVioletRed;
				break;
			case 37:
				day37->ForeColor = Color::PaleVioletRed;
				break;
			case 38:
				day38->ForeColor = Color::PaleVioletRed;
				break;
			case 39:
				day39->ForeColor = Color::PaleVioletRed;
				break;
			case 40:
				day40->ForeColor = Color::PaleVioletRed;
				break;
			case 41:
				day41->ForeColor = Color::PaleVioletRed;
				break;
			case 42:
				day42->ForeColor = Color::PaleVioletRed;
				break;
			default:
				break;
			}
		}
		void ChangeDayList(array<int^, 2>^ dayList)
		{
			if (dayList[0, 0]->Equals(-999))
				day1->Text = "";
			else
				day1->Text = dayList[0, 0]->ToString();
			if (dayList[0, 1]->Equals(-999))
				day2->Text = "";
			else
				day2->Text = dayList[0, 1]->ToString();
			if (dayList[0, 2]->Equals(-999))
				day3->Text = "";
			else
				day3->Text = dayList[0, 2]->ToString();
			if (dayList[0, 3]->Equals(-999))
				day4->Text = "";
			else
				day4->Text = dayList[0, 3]->ToString();
			if (dayList[0, 4]->Equals(-999))
				day5->Text = "";
			else
				day5->Text = dayList[0, 4]->ToString();
			if (dayList[0, 5]->Equals(-999))
				day6->Text = "";
			else
				day6->Text = dayList[0, 5]->ToString();
			if (dayList[0, 6]->Equals(-999))
				day7->Text = "";
			else
				day7->Text = dayList[0, 6]->ToString();
			if (dayList[1, 0]->Equals(-999))
				day8->Text = "";
			else
				day8->Text = dayList[1, 0]->ToString();
			if (dayList[1, 1]->Equals(-999))
				day9->Text = "";
			else
				day9->Text = dayList[1, 1]->ToString();
			if (dayList[1, 2]->Equals(-999))
				day10->Text = "";
			else
				day10->Text = dayList[1, 2]->ToString();
			if (dayList[1, 3]->Equals(-999))
				day11->Text = "";
			else
				day11->Text = dayList[1, 3]->ToString();
			if (dayList[1, 4]->Equals(-999))
				day12->Text = "";
			else
				day12->Text = dayList[1, 4]->ToString();
			if (dayList[1, 5]->Equals(-999))
				day13->Text = "";
			else
				day13->Text = dayList[1, 5]->ToString();
			if (dayList[1, 6]->Equals(-999))
				day14->Text = "";
			else
				day14->Text = dayList[1, 6]->ToString();
			if (dayList[2, 0]->Equals(-999))
				day15->Text = "";
			else
				day15->Text = dayList[2, 0]->ToString();
			if (dayList[2, 1]->Equals(-999))
				day16->Text = "";
			else
				day16->Text = dayList[2, 1]->ToString();
			if (dayList[2, 2]->Equals(-999))
				day17->Text = "";
			else
				day17->Text = dayList[2, 2]->ToString();
			if (dayList[2, 3]->Equals(-999))
				day18->Text = "";
			else
				day18->Text = dayList[2, 3]->ToString();
			if (dayList[2, 4]->Equals(-999))
				day19->Text = "";
			else
				day19->Text = dayList[2, 4]->ToString();
			if (dayList[2, 5]->Equals(-999))
				day20->Text = "";
			else
				day20->Text = dayList[2, 5]->ToString();
			if (dayList[2, 6]->Equals(-999))
				day21->Text = "";
			else
				day21->Text = dayList[2, 6]->ToString();
			if (dayList[3, 0]->Equals(-999))
				day22->Text = "";
			else
				day22->Text = dayList[3, 0]->ToString();
			if (dayList[3, 1]->Equals(-999))
				day23->Text = "";
			else
				day23->Text = dayList[3, 1]->ToString();
			if (dayList[3, 2]->Equals(-999))
				day24->Text = "";
			else
				day24->Text = dayList[3, 2]->ToString();
			if (dayList[3, 3]->Equals(-999))
				day25->Text = "";
			else
				day25->Text = dayList[3, 3]->ToString();
			if (dayList[3, 4]->Equals(-999))
				day26->Text = "";
			else
				day26->Text = dayList[3, 4]->ToString();
			if (dayList[3, 5]->Equals(-999))
				day27->Text = "";
			else
				day27->Text = dayList[3, 5]->ToString();
			if (dayList[3, 6]->Equals(-999))
				day28->Text = "";
			else
				day28->Text = dayList[3, 6]->ToString();
			if (dayList[4, 0]->Equals(-999))
				day29->Text = "";
			else
				day29->Text = dayList[4, 0]->ToString();
			if (dayList[4, 1]->Equals(-999))
				day30->Text = "";
			else
				day30->Text = dayList[4, 1]->ToString();
			if (dayList[4, 2]->Equals(-999))
				day31->Text = "";
			else
				day31->Text = dayList[4, 2]->ToString();
			if (dayList[4, 3]->Equals(-999))
				day32->Text = "";
			else
				day32->Text = dayList[4, 3]->ToString();
			if (dayList[4, 4]->Equals(-999))
				day33->Text = "";
			else
				day33->Text = dayList[4, 4]->ToString();
			if (dayList[4, 5]->Equals(-999))
				day34->Text = "";
			else
				day34->Text = dayList[4, 5]->ToString();
			if (dayList[4, 6]->Equals(-999))
				day35->Text = "";
			else
				day35->Text = dayList[4, 6]->ToString();
			if (dayList[5, 0]->Equals(-999))
				day36->Text = "";
			else
				day36->Text = dayList[5, 0]->ToString();
			if (dayList[5, 1]->Equals(-999))
				day37->Text = "";
			else
				day37->Text = dayList[5, 1]->ToString();
			if (dayList[5, 2]->Equals(-999))
				day38->Text = "";
			else
				day38->Text = dayList[5, 2]->ToString();
			if (dayList[5, 3]->Equals(-999))
				day39->Text = "";
			else
				day39->Text = dayList[5, 3]->ToString();
			if (dayList[5, 4]->Equals(-999))
				day40->Text = "";
			else
				day40->Text = dayList[5, 4]->ToString();
			if (dayList[5, 5]->Equals(-999))
				day41->Text = "";
			else
				day41->Text = dayList[5, 5]->ToString();
			if (dayList[5, 6]->Equals(-999))
				day42->Text = "";
			else
				day42->Text = dayList[5, 6]->ToString();
		}
		void ChangePrivDayList(array<int^, 2>^ dayList)
		{
			if (dayList[0, 0]->Equals(-999))
				privday1->Text = "";
			else
				privday1->Text = dayList[0, 0]->ToString();
			if (dayList[1, 0]->Equals(-999))
				privday8->Text = "";
			else
				privday8->Text = dayList[1, 0]->ToString();
			if (dayList[2, 0]->Equals(-999))
				privday15->Text = "";
			else
				privday15->Text = dayList[2, 0]->ToString();
			if (dayList[3, 0]->Equals(-999))
				privday22->Text = "";
			else
				privday22->Text = dayList[3, 0]->ToString();
			if (dayList[4, 0]->Equals(-999))
				privday29->Text = "";
			else
				privday29->Text = dayList[4, 0]->ToString();
			if (dayList[5, 0]->Equals(-999))
				privday36->Text = "";
			else
				privday36->Text = dayList[5, 0]->ToString();
			if (dayList[5, 1]->Equals(-999))
				privday37->Text = "";
			else
				privday37->Text = dayList[5, 1]->ToString();
			if (dayList[5, 2]->Equals(-999))
				privday38->Text = "";
			else
				privday38->Text = dayList[5, 2]->ToString();
			if (dayList[5, 3]->Equals(-999))
				privday39->Text = "";
			else
				privday39->Text = dayList[5, 3]->ToString();
			if (dayList[5, 4]->Equals(-999))
				privday40->Text = "";
			else
				privday40->Text = dayList[5, 4]->ToString();
			if (dayList[5, 5]->Equals(-999))
				privday41->Text = "";
			else
				privday41->Text = dayList[5, 5]->ToString();
			if (dayList[5, 6]->Equals(-999))
				privday42->Text = "";
			else
				privday42->Text = dayList[5, 6]->ToString();
		}
	protected:
		/// <summary>
		/// 사용 중인 모든 리소스를 정리합니다.
		/// </summary>
		~AlarmPage()
		{
			if (components)
			{
				delete components;
			}
			updateAlarm();
		}
	private: System::Windows::Forms::PictureBox^  mainTable;
	protected:
	private: System::Windows::Forms::PictureBox^  backTable;
	private: System::Windows::Forms::ComboBox^  textBox1;

	private: System::Windows::Forms::PictureBox^  popupBox;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::Button^  deleteButton;
	private: System::Windows::Forms::Button^  saveButton;
	private: System::Windows::Forms::Button^  searchButton;
	private: System::Windows::Forms::TextBox^  year;
	private: System::Windows::Forms::TextBox^  month;

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::TextBox^  textBox4;
	private: System::Windows::Forms::TextBox^  textBox5;
	private: System::Windows::Forms::TextBox^  textBox6;
	private: System::Windows::Forms::TextBox^  textBox7;
	private: System::Windows::Forms::TextBox^  textBox8;
	private: System::Windows::Forms::TextBox^  textBox9;
	private: System::Windows::Forms::TextBox^  textBox10;
	private: System::Windows::Forms::TextBox^  day1;
	private: System::Windows::Forms::TextBox^  day2;
	private: System::Windows::Forms::TextBox^  day3;
	private: System::Windows::Forms::TextBox^  day4;
	private: System::Windows::Forms::TextBox^  day5;
	private: System::Windows::Forms::TextBox^  day6;
	private: System::Windows::Forms::TextBox^  day7;
	private: System::Windows::Forms::TextBox^  day8;
	private: System::Windows::Forms::TextBox^  day9;
	private: System::Windows::Forms::TextBox^  day10;
	private: System::Windows::Forms::TextBox^  day11;
	private: System::Windows::Forms::TextBox^  day12;
	private: System::Windows::Forms::TextBox^  day14;
	private: System::Windows::Forms::TextBox^  day15;
	private: System::Windows::Forms::TextBox^  day16;
	private: System::Windows::Forms::TextBox^  day17;
	private: System::Windows::Forms::TextBox^  day18;
	private: System::Windows::Forms::TextBox^  day19;
	private: System::Windows::Forms::TextBox^  day20;
	private: System::Windows::Forms::TextBox^  day21;
	private: System::Windows::Forms::TextBox^  day22;
	private: System::Windows::Forms::TextBox^  day23;
	private: System::Windows::Forms::TextBox^  day24;
	private: System::Windows::Forms::TextBox^  day25;
	private: System::Windows::Forms::TextBox^  day26;
	private: System::Windows::Forms::TextBox^  day27;
	private: System::Windows::Forms::TextBox^  day28;
	private: System::Windows::Forms::TextBox^  day29;
	private: System::Windows::Forms::TextBox^  day30;
	private: System::Windows::Forms::TextBox^  day31;
	private: System::Windows::Forms::TextBox^  day32;
	private: System::Windows::Forms::TextBox^  day33;
	private: System::Windows::Forms::TextBox^  day34;
	private: System::Windows::Forms::TextBox^  day35;


	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::PictureBox^  pictureBox4;
	private: System::Windows::Forms::PictureBox^  pictureBox5;
	private: System::Windows::Forms::PictureBox^  pictureBox6;
	private: System::Windows::Forms::PictureBox^  pictureBox7;
	private: System::Windows::Forms::PictureBox^  pictureBox8;
	private: System::Windows::Forms::TextBox^  textBox46;
	private: System::Windows::Forms::TextBox^  privday1;
	private: System::Windows::Forms::TextBox^  privday8;
	private: System::Windows::Forms::TextBox^  privday15;
	private: System::Windows::Forms::TextBox^  privday22;
	private: System::Windows::Forms::TextBox^  privday29;
	private: System::Windows::Forms::TextBox^  privday37;
	private: System::Windows::Forms::TextBox^  privday38;
	private: System::Windows::Forms::TextBox^  privday39;
	private: System::Windows::Forms::TextBox^  privday40;
	private: System::Windows::Forms::TextBox^  privday41;
	private: System::Windows::Forms::TextBox^  privday42;






	private: System::Windows::Forms::TextBox^  day13;
	private: System::Windows::Forms::TextBox^  privday36;
	private: System::Windows::Forms::TextBox^  day36;
	private: System::Windows::Forms::TextBox^  day37;
	private: System::Windows::Forms::TextBox^  day38;
	private: System::Windows::Forms::TextBox^  day39;
	private: System::Windows::Forms::TextBox^  day40;
	private: System::Windows::Forms::TextBox^  day41;
	private: System::Windows::Forms::TextBox^  day42;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(AlarmPage::typeid));
			this->mainTable = (gcnew System::Windows::Forms::PictureBox());
			this->backTable = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->popupBox = (gcnew System::Windows::Forms::PictureBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->deleteButton = (gcnew System::Windows::Forms::Button());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->searchButton = (gcnew System::Windows::Forms::Button());
			this->year = (gcnew System::Windows::Forms::TextBox());
			this->month = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->day1 = (gcnew System::Windows::Forms::TextBox());
			this->day2 = (gcnew System::Windows::Forms::TextBox());
			this->day3 = (gcnew System::Windows::Forms::TextBox());
			this->day4 = (gcnew System::Windows::Forms::TextBox());
			this->day5 = (gcnew System::Windows::Forms::TextBox());
			this->day6 = (gcnew System::Windows::Forms::TextBox());
			this->day7 = (gcnew System::Windows::Forms::TextBox());
			this->day8 = (gcnew System::Windows::Forms::TextBox());
			this->day9 = (gcnew System::Windows::Forms::TextBox());
			this->day10 = (gcnew System::Windows::Forms::TextBox());
			this->day11 = (gcnew System::Windows::Forms::TextBox());
			this->day12 = (gcnew System::Windows::Forms::TextBox());
			this->day14 = (gcnew System::Windows::Forms::TextBox());
			this->day15 = (gcnew System::Windows::Forms::TextBox());
			this->day16 = (gcnew System::Windows::Forms::TextBox());
			this->day17 = (gcnew System::Windows::Forms::TextBox());
			this->day18 = (gcnew System::Windows::Forms::TextBox());
			this->day19 = (gcnew System::Windows::Forms::TextBox());
			this->day20 = (gcnew System::Windows::Forms::TextBox());
			this->day21 = (gcnew System::Windows::Forms::TextBox());
			this->day22 = (gcnew System::Windows::Forms::TextBox());
			this->day23 = (gcnew System::Windows::Forms::TextBox());
			this->day24 = (gcnew System::Windows::Forms::TextBox());
			this->day25 = (gcnew System::Windows::Forms::TextBox());
			this->day26 = (gcnew System::Windows::Forms::TextBox());
			this->day27 = (gcnew System::Windows::Forms::TextBox());
			this->day28 = (gcnew System::Windows::Forms::TextBox());
			this->day29 = (gcnew System::Windows::Forms::TextBox());
			this->day30 = (gcnew System::Windows::Forms::TextBox());
			this->day31 = (gcnew System::Windows::Forms::TextBox());
			this->day32 = (gcnew System::Windows::Forms::TextBox());
			this->day33 = (gcnew System::Windows::Forms::TextBox());
			this->day34 = (gcnew System::Windows::Forms::TextBox());
			this->day35 = (gcnew System::Windows::Forms::TextBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox6 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox46 = (gcnew System::Windows::Forms::TextBox());
			this->privday1 = (gcnew System::Windows::Forms::TextBox());
			this->privday8 = (gcnew System::Windows::Forms::TextBox());
			this->privday15 = (gcnew System::Windows::Forms::TextBox());
			this->privday22 = (gcnew System::Windows::Forms::TextBox());
			this->privday29 = (gcnew System::Windows::Forms::TextBox());
			this->privday37 = (gcnew System::Windows::Forms::TextBox());
			this->privday38 = (gcnew System::Windows::Forms::TextBox());
			this->privday39 = (gcnew System::Windows::Forms::TextBox());
			this->privday40 = (gcnew System::Windows::Forms::TextBox());
			this->privday41 = (gcnew System::Windows::Forms::TextBox());
			this->privday42 = (gcnew System::Windows::Forms::TextBox());
			this->day13 = (gcnew System::Windows::Forms::TextBox());
			this->privday36 = (gcnew System::Windows::Forms::TextBox());
			this->day36 = (gcnew System::Windows::Forms::TextBox());
			this->day37 = (gcnew System::Windows::Forms::TextBox());
			this->day38 = (gcnew System::Windows::Forms::TextBox());
			this->day39 = (gcnew System::Windows::Forms::TextBox());
			this->day40 = (gcnew System::Windows::Forms::TextBox());
			this->day41 = (gcnew System::Windows::Forms::TextBox());
			this->day42 = (gcnew System::Windows::Forms::TextBox());
			this->tableReset = (gcnew System::Windows::Forms::Timer(this->components));
			this->totalReset = (gcnew System::Windows::Forms::Timer(this->components));
			this->CloseTimer = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainTable))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->backTable))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->popupBox))->BeginInit();
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
			// mainTable
			// 
			this->mainTable->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->mainTable->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"mainTable.Image")));
			this->mainTable->Location = System::Drawing::Point(121, 6);
			this->mainTable->Name = L"mainTable";
			this->mainTable->Size = System::Drawing::Size(773, 553);
			this->mainTable->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->mainTable->TabIndex = 0;
			this->mainTable->TabStop = false;
			// 
			// backTable
			// 
			this->backTable->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"backTable.Image")));
			this->backTable->Location = System::Drawing::Point(26, 116);
			this->backTable->Name = L"backTable";
			this->backTable->Size = System::Drawing::Size(773, 527);
			this->backTable->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->backTable->TabIndex = 1;
			this->backTable->TabStop = false;
			// 
			// textBox1
			// 
			this->textBox1->AutoCompleteMode = System::Windows::Forms::AutoCompleteMode::SuggestAppend;
			this->textBox1->AutoCompleteSource = System::Windows::Forms::AutoCompleteSource::CustomSource;
			this->textBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox1->ForeColor = System::Drawing::Color::White;
			this->textBox1->FormattingEnabled = true;
			this->textBox1->Location = System::Drawing::Point(998, 321);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(195, 33);
			this->textBox1->TabIndex = 76;
			// 
			// popupBox
			// 
			this->popupBox->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"popupBox.Image")));
			this->popupBox->Location = System::Drawing::Point(920, 304);
			this->popupBox->Name = L"popupBox";
			this->popupBox->Size = System::Drawing::Size(352, 205);
			this->popupBox->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->popupBox->TabIndex = 77;
			this->popupBox->TabStop = false;
			// 
			// textBox2
			// 
			this->textBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox2->Font = (gcnew System::Drawing::Font(L"나눔고딕", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox2->ForeColor = System::Drawing::Color::White;
			this->textBox2->Location = System::Drawing::Point(932, 327);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(63, 28);
			this->textBox2->TabIndex = 78;
			this->textBox2->Text = L"지역";
			// 
			// deleteButton
			// 
			this->deleteButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->deleteButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"deleteButton.BackgroundImage")));
			this->deleteButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->deleteButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->deleteButton->Location = System::Drawing::Point(1106, 426);
			this->deleteButton->Name = L"deleteButton";
			this->deleteButton->Size = System::Drawing::Size(134, 60);
			this->deleteButton->TabIndex = 80;
			this->deleteButton->UseVisualStyleBackColor = false;
			this->deleteButton->Click += gcnew System::EventHandler(this, &AlarmPage::deleteButton_Click);
			// 
			// saveButton
			// 
			this->saveButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->saveButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"saveButton.BackgroundImage")));
			this->saveButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->saveButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->saveButton->Location = System::Drawing::Point(945, 426);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(134, 60);
			this->saveButton->TabIndex = 79;
			this->saveButton->UseVisualStyleBackColor = false;
			this->saveButton->Click += gcnew System::EventHandler(this, &AlarmPage::saveButton_Click);
			// 
			// searchButton
			// 
			this->searchButton->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->searchButton->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"searchButton.BackgroundImage")));
			this->searchButton->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->searchButton->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->searchButton->Location = System::Drawing::Point(1199, 320);
			this->searchButton->Name = L"searchButton";
			this->searchButton->Size = System::Drawing::Size(42, 43);
			this->searchButton->TabIndex = 81;
			this->searchButton->UseVisualStyleBackColor = false;
			// 
			// year
			// 
			this->year->BackColor = System::Drawing::Color::Silver;
			this->year->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->year->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->year->Location = System::Drawing::Point(1005, 36);
			this->year->Name = L"year";
			this->year->Size = System::Drawing::Size(190, 46);
			this->year->TabIndex = 82;
			this->year->Text = L"2015년";
			this->year->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// month
			// 
			this->month->BackColor = System::Drawing::Color::Silver;
			this->month->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->month->Font = (gcnew System::Drawing::Font(L"나눔고딕 ExtraBold", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->month->Location = System::Drawing::Point(1038, 119);
			this->month->Name = L"month";
			this->month->Size = System::Drawing::Size(128, 46);
			this->month->TabIndex = 82;
			this->month->Text = L"9월";
			this->month->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(981, 124);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(38, 45);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 83;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &AlarmPage::pictureBox1_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(1172, 124);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(38, 45);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 84;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &AlarmPage::pictureBox2_Click);
			// 
			// textBox4
			// 
			this->textBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox4->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox4->ForeColor = System::Drawing::Color::White;
			this->textBox4->Location = System::Drawing::Point(251, 23);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(80, 55);
			this->textBox4->TabIndex = 85;
			this->textBox4->Text = L"M";
			this->textBox4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox5
			// 
			this->textBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox5->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox5->ForeColor = System::Drawing::Color::White;
			this->textBox5->Location = System::Drawing::Point(359, 23);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(80, 55);
			this->textBox5->TabIndex = 85;
			this->textBox5->Text = L"T";
			this->textBox5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox6
			// 
			this->textBox6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox6->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox6->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox6->ForeColor = System::Drawing::Color::White;
			this->textBox6->Location = System::Drawing::Point(467, 23);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(80, 55);
			this->textBox6->TabIndex = 85;
			this->textBox6->Text = L"W";
			this->textBox6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox7
			// 
			this->textBox7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox7->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox7->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox7->ForeColor = System::Drawing::Color::White;
			this->textBox7->Location = System::Drawing::Point(575, 23);
			this->textBox7->Name = L"textBox7";
			this->textBox7->Size = System::Drawing::Size(80, 55);
			this->textBox7->TabIndex = 85;
			this->textBox7->Text = L"T";
			this->textBox7->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox8
			// 
			this->textBox8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox8->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox8->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox8->ForeColor = System::Drawing::Color::White;
			this->textBox8->Location = System::Drawing::Point(683, 23);
			this->textBox8->Name = L"textBox8";
			this->textBox8->Size = System::Drawing::Size(80, 55);
			this->textBox8->TabIndex = 85;
			this->textBox8->Text = L"F";
			this->textBox8->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox9
			// 
			this->textBox9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox9->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox9->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox9->ForeColor = System::Drawing::Color::White;
			this->textBox9->Location = System::Drawing::Point(791, 23);
			this->textBox9->Name = L"textBox9";
			this->textBox9->Size = System::Drawing::Size(80, 55);
			this->textBox9->TabIndex = 85;
			this->textBox9->Text = L"S";
			this->textBox9->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// textBox10
			// 
			this->textBox10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->textBox10->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox10->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox10->ForeColor = System::Drawing::Color::Red;
			this->textBox10->Location = System::Drawing::Point(143, 23);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(80, 55);
			this->textBox10->TabIndex = 85;
			this->textBox10->Text = L"S";
			this->textBox10->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// day1
			// 
			this->day1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day1->Cursor = System::Windows::Forms::Cursors::Default;
			this->day1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day1->ForeColor = System::Drawing::Color::White;
			this->day1->Location = System::Drawing::Point(143, 96);
			this->day1->Name = L"day1";
			this->day1->Size = System::Drawing::Size(80, 55);
			this->day1->TabIndex = 85;
			this->day1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day1_MouseClick);
			// 
			// day2
			// 
			this->day2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day2->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day2->Cursor = System::Windows::Forms::Cursors::Default;
			this->day2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day2->ForeColor = System::Drawing::Color::White;
			this->day2->Location = System::Drawing::Point(251, 96);
			this->day2->Name = L"day2";
			this->day2->Size = System::Drawing::Size(80, 55);
			this->day2->TabIndex = 85;
			this->day2->Text = L"1";
			this->day2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day2->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day2_MouseClick);
			// 
			// day3
			// 
			this->day3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day3->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day3->Cursor = System::Windows::Forms::Cursors::Default;
			this->day3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day3->ForeColor = System::Drawing::Color::White;
			this->day3->Location = System::Drawing::Point(359, 96);
			this->day3->Name = L"day3";
			this->day3->Size = System::Drawing::Size(80, 55);
			this->day3->TabIndex = 85;
			this->day3->Text = L"2";
			this->day3->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day3->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day3_MouseClick);
			// 
			// day4
			// 
			this->day4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day4->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day4->Cursor = System::Windows::Forms::Cursors::Default;
			this->day4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day4->ForeColor = System::Drawing::Color::White;
			this->day4->Location = System::Drawing::Point(467, 96);
			this->day4->Name = L"day4";
			this->day4->Size = System::Drawing::Size(80, 55);
			this->day4->TabIndex = 85;
			this->day4->Text = L"3";
			this->day4->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day4->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day4_MouseClick);
			// 
			// day5
			// 
			this->day5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day5->Cursor = System::Windows::Forms::Cursors::Default;
			this->day5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day5->ForeColor = System::Drawing::Color::White;
			this->day5->Location = System::Drawing::Point(575, 96);
			this->day5->Name = L"day5";
			this->day5->Size = System::Drawing::Size(80, 55);
			this->day5->TabIndex = 85;
			this->day5->Text = L"4";
			this->day5->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day5->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day5_MouseClick);
			// 
			// day6
			// 
			this->day6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day6->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day6->Cursor = System::Windows::Forms::Cursors::Default;
			this->day6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day6->ForeColor = System::Drawing::Color::White;
			this->day6->Location = System::Drawing::Point(683, 96);
			this->day6->Name = L"day6";
			this->day6->Size = System::Drawing::Size(80, 55);
			this->day6->TabIndex = 85;
			this->day6->Text = L"5";
			this->day6->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day6->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day6_MouseClick);
			// 
			// day7
			// 
			this->day7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day7->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day7->Cursor = System::Windows::Forms::Cursors::Default;
			this->day7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day7->ForeColor = System::Drawing::Color::White;
			this->day7->Location = System::Drawing::Point(791, 96);
			this->day7->Name = L"day7";
			this->day7->Size = System::Drawing::Size(80, 55);
			this->day7->TabIndex = 85;
			this->day7->Text = L"6";
			this->day7->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day7->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day7_MouseClick);
			// 
			// day8
			// 
			this->day8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day8->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day8->Cursor = System::Windows::Forms::Cursors::Default;
			this->day8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day8->ForeColor = System::Drawing::Color::White;
			this->day8->Location = System::Drawing::Point(143, 173);
			this->day8->Name = L"day8";
			this->day8->Size = System::Drawing::Size(80, 55);
			this->day8->TabIndex = 85;
			this->day8->Text = L"7";
			this->day8->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day8->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day8_MouseClick);
			// 
			// day9
			// 
			this->day9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day9->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day9->Cursor = System::Windows::Forms::Cursors::Default;
			this->day9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day9->ForeColor = System::Drawing::Color::White;
			this->day9->Location = System::Drawing::Point(251, 173);
			this->day9->Name = L"day9";
			this->day9->Size = System::Drawing::Size(80, 55);
			this->day9->TabIndex = 85;
			this->day9->Text = L"8";
			this->day9->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day9->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day9_MouseClick);
			// 
			// day10
			// 
			this->day10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day10->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day10->Cursor = System::Windows::Forms::Cursors::Default;
			this->day10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day10->ForeColor = System::Drawing::Color::White;
			this->day10->Location = System::Drawing::Point(359, 173);
			this->day10->Name = L"day10";
			this->day10->Size = System::Drawing::Size(80, 55);
			this->day10->TabIndex = 85;
			this->day10->Text = L"9";
			this->day10->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day10->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day10_MouseClick);
			// 
			// day11
			// 
			this->day11->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day11->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day11->Cursor = System::Windows::Forms::Cursors::Default;
			this->day11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day11->ForeColor = System::Drawing::Color::White;
			this->day11->Location = System::Drawing::Point(467, 173);
			this->day11->Name = L"day11";
			this->day11->Size = System::Drawing::Size(80, 55);
			this->day11->TabIndex = 85;
			this->day11->Text = L"10";
			this->day11->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day11->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day11_MouseClick);
			// 
			// day12
			// 
			this->day12->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day12->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day12->Cursor = System::Windows::Forms::Cursors::Default;
			this->day12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day12->ForeColor = System::Drawing::Color::White;
			this->day12->Location = System::Drawing::Point(575, 173);
			this->day12->Name = L"day12";
			this->day12->Size = System::Drawing::Size(80, 55);
			this->day12->TabIndex = 85;
			this->day12->Text = L"11";
			this->day12->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day12->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day12_MouseClick);
			// 
			// day14
			// 
			this->day14->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day14->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day14->Cursor = System::Windows::Forms::Cursors::Default;
			this->day14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day14->ForeColor = System::Drawing::Color::White;
			this->day14->Location = System::Drawing::Point(791, 173);
			this->day14->Name = L"day14";
			this->day14->Size = System::Drawing::Size(80, 55);
			this->day14->TabIndex = 85;
			this->day14->Text = L"13";
			this->day14->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day14->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day14_MouseClick);
			// 
			// day15
			// 
			this->day15->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day15->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day15->Cursor = System::Windows::Forms::Cursors::Default;
			this->day15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day15->ForeColor = System::Drawing::Color::White;
			this->day15->Location = System::Drawing::Point(143, 250);
			this->day15->Name = L"day15";
			this->day15->Size = System::Drawing::Size(80, 55);
			this->day15->TabIndex = 85;
			this->day15->Text = L"14";
			this->day15->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day15->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day15_MouseClick);
			// 
			// day16
			// 
			this->day16->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day16->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day16->Cursor = System::Windows::Forms::Cursors::Default;
			this->day16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day16->ForeColor = System::Drawing::Color::White;
			this->day16->Location = System::Drawing::Point(251, 250);
			this->day16->Name = L"day16";
			this->day16->Size = System::Drawing::Size(80, 55);
			this->day16->TabIndex = 85;
			this->day16->Text = L"15";
			this->day16->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day16->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day16_MouseClick);
			// 
			// day17
			// 
			this->day17->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day17->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day17->Cursor = System::Windows::Forms::Cursors::Default;
			this->day17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day17->ForeColor = System::Drawing::Color::White;
			this->day17->Location = System::Drawing::Point(359, 250);
			this->day17->Name = L"day17";
			this->day17->Size = System::Drawing::Size(80, 55);
			this->day17->TabIndex = 85;
			this->day17->Text = L"16";
			this->day17->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day17->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day17_MouseClick);
			// 
			// day18
			// 
			this->day18->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day18->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day18->Cursor = System::Windows::Forms::Cursors::Default;
			this->day18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day18->ForeColor = System::Drawing::Color::White;
			this->day18->Location = System::Drawing::Point(467, 250);
			this->day18->Name = L"day18";
			this->day18->Size = System::Drawing::Size(80, 55);
			this->day18->TabIndex = 85;
			this->day18->Text = L"17";
			this->day18->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day18->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day18_MouseClick);
			// 
			// day19
			// 
			this->day19->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day19->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day19->Cursor = System::Windows::Forms::Cursors::Default;
			this->day19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day19->ForeColor = System::Drawing::Color::White;
			this->day19->Location = System::Drawing::Point(575, 250);
			this->day19->Name = L"day19";
			this->day19->Size = System::Drawing::Size(80, 55);
			this->day19->TabIndex = 85;
			this->day19->Text = L"18";
			this->day19->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day19->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day19_MouseClick);
			// 
			// day20
			// 
			this->day20->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day20->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day20->Cursor = System::Windows::Forms::Cursors::Default;
			this->day20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day20->ForeColor = System::Drawing::Color::White;
			this->day20->Location = System::Drawing::Point(683, 250);
			this->day20->Name = L"day20";
			this->day20->Size = System::Drawing::Size(80, 55);
			this->day20->TabIndex = 85;
			this->day20->Text = L"19";
			this->day20->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day20->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day20_MouseClick);
			// 
			// day21
			// 
			this->day21->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day21->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day21->Cursor = System::Windows::Forms::Cursors::Default;
			this->day21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day21->ForeColor = System::Drawing::Color::White;
			this->day21->Location = System::Drawing::Point(791, 250);
			this->day21->Name = L"day21";
			this->day21->Size = System::Drawing::Size(80, 55);
			this->day21->TabIndex = 85;
			this->day21->Text = L"20";
			this->day21->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day21->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day21_MouseClick);
			// 
			// day22
			// 
			this->day22->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day22->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day22->Cursor = System::Windows::Forms::Cursors::Default;
			this->day22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day22->ForeColor = System::Drawing::Color::White;
			this->day22->Location = System::Drawing::Point(143, 327);
			this->day22->Name = L"day22";
			this->day22->Size = System::Drawing::Size(80, 55);
			this->day22->TabIndex = 85;
			this->day22->Text = L"21";
			this->day22->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day22->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day22_MouseClick);
			// 
			// day23
			// 
			this->day23->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day23->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day23->Cursor = System::Windows::Forms::Cursors::Default;
			this->day23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day23->ForeColor = System::Drawing::Color::White;
			this->day23->Location = System::Drawing::Point(251, 327);
			this->day23->Name = L"day23";
			this->day23->Size = System::Drawing::Size(80, 55);
			this->day23->TabIndex = 85;
			this->day23->Text = L"22";
			this->day23->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day23->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day23_MouseClick);
			// 
			// day24
			// 
			this->day24->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day24->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day24->Cursor = System::Windows::Forms::Cursors::Default;
			this->day24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day24->ForeColor = System::Drawing::Color::White;
			this->day24->Location = System::Drawing::Point(359, 327);
			this->day24->Name = L"day24";
			this->day24->Size = System::Drawing::Size(80, 55);
			this->day24->TabIndex = 85;
			this->day24->Text = L"23";
			this->day24->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day24->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day24_MouseClick);
			// 
			// day25
			// 
			this->day25->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day25->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day25->Cursor = System::Windows::Forms::Cursors::Default;
			this->day25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day25->ForeColor = System::Drawing::Color::White;
			this->day25->Location = System::Drawing::Point(467, 327);
			this->day25->Name = L"day25";
			this->day25->Size = System::Drawing::Size(80, 55);
			this->day25->TabIndex = 85;
			this->day25->Text = L"24";
			this->day25->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day25->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day25_MouseClick);
			// 
			// day26
			// 
			this->day26->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day26->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day26->Cursor = System::Windows::Forms::Cursors::Default;
			this->day26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day26->ForeColor = System::Drawing::Color::White;
			this->day26->Location = System::Drawing::Point(575, 327);
			this->day26->Name = L"day26";
			this->day26->Size = System::Drawing::Size(80, 55);
			this->day26->TabIndex = 85;
			this->day26->Text = L"25";
			this->day26->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day26->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day26_MouseClick);
			// 
			// day27
			// 
			this->day27->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day27->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day27->Cursor = System::Windows::Forms::Cursors::Default;
			this->day27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day27->ForeColor = System::Drawing::Color::White;
			this->day27->Location = System::Drawing::Point(683, 327);
			this->day27->Name = L"day27";
			this->day27->Size = System::Drawing::Size(80, 55);
			this->day27->TabIndex = 85;
			this->day27->Text = L"26";
			this->day27->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day27->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day27_MouseClick);
			// 
			// day28
			// 
			this->day28->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day28->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day28->Cursor = System::Windows::Forms::Cursors::Default;
			this->day28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day28->ForeColor = System::Drawing::Color::White;
			this->day28->Location = System::Drawing::Point(791, 327);
			this->day28->Name = L"day28";
			this->day28->Size = System::Drawing::Size(80, 55);
			this->day28->TabIndex = 85;
			this->day28->Text = L"27";
			this->day28->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day28->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day28_MouseClick);
			// 
			// day29
			// 
			this->day29->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day29->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day29->Cursor = System::Windows::Forms::Cursors::Default;
			this->day29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day29->ForeColor = System::Drawing::Color::White;
			this->day29->Location = System::Drawing::Point(143, 404);
			this->day29->Name = L"day29";
			this->day29->Size = System::Drawing::Size(80, 55);
			this->day29->TabIndex = 85;
			this->day29->Text = L"28";
			this->day29->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day29->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day29_MouseClick);
			// 
			// day30
			// 
			this->day30->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day30->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day30->Cursor = System::Windows::Forms::Cursors::Default;
			this->day30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day30->ForeColor = System::Drawing::Color::White;
			this->day30->Location = System::Drawing::Point(251, 404);
			this->day30->Name = L"day30";
			this->day30->Size = System::Drawing::Size(80, 55);
			this->day30->TabIndex = 85;
			this->day30->Text = L"29";
			this->day30->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day30->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day30_MouseClick);
			// 
			// day31
			// 
			this->day31->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day31->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day31->Cursor = System::Windows::Forms::Cursors::Default;
			this->day31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day31->ForeColor = System::Drawing::Color::White;
			this->day31->Location = System::Drawing::Point(359, 404);
			this->day31->Name = L"day31";
			this->day31->Size = System::Drawing::Size(80, 55);
			this->day31->TabIndex = 85;
			this->day31->Text = L"30";
			this->day31->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day31->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day31_MouseClick);
			// 
			// day32
			// 
			this->day32->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day32->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day32->Cursor = System::Windows::Forms::Cursors::Default;
			this->day32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day32->ForeColor = System::Drawing::Color::White;
			this->day32->Location = System::Drawing::Point(467, 404);
			this->day32->Name = L"day32";
			this->day32->Size = System::Drawing::Size(80, 55);
			this->day32->TabIndex = 85;
			this->day32->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day32->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day32_MouseClick);
			// 
			// day33
			// 
			this->day33->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day33->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day33->Cursor = System::Windows::Forms::Cursors::Default;
			this->day33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day33->ForeColor = System::Drawing::Color::White;
			this->day33->Location = System::Drawing::Point(575, 404);
			this->day33->Name = L"day33";
			this->day33->Size = System::Drawing::Size(80, 55);
			this->day33->TabIndex = 85;
			this->day33->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day33->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day33_MouseClick);
			// 
			// day34
			// 
			this->day34->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day34->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day34->Cursor = System::Windows::Forms::Cursors::Default;
			this->day34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day34->ForeColor = System::Drawing::Color::White;
			this->day34->Location = System::Drawing::Point(683, 404);
			this->day34->Name = L"day34";
			this->day34->Size = System::Drawing::Size(80, 55);
			this->day34->TabIndex = 85;
			this->day34->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day34->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day34_MouseClick);
			// 
			// day35
			// 
			this->day35->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day35->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day35->Cursor = System::Windows::Forms::Cursors::Default;
			this->day35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day35->ForeColor = System::Drawing::Color::White;
			this->day35->Location = System::Drawing::Point(791, 404);
			this->day35->Name = L"day35";
			this->day35->Size = System::Drawing::Size(80, 55);
			this->day35->TabIndex = 85;
			this->day35->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day35->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day35_MouseClick);
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::White;
			this->pictureBox3->Location = System::Drawing::Point(235, 11);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(5, 540);
			this->pictureBox3->TabIndex = 86;
			this->pictureBox3->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->BackColor = System::Drawing::Color::White;
			this->pictureBox4->Location = System::Drawing::Point(343, 11);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(5, 540);
			this->pictureBox4->TabIndex = 86;
			this->pictureBox4->TabStop = false;
			// 
			// pictureBox5
			// 
			this->pictureBox5->BackColor = System::Drawing::Color::White;
			this->pictureBox5->Location = System::Drawing::Point(449, 11);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(5, 540);
			this->pictureBox5->TabIndex = 86;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox6
			// 
			this->pictureBox6->BackColor = System::Drawing::Color::White;
			this->pictureBox6->Location = System::Drawing::Point(558, 11);
			this->pictureBox6->Name = L"pictureBox6";
			this->pictureBox6->Size = System::Drawing::Size(5, 540);
			this->pictureBox6->TabIndex = 86;
			this->pictureBox6->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->BackColor = System::Drawing::Color::White;
			this->pictureBox7->Location = System::Drawing::Point(666, 11);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(5, 540);
			this->pictureBox7->TabIndex = 86;
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox8
			// 
			this->pictureBox8->BackColor = System::Drawing::Color::White;
			this->pictureBox8->Location = System::Drawing::Point(775, 11);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(5, 540);
			this->pictureBox8->TabIndex = 86;
			this->pictureBox8->TabStop = false;
			// 
			// textBox46
			// 
			this->textBox46->BackColor = System::Drawing::Color::WhiteSmoke;
			this->textBox46->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox46->Cursor = System::Windows::Forms::Cursors::Default;
			this->textBox46->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->textBox46->ForeColor = System::Drawing::Color::Red;
			this->textBox46->Location = System::Drawing::Point(35, 119);
			this->textBox46->Name = L"textBox46";
			this->textBox46->Size = System::Drawing::Size(80, 55);
			this->textBox46->TabIndex = 85;
			this->textBox46->Text = L"S";
			this->textBox46->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday1
			// 
			this->privday1->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday1->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday1->ForeColor = System::Drawing::Color::Black;
			this->privday1->Location = System::Drawing::Point(35, 185);
			this->privday1->Name = L"privday1";
			this->privday1->Size = System::Drawing::Size(80, 55);
			this->privday1->TabIndex = 85;
			this->privday1->Text = L"10";
			this->privday1->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday8
			// 
			this->privday8->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday8->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday8->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday8->ForeColor = System::Drawing::Color::Black;
			this->privday8->Location = System::Drawing::Point(35, 261);
			this->privday8->Name = L"privday8";
			this->privday8->Size = System::Drawing::Size(80, 55);
			this->privday8->TabIndex = 85;
			this->privday8->Text = L"7";
			this->privday8->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday15
			// 
			this->privday15->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday15->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday15->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday15->ForeColor = System::Drawing::Color::Black;
			this->privday15->Location = System::Drawing::Point(35, 337);
			this->privday15->Name = L"privday15";
			this->privday15->Size = System::Drawing::Size(80, 55);
			this->privday15->TabIndex = 85;
			this->privday15->Text = L"14";
			this->privday15->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday22
			// 
			this->privday22->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday22->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday22->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday22->ForeColor = System::Drawing::Color::Black;
			this->privday22->Location = System::Drawing::Point(35, 413);
			this->privday22->Name = L"privday22";
			this->privday22->Size = System::Drawing::Size(80, 55);
			this->privday22->TabIndex = 85;
			this->privday22->Text = L"21";
			this->privday22->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday29
			// 
			this->privday29->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday29->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday29->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday29->ForeColor = System::Drawing::Color::Black;
			this->privday29->Location = System::Drawing::Point(35, 489);
			this->privday29->Name = L"privday29";
			this->privday29->Size = System::Drawing::Size(80, 55);
			this->privday29->TabIndex = 85;
			this->privday29->Text = L"28";
			this->privday29->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday37
			// 
			this->privday37->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday37->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday37->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday37->ForeColor = System::Drawing::Color::Black;
			this->privday37->Location = System::Drawing::Point(143, 567);
			this->privday37->Name = L"privday37";
			this->privday37->Size = System::Drawing::Size(80, 55);
			this->privday37->TabIndex = 85;
			this->privday37->Text = L"29";
			this->privday37->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday38
			// 
			this->privday38->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday38->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday38->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday38->ForeColor = System::Drawing::Color::Black;
			this->privday38->Location = System::Drawing::Point(251, 567);
			this->privday38->Name = L"privday38";
			this->privday38->Size = System::Drawing::Size(80, 55);
			this->privday38->TabIndex = 85;
			this->privday38->Text = L"30";
			this->privday38->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday39
			// 
			this->privday39->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday39->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday39->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday39->ForeColor = System::Drawing::Color::Black;
			this->privday39->Location = System::Drawing::Point(359, 567);
			this->privday39->Name = L"privday39";
			this->privday39->Size = System::Drawing::Size(80, 55);
			this->privday39->TabIndex = 85;
			this->privday39->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday40
			// 
			this->privday40->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday40->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday40->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday40->ForeColor = System::Drawing::Color::Black;
			this->privday40->Location = System::Drawing::Point(467, 567);
			this->privday40->Name = L"privday40";
			this->privday40->Size = System::Drawing::Size(80, 55);
			this->privday40->TabIndex = 85;
			this->privday40->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday41
			// 
			this->privday41->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday41->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday41->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday41->ForeColor = System::Drawing::Color::Black;
			this->privday41->Location = System::Drawing::Point(575, 567);
			this->privday41->Name = L"privday41";
			this->privday41->Size = System::Drawing::Size(80, 55);
			this->privday41->TabIndex = 85;
			this->privday41->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// privday42
			// 
			this->privday42->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday42->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday42->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday42->ForeColor = System::Drawing::Color::Black;
			this->privday42->Location = System::Drawing::Point(683, 567);
			this->privday42->Name = L"privday42";
			this->privday42->Size = System::Drawing::Size(80, 55);
			this->privday42->TabIndex = 85;
			this->privday42->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// day13
			// 
			this->day13->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day13->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day13->Cursor = System::Windows::Forms::Cursors::Default;
			this->day13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day13->ForeColor = System::Drawing::Color::White;
			this->day13->Location = System::Drawing::Point(683, 173);
			this->day13->Name = L"day13";
			this->day13->Size = System::Drawing::Size(80, 55);
			this->day13->TabIndex = 85;
			this->day13->Text = L"12";
			this->day13->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day13->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day13_MouseClick);
			// 
			// privday36
			// 
			this->privday36->BackColor = System::Drawing::Color::WhiteSmoke;
			this->privday36->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->privday36->Cursor = System::Windows::Forms::Cursors::Default;
			this->privday36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->privday36->ForeColor = System::Drawing::Color::Black;
			this->privday36->Location = System::Drawing::Point(35, 567);
			this->privday36->Name = L"privday36";
			this->privday36->Size = System::Drawing::Size(80, 55);
			this->privday36->TabIndex = 85;
			this->privday36->Text = L"10";
			this->privday36->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// day36
			// 
			this->day36->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day36->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day36->Cursor = System::Windows::Forms::Cursors::Default;
			this->day36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day36->ForeColor = System::Drawing::Color::White;
			this->day36->Location = System::Drawing::Point(143, 481);
			this->day36->Name = L"day36";
			this->day36->Size = System::Drawing::Size(80, 55);
			this->day36->TabIndex = 85;
			this->day36->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day36->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day36_MouseClick);
			// 
			// day37
			// 
			this->day37->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day37->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day37->Cursor = System::Windows::Forms::Cursors::Default;
			this->day37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day37->ForeColor = System::Drawing::Color::White;
			this->day37->Location = System::Drawing::Point(251, 481);
			this->day37->Name = L"day37";
			this->day37->Size = System::Drawing::Size(80, 55);
			this->day37->TabIndex = 85;
			this->day37->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day37->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day37_MouseClick);
			// 
			// day38
			// 
			this->day38->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day38->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day38->Cursor = System::Windows::Forms::Cursors::Default;
			this->day38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day38->ForeColor = System::Drawing::Color::White;
			this->day38->Location = System::Drawing::Point(359, 481);
			this->day38->Name = L"day38";
			this->day38->Size = System::Drawing::Size(80, 55);
			this->day38->TabIndex = 85;
			this->day38->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day38->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day38_MouseClick);
			// 
			// day39
			// 
			this->day39->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day39->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day39->Cursor = System::Windows::Forms::Cursors::Default;
			this->day39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day39->ForeColor = System::Drawing::Color::White;
			this->day39->Location = System::Drawing::Point(467, 481);
			this->day39->Name = L"day39";
			this->day39->Size = System::Drawing::Size(80, 55);
			this->day39->TabIndex = 85;
			this->day39->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day39->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day39_MouseClick);
			// 
			// day40
			// 
			this->day40->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day40->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day40->Cursor = System::Windows::Forms::Cursors::Default;
			this->day40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day40->ForeColor = System::Drawing::Color::White;
			this->day40->Location = System::Drawing::Point(575, 481);
			this->day40->Name = L"day40";
			this->day40->Size = System::Drawing::Size(80, 55);
			this->day40->TabIndex = 85;
			this->day40->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day40->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day40_MouseClick);
			// 
			// day41
			// 
			this->day41->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day41->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day41->Cursor = System::Windows::Forms::Cursors::Default;
			this->day41->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day41->ForeColor = System::Drawing::Color::White;
			this->day41->Location = System::Drawing::Point(683, 481);
			this->day41->Name = L"day41";
			this->day41->Size = System::Drawing::Size(80, 55);
			this->day41->TabIndex = 85;
			this->day41->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day41->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day41_MouseClick);
			// 
			// day42
			// 
			this->day42->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)));
			this->day42->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->day42->Cursor = System::Windows::Forms::Cursors::Default;
			this->day42->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 36, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(129)));
			this->day42->ForeColor = System::Drawing::Color::White;
			this->day42->Location = System::Drawing::Point(791, 481);
			this->day42->Name = L"day42";
			this->day42->Size = System::Drawing::Size(80, 55);
			this->day42->TabIndex = 85;
			this->day42->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->day42->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::day42_MouseClick);
			// 
			// tableReset
			// 
			this->tableReset->Tick += gcnew System::EventHandler(this, &AlarmPage::tableReset_Tick);
			// 
			// totalReset
			// 
			this->totalReset->Interval = 10000;
			this->totalReset->Tick += gcnew System::EventHandler(this, &AlarmPage::totalReset_Tick);
			// 
			// CloseTimer
			// 
			this->CloseTimer->Enabled = true;
			this->CloseTimer->Interval = 1000;
			this->CloseTimer->Tick += gcnew System::EventHandler(this, &AlarmPage::CloseTimer_Tick);
			// 
			// AlarmPage
			// 
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::Silver;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->ClientSize = System::Drawing::Size(1395, 649);
			this->Controls->Add(this->pictureBox8);
			this->Controls->Add(this->pictureBox7);
			this->Controls->Add(this->pictureBox6);
			this->Controls->Add(this->pictureBox5);
			this->Controls->Add(this->pictureBox4);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->privday42);
			this->Controls->Add(this->day35);
			this->Controls->Add(this->privday41);
			this->Controls->Add(this->day34);
			this->Controls->Add(this->day28);
			this->Controls->Add(this->day27);
			this->Controls->Add(this->day21);
			this->Controls->Add(this->day20);
			this->Controls->Add(this->day13);
			this->Controls->Add(this->day14);
			this->Controls->Add(this->privday40);
			this->Controls->Add(this->day33);
			this->Controls->Add(this->day26);
			this->Controls->Add(this->day42);
			this->Controls->Add(this->day7);
			this->Controls->Add(this->day41);
			this->Controls->Add(this->day19);
			this->Controls->Add(this->day6);
			this->Controls->Add(this->privday39);
			this->Controls->Add(this->day32);
			this->Controls->Add(this->day12);
			this->Controls->Add(this->day25);
			this->Controls->Add(this->textBox10);
			this->Controls->Add(this->day40);
			this->Controls->Add(this->day18);
			this->Controls->Add(this->day5);
			this->Controls->Add(this->privday38);
			this->Controls->Add(this->day31);
			this->Controls->Add(this->day11);
			this->Controls->Add(this->day24);
			this->Controls->Add(this->textBox9);
			this->Controls->Add(this->day39);
			this->Controls->Add(this->day17);
			this->Controls->Add(this->day4);
			this->Controls->Add(this->privday37);
			this->Controls->Add(this->day30);
			this->Controls->Add(this->day10);
			this->Controls->Add(this->day23);
			this->Controls->Add(this->textBox8);
			this->Controls->Add(this->day38);
			this->Controls->Add(this->day16);
			this->Controls->Add(this->day3);
			this->Controls->Add(this->privday29);
			this->Controls->Add(this->day29);
			this->Controls->Add(this->privday22);
			this->Controls->Add(this->day9);
			this->Controls->Add(this->day22);
			this->Controls->Add(this->privday15);
			this->Controls->Add(this->textBox7);
			this->Controls->Add(this->day15);
			this->Controls->Add(this->day37);
			this->Controls->Add(this->privday8);
			this->Controls->Add(this->day2);
			this->Controls->Add(this->day8);
			this->Controls->Add(this->privday36);
			this->Controls->Add(this->privday1);
			this->Controls->Add(this->day36);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->day1);
			this->Controls->Add(this->textBox46);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->month);
			this->Controls->Add(this->year);
			this->Controls->Add(this->searchButton);
			this->Controls->Add(this->deleteButton);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->mainTable);
			this->Controls->Add(this->backTable);
			this->Controls->Add(this->popupBox);
			this->Cursor = System::Windows::Forms::Cursors::Default;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"AlarmPage";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"AlarmPage";
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &AlarmPage::AlarmPage_MouseDown);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->mainTable))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->backTable))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->popupBox))->EndInit();
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
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
		monthVal--;

		if (monthVal < 1)
		{
			yearVal = yearVal - 1;
			monthVal = monthVal + 12;
		}

		year->Text = yearVal.ToString() + "년";
		month->Text = monthVal.ToString() + "월";

		int lastMonth = monthVal - 1;
		int lastYear = yearVal - 1;

		if (lastMonth < 1) // 지난 달
		{
			if (lastMonth == 0)
			{
				insertDate(yearVal - 1, 12, privDayList);
			}
			else
			{
				insertDate(yearVal - 1, (lastMonth + 12) % 12, privDayList);
			}
		}
		else
		{
			insertDate(yearVal, lastMonth, privDayList);

		}

		if (monthVal < 1) // 이번 달
		{
			insertDate(yearVal - 1, monthVal + 12, dayList);
		}
		else
		{
			insertDate(yearVal, monthVal, dayList);
		}

		ChangeDayList(dayList); // 현재달값
		ChangePrivDayList(privDayList); // 이전달값
		ChangeDayColor(-999);
		selectCityName();
	}
	private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
		monthVal++;

		int lastMonth = monthVal - 1;
		int lastYear = yearVal - 1;


		if (lastMonth > 12) // 지난 달
		{
			insertDate(yearVal + 1, lastMonth - 12, privDayList);
		}
		else
		{
			insertDate(yearVal, lastMonth, privDayList);
		}

		if (monthVal > 12) // 이번 달
		{
			insertDate(yearVal + 1, monthVal - 12, dayList);

		}
		else
		{
			insertDate(yearVal, monthVal, dayList);
		}

		if (monthVal > 12)
		{
			yearVal = yearVal + 1;
			monthVal = monthVal - 12;
		}

		year->Text = yearVal.ToString() + "년";
		month->Text = monthVal.ToString() + "월";

		ChangeDayList(dayList); // 현재달값
		ChangePrivDayList(privDayList); // 이전달값
		ChangeDayColor(-999);
		selectCityName();
	}
	private: System::Void day1_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day1->Text != "")
			selectDay = Convert::ToInt32(day1->Text);
		else
			selectDay = -999;

		if (tmpCityName[1] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day1->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[1];
	}

	private: System::Void day2_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day2->Text != "")
			selectDay = Convert::ToInt32(day2->Text);
		else
			selectDay = -999;

		if (tmpCityName[2] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day2->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[2];
	}

	private: System::Void day3_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day3->Text != "")
			selectDay = Convert::ToInt32(day3->Text);
		else
			selectDay = -999;

		if (tmpCityName[3] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day3->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[3];
	}

	private: System::Void day4_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day4->Text != "")
			selectDay = Convert::ToInt32(day4->Text);
		else
			selectDay = -999;

		if (tmpCityName[4] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day4->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[4];
	}

	private: System::Void day5_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day5->Text != "")
			selectDay = Convert::ToInt32(day5->Text);
		else
			selectDay = -999;

		if (tmpCityName[5] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day5->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[5];
	}

	private: System::Void day6_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day6->Text != "")
			selectDay = Convert::ToInt32(day6->Text);
		else
			selectDay = -999;

		if (tmpCityName[6] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day6->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[6];
	}

	private: System::Void day7_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day7->Text != "")
			selectDay = Convert::ToInt32(day7->Text);
		else
			selectDay = -999;

		if (tmpCityName[7] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day7->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[7];
	}

	private: System::Void day8_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day8->Text != "")
			selectDay = Convert::ToInt32(day8->Text);
		else
			selectDay = -999;

		if (tmpCityName[8] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day8->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[8];
	}

	private: System::Void day9_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day9->Text != "")
			selectDay = Convert::ToInt32(day9->Text);
		else
			selectDay = -999;

		if (tmpCityName[9] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day9->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[9];
	}

	private: System::Void day10_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day10->Text != "")
			selectDay = Convert::ToInt32(day10->Text);
		else
			selectDay = -999;

		if (tmpCityName[10] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day10->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[10];
	}

	private: System::Void day11_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day11->Text != "")
			selectDay = Convert::ToInt32(day11->Text);
		else
			selectDay = -999;

		if (tmpCityName[11] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day11->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[11];
	}

	private: System::Void day12_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day12->Text != "")
			selectDay = Convert::ToInt32(day12->Text);
		else
			selectDay = -999;
		if (tmpCityName[12] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day12->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[12];
	}

	private: System::Void day13_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day13->Text != "")
			selectDay = Convert::ToInt32(day13->Text);
		else
			selectDay = -999;

		if (tmpCityName[13] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day13->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[13];
	}

	private: System::Void day14_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = " ";
		if (day14->Text != "")
			selectDay = Convert::ToInt32(day14->Text);
		else
			selectDay = -999;

		if (tmpCityName[14] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day14->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[14];
	}

	private: System::Void day15_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = " ";
		if (day15->Text != "")
			selectDay = Convert::ToInt32(day15->Text);
		else
			selectDay = -999;

		if (tmpCityName[15] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day15->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[15];
	}

	private: System::Void day16_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day16->Text != "")
			selectDay = Convert::ToInt32(day16->Text);
		else
			selectDay = -999;

		if (tmpCityName[16] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day16->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[16];
	}

	private: System::Void day17_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day17->Text != "")
			selectDay = Convert::ToInt32(day17->Text);
		else
			selectDay = -999;

		if (tmpCityName[17] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day17->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[17];
	}

	private: System::Void day18_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day18->Text != "")
			selectDay = Convert::ToInt32(day18->Text);
		else
			selectDay = -999;

		if (tmpCityName[18] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day18->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[18];
	}

	private: System::Void day19_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day19->Text != "")
			selectDay = Convert::ToInt32(day19->Text);
		else
			selectDay = -999;

		if (tmpCityName[19] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day19->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[19];
	}


	private: System::Void day20_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day20->Text != "")
			selectDay = Convert::ToInt32(day20->Text);
		else
			selectDay = -999;

		if (tmpCityName[20] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day20->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[20];
	}

	private: System::Void day21_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day21->Text != "")
			selectDay = Convert::ToInt32(day21->Text);
		else
			selectDay = -999;

		if (tmpCityName[21] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day21->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[21];
	}

	private: System::Void day22_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day22->Text != "")
			selectDay = Convert::ToInt32(day22->Text);
		else
			selectDay = -999;

		if (tmpCityName[22] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day22->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[22];
	}

	private: System::Void day23_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day23->Text != "")
			selectDay = Convert::ToInt32(day23->Text);
		else
			selectDay = -999;

		if (tmpCityName[23] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day23->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[23];
	}

	private: System::Void day24_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day24->Text != "")
			selectDay = Convert::ToInt32(day24->Text);
		else
			selectDay = -999;

		if (tmpCityName[24] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day24->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[24];
	}

	private: System::Void day25_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day25->Text != "")
			selectDay = Convert::ToInt32(day25->Text);
		else
			selectDay = -999;

		if (tmpCityName[25] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day25->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[25];
	}

	private: System::Void day26_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day26->Text != "")
			selectDay = Convert::ToInt32(day26->Text);
		else
			selectDay = -999;

		if (tmpCityName[26] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day26->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[26];
	}

	private: System::Void day27_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day27->Text != "")
			selectDay = Convert::ToInt32(day27->Text);
		else
			selectDay = -999;

		if (tmpCityName[27] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day27->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[27];
	}

	private: System::Void day28_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day28->Text != "")
			selectDay = Convert::ToInt32(day28->Text);
		else
			selectDay = -999;

		if (tmpCityName[28] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day28->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[28];
	}

	private: System::Void day29_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day29->Text != "")
			selectDay = Convert::ToInt32(day29->Text);
		else
			selectDay = -999;

		if (tmpCityName[29] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day29->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[29];
	}

	private: System::Void day30_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day30->Text != "")
			selectDay = Convert::ToInt32(day30->Text);
		else
			selectDay = -999;

		if (tmpCityName[30] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day30->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[30];
	}

	private: System::Void day31_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day31->Text != "")
			selectDay = Convert::ToInt32(day31->Text);
		else
			selectDay = -999;

		if (tmpCityName[31] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day31->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[31];
	}

	private: System::Void day32_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day32->Text != "")
			selectDay = Convert::ToInt32(day32->Text);
		else
			selectDay = -999;

		if (tmpCityName[32] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day32->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[32];
	}

	private: System::Void day33_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day33->Text != "")
			selectDay = Convert::ToInt32(day33->Text);
		else
			selectDay = -999;

		if (tmpCityName[33] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day33->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[33];
	}

	private: System::Void day34_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day34->Text != "")
			selectDay = Convert::ToInt32(day34->Text);
		else
			selectDay = -999;

		if (tmpCityName[34] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day34->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[34];
	}

	private: System::Void day35_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day35->Text != "")
			selectDay = Convert::ToInt32(day35->Text);
		else
			selectDay = -999;

		if (tmpCityName[35] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day35->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[35];
	}

	private: System::Void day36_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day36->Text != "")
			selectDay = Convert::ToInt32(day36->Text);
		else
			selectDay = -999;

		if (tmpCityName[36] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day36->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[36];
	}

	private: System::Void day37_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day37->Text != "")
			selectDay = Convert::ToInt32(day37->Text);
		else
			selectDay = -999;

		if (tmpCityName[37] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day37->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[37];
	}

	private: System::Void day38_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day38->Text != "")
			selectDay = Convert::ToInt32(day38->Text);
		else
			selectDay = -999;

		if (tmpCityName[38] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day38->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[38];
	}

	private: System::Void day39_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day39->Text != "")
			selectDay = Convert::ToInt32(day39->Text);
		else
			selectDay = -999;

		if (tmpCityName[39] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day39->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[39];
	}

	private: System::Void day40_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day40->Text != "")
			selectDay = Convert::ToInt32(day40->Text);
		else
			selectDay = -999;

		if (tmpCityName[40] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day40->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[40];
	}

	private: System::Void day41_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day41->Text != "")
			selectDay = Convert::ToInt32(day41->Text);
		else
			selectDay = -999;

		if (tmpCityName[41] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day41->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[41];
	}

	private: System::Void day42_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
		textBox1->Text = "";
		if (day42->Text != "")
			selectDay = Convert::ToInt32(day42->Text);
		else
			selectDay = -999;

		if (tmpCityName[42] == nullptr)
			selectCityName();
		ChangeDayColor(-999);
		day42->ForeColor = Color::DeepSkyBlue;
		textBox1->Text = tmpCityName[42];
	}
	private: System::Void saveButton_Click(System::Object^  sender, System::EventArgs^  e) {

		if (yearVal <= nowYearVal && monthVal <= nowMonthVal && selectDay < nowDayVal)
		{
			textBox1->Text = "";
			return;
		}
		else
		{
			saveAlarm(yearVal, monthVal, selectDay, textBox1->Text);
			selectCityName();
			textBox1->Text = "";
		}
	}
	private: System::Void tableReset_Tick(System::Object^  sender, System::EventArgs^  e) {
		loadAlarm(dayList);
	}
	private: System::Void totalReset_Tick(System::Object^  sender, System::EventArgs^  e) {
		ChangeDayColor(-999);
	}
	private: System::Void deleteButton_Click(System::Object^  sender, System::EventArgs^  e) {
		deleteAlarm(yearVal, monthVal, selectDay, textBox1->Text);
		textBox1->Text = "";
	}
	private: System::Void CloseTimer_Tick(System::Object^  sender, System::EventArgs^  e) {
		if (alarmCloseCount == 1)
		{
			this->Close();
			alarmCloseCount = 0;
		}
		else if (alarmCloseCount == 2)
		{
			this->Show();
			alarmCloseCount = 0;
		}
	}
	private: System::Void AlarmPage_MouseDown(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {

		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			menubarState = 1;
		}
	}
			 Void addCities() {
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
				 textBox1->AutoCompleteCustomSource->AddRange(cities);
			 }
	};
}