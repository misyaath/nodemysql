## NodeMysql

## Table of Contents

- [Install](#install)
- [Introduction](#introduction)



## Install

```sh
$ npm install nodemysql
```

This Addnon Will support for Windows and Linux generic 64bit OS only 

## Introduction

This is a node.js native addon for mysql. It is written in C/C++, does not
require compiling, and is Apache-2.0 licensed.

Here is an example on how to use it:

```js
var mysql      = require('nodemysql');
var db = mysql.connect({
  host     : '127.0.0.1',
  user     : 'username',
  password : 'password',
  database : 'database name'
});

db.mysql_real_query("SELECT * FROM users");

db.mysql_store_result();
var result = db.mysql_fetch_row();

for(var i=0; i< result.length; i++){
    result[i].COLUMN_NAME;
}

db.mysql_free_result();
db.mysql_close();
```
