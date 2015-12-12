<?php

include 'xml_maker.php';
include 'db_manager.php';


$db = new DBManager;
$big = $_GET['big'];
$mid = $_GET['mid'];
$small = $_GET['small'];

$table1 = $db->db_select_full("se_region_list", "code, x, y", "big='".$big."' and mid='".$mid."' and sm='".$small."'");
$region_code = $table1[0]['code'];
$today = date("Y-m-d");

$total = $db->db_query2("select * from  se_time_forecast where region_code='".$region_code."' and date='".$today."';");

$XmlConstruct = new XmlConstruct('time_weather');

$count= 0;
foreach($total as $row)
{
	$XmlConstruct->startElement('section');
	$XmlConstruct->startAttribute('id');
	$XmlConstruct->text($count);
	$XmlConstruct->endAttribute();

	$XmlConstruct->startElement('day');
	$XmlConstruct->text($row[day]);
	$XmlConstruct->endElement();
	$XmlConstruct->startElement('hour');
	$XmlConstruct->text($row[hour]);
	$XmlConstruct->endElement();
	$XmlConstruct->startElement('temp');
	$XmlConstruct->text($row[temp]);
	$XmlConstruct->endElement();
	$XmlConstruct->startElement('sky');
	$XmlConstruct->text($row[sky]);
	$XmlConstruct->endElement();
	$XmlConstruct->startElement('reh');
	$XmlConstruct->text($row[reh]);
	$XmlConstruct->endElement();
	$XmlConstruct->startElement('pop');
	$XmlConstruct->text($row[pop]);
	$XmlConstruct->endElement();
	$XmlConstruct->endElement();

	$count++;
}

$XmlConstruct->output("./xml/time_forecast.xml");
header("Location: ./xml/time_forecast.xml");
die();

?>
