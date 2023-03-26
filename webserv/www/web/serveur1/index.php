<?php
echo "first file found is index.php<br>";
$date = date('d-m-y h:i:s');
echo $date, "<br>";
if (isset($_GET["name"]))
	echo "Hello ", $_GET["name"];
?>
