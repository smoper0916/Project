<?
include "db_manager.php";

/*
 * 이 Class가 주석처리 된 이유
 * 1. 개발자가 최대한 객체지향적으로 개발하고자 했음
 * 2. 주간날씨까지는 어찌어찌 객체지향적으로 넣었는데
 * 3. 시간별날씨는 객체고 뭐고 걍 쉽게 빨리 넣고 싶었음.
 * 4. 그래서 걍 TimeData Class를 안씀
 * 5. 아마 사장될거임. ㅇㅇ
 *
class TimeData{
    public $time, $day, $hour, $temp,    $sky,    $pop,    $pty,     $tmn,     $tmx,    $ws, $wd, $reh;

    // 생성자
    function __construct($time, $day, $hour, $temp, $sky, $pop, $pty, $tmx, $tmn, $ws, $wd, $reh){
        $this->time = $time;
        $this->tmn = $tmn;
        $this->tmx = $tmx;
        $this->sky = $sky;
        $this->day = $day;
        $this->hour = $hour;
        $this->temp = $temp;
        $this->pop = $pop;
        $this->ws = $ws;
        $this->wd = $wd;
        $this->reh = $reh;
        $this->pty = $pty;
    }
}
*/
/*
 * 이 프로그램이 제대로 작동하기 위한 가정
 * 1. db Insert는 매일 0시 해야함
 * 2. 매번 테이블을 비우고 새로 insert 한다고 가정 하든지 아니면 기준 날짜를 설정해 그 날의 데이터만 포함하든지.
 *
 */
/*
 * 이 프로그램을 사용하는 방법
 * 1. db에 조회 시 도시 이름만으로 검색 가능
 * 2. 현재 시간부터 3일간의 시간별날씨는 오늘날짜를 통해서 접근
 *
 */

function convertRegionCode($big, $mid, $small){ //도, 시, 동  또는 시, 구, 동
    $dbm = new DBManager();
    //$dbm->db_select_full("se_region_list","","");
}

class UpdateTimeForecast
{
    // 멤버변수
    private $dbm;
    private $list; // 날씨 Array
    private $today; // 오늘 날짜

    function __construct()
    {
        $this->dbm = new DBManager();
        $this->list = array();
        $this->today = date("Y-m-d");
    }
    // 기초 작업 함수
    function run($big, $mid, $small){
        $table1 = $this->dbm->db_select_full("se_region_list", "code, x, y", "big='".$big."' and mid='".$mid."' and sm='".$small."'");
        $region_code = $table1[0]['code'];
        $gridx = $table1[0]['x'];
        $gridy = $table1[0]['y'];
        $this->parse($region_code, $gridx, $gridy);
    }
    //1. 도, 시, 동으로 조회
    //2. 도, 시, 동을 가지고 테이블에 조회하여 gridx, gridy, region_code를 받아온다.
    //3. 그것을 이용하여 파싱
    // 파싱
    function parse($region_code, $gridx, $gridy)
    {
        $url = "http://www.kma.go.kr/wid/queryDFS.jsp?gridx=" . $gridx . "&gridy=" . $gridy;
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_HEADER, false);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        $xml = curl_exec($ch);
        curl_close($ch);

        $result = new SimpleXMLElement($xml);
        $list = array();

        $results = $result->body->data; // data 태그부터 파싱

        foreach ($results as $item) {
            $hour = $item->hour; // 날짜
            $day = $item->day; //날씨, (맑음,구름조금,구름많음,흐림,비,눈/비,눈
            $temp = $item->temp;
            $pop = $item->pop;
            $sky = $item->wfKor;
            $reh = $item->reh;


            // region_code의 최대값은 3481
            // region_code에서 x,y값을 불러온다.

            // DB 삽입
            $sql = "'".$region_code."', '".$this->today."', '".$day."', '".$hour."', '".$temp."', '".$sky."', '".$pop."', '".$reh."'";
            $this->dbm->db_insert("se_time_forecast", $sql);
        }
    }
}
?>