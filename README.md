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

```js
var effected_rows = db.mysql_affected_rows();
```

Description

mysql_affected_rows() may be called immediately after executing a statement with mysql_query() or mysql_real_query(). It returns the number of rows changed, deleted, or inserted by the last statement if it was an UPDATE, DELETE, or INSERT. For SELECT statements, mysql_affected_rows() works like mysql_num_rows(). 

See https://dev.mysql.com/doc/refman/5.7/en/mysql-affected-rows.html


## mysql_autocommit()

```js
db.mysql_autocommit(int mode)
```

Description

Sets autocommit mode on if mode is 1, off if mode is 0. 
See https://dev.mysql.com/doc/refman/5.7/en/mysql-autocommit.html

Return Values

true for success. false if an error occurred.


## mysql_change_user()

```js
bool =  db.mysql_change_user(user,password,db);
```

Description

Changes the user and causes the database specified by db to become the default (current) database on the connection specified by mysql. In subsequent queries, this database is the default for table references that include no explicit database specifier.

mysql_change_user() fails if the connected user cannot be authenticated or does not have permission to use the database. In this case, the user and database are not changed. 
See https://dev.mysql.com/doc/refman/5.7/en/mysql-change-user.html

Return Values

true for success. false if an error occurred.

## mysql_character_set_name()

```js
string = db.mysql_character_set_name();
```
Description

Returns the default character set name for the current connection. 
See https://dev.mysql.com/doc/refman/5.7/en/mysql-character-set-name.html

Return Values

The default character set name

## mysql_close()

```js
void db.mysql_close()
```

Description

Closes a previously opened connection. mysql_close() also deallocates the connection handle pointed to by mysql if the handle was allocated automatically by mysql_init() or mysql_connect().

Return Values

None.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-close.html

## mysql_commit()

```js
boll =  db.mysql_commit()
```

Description

Commits the current transaction.

The action of this function is subject to the value of the completion_type system variable. In particular, if the value of completion_type is RELEASE (or 2), the server performs a release after terminating a transaction and closes the client connection. Call mysql_close() from the client program to close the connection from the client side.

Return Values

True for success. False if an error occurred.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-commit.html

## mysql_data_seek()

```js
void db.mysql_data_seek(int offset)
```

Description

Seeks to an arbitrary row in a query result set. The offset value is a row number. Specify a value in the range from 0 to mysql_num_rows(result)-1.

This function requires that the result set structure contains the entire result of the query, so mysql_data_seek() may be used only in conjunction with mysql_store_result(), not with mysql_use_result().

Return Values

None.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-data-seek.html

## mysql_debug()

```js
void db.mysql_debug("d:t:O,/tmp/client.trace");
```

Description

Does a DBUG_PUSH with the given string. mysql_debug() uses the Fred Fish debug library. To use this function, you must compile the client library to support debugging. See Section 27.5.3, “The DBUG Package”.

Return Values

None.





