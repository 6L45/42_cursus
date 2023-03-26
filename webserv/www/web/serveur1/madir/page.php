<?php
// Return current date from the remote server
$date = date('d-m-y h:i:s');
echo $date, "<br>";
if (isset($_GET["name"]))
	echo "Hello ", $_GET["name"];
?>
