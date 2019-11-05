#pragma once

namespace newCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// 전국날씨지도에 대한 요약입니다.
	/// </summary>
	public ref class 전국날씨지도 : public System::Windows::Forms::Form
	{
	public:
		전국날씨지도(void)
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
		~전국날씨지도()
		{
			if (components)
			{
				delete components;
			}
		}

	protected: 

	private:
		/// <summary>
		/// 필수 디자이너 변수입니다.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 디자이너 지원에 필요한 메서드입니다.
		/// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// 전국날씨지도
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(285, 375);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"전국날씨지도";
			this->Opacity = 0.8;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"전국날씨지도";
			this->TransparencyKey = System::Drawing::Color::Transparent;
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
