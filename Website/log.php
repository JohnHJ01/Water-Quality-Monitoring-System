<?php
//An external file for parsing data coming from Arduino into DB
require ($_SERVER['DOCUMENT_ROOT']."/username_password.php");

//$time = $_GET["t"];
$temp = $_GET["te"];
$DO = $_GET["do"];
$pH = $_GET["pH"];
$turbidity = $_GET["tu"];
$lat = $_GET["la"];
$lng = $_GET["ln"];

//Adapted from http://stackoverflow.com/a/16814230/7064721
$tz = 'Asia/Kuala_Lumpur';
$timestamp = time();
$dt = new DateTime("now", new DateTimeZone($tz)); //first argument "must" be a string
$dt->setTimestamp($timestamp); //adjust the object to correct timestamp
$time = $dt->format('Y-m-d,H:i:s');

echo $time;
echo(",");
echo($lat);
echo(",");
echo($lng);

$connection = mysqli_connect ($server, $username, $password);
if (!$connection) {
  die("Not connected : " . mysqli_error());
}

// Set the active mySQL database
$db_selected = mysqli_select_db($connection,$database);
if (!$db_selected) {
  die ("Can\'t use db : " . mysqli_error());
}

$SQL = "INSERT INTO sensors(time, temperature, o2level, pH, turbidity, lat, lng)
   VALUES ('$time', '$temp', '$DO', '$pH', '$turbidity', '$lat', '$lng')";
$result = mysqli_query($connection, $SQL);
if(!$result){
    die(mysqli_error($connection));
}

mysqli_close($connection);
/*WARNING: MAKE SURE NO EMPTY LINE IS AROUND AFTER ?> SIGN*/
?>
