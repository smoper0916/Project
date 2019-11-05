<?php
/**
 * Created by PhpStorm.
 * User: 재혁
 * Date: 2015-11-25
 * Time: 오후 10:10
 */

include "db_manager.php";
include 'xml_maker.php';

$lat = $_GET["lat"];
$lon = $_GET["lon"];

$db = new DBManager();

$total = $db->db_query2("select code, lat, lon from se_region_list where lat BETWEEN '".$lat."'-0.2 and '".$lat."'+0.2 and lon BETWEEN '".$lon."'-0.2 and '".$lon."'+0.2");
$XmlConstruct = new XmlConstruct('search_result');

$count=0;
foreach($total as $row)
{
    $XmlConstruct->startElement('row');
    $XmlConstruct->startAttribute('id');
    $XmlConstruct->text($count);
    $XmlConstruct->endAttribute();

    //echo "row[0] : ".$row[0]."          row[1] :  ".$row[1]."    row[2] :  ";
    //print_r($row);
    for($i=0;$i<count($row)/2; $i++) {

        //echo $att."          ";
        $XmlConstruct->startElement('att');
        $XmlConstruct->text($row[$i]);
        //echo "값 : ".$att." count".$count."    ";
        $XmlConstruct->endElement();
    }
    $XmlConstruct->endElement();
    $count++;
}

$XmlConstruct->output("./xml/search_result.xml");
header("Location: ./xml/search_result.xml");
?>