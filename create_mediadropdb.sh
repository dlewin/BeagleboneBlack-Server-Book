#!/bin/bash
mysql -u root -proot << EOF
CREATE user 'debian'@'localhost'IDENTIFIED BY 'temppwd';
CREATE DATABASE MediaDrop;
USE MediaDrop;
GRANT create,insert,update,select,delete on MediaDrop.* to debian@localhost;
SHOW databases;
SHOW tables;
EOF
