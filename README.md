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
 
- [Connection Flags](#connection-flags)
- [Multiple Statement Execution](#multiple_statement_execution)
  



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

See https://dev.mysql.com/doc/refman/5.7/en/mysql-debug.html

## mysql_dump_debug_info()

```js
bool db.mysql_dump_debug_info()
```

Description

Instructs the server to write debugging information to the error log. The connected user must have the SUPER privilege.

Return Values

True for success. False if an error occurred.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-dump-debug-info.html

## mysql_errno()

```js
int db.mysql_errno()
```
Description

For the connection specified by mysql, mysql_errno() returns the error code for the most recently invoked API function that can succeed or fail. A return value of zero means that no error occurred. Client error message numbers are listed in the MySQL errmsg.h header file. Server error message numbers are listed in mysqld_error.h. Errors also are listed at Appendix B, Errors, Error Codes, and Common Problems.


Return Values

An error code value for the last mysql_xxx() call, if it failed. zero means no error occurred.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-errno.html

## mysql_error()

```js
string db.mysql_error()
```

Description

For the connection specified by mysql, mysql_error() returns a string containing the error message for the most recently invoked API function that failed. If a function did not fail, the return value of mysql_error() may be the previous error or an empty string to indicate no error.

A rule of thumb is that all functions that have to ask the server for information reset mysql_error() if they succeed.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-error.html

## mysql_fetch_field()

```js

db.mysql_real_query("SELECT * FROM table");
var res = db.mysql_store_result();
var field = db.mysql_fetch_field()

for (var i = 0; i < field.length; i++) {

    console.log(field[i].org_name);
    console.log(field[i].table);
    console.log(field[i].org_table);
    console.log(field[i].db);
    console.log(field[i].catalog);
    console.log(field[i].length);
    console.log(field[i].max_length);
    console.log(field[i].name_length);
    console.log(field[i].org_name_length);
    console.log(field[i].table_length);
    console.log(field[i].org_table_length);
    console.log(field[i].db_length);
    console.log(field[i].catalog_length);
    console.log(field[i].charsetnr);
    console.log(field[i].type);
    
}

```

Description

Returns an array of all MYSQL_FIELD structures for a result set. Each structure provides the field definition for one column of the result set.

Return Values

An array of array for all columns of a result set.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-fetch-fields.html



## mysql_fetch_field_direct()

```js

db.mysql_real_query("SELECT * FROM pet");
var res = db.mysql_store_result();
var field = db.mysql_fetch_field_direct(5)

console.log(field.name);

```

Description

Given a field number fieldnr for a column within a result set, returns that column's field definition as a MYSQL_FIELD structure. Use this function to retrieve the definition for an arbitrary column. Specify a value for fieldnr in the range from 0 to mysql_num_fields(result)-1.

Return Values

The JSON object for the specified column.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-fetch-field-direct.html

## mysql_fetch_fields()

```js

db.mysql_real_query("SELECT * FROM table");
var res = db.mysql_store_result();
var field = db.mysql_fetch_fields()


    console.log(field[i].org_name);
    console.log(field[i].table);
    console.log(field[i].org_table);
    console.log(field[i].db);
    console.log(field[i].catalog);
    console.log(field[i].length);
    console.log(field[i].max_length);
    console.log(field[i].name_length);
    console.log(field[i].org_name_length);
    console.log(field[i].table_length);
    console.log(field[i].org_table_length);
    console.log(field[i].db_length);
    console.log(field[i].catalog_length);
    console.log(field[i].charsetnr);
    console.log(field[i].type);
  

```


Description

mysql_fetch_field() is reset to return information about the first field each time you execute a new SELECT query. The field returned by mysql_fetch_field() is also affected by calls to mysql_field_seek().


Return Values

The array for the current column.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-fetch-field.html


## mysql_fetch_lengths()

```js
db.mysql_real_query("SELECT * FROM pet");
var res = db.mysql_store_result();
var row = db.mysql_fetch_row();
var field = db.mysql_fetch_lengths()

console.log(field);


for (var i = 0; i < field.length; i++) {

    console.log(field[i].fieldname);

}

```
Description

Returns the lengths of the columns of the current row within a result set. If you plan to copy field values, this length information is also useful for optimization, 

Return Values

An array of integers representing the size of each column (not including any terminating null bytes). NULL if an error occurred.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-fetch-lengths.html


## mysql_fetch_row()

```js

db.mysql_real_query("SELECT * FROM pet");
var res = db.mysql_store_result();
var row = db.mysql_fetch_row();

for (var i = 0; i < field.length; i++) {

 console.log(field[i].fieldname);

}


```
Description

Retrieves the row of a result set. 

Return Values

A array structure for the row. NULL if there are no more rows to retrieve or if an error occurred.

## mysql_field_count()

```js
db.mysql_real_query("SELECT * FROM pet");
var res = db.mysql_store_result();

console.log(db.mysql_field_count());

```
Description

Returns the number of columns for the most recent query on the connection.

The normal use of this function is when mysql_store_result() returned NULL (and thus you have no result set pointer). In this case, you can call mysql_field_count() to determine whether mysql_store_result() should have produced a nonempty result. This enables the client program to take proper action without knowing whether the query was a SELECT (or SELECT-like) statement. The example shown here illustrates how this may be done.

See Section 26.8.15.1, “Why mysql_store_result() Sometimes Returns NULL After mysql_query() Returns Success”.

Return Values

An integer representing the number of columns in a result set.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-field-count.html


## mysql_free_result()

```js

db.mysql_real_query("SELECT * FROM pet");
var res = db.mysql_store_result();
var row = db.mysql_fetch_row();

db.mysql_free_result()

```
Description

Frees the memory allocated for a result set by mysql_store_result(), mysql_use_result(), mysql_list_dbs(), and so forth. When you are done with a result set, you must free the memory it uses by calling mysql_free_result().

Do not attempt to access a result set after freeing it.

Return Values

None.


## mysql_get_character_set_info()

```js

   var cs = db.mysql_get_character_set_info();
    
    console.log("character set+collation number: " + cs.number);
    console.log("character set name: " + cs.name);
    console.log("collation name: " +cs.csname);
    console.log("comment: " +cs.comment);
    console.log("directory: " +cs.dir);
    console.log("multi byte character min. length: "+ cs.mbminlen);
    console.log("multi byte character max. length: "+ cs.mbmaxlen);

```

Description

This function provides information about the default client character set. The default character set may be changed with the mysql_set_character_set() function.


## mysql_get_client_info()

```js
var version = db.mysql_get_client_info()
```
Description

Returns a string that represents the MySQL client library version; for example, "5.7.18".

Return Values

A character string that represents the MySQL client library version.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-get-client-info.html

## mysql_get_client_version()

```js
var version =  db.mysql_get_client_version()
```
Description

Returns an integer that represents the MySQL client library version. The value has the format XYYZZ where X is the major version, YY is the release level (or minor version), and ZZ is the sub-version within the release level:

For example, "5.7.18" is returned as 50718.

Return Values

An integer that represents the MySQL client library version.

## mysql_get_host_info()

```js
var host = db.mysql_get_host_info();
```

Description

Returns a string describing the type of connection in use, including the server host name.

Return Values

A character string representing the server host name and the connection type.

## mysql_get_proto_info()

```js
var proto_info =  db.mysql_get_proto_info();
```

Description

Returns the protocol version used by current connection.

Return Values

An unsigned integer representing the protocol version used by the current connection.


## mysql_get_server_info()

```js
var server = db.mysql_get_server_info();
```

Description

Returns a string that represents the MySQL server version; for example, "5.7.18".

Return Values

A character string that represents the MySQL server version.


## mysql_get_server_version()

```js
var server_v = db.mysql_get_server_version();
```

Description

Returns an integer that represents the MySQL server version. The value has the format XYYZZ where X is the major version, YY is the release level (or minor version), and ZZ is the sub-version within the release level:

For example, "5.7.18" is returned as 50718.

This function is useful in client programs for determining whether some version-specific server capability exists.

Return Values

An integer that represents the MySQL server version

## mysql_get_ssl_cipher()

```js
var chiper = db.mysql_get_ssl_cipher();
```

Description

mysql_get_ssl_cipher() returns the encryption cipher used for the given connection to the server. mysql is the connection handler returned from mysql_init().

Return Values

A string naming the encryption cipher used for the connection, or NULL if no cipher is being used.

## mysql_info()

```js
var info = db.mysql_info();
```

Description

Retrieves a string providing information about the most recently executed statement, but only for the statements listed here. For other statements, mysql_info() returns NULL. The format of the string varies depending on the type of statement, as described here. The numbers are illustrative only; the string contains values appropriate for the statement.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-info.html

## mysql_insert_id()

```js
db.mysql_real_query(INSERT INTO pet (name) VALUE ('dog'));
var insert_ID =  db.mysql_insert_id);
```

Description

Returns the value generated for an AUTO_INCREMENT column by the previous INSERT or UPDATE statement. Use this function after you have performed an INSERT statement into a table that contains an AUTO_INCREMENT field, or have used INSERT or UPDATE to set a column value with LAST_INSERT_ID(expr).


See https://dev.mysql.com/doc/refman/5.7/en/mysql-insert-id.html

## mysql_num_fields()

```js
var fields =  db.mysql_num_fields();
```

Description

Returns the number of columns in a result set.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-num-fields.html

## mysql_ping()

```js
var ping  = db.mysql_ping()
```

Description

Checks whether the connection to the server is working. If the connection has gone down and auto-reconnect is enabled an attempt to reconnect is made. If the connection is down and auto-reconnect is disabled, mysql_ping() returns an error.

Auto-reconnect is disabled by default. To enable it, call mysql_options() with the MYSQL_OPT_RECONNECT option

Return Values

True if the connection to the server is active. False if an error occurred. A False return does not indicate whether the MySQL server itself is down; the connection might be broken for other reasons such as network problems.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-ping.html

## mysql_query()

```js

 db.mysql_query(stmt_str);
 
```
Description

Executes the SQL statement pointed to by the null-terminated string stmt_str. Normally, the string must consist of a single SQL statement without a terminating semicolon (;) or \g. If multiple-statement execution has been enabled, the string can contain several statements separated by semicolons. 
mysql_query() cannot be used for statements that contain binary data; you must use mysql_real_query() instead. (Binary data may contain the \0 character, which mysql_query() interprets as the end of the statement string.)


## mysql_real_escape_string()

```js
var str =  db.mysql_real_escape_string(str);
```

Description

This function creates a legal SQL string for use in an SQL statement
The mysql argument must be a valid, open connection because character escaping depends on the character set in use by the server.

see https://dev.mysql.com/doc/refman/5.7/en/mysql-real-escape-string.html

## mysql_real_query()

```js 
db.mysql_real_query(stmt_str);
```
Description

Executes the SQL statement pointed to by stmt_str, a string length bytes long. Normally, the string must consist of a single SQL statement without a terminating semicolon (;) or \g. If multiple-statement execution has been enabled, the string can contain several statements separated by semicolons

See https://dev.mysql.com/doc/refman/5.7/en/mysql-real-query.html

## mysql_reload()

```js
db.mysql_reload();
```

Description

Asks the MySQL server to reload the grant tables. The connected user must have the RELOAD privilege.

This function is deprecated. It is preferable to use mysql_query() to issue an SQL FLUSH PRIVILEGES statement instead.

Return Values

True for success. False if an error occurred.

## mysql_reset_connection()

```js
db.mysql_reset_connection()
```
Description

Resets the connection to clear the session state. This function was added in MySQL 5.7.3.

mysql_reset_connection() has effects similar to mysql_change_user() or an auto-reconnect except that the connection is not closed and reopened, and reauthentication is not done. 

The connection-related state is affected as follows:

- Any active transactions are rolled back and autocommit mode is reset.
- All table locks are released.
- All TEMPORARY tables are closed (and dropped).
- Session system variables are reinitialized to the values of the corresponding global system variables, including system variables that are set implicitly by statements such as SET NAMES.
- User variable settings are lost.
- Prepared statements are released.
- HANDLER variables are closed.
- The value of LAST_INSERT_ID() is reset to 0.
- Locks acquired with GET_LOCK() are released.

Return Values

True for success. False if an error occurred.

## mysql_rollback()

```js
 ........................
 
db.mysql_autocommit(0);   // set autocommit to false
 
db.mysql_query(my, "TRUNCATE TABLE `collection`;");
db.mysql_query(my, "INSERT INTO `test`.`collection`"
	        " (`id`, `name`, `title`, `published`)"
		" VALUES (NULL, 'Debian', 'Debian 4.0', '2011-02-14');");
db.mysql_query(my, "SELECT * from collection WHERE 1;");
 
if (db.mysql_affected_rows(my) >= 1) {
   db.mysql_rollback(my);
}
else {
   db.mysql_commit(my);
}

..........
```

Description

Rolls back the current transaction.

Return Values

True for success. False if an error occurred.

## mysql_sqlstate()

```js
var state = db.mysql_sqlstate();
```

Description

Returns a null-terminated string containing the SQLSTATE error code for the most recently executed SQL statement. The error code consists of five characters. '00000' means “no error.” The values are specified by ANSI SQL and ODBC. For a list of possible values

See https://dev.mysql.com/doc/refman/5.7/en/mysql-sqlstate.html

## mysql_ssl_set()

```js
db.mysql_ssl_set(key,cert,ca,capath,cipher);
```
Description

mysql_ssl_set() is used for establishing secure connections using SSL. It must be called before mysql_real_connect().
mysql_ssl_set() does nothing unless SSL support is enabled in the client library.

- `key`: The path name to the key file
- `cert`: The path name to the certificate file
- `ca`: The path name to the certificate authority file
- `capath`: The path name to a directory that contains trusted SSL CA certificates in PEM format
- `cipher`: A list of permissible ciphers to use for SSL encryption

Return Values

This function returns true. If SSL setup is incorrect return false, mysql_real_connect() returns an error when you attempt to connect.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-ssl-set.html

## mysql_stat()

db.mysql_stat();

Description

Returns a character string containing information similar to that provided by the mysqladmin status command. This includes uptime in seconds and the number of running threads, questions, reloads, and open tables.

Return Values

A character string describing the server status. 

## mysql_store_result()

```js
db.mysql_store_result();
```

Description

After invoking mysql_query() or mysql_real_query(), you must call mysql_store_result() or mysql_use_result() for every statement that successfully produces a result set (SELECT, SHOW, DESCRIBE, EXPLAIN, CHECK TABLE, and so forth). You must also call mysql_free_result() after you are done with the result set.

You need not call mysql_store_result() or mysql_use_result() for other statements, but it does not do any harm or cause any notable performance degradation if you call mysql_store_result() in all cases. You can detect whether the statement has a result set by checking whether mysql_store_result() returns a nonzero value (more about this later).

Return Values

If success retrun nothing if result set NULL it return Mysql Error message or Mysql affected rows 

## mysql_use_result()

```js
db.mysql_use_result();
```

Description

After invoking mysql_query() or mysql_real_query(), you must call mysql_store_result() or mysql_use_result() for every statement that successfully produces a result set (SELECT, SHOW, DESCRIBE, EXPLAIN, CHECK TABLE, and so forth). You must also call mysql_free_result() after you are done with the result set.

mysql_use_result() initiates a result set retrieval but does not actually read the result set into the client like mysql_store_result() does. Instead, each row must be retrieved individually by making calls to mysql_fetch_row(). This reads the result of a query directly from the server without storing it in a temporary table or local buffer, which is somewhat faster and uses much less memory than mysql_store_result(). The client allocates memory only for the current row and a communication buffer that may grow up to max_allowed_packet bytes.

On the other hand, you should not use mysql_use_result() for locking reads if you are doing a lot of processing for each row on the client side, or if the output is sent to a screen on which the user may type a ^S (stop scroll). This ties up the server and prevent other threads from updating any tables from which the data is being fetched.

Return Values

True if not NULL. False if an error occurred.

See https://dev.mysql.com/doc/refman/5.7/en/mysql-use-result.html

## mysql_warning_count()

```js
db.mysql_warning_count();
```

Description

Returns the number of errors, warnings, and notes generated during execution of the previous SQL statement.

Return Values

The warning count.

## Connection Flags

The value of client_flag is usually 0, but can be set to a combination of the following flags to enable certain features.

| Flag Name           | Flag Description                                                                                               |
  ------------------- | ----------------------------------------------------------------------------------------------------------------
| 32 `CLIENT_COMPRESS`| Use compression in the client/server protocol.    							       |
| 2 `CLIENT_FOUND_ROWS`|Return the number of found (matched) rows, not the number of changed rows.                                     |
| 4096 `CLIENT_IGNORE_SIGPIPE`|	Prevents the client library from installing a SIGPIPE signal handler. This can be used to avoid 					conflicts with a handler that the application has already installed.     			       |
| 256 `CLIENT_IGNORE_SPACE`|	Permit spaces after function names. Makes all functions names reserved words.			       |
| 1024 `CLIENT_INTERACTIVE`|	Permit interactive_timeout seconds of inactivity (rather than wait_timeout seconds) before closing the 					connection. The client's session wait_timeout variable is set to the value of the session 					    	interactive_timeout variable.
| 128 `CLIENT_LOCAL_FILES` |	Enable LOAD DATA LOCAL handling.
| 171 `CLIENT_MULTI_RESULTS`| 	Tell the server that the client can handle multiple result sets from multiple-statement executions or 					stored procedures. This flag is automatically enabled if CLIENT_MULTI_STATEMENTS is enabled. See the 					note following this table for more information about this flag.
| 161 `CLIENT_MULTI_STATEMENTS`|Tell the server that the client may send multiple statements in a single string (separated by ; 					characters). If this flag is not set, multiple-statement execution is disabled. See the note following 					this table for more information about this flag.
| 16 `CLIENT_NO_SCHEMA`       |Do not permit db_name.tbl_name.col_name syntax. This is for ODBC. It causes the parser to generate an 					error if you use that syntax, which is useful for trapping bugs in some ODBC programs.
| 64 `CLIENT_ODBC` |		Unused.
| 2048 `CLIENT_SSL` |		Use SSL (encrypted protocol). Do not set this option within an application program; it is set internally 				in the client library. Instead, use mysql_ssl_set() before calling mysql_real_connect().
| 311 `CLIENT_REMEMBER_OPTIONS` |Remember options specified by calls to mysql_options(). Without this option, if mysql_real_connect() 					fails, you must repeat the mysql_options() calls before trying to connect again. With this option, the 					mysql_options() calls need not be repeated.

## Multiple Statement Execution

By default, mysql_query() and mysql_real_query() interpret their statement string argument as a single statement to be executed, and you process the result according to whether the statement produces a result set (a set of rows, as for SELECT) or an affected-rows count (as for INSERT, UPDATE, and so forth).

MySQL also supports the execution of a string containing multiple statements separated by semicolon (;) characters. This capability is enabled by special options that are specified either when you connect to the server with mysql_real_connect() or after connecting by calling` mysql_set_server_option().

To enable multiple-statement execution and result processing, the following options may be used:

- The mysql_real_connect() function has a flags argument for which two option values are relevant:

  -`171`(CLIENT_MULTI_RESULTS) enables the client program to process multiple results. This option must be enabled if you execute CALL   statements for stored procedures that produce result sets. Otherwise, such procedures result in an error Error 1312 (0A000): PROCEDURE proc_name can't return a result set in the given context. In MySQL 5.7, CLIENT_MULTI_RESULTS is enabled by default.
 	
  -`161` (CLIENT_MULTI_STATEMENTS) enables mysql_query() and mysql_real_query() to execute statement strings containing multiple statements separ1ated by semicolons. This option also enables CLIENT_MULTI_RESULTS implicitly, so a flags argument of CLIENT_MULTI_STATEMENTS to mysql_real_connect() is equivalent to an argument of [171,161]. That is, [161] is sufficient to enable multiple-statement execution and all multiple-result processing.

```js

var mysql = require("nodemysql");

var db = mysql.connect({
    host: "127.0.0.1",
    username: "username",
    password: "",
    database: "test",
    flag: [161]
})

db.mysql_real_query("SELECT * FROM pet WHERE name = 'PEACOCK';\  INSERT INTO pet (name,owner) VALUE ('PEACOCK','zuckerburk')");

var result = db.mysql_multiple_statement();
console.log(result);

result Will be  -------------------------------------------------------------------------------------

[ RESULT: [ { name: 'DOG',
      owner: 'NULL',
      species: 'NULL',
      sex: 'NULL',
      birth: 'NULL',
      death: 'NULL' },
    { name: 'DOG',
      owner: 'NULL',
      species: 'NULL',
      sex: 'NULL',
      birth: 'NULL',
      death: 'NULL' },
    { name: 'DOG',
      owner: 'NULL',
      species: 'NULL',
      sex: 'NULL',
      birth: 'NULL',
      death: 'NULL' } ],
  AFFECTED_ROWS: 1 ]

```

