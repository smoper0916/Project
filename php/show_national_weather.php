<?php
/**
 * Created by PhpStorm.
 * User: 재혁
 * Date: 2015-12-05
 * Time: 오후 8:58
 */

include 'xml_maker.php';
include 'db_manager.php';

$db = new DBManager(); // 디버깅용 db정보
$today = date("Y-m-d");


// 전국날씨 대상 기준코드 추출
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='서울특별시'");
$seoul_std_code = $std_arr[0]['std_code'];
echo $seoul_std_code."nation!";
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='인천광역시'");
$incheon_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='대전광역시'");
$daejeon_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='대구광역시'");
$daegu_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='광주광역시'");
$kwangju_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='울산광역시'");
$ulsan_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='부산광역시'");
$busan_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big='제주특별자치도' and name='제주시'");
$jeju_std_code = $std_arr[0]['std_code'];
$std_arr = $db->db_query2("select std_code from se_all_region where big='제주특별자치도' and name='서귀포시'");
$jeju2_std_code = $std_arr[0]['std_code'];

//$std_code = 17;
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$seoul_std_code."' and date>='".$today."';");
$seoul_tmx = $day_total[0]['tmx'];
$seoul_tmn = $day_total[0]['tmn'];
echo $seoul_tmn."nation!";
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$incheon_std_code."' and date>='".$today."';");
$incheon_tmx = $day_total[0]['tmx'];
$incheon_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$daejeon_std_code."' and date>='".$today."';");
$daejeon_tmx = $day_total[0]['tmx'];
$daejeon_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$daegu_std_code."' and date>='".$today."';");
$daegu_tmx = $day_total[0]['tmx'];
$daegu_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$kwangju_std_code."' and date>='".$today."';");
$kwangju_tmx = $day_total[0]['tmx'];
$kwangju_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$ulsan_std_code."' and date>='".$today."';");
$ulsan_tmx = $day_total[0]['tmx'];
$ulsan_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$busan_std_code."' and date>='".$today."';");
$busan_tmx = $day_total[0]['tmx'];
$busan_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$jeju_std_code."' and date>='".$today."';");
$jeju_tmx = $day_total[0]['tmx'];
$jeju_tmn = $day_total[0]['tmn'];
$day_total = $db->db_query2("select tmn, tmx from  se_day_forecast where region_code='".$jeju2_std_code."' and date>='".$today."';");
$jeju2_tmx = $day_total[0]['tmx'];
$jeju2_tmn = $day_total[0]['tmn'];

$cur_time = date("H");

switch($cur_time)
{
    case 1:
    case 2:
    case 3:
        $cur_time = 3;
        break;
    case 4:
    case 5:
    case 6:
        $cur_time = 6;
        break;
    case 7:
    case 8:
    case 9:
        $cur_time = 9;
        break;
    case 10:
    case 11:
    case 12:
        $cur_time = 12;
        break;
    case 13:
    case 14:
    case 15:
        $cur_time = 15;
        break;
    case 16:
    case 17:
    case 18:
        $cur_time = 18;
        break;
    case 19:
    case 20:
    case 21:
        $cur_time = 21;
        break;
    case 22:
    case 23:
    case 24:
        $cur_time = 24;
        break;
}
echo "nation!";
$seoul_time_total = $db->db_query2("select * from  se_time_forecast where region_code=1911 and date='".$today."';"); // 서울
$incheon_time_total = $db->db_query2("select * from  se_time_forecast where region_code=2402 and date='".$today."';"); // 인천
$daejeon_time_total = $db->db_query2("select * from  se_time_forecast where region_code=1623 and date='".$today."';"); // 대전
$daegu_time_total = $db->db_query2("select * from  se_time_forecast where region_code=1480 and date='".$today."';"); // 대구
$kwangju_time_total = $db->db_query2("select * from  se_time_forecast where region_code=1388 and date='".$today."';"); // 광주
$ulsan_time_total = $db->db_query2("select * from  se_time_forecast where region_code=2346 and date='".$today."';"); // 울산
$busan_time_total = $db->db_query2("select * from  se_time_forecast where region_code=1698 and date='".$today."';"); // 부산
$jeju_time_total = $db->db_query2("select * from  se_time_forecast where region_code=3100 and date='".$today."';"); // 제주시
$jeju2_time_total = $db->db_query2("select * from  se_time_forecast where region_code=3082 and date='".$today."';"); // 서귀포시
echo "nation!";
/*
 * [0] 서울특별시
 * [1] 인천광역시
 * [2] 대전광역시
 * [3] 대구광역시
 * [4] 광주광역시
 * [5] 울산광역시
 * [6] 부산광역시
 * [7] 제주시
 * [8] 서귀포시
 *
 */
$korea_arr = array();
foreach($seoul_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($incheon_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($daejeon_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($daegu_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($kwangju_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($ulsan_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($busan_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($jeju_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}
foreach($jeju2_time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    $pop = $row[pop];
    $reh = $row[reh];
    if($day == 0) {
        if($cur_time % 3 != 0){
            if($hour == (3-$cur_time%3+$cur_time)){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
        else{
            if($hour == $cur_time){
                $today_arr = array('temp'=>$temp, 'sky'=>$sky, 'pop'=>$pop, 'reh'=>$reh);
                array_push($korea_arr, $today_arr);
            }
        }
    }
}


// 날씨 구하기
$seoul_temp = $korea_arr[0][temp];
$seoul_sky = $korea_arr[0][sky];
$seoul_pop = $korea_arr[0][pop];
$seoul_reh = $korea_arr[0][reh];
$incheon_temp = $korea_arr[1][temp];
$incheon_sky = $korea_arr[1][sky];
$incheon_pop = $korea_arr[1][pop];
$incheon_reh = $korea_arr[1][reh];
$daejeon_temp = $korea_arr[2][temp];
$daejeon_sky = $korea_arr[2][sky];
$daejeon_pop = $korea_arr[2][pop];
$daejeon_reh = $korea_arr[2][reh];
$daegu_temp = $korea_arr[3][temp];
$daegu_sky = $korea_arr[3][sky];
$daegu_pop = $korea_arr[3][pop];
$daegu_reh = $korea_arr[3][reh];
$kwangju_temp = $korea_arr[4][temp];
$kwangju_sky = $korea_arr[4][sky];
$kwangju_pop = $korea_arr[4][pop];
$kwangju_reh = $korea_arr[4][reh];
$ulsan_temp = $korea_arr[5][temp];
$ulsan_sky = $korea_arr[5][sky];
$ulsan_pop = $korea_arr[5][pop];
$ulsan_reh = $korea_arr[5][reh];
$busan_temp = $korea_arr[6][temp];
$busan_sky = $korea_arr[6][sky];
$busan_pop = $korea_arr[6][pop];
$busan_reh = $korea_arr[6][reh];
$jeju_temp = ($korea_arr[7][temp] + $korea_arr[8][temp]) / 2;
$jeju_sky = $korea_arr[7][sky];
$jeju_pop = ($korea_arr[7][pop] + $korea_arr[8][pop]) / 2;
$jeju_reh = ($korea_arr[7][reh] + $korea_arr[8][reh]) / 2;


$XmlConstruct = new XmlConstruct('the_national_weather');


$XmlConstruct->startElement('seoul');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($seoul_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($seoul_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($seoul_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($seoul_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($seoul_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($seoul_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('incheon');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($incheon_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($incheon_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($incheon_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($incheon_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($incheon_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($incheon_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('daejeon');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($daejeon_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($daejeon_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($daejeon_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($daejeon_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($daejeon_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($daejeon_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('daegu');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($daegu_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($daegu_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($daegu_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($daegu_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($daegu_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($daegu_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('kwangju');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($kwangju_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($kwangju_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($kwangju_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($kwangju_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($kwangju_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($kwangju_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('ulsan');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($ulsan_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($ulsan_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($ulsan_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($ulsan_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($ulsan_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($ulsan_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('busan');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($busan_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($busan_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($busan_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($busan_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($busan_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($busan_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('jeju');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($jeju_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($jeju_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($jeju_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($jeju_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('pop');
$XmlConstruct->text($jeju_pop);
$XmlConstruct->endElement();
$XmlConstruct->startElement('reh');
$XmlConstruct->text($jeju_reh);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
/*
$contents = array( 'section' => array(
        'date' => $row[date],
        'tmn' =>  $row[tmn],
        'tmx' =>  $row[tmx],
        'sky' =>  $row[sky],
        'note' =>  $row[note]));
*/
//array_push($document, $contents);
//$doc[$count++] = $contents;
// $count++;


$XmlConstruct->output("./xml/transaction_national_weather.xml");
header("Location: ./xml/transaction_national_weather.xml");
die();

?>