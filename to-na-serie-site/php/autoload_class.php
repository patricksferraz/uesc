<?php

spl_autoload_register(function ($class_name)
{
    require_once 'controller/class.' . $class_name . '.php';
});

?>