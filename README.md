# 날씨정보소프트웨어 Project
## 개요
**프로젝트 기간** : 2015.09.10~2015.12.10  
**개발환경** : Visual Studio  
**개발언어** : C++/CLI, PHP  
**제작자** : 최재혁, 윤정근, 김민홍, 최정헌, 정재훈 (총 5명)  

이 프로젝트는 금오공과대학교 2학년 2학기 '프로그래밍설계' 과목 프로젝트입니다.
이 프로젝트는 C, C++ 계열의 언어만 사용해야하며 C#, Java 등의 언어는 사용 불가능하다는 제한사항이 있었습니다.
그래서 저희 팀은 C++에서 C#의 기능을 활용할 수 있는 언어인 C++/CLI(Managed C++)를 개발 언어로 채택하였습니다.

이 프로젝트는 기상청 api를 활용하여 각 지역의 현재 날씨를 보여주는 프로그램입니다.
기상청에서 주는 XML 파일을 파싱하여 DB(MySQL)에 가져왔고 IP를 통해 현재 위치도 파악하여 현재 위치의 현재 날씨를 보여주게 했습니다.
더불어서 예보도 가져와 앞으로 약 3일 간의 날씨도 볼 수 있게 하였습니다.
기존 프로그램과 가장 큰 차별점은 지역마다 특색있는 고화질의 배경이미지를 설정하여 그 지역의 분위기가 날 수 있게 하였습니다.
낮에는 그 지역의 아름다운 주경, 밤에는 그 지역에서만 볼 수 있는 야경을 넣었습니다.

DB 조회를 위해 php를 통해 웹페이지를 구현하였습니다.
그래서 C++/CLI에서 php 페이지로 요청을 넣으면 알맞은 기능을 수행하여 결과로 가져옵니다. 

### DB 스키마
**테이블명** : se_all_region  
이 테이블은 각 지역별로 기상청에서 제공하는 기준지역코드와 맵핑해놓은 테이블입니다.  
<img src="/se_all_region%20table.PNG" width="300px" height="600px" title="" alt=""></img><br/>
  
**테이블명** : se_std_region_list  
이 테이블은 기상청에서 제공하는 기준지역코드 리스트 테이블입니다.  
<img src="/se_std_region_list%20table.PNG" width="147px" height="800px" title="" alt=""></img><br/>
  
**테이블명** : se_region_list  
이 테이블은 모든 행정동과 그의 위도, 경도 정보를 담고 있는 리스트 테이블입니다.  
<img src="/se_region_list%20table.PNG" width="300px" height="600px" title="" alt=""></img><br/>
  
**테이블명** : se_day_forecast  
이 테이블은 주간날씨를 담고 있는 테이블입니다.   
<img src="/se_day_forecast%20table.PNG" width="1300px" height="850px" title="" alt=""></img><br/>
  
## 스크린샷
![Alt text](/p1_cap1.png)
![Alt text](/p1_cap2.png)

## 시연 동영상
https://youtu.be/UPEBEb2aYZY


