<?php
/**
 * Created by PhpStorm.
 * User: Administrator
 * Date: 2015-12-05
 * Time: 오전 1:30
 */


include 'xml_maker.php';
include 'db_manager.php';

$db = new DBManager();
$today = date("Y-m-d");
//echo $code;
$big = $_GET['big'];
$mid = $_GET['mid'];
$small = $_GET['small'];

$table1 = $db->db_select_full("se_region_list", "code, x, y", "big='".$big."' and mid='".$mid."' and sm='".$small."'");
$region_code = $table1[0]['code'];
echo "[1]".$region_code;
$s_big = $big;
if (strpos($big,'광역시') !== false || strpos($big,'특별시') !== false)
    $std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='".$big."'");
else if(strlen($mid) >= 15) {
    $pos = strpos($mid, '시');
    $newMid = substr($mid, 0, $pos+3);
    $std_arr = $db->db_query2("select std_code from se_all_region where big='".$big."' and name='".$newMid."'");
}
else
    $std_arr = $db->db_query2("select std_code from se_all_region where big='".$big."' and name='".$mid."'");
$std_code = $std_arr[0]['std_code'];
//$std_code = 17;
$day_total = $db->db_query2("select tmn, tmx, sky from  se_day_forecast where region_code='".$std_code."' and date>='".$today."';");
$tmx = $day_total[0]['tmx'];
$tmn = $day_total[0]['tmn'];
$t_tmx = $day_total[1]['tmx'];
$t_tmn = $day_total[1]['tmn'];
$t_sky = $day_total[1]['sky'];
echo "[2]".$std_code;
echo $tmx." ".$tmn;
//echo "<br>";
echo "[3]";
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



echo "[3-11]".$cur_time." ㅎㅎ";
$time_total = $db->db_query2("select day, hour, temp, sky from  se_time_forecast where region_code='".$region_code."' and date='".$today."';");

$today_arr = array();
$tomorrow_arr = array();
foreach($time_total as $row)
{
    $day = $row[day];
    $hour = $row[hour];
    $temp = $row[temp];
    $sky = $row[sky];
    if($day == 0) {
        $tmp = array('hour'=>$hour, 'temp'=>$temp, 'sky'=>$sky);
        array_push($today_arr, $tmp);
    }
    else if($day == 1) {
        $tmp = array('hour'=>$hour, 'temp'=>$temp, 'sky'=>$sky);
        array_push($tomorrow_arr, $tmp);
    }
}
print_r($today_arr);

// section "오늘"
// - 오늘날씨 정보를 보여줌.
// - 최저, 최고 온도
// - 시간별 온도, 날씨상태  (아침, 점심, 저녁)

// section "내일"
// - 최저, 최고, 평균온도, 날씨상태
// - 시간별 온도, 날씨상태(새벽)

//날씨상태 조합
echo "[4]";
switch($today_arr[1][sky])
{
    case "맑음":
        $sky_code_t_2 = 1; // 오늘 중 index 2에 해당하는 하늘상태
        break;

    case "구름 조금":
        $sky_code_t_2 = 2;
        break;
    case "구름 많음":
        $sky_code_t_2 = 3;
        break;
    case "흐림":
        $sky_code_t_2 = 4;
        break;
    case "비":
        $sky_code_t_2 = 5;
        break;
    case "눈/비":
        $sky_code_t_2 = 6;
        break;
    case "눈":
        $sky_code_t_2 = 7;
        break;
}
switch($today_arr[2][sky])
{
    case "맑음":
        $sky_code_t_3 = 1;
        break;

    case "구름 조금":
        $sky_code_t_3 = 2;
        break;
    case "구름 많음":
        $sky_code_t_3 = 3;
        break;
    case "흐림":
        $sky_code_t_3 = 4;
        break;
    case "비":
        $sky_code_t_3 = 5;
        break;
    case "눈/비":
        $sky_code_t_3 = 6;
        break;
    case "눈":
        $sky_code_t_3 = 7;
        break;
}
switch($today_arr[3][sky])
{
    case "맑음":
        $sky_code_t_4 = 1;
        break;

    case "구름 조금":
        $sky_code_t_4 = 2;
        break;
    case "구름 많음":
        $sky_code_t_4 = 3;
        break;
    case "흐림":
        $sky_code_t_4 = 4;
        break;
    case "비":
        $sky_code_t_4 = 5;
        break;
    case "눈/비":
        $sky_code_t_4 = 6;
        break;
    case "눈":
        $sky_code_t_4 = 7;
        break;
}
switch($today_arr[5][sky])
{
    case "맑음":
        $sky_code_t_6 = 1;
        break;

    case "구름 조금":
        $sky_code_t_6 = 2;
        break;
    case "구름 많음":
        $sky_code_t_6 = 3;
        break;
    case "흐림":
        $sky_code_t_6 = 4;
        break;
    case "비":
        $sky_code_t_6 = 5;
        break;
    case "눈/비":
        $sky_code_t_6 = 6;
        break;
    case "눈":
        $sky_code_t_6 = 7;
        break;
}

switch($today_arr[6][sky])
{
    case "맑음":
        $sky_code_t_7 = 1;
        break;

    case "구름 조금":
        $sky_code_t_7 = 2;
        break;
    case "구름 많음":
        $sky_code_t_7 = 3;
        break;
    case "흐림":
        $sky_code_t_7 = 4;
        break;
    case "비":
        $sky_code_t_7 = 5;
        break;
    case "눈/비":
        $sky_code_t_7 = 6;
        break;
    case "눈":
        $sky_code_t_7 = 7;
        break;
}
switch($tomorrow_arr[0][sky])
{
    case "맑음":
        $sky_code_to_0 = 1; // 내일 중에 index 0에 해당하는 하늘상태
        break;

    case "구름 조금":
        $sky_code_to_0 = 2;
        break;
    case "구름 많음":
        $sky_code_to_0 = 3;
        break;
    case "흐림":
        $sky_code_to_0 = 4;
        break;
    case "비":
        $sky_code_to_0 = 5;
        break;
    case "눈/비":
        $sky_code_to_0 = 6;
        break;
    case "눈":
        $sky_code_to_0 = 7;
        break;
}
switch($tomorrow_arr[1][sky])
{
    case "맑음":
        $sky_code_to_1 = 1;
        break;

    case "구름 조금":
        $sky_code_to_1 = 2;
        break;
    case "구름 많음":
        $sky_code_to_1 = 3;
        break;
    case "흐림":
        $sky_code_to_1 = 4;
        break;
    case "비":
        $sky_code_to_1 = 5;
        break;
    case "눈/비":
        $sky_code_to_1 = 6;
        break;
    case "눈":
        $sky_code_to_1 = 7;
        break;
}
echo "[5]";

// toay_arr의 [0] : hour=3, [1] : hour=6   ===> [x] : hour=(x+1)*3
$morning_temp = ($today_arr[1][temp] + $today_arr[2][temp])/2; // hour = 9 , hour = 12인 애들 종합
echo "[5-1]";
if($sky_code_t_2 < $sky_code_t_3)
    $morning_sky = $today_arr[2][sky];
else
    $morning_sky = $today_arr[1][sky];
echo "[5-2]".$morning_temp;
$launch_temp = ($today_arr[2][temp]+$today_arr[3][temp])/2;
echo "[5-2-1]".$launch_temp;
if($sky_code_t_3 < $sky_code_t_4)
    $launch_sky = $today_arr[3][sky];
else
    $launch_sky = $today_arr[2][sky];
echo "[5-3]".$launch_sky;
echo "[5-3-1]".$today_arr[5][temp].$today_arr[6][temp];
$dinner_temp = ($today_arr[5][temp]+$today_arr[6][temp])/2;
echo "[5-4]".$dinner_temp;
if($sky_code_t_6 < $sky_code_t_7)
    $dinner_sky = $today_arr[6][sky];
else
    $dinner_sky = $today_arr[5][sky];

echo "[5-4-1]".$dinner_sky;
//$t_early_temp = ($tomorrow_arr[0][temp] + $tomorrow_arr[1][temp])/2;
$t_early_temp = $tomorrow_arr[0][temp];
echo "[5-5]".$t_early_temp;
/*
if($sky_code_to_0 < $sky_code_to_1)
    $t_early_sky = $tomorrow_arr[1][sky];
else
    $t_early_sky = $tomorrow_arr[0][sky];
echo "[6]".$dinner_sky;
*/
$t_early_sky = $tomorrow_arr[0][sky];
$XmlConstruct = new XmlConstruct('current_weather');

if($cur_time == 0 || $cur_time == 1 || $cur_time == 2)
    $cur_time = 3;
$XmlConstruct->startElement('today'); // 먼저 오늘 날씨의 최고, 최저 온도를 보여줌
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('temp');
$XmlConstruct->text($today_arr[$cur_time/3-2][temp]);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($today_arr[$cur_time/3-2][sky]);
$XmlConstruct->endElement();
$XmlConstruct->startElement('morning'); // 아침
$XmlConstruct->startElement('temp');
$XmlConstruct->text($morning_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($morning_sky);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('launch'); // 점심
$XmlConstruct->startElement('temp');
$XmlConstruct->text($launch_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($launch_sky);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->startElement('dinner'); // 저녁
$XmlConstruct->startElement('temp');
$XmlConstruct->text($dinner_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($dinner_sky);
$XmlConstruct->endElement();
$XmlConstruct->endElement();
$XmlConstruct->endElement();


//여기부터 내일 날씨
$XmlConstruct->startElement('tomorrow');
$XmlConstruct->startElement('tmx');
$XmlConstruct->text($t_tmx);
$XmlConstruct->endElement();
$XmlConstruct->startElement('tmn');
$XmlConstruct->text($t_tmn);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($t_sky);
$XmlConstruct->endElement();
$XmlConstruct->startElement('dawn'); // 새벽
$XmlConstruct->startElement('temp');
$XmlConstruct->text($t_early_temp);
$XmlConstruct->endElement();
$XmlConstruct->startElement('sky');
$XmlConstruct->text($t_early_sky);
$XmlConstruct->endElement();
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

echo "[Curtime : ] $cur_time";
$XmlConstruct->output("./xml/transaction_current_weather.xml");
header("Location: ./xml/transaction_current_weather.xml");
die();

?>