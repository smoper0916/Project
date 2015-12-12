<?php

include 'xml_maker.php';
include 'db_manager.php';

$db = new DBManager;
if(!$_GET['city'] && $_GET['code']) {

$code = $_GET['code'];
}
else {
	$city = $_GET['city'];


	$tmp = $db->db_select_full("se_std_region_list", "code", "name='" . $city . "'");
	$code = $tmp[0]['code'];
}
$today = date("Y-m-d");

$total = $db->db_query2("select * from  se_day_forecast where region_code='".$code."' and date>='".$today."';");

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

$XmlConstruct->output("./xml/week_forecast.xml");
header("Location: ./xml/week_forecast.xml");
die();

?>
