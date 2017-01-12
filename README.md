## NodeMysql

## Table of Contents

- [Install](#install)
- [Introduction](#introduction)
- [Establishing connections](#establishing-connections)
- [Connection options](#connection-options)
- [Function Descriptions](#function-descriptions)
 - [mysql_affected_rows()](#mysql_affected_rows)
 - [mysql_real_connect()](#mysql_real_connect)
 - [mysql_close()](#mysql_close)
 - [mysql_query()](#mysql_query)
 - [mysql_store_result()](#mysql_store_result)
 - [mysql_free_result()](#mysql_free_result)
 - [mysql_fetch_row()](#mysql_fetch_row)
 - [mysql_affected_rows()](#mysql_affected_rows)
 - [mysql_character_set_name()](#mysql_character_set_name)
 - [mysql_commit()](#mysql_commit)
 - [mysql_data_seek()](#mysql_data_seek)
 - [mysql_debug()](#mysql_debug)
 - [mysql_dump_debug_info()](#mysql_dump_debug_info)
 - [mysql_errno()](#mysql_errno)
 - [mysql_error()](#mysql_error)
 - [mysql_fetch_field()](#mysql_fetch_field)
 - [mysql_fetch_field_direct()](#mysql_fetch_field_direct)
 - [mysql_fetch_fields()](#mysql_fetch_fields)
 - [mysql_field_count()](#mysql_field_count)
 - [mysql_get_character_set_info()](#mysql_get_character_set_info)
 - [mysql_get_client_info()](#mysql_get_client_info)
 - [mysql_get_client_version()](#mysql_get_client_version)
 - [mysql_get_host_info()](#mysql_get_host_info)
 - [mysql_get_proto_info()](#mysql_get_proto_info)
 - [mysql_get_server_info()](#mysql_get_server_info)
 - [mysql_get_ssl_cipher()](#mysql_get_ssl_cipher)
 - [mysql_info()](#mysql_info)
 - [mysql_insert_id()](#mysql_insert_id)
 - [mysql_more_results()](#mysql_more_results)
 - [mysql_num_fields()](#mysql_num_fields)
 - [mysql_num_rows()](#mysql_num_rows)
 - [mysql_real_query()](#mysql_real_query)
 - [mysql_reload()](#mysql_reload)
 - [mysql_reset_connection()](#mysql_reset_connection)
 - [mysql_rollback()](#mysql_rollback)
 - [mysql_select_db()](#mysql_select_db)
 - [mysql_set_local_infile_default()](#mysql_set_local_infile_default)
 - [mysql_sqlstate()](#mysql_sqlstate)
 - [mysql_ssl_set()](#mysql_ssl_set)
 - [mysql_stat()](#mysql_stat)
 - [mysql_use_result()](#mysql_use_result)
 - [mysql_warning_count()](#mysql_warning_count)
 - [mysql_change_user()](#mysql_change_user)
 - [mysql_fetch_lengths()](#mysql_fetch_lengths)
 - [mysql_autocommit()](#mysql_autocommit)
 - [mysql_real_escape_string()](#mysql_real_escape_string)
 - [mysql_ping()](#mysql_ping)
 - [mysql_multiple_statement()](#mysql_multiple_statement)
  



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

## Function Descriptions

## mysql_affected_rows()
