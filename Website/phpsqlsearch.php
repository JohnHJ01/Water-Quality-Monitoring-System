<?php
//Adapted from Goole Store Locater tutorial
//06/10/2016
//Chan Hao Jie

require ($_SERVER['DOCUMENT_ROOT']."/username_password.php");

// Get parameters from URL
//$center_lat = $_GET["lat"];
//$center_lng = $_GET["lng"];
//$radius = $_GET["radius"];

// Start XML file, create parent node
$dom = new DOMDocument("1.0");
$node = $dom->createElement("markers");
$parnode = $dom->appendChild($node);

// Opens a connection to a mySQL server
$connection = mysqli_connect ($server, $username, $password);
if (!$connection) {
  die("Not connected : " . mysqli_error());
}

// Set the active mySQL database
$db_selected = mysqli_select_db($connection,$database);
if (!$db_selected) {
  die ("Can\'t use db : " . mysqli_error());
}

// Search the rows in the markers table
//$query = "SELECT * From sensors
//WHERE time IN(
//    SELECT MAX(time) FROM sensors GROUP BY lat,lng)";

$query = "SELECT * From sensors
WHERE time IN(
    SELECT MAX(time) FROM sensors GROUP BY lat)"; //band-aid to reduce the markers 08/12/16

//  mysqli_real_escape_string($center_lat),
//  mysql_real_escape_string($center_lng),
//  mysql_real_escape_string($center_lat),
//  mysql_real_escape_string($radius));
$result = mysqli_query($connection,$query);

if (!$result) {
  die("Invalid query: " . mysqli_error());
}

header("Content-type: text/xml");

// Iterate through the rows, adding XML nodes for each
while ($row = @mysqli_fetch_assoc($result)){
//    echo "lat: ". $row["lat"]. "  lng: " . $row["lng"];
  $node = $dom->createElement("marker");
  $newnode = $parnode->appendChild($node);
  $newnode->setAttribute("lat", $row['lat']);
  $newnode->setAttribute("lng", $row['lng']);
  $newnode->setAttribute("time", $row['time']);
  $newnode->setAttribute("temperature", $row['temperature']);
  $newnode->setAttribute("o2level", $row['o2level']);
  $newnode->setAttribute("pH", $row['pH']);
  $newnode->setAttribute("turbidity", $row['turbidity']);
}

echo $dom->saveXML();
mysqli_close($connection);
?>
