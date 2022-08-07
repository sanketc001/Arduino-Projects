<?php
    $host = "localhost"; 
    $dbname = "epiz_27664234_parking";    // Database name
    $username = "admin";                    // Database username
    $password = "1234";                        // Database password
    $conn = new mysqli($host, $username, $password, $dbname);
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } else {
        echo "Connected to mysql database. ";
    }
  if(!empty($_POST['inches'])){
            $inches = $_POST['inches'];
		  $sql = "INSERT INTO parkingdata (inches) VALUES ('$inches')";
                //$sql = "INSERT INTO parkingdata (temperature, humidity) VALUES ('".$temperature."','".$humidity."')";
                        if ($conn->query($sql) === TRUE) {
                            echo "Values inserted in MySQL database table.";
                        } else {
                            echo "Error: " . $sql . "<br>" . $conn->error;
                        }
            }
    // Close MySQL connection
    $conn->close();
?>