<?php
/**
 * Created by PhpStorm.
 * User: 재혁
 * Date: 2015-12-05
 * Time: 오후 5:56
 */

include 'xml_maker.php';
include 'db_manager.php';

$db = new DBManager;

//광역시면 mid만 있으면 되고 일반 시이면 big, mid 둘 다 있어야 함
$big = $_GET['big'];
if(!$_GET['mid']){

}
else {
    $mid = $_GET['mid'];
}

if (strpos($big,'광역시') !== false || strpos($big,'특별시') !== false)
    $std_arr = $db->db_query2("select std_code from se_all_region where big is NULL and name='".$big."'");
else
    $std_arr = $db->db_query2("select std_code from se_all_region where big='".$big."' and name='".$mid."'");
$std_code = $std_arr[0]['std_code'];

$today = date("Y-m-d");

$total = $db->db_query2("select * from  se_day_forecast where region_code='".$std_code."' and date>='".$today."';");

$XmlConstruct = new XmlConstruct('week_weather');

$count= 0;
foreach($total as $row)
{
    if($count > 5)
        break;
    $XmlConstruct->startElement('section');
    $XmlConstruct->startAttribute('id');
    $XmlConstruct->text($count);
    $XmlConstruct->endAttribute();

    $XmlConstruct->startElement('date');
    $XmlConstruct->text($row[date]);
    $XmlConstruct->endElement();
    $XmlConstruct->startElement('tmx');
    $XmlConstruct->text($row[tmx]);
    $XmlConstruct->endElement();
    $XmlConstruct->startElement('tmn');
    $XmlConstruct->text($row[tmn]);
    $XmlConstruct->endElement();
    $XmlConstruct->startElement('sky');
    $XmlConstruct->text($row[sky]);
    $XmlConstruct->endElement();
    $XmlConstruct->startElement('note');
    $XmlConstruct->text($row[note]);
    $XmlConstruct->endElement();
    $XmlConstruct->endElement();

    $count++;
}

$XmlConstruct->output("./xml/transaction_week_forecast.xml");
header("Location: ./xml/transaction_week_forecast.xml");
die();

?>
