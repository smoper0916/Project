<?php
include "db_manager.php";
/**
 * Created by PhpStorm.
 * User: 재혁
 * Date: 2015-11-10
 * Time: 오전 3:06
 */
class DayData{
    public $date;
    public $tmn;
    public $tmx;
    public $sky;

    // 생성자
    function __construct($date, $tmx, $tmn, $sky){
        $this->date = $date;
        $this->tmn = $tmn;
        $this->tmx = $tmx;
        $this->sky = $sky;
    }
}
class UpdateDayForecast
{
    // 멤버변수
    private $dbm;
    private $list; // 날씨 Array

    function __construct(){
        $this->dbm = new DBManager();
        $this->list = array();
        $this->today = date("Y-m-d");
    }
    // 형식적인 함수
    function run(){
        $this->parse();
    }
    // 파싱
    function parse(){
        $url = "http://www.kma.go.kr/weather/forecast/mid-term-xml.jsp?stnId=108";
        $ch = curl_init();
        curl_setopt($ch, CURLOPT_URL, $url);
        curl_setopt($ch, CURLOPT_HEADER, false);
        curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
        $xml = curl_exec($ch);
        curl_close($ch);

        $result = new SimpleXMLElement($xml);

        $results = $result->body->location;
        $message = $result->header->wf; // 기상안내

        foreach($results as $index) {

            $city = $index->city;

            $count = 0;
            $list = array();
            foreach ($index as $item) {
                    //$num = $item->numEf;  //n 일후 예보
                    $wdate = $item->tmEf; // 날짜
                    $sky = $item->wf; //날씨, (맑음,구름조금,구름많음,흐림,비,눈/비,눈
                    $tmn = $item->tmn; //최저온도
                    $tmx = $item->tmx; //최고온도
                    //$rainrate = $item->reliability; //신뢰도
                    $tmparr = new DayData($wdate, $tmx, $tmn, $sky);
                //array_push($list, $tmparr);

                    $list[$count++] = $tmparr;
                echo "완료";

                //echo $list[$count-1]->tmx;
                        //echo $list[$count-1]->tmx." <- 최고온도 ".$list[$count-1]->tmn." <- 최저온도 ".$list[$count-1]->date." <- 날짜".$list[$count-1]->sky." <- sky     <br>";
            }
            // DB 삽입
            /*
             * 1. city에 해당하는 지역코드를 select로 받아옴
             * 2. 그 코드를 그대로 insert문에 넣어서 db에 삽입
             *
             * php로는 현재 지역 코드를 넘겨주면 된다.
             */

            $tmp = $this->dbm->db_select_full("se_std_region_list", "code","name='".$city."'");
            $code = $tmp[0]['code']; //0번째 행의 code라는 attribute
            $c = 0;

            foreach($list as $i)
            {

                if($c == 0 || $c == 1) {
                    $c++;
                    continue;
                }
                $text = "NULL";
                if($c == 2)
                    $text = $message;
                $sql = "'".$code."', '".$i->date."', '".$i->tmx."', '".$i->tmn."', '".$i->sky."', '".$text."'";
                $this->dbm->db_insert("se_day_forecast", $sql);
                $c++;
            }

        }

    }

}