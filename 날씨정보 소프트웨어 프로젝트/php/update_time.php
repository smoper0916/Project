<?
include 'update_time_forecast.php';
/**
 * Created by PhpStorm.
 * User: 재혁
 * Date: 2015-11-22
 * Time: 오후 7:55
 */
// 필요한 변수 GET
$big = $_GET['big'];
$mid = $_GET['mid'];
$small = $_GET['small'];

$s = new UpdateTimeForecast();
$s->run($big, $mid, $small);
?>