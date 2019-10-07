<?php
//RECEBE
$id = $_GET["id"];
$img = $_GET['img'];

header("Content-type: ".$id."");

echo $img;
?>