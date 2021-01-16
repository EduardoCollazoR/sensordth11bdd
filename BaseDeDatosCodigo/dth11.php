<?php
class dht11{
 public $link='';
 function __construct($temperatura, $humedad){
  $this->connect();
  $this->storeInDB($temperatura, $humedad);
 }
 
 function connect(){
  $this->link = mysqli_connect('escobedo.nerdpol.ovh:3306','escobedo','maria123') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'ITN-ADF-1702IF8A') or die('Cannot select the DB');
 }
 
 function storeInDB($temperatura, $humedad){
  $query = "insert into sensores set temperatura='".$temperatura."', humedad='".$humedad."', hora=current_timestamp, fecha=current_timestamp";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['temperatura'] != '' and  $_GET['humedad'] != ''){
 $dht11=new dht11($_GET['temperatura'],$_GET['humedad']);
}
?>