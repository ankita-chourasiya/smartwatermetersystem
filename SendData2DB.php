<?php
class dht11{
 public $link='';
 function __construct($totalvol,$macIdval){
  $this->connect();
  $this->storeInDB($totalvol,$macIdval);
 }
 
 function connect(){
  $this->link = mysqli_connect('localhost','root','') or die('Cannot connect to the DB');
  mysqli_select_db($this->link,'watermeter') or die('Cannot select the DB');
 }
 
 function storeInDB($totalvol,$macIdval){
  $query = "insert into readings set water_reading ='".$totalvol."', macId='".$macIdval."'";
  $result = mysqli_query($this->link,$query) or die('Errant query:  '.$query);
 }
 
}
if($_GET['totalvol'] != '' and  $_GET['macIdval'] != ''){
 $dht11=new dht11($_GET['totalvol'],$_GET['macIdval']); 

}


?>
