<?php 

// This is just an example of reading server side data and sending it to the client.
// It reads a json formatted text file and outputs it.

//$string = file_get_contents("sampleData.json");
//echo $string;

// Instead you can query your database and parse into JSON etc etc
$lat = $_GET["lat"];
$lng = $_GET["lng"];

$EPSLION = 0.0003;

require ($_SERVER['DOCUMENT_ROOT']."/username_password.php");
$connection = mysqli_connect ($server, $username, $password);
if (!$connection) {
  die("Not connected : " . mysqli_error());
}
$db_selected = mysqli_select_db($connection,$database);
if (!$db_selected) {
  die ("Can\'t use db : " . mysqli_error());
}


//$query = "SELECT time," .$type." FROM sensors";

$query = <<<SQL
SELECT time, temperature, pH, o2level, turbidity
FROM sensors
WHERE (lat BETWEEN $lat-$EPSLION AND $lat+$EPSLION)
AND (lng BETWEEN $lng-$EPSLION AND $lng+$EPSLION)    
SQL;

$result = mysqli_query($connection,$query) or die("Error in Selecting " . mysqli_error($connection));

$table = array();
$table['cols'] = array(
    //Labels for the chart, these represent the column titles
    array('id' => '', 'label' => 'Time', 'type' => 'datetime'),
    array('id' => '', 'label' => 'Temperature', 'type' => 'number'),
    array('id' => '', 'label' => 'pH', 'type' => 'number'),
    array('id' => '', 'label' => 'DO', 'type' => 'number'),
    array('id' => '', 'label' => 'Turbidity', 'type' => 'number')
    ); 
$rows = array();
while($row = mysqli_fetch_assoc($result)){
    $temp = array();  
    
    $year=date("Y", strtotime($row['time']));
    $month=date("m", strtotime($row['time']));
    $month = intval($month)-1;
    $day=date("d", strtotime($row['time']));
    $hour=date("H", strtotime($row['time']));
    $minute=date("i", strtotime($row['time']));
    $second=date("s", strtotime($row['time']));
//    echo $formatted_time;
    $temp[] = array('v' => "Date($year, $month, $day, $hour, $minute, $second)");
    $temp[] = array('v' => (float) $row['temperature']);
    $temp[] = array('v' => (float) $row['pH']);
    $temp[] = array('v' => (float) $row['o2level']);
    $temp[] = array('v' => (float) $row['turbidity']);
    
//    echo json_encode($temp);
    $rows[] = array('c' => $temp);  
//    echo json_encode($rows);
    }
$table['rows'] = $rows;
mysqli_close($connection);
echo json_encode($table);
?>
