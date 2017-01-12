## NodeMysql

## Table of Contents

- [Install](#install)
- [Introduction](#introduction)
- [Establishing connections](#establishing-connections)
- [Connection options](#connection-options)
- [Function Descriptions](#function-descriptions)
  - [mysql_affected_rows()](#mysql_affected_rows())
  - [mysql_real_connect()](#mysql_real_connect())
  - [mysql_close()](#mysql_close())
  - [mysql_query()](#mysql_query())
  - [mysql_store_result()](#mysql_store_result())
  - [mysql_free_result()](#mysql_free_result())
  - [mysql_fetch_row()](#mysql_fetch_row())
  - [mysql_affected_rows()](#mysql_affected_rows())
  - [mysql_character_set_name()](#mysql_character_set_name())
  - [mysql_commit()](#mysql_commit())
  - [mysql_data_seek()](#mysql_data_seek())
  - [mysql_debug()](#mysql_debug())
  - [mysql_dump_debug_info()](#mysql_dump_debug_info())
  - [mysql_errno()](#mysql_errno())
  - [mysql_error()](#mysql_error())



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
  username : 'username',
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


## Establishing connections

The recommended way to establish a connection is this:

```js

var mysql      = require('nodemysql');
var db = mysql.connect({
  host     : '127.0.0.1',
  username : 'username',
  password : 'password',
  database : 'database name'
  port     : 3306,
  socket   : "tcp"
  falg     : 0,
});

console.log("Error: " + db.mysql_error() + " Error No: " + mysql_errno())

```
## Connection options

When establishing a connection, you can set the following options:

* `host`: The hostname of the database you are connecting to. (Default:
  `localhost` for Linux generic `"127.0.0.1"`)
* `port`: The port number to connect to. (Default: `3306`)(Optional),
* `socket`: The source IP address to use for TCP connection. (Optional)
* `username`: The MySQL user to authenticate as.
* `password`: The password of that MySQL user.
* `database`: Name of the database to use for this connection (Optional).
* `flags`: List of connection flags to use other than the default ones. It is
  also possible to blacklist default ones. For more information, check
  [Connection Flags](#connection-flags).

