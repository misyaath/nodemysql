#include <stdio.h>
#include <vector>
#include <limits>
#include <mysql.h>
#include <node.h>
#include "common.h"


namespace NodeSql {

	using v8::Context;
	using v8::Function;
	using v8::FunctionCallbackInfo;
	using v8::FunctionTemplate;
	using v8::Isolate;
	using v8::Local;
	using v8::Number;
	using v8::Object;
	using v8::Persistent;
	using v8::String;
	using v8::Value;
	using v8::Array;

	Persistent<Function> NodeMysql::constructor;
	NodeMysql *NodeMysql::instance;


	NodeMysql::NodeMysql(std::string host_name, std::string user_name, std::string password, std::string db_name,
		unsigned int port_num, std::string socket_name, unsigned int flags) :
		host_name(host_name), user_name(user_name), password(password), db_name(db_name), port_num(port_num), socket_name(socket_name), flags(flags)
	{
	}

	NodeMysql::~NodeMysql()
	{
	}


	void NodeMysql::Init(Isolate *isolate) {

		Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate, New);
		tpl->SetClassName(String::NewFromUtf8(isolate, "NodeMysql"));
		tpl->InstanceTemplate()->SetInternalFieldCount(1);

		// Prototype
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_real_connect", do_connect);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_close", do_disconnect);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_query", do_mysqlQuery);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_store_result", do_mysql_store_Result);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_free_result", do_mysql_free_result);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_fetch_row", do_mysql_fetch_row);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_affected_rows", do_mysql_affected_rows);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_character_set_name", do_mysql_character_set_name);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_commit", do_mysql_commit);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_data_seek", do_mysql_data_seek);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_debug", do_mysql_debug);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_dump_debug_info", do_mysql_dump_debug_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_errno", do_mysql_errno);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_error", do_mysql_error);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_fetch_field", do_mysql_fetch_field);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_fetch_field_direct", do_mysql_fetch_field_direct);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_fetch_fields", do_mysql_fetch_fields);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_field_count", do_mysql_field_count);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_character_set_info", do_mysql_get_character_set_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_client_info", do_mysql_get_client_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_client_version", do_mysql_get_client_version);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_host_info", do_mysql_get_host_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_proto_info", do_mysql_get_proto_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_server_info", do_mysql_get_server_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_get_ssl_cipher", do_mysql_get_ssl_cipher);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_info", do_mysql_info);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_insert_id", do_mysql_insert_id);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_more_results", do_mysql_more_results);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_num_fields", do_mysql_num_fields);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_num_rows", do_mysql_num_rows);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_real_query", do_mysql_real_query);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_reload", do_mysql_reload);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_reset_connection", do_mysql_reset_connection);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_rollback", do_mysql_rollback);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_select_db", do_mysql_select_db);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_set_local_infile_default", do_mysql_set_local_infile_default);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_sqlstate", do_mysql_sqlstate);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_ssl_set", do_mysql_ssl_set);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_stat", do_mysql_stat);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_use_result", do_mysql_use_result);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_warning_count", do_mysql_warning_count);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_change_user", do_mysql_change_user);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_fetch_lengths", do_mysql_fetch_lengths);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_autocommit", do_mysql_autocommit);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_real_escape_string", do_mysql_real_escape_string);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_ping", do_mysql_ping);
		NODE_SET_PROTOTYPE_METHOD(tpl, "mysql_multiple_statement", do_mysql_multiple_statement);
		constructor.Reset(isolate, tpl->GetFunction());
	}

	void NodeMysql::New(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();


		std::string host = std::string(*v8::String::Utf8Value(args[0]->ToString()));
		std::string username = std::string(*v8::String::Utf8Value(args[1]->ToString()));
		std::string password = std::string(*v8::String::Utf8Value(args[2]->ToString()));
		std::string database = std::string(*v8::String::Utf8Value(args[3]->ToString()));
		unsigned int port;
		std::string socket_name;
		unsigned int flags;

		if (args[5]->IsUndefined()) {
			socket_name = "tcp";
		}
		else {
			socket_name = std::string(*v8::String::Utf8Value(args[5]->ToString()));
		}

		if (args[4]->IsUndefined()) {
			port = 3306;
		}
		else {
			port = (unsigned int)args[4]->IntegerValue();
		}

		if (args[6]->IsUndefined()) {
			flags = 0;
		}
		else {
			Local<Array> arr = Local<Array>::Cast(args[6]);
			flags = NodeMysql::instance->get_flag(arr);
		}



		if (args.IsConstructCall()) {

			NodeMysql* obj = new NodeMysql(host, username, password, database, port, socket_name, flags);
			obj->Wrap(args.This());
			args.GetReturnValue().Set(args.This());
		}
		else {

			const unsigned argc = 7;
			Local<Value> argv[argc] = { args[0],args[1],args[2],args[3],args[4],args[5],args[6] };
			Local<Function> cons = Local<Function>::New(isolate, constructor);
			Local<Context> context = isolate->GetCurrentContext();
			Local<Object> instance =
				cons->NewInstance(context, argc, argv).ToLocalChecked();
			args.GetReturnValue().Set(instance);
		}
	}

	unsigned int NodeMysql::get_flag(Local<Array> arr) {
		int length = arr->Length();
		unsigned int return_val = 0;

		if (length > 1) {
			Local<Value> flag = arr->Get(0);
			return_val = NodeMysql::instance->get_option(flag->NumberValue());

		}
		else {
			for (int i = 0; i < length; i++)
			{
				Local<Value> flag = arr->Get(i);
				unsigned int flag_val = NodeMysql::instance->get_option(flag->NumberValue());
				return_val += flag_val;
			}
		}
		return return_val;
	}

	unsigned int NodeMysql::get_option(int flag) {

		switch (flag)
		{
		case 32:
			return CLIENT_COMPRESS;
		case 2:
			return CLIENT_FOUND_ROWS;
		case 4096:
			return CLIENT_IGNORE_SIGPIPE;
		case 256:
			return CLIENT_IGNORE_SPACE;
		case 1024:
			return CLIENT_INTERACTIVE;
		case 128:
			return CLIENT_LOCAL_FILES;
		case 171:
			return CLIENT_MULTI_RESULTS;
		case 161:
			return CLIENT_MULTI_STATEMENTS;
		case 16:
			return CLIENT_NO_SCHEMA;
		case 64:
			return CLIENT_ODBC;
		case 2048:
			return CLIENT_SSL;
		case 311:
			return CLIENT_REMEMBER_OPTIONS;
		default:
			return 0;
			break;
		}
	}

	void NodeMysql::NewInstance(const FunctionCallbackInfo<Value>& args) {
		Isolate* isolate = args.GetIsolate();



		const unsigned argc = 7;
		Local<Value> argv[argc] = { args[0],args[1],args[2],args[3],args[4],args[5],args[6] };
		Local<Function> cons = Local<Function>::New(isolate, constructor);
		Local<Context> context = isolate->GetCurrentContext();
		Local<Object> instance =
			cons->NewInstance(context, argc, argv).ToLocalChecked();

		args.GetReturnValue().Set(instance);
	}


	std::string NodeMysql::get_mysql_Error(MYSQL *conn) {

		unsigned int err_no = mysql_errno(conn);
		std::string error_no = std::to_string(err_no);
		std::string error = mysql_error(conn);
		std::string errors = "Mysql Error No: " + error_no + "  Mysql Error: " + error;

		return errors;
	}

	std::vector<std::string>  NodeMysql::get_result_set_fileds() {

		MYSQL_RES *res_set = NodeMysql::instance->res_set;
		MYSQL_FIELD *fields;
		unsigned int num_fields = mysql_num_fields(res_set);
		std::string *field_name = new std::string[num_fields];
		unsigned int i = 0;

		std::vector<std::string> ve_str(num_fields);

		while ((fields = mysql_fetch_field(res_set)))
		{
			ve_str[i] = fields->name;
			std::string s = fields->name;
			field_name[i] = s.c_str();
			i++;
		}

		return ve_str;

	}

	void NodeMysql::do_connect(const FunctionCallbackInfo<Value>& args)
	{
		Isolate *isolate = args.GetIsolate();
		NodeMysql::instance = ObjectWrap::Unwrap<NodeMysql>(args.Holder());

		MYSQL *conn;
		conn = mysql_init(NULL);

		if (conn == NULL)
		{

			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "mysql_init() failed(probably out of memory)")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}


		if (MYSQL_VERSION_ID && MYSQL_VERSION_ID >= 32200) {


			if (mysql_real_connect(conn, instance->host_name.c_str(),
				instance->user_name.c_str(),
				instance->password.c_str(),
				instance->db_name.c_str(), instance->port_num, instance->socket_name.c_str(), instance->flags) == NULL)
			{
				isolate->ThrowException(Exception::TypeError(
					String::NewFromUtf8(isolate, get_mysql_Error(conn).c_str())));
				args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
				return;
			}

		}
		else {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Your Mysql Verrsion must be higher than 3.22")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;

		}
		NodeMysql::instance->connection = conn;
		args.GetReturnValue().Set(v8::Boolean::New(isolate, TRUE));
	}

	void NodeMysql::do_mysqlQuery(const FunctionCallbackInfo<Value>& args) {
		Isolate *isolate = args.GetIsolate();

		if (args.Length() < 1 || args[0]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "You must enter Mysql Query")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}

		std::string query = std::string(*v8::String::Utf8Value(args[0]->ToString()));

		if (mysql_query(NodeMysql::instance->connection, query.c_str()) != 0) {
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}
	}

	void NodeMysql::do_mysql_store_Result(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();

		MYSQL_RES *res_set = mysql_store_result(NodeMysql::instance->connection);

		if (res_set == NULL)
		{
			if (mysql_errno(NodeMysql::instance->connection) != 0) {

				isolate->ThrowException(Exception::TypeError(
					String::NewFromUtf8(isolate, get_mysql_Error(NodeMysql::instance->connection).c_str())));
				args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));

			}
			else {
				std::string  message = "  rows affected";
				std::string conc = std::to_string((unsigned long)mysql_affected_rows(NodeMysql::instance->connection)) + message;
				args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, conc.c_str()));
			}
		}
		else
		{
			NodeMysql::instance->res_set = res_set;
		}
	}

	void NodeMysql::do_mysql_fetch_row(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();


		Local<Array> arra = NodeMysql::instance->get_mysql_fetch_data(isolate);

		if (mysql_errno(NodeMysql::instance->connection) != 0) {
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}


		args.GetReturnValue().Set(arra);

	}

	void NodeMysql::do_mysql_fetch_lengths(const FunctionCallbackInfo<Value> &args) {
		args.GetReturnValue().Set(NodeMysql::instance->fetch_lengths);
	}

	v8::Local<v8::Array> NodeMysql::get_mysql_fetch_data(Isolate *isolate) {
		MYSQL_ROW row;
		MYSQL_RES *res_set = NodeMysql::instance->res_set;
		unsigned int i, a = 0;
		my_ulonglong row_num = mysql_num_rows(res_set);
		unsigned int num_fields = mysql_num_fields(res_set);

		v8::Local<v8::Array> arra = Array::New(isolate, (int)row_num);
		NodeMysql::instance->fetch_lengths = Array::New(isolate, (int)row_num);
		v8::Local<v8::Object> obj;
		v8::Local<v8::Object> obj_fetch_length;
		unsigned long *lengths;

		std::vector<std::string> ve_str = NodeMysql::instance->get_result_set_fileds();

		while ((row = mysql_fetch_row(res_set)) != NULL) {

			lengths = mysql_fetch_lengths(res_set);
			obj = Object::New(isolate);
			obj_fetch_length = Object::New(isolate);

			for (i = 0; i < mysql_num_fields(res_set); i++) {

				std::string fieldName = std::string(ve_str[i]);

				if (lengths != NULL) {
					obj_fetch_length->Set(String::NewFromUtf8(isolate, fieldName.c_str()), Number::New(isolate, lengths[i]));
				}

				if (row[i] != NULL) {

					std::string row_str = std::string(row[i]);
					v8::Local<v8::String> row_obj = v8::String::NewFromUtf8(isolate, row_str.c_str());
					obj->Set(String::NewFromUtf8(isolate, fieldName.c_str()), row_obj);
				}
				else {
					Local<v8::String> nullStr = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "NULL");
					obj->Set(String::NewFromUtf8(isolate, fieldName.c_str()), nullStr);
				}


			}
			NodeMysql::instance->fetch_lengths->Set(a, obj_fetch_length);
			arra->Set(a, obj);
			a++;
		}
		return arra;
	}

	void NodeMysql::do_mysql_autocommit(const FunctionCallbackInfo<Value> &args) {

		double mode = args[0]->NumberValue();

		my_bool auCommit = mysql_autocommit(NodeMysql::instance->connection, (int)mode);

		if (auCommit == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}

		args.GetReturnValue().Set(FALSE);

	}

	void NodeMysql::do_mysql_real_escape_string(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		char *from = *v8::String::Utf8Value(args[0]->ToString());
		char *to = new char[(strlen(from) * 2) + 1];

		unsigned long escape = mysql_real_escape_string(NodeMysql::instance->connection, to, from, strlen(from));
		to[escape] = '\0';
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, to));
	}

	void NodeMysql::do_mysql_ping(const FunctionCallbackInfo<Value> &args) {
		int ping = mysql_ping(NodeMysql::instance->connection);

		if (ping == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);
	}

	void NodeMysql::do_mysql_affected_rows(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		unsigned long affected_rows = (unsigned long)mysql_affected_rows(NodeMysql::instance->connection);
		std::string rows_str_cpp = std::to_string(affected_rows);


		if (affected_rows == (my_ulonglong)~0) {
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, rows_str_cpp.c_str()));

	}

	void NodeMysql::do_mysql_character_set_name(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *charecterset = mysql_character_set_name(NodeMysql::instance->connection);
		std::string rows_str_cpp = std::string(charecterset);


		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, rows_str_cpp.c_str()));
	}

	void NodeMysql::do_mysql_commit(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		my_bool commit = mysql_commit(NodeMysql::instance->connection);

		if (commit != 0) {
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}
		args.GetReturnValue().Set(v8::Boolean::New(isolate, TRUE));

	}

	void NodeMysql::do_mysql_data_seek(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();
		my_ulonglong row_number;

		if (args.Length() < 1) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "You Must enter rows Number")));
		}
		if (args[0]->IsUndefined()) {

			row_number = 0;
		}
		else {
			row_number = args[0]->NumberValue();
		}

		mysql_data_seek(NodeMysql::instance->res_set, row_number);
	}

	void NodeMysql::do_mysql_debug(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();

		if (args.Length() < 1) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "You Must enter rows Number")));
		}
		std::string debugStr = std::string(*v8::String::Utf8Value(args[0]->ToString()));

		mysql_debug(debugStr.c_str());
	}

	void NodeMysql::do_mysql_dump_debug_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		int debufInfo = mysql_dump_debug_info(NodeMysql::instance->connection);

		if (debufInfo != 0) {
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}
		args.GetReturnValue().Set(v8::Boolean::New(isolate, TRUE));
	}

	void NodeMysql::do_mysql_errno(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		unsigned int error_num = mysql_errno(NodeMysql::instance->connection);
		args.GetReturnValue().Set(v8::Number::New(isolate, error_num));
	}

	void NodeMysql::do_mysql_error(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *error = mysql_error(NodeMysql::instance->connection);

		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, error));

	}
	void NodeMysql::do_mysql_fetch_field(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		MYSQL_FIELD *field;
		unsigned int num_fields = mysql_num_fields(NodeMysql::instance->res_set);
		v8::Local<v8::Object> obj;
		v8::Local<v8::Array> array = Array::New(isolate, num_fields);
		unsigned int i = 0;

		while ((field = mysql_fetch_field(NodeMysql::instance->res_set)) != NULL)
		{
			obj = Object::New(isolate);
			obj = NodeMysql::instance->do_fetch_field_object(field, isolate);
			array->Set(i, obj);
			i++;

		}

		args.GetReturnValue().Set(array);
	}

	void NodeMysql::do_mysql_fetch_field_direct(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		MYSQL_FIELD *field;
		v8::Local<v8::Object> obj = Object::New(isolate);

		if (args.Length() < 1) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "You Must enter field number")));
		}

		unsigned int fieldnr = args[0]->NumberValue();
		field = mysql_fetch_field_direct(NodeMysql::instance->res_set, fieldnr);
		obj = NodeMysql::instance->do_fetch_field_object(field, isolate);
		args.GetReturnValue().Set(obj);
	}

	void NodeMysql::do_mysql_fetch_fields(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		MYSQL_FIELD *fields;
		v8::Local<v8::Object> obj = Object::New(isolate);
		unsigned int num_fields;
		unsigned int i;

		num_fields = mysql_num_fields(NodeMysql::instance->res_set);
		fields = mysql_fetch_fields(NodeMysql::instance->res_set);

		for (i = 0; i < num_fields; i++)
		{
			MYSQL_FIELD *field = &fields[i];
			obj = NodeMysql::instance->do_fetch_field_object(field, isolate);
		}

		args.GetReturnValue().Set(obj);
	}

	void NodeMysql::do_mysql_field_count(const FunctionCallbackInfo<Value> &args) {

		unsigned int count = mysql_field_count(NodeMysql::instance->connection);
		args.GetReturnValue().Set(count);
	}

	void NodeMysql::do_mysql_get_character_set_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		MY_CHARSET_INFO cs;
		mysql_get_character_set_info(NodeMysql::instance->connection, &cs);
		v8::Local<v8::Object> obj = Object::New(isolate);

		if (cs.number)
			obj->Set(String::NewFromUtf8(isolate, "number"), Number::New(isolate, cs.number));
		if (cs.name)
			obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, cs.name));
		if (cs.csname)
			obj->Set(String::NewFromUtf8(isolate, "csname"), String::NewFromUtf8(isolate, cs.csname));
		if (cs.comment)
			obj->Set(String::NewFromUtf8(isolate, "comment"), String::NewFromUtf8(isolate, cs.comment));
		if (cs.dir)
			obj->Set(String::NewFromUtf8(isolate, "dir"), String::NewFromUtf8(isolate, cs.dir));
		if (cs.mbminlen)
			obj->Set(String::NewFromUtf8(isolate, "mbminlen"), Number::New(isolate, cs.mbminlen));
		if (cs.mbmaxlen)
			obj->Set(String::NewFromUtf8(isolate, "mbmaxlen"), Number::New(isolate, cs.mbmaxlen));

		args.GetReturnValue().Set(obj);

	}

	void NodeMysql::do_mysql_get_client_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *client_info = mysql_get_client_info();
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, client_info));
	}

	void NodeMysql::do_mysql_get_client_version(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		unsigned int client_info = mysql_get_client_version();
		args.GetReturnValue().Set(client_info);
	}

	void NodeMysql::do_mysql_get_host_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *client_info = mysql_get_host_info(NodeMysql::instance->connection);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, client_info));
	}

	void NodeMysql::do_mysql_get_server_version(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		unsigned long client_version = mysql_get_server_version(NodeMysql::instance->connection);
		args.GetReturnValue().Set(Number::New(isolate, client_version));
	}

	void NodeMysql::do_mysql_get_proto_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		unsigned int proto_info = mysql_get_proto_info(NodeMysql::instance->connection);
		args.GetReturnValue().Set(proto_info);
	}

	void NodeMysql::do_mysql_get_server_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *server_info = mysql_get_server_info(NodeMysql::instance->connection);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, server_info));
	}

	void NodeMysql::do_mysql_get_ssl_cipher(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *ssl_chiper = mysql_get_ssl_cipher(NodeMysql::instance->connection);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, ssl_chiper));
	}

	void NodeMysql::do_mysql_info(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *sql_info = mysql_info(NodeMysql::instance->connection);

		if (sql_info == NULL) {
			args.GetReturnValue().Set(String::NewFromUtf8(isolate, "NULL"));
			return;
		}

		args.GetReturnValue().Set(String::NewFromUtf8(isolate, sql_info));
	}

	void NodeMysql::do_mysql_insert_id(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();

		my_ulonglong inserted_id = mysql_insert_id(NodeMysql::instance->connection);
		args.GetReturnValue().Set(v8::Uint32::New(isolate, inserted_id));
	}

	void NodeMysql::do_mysql_more_results(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();

		my_bool moreResult = mysql_more_results(NodeMysql::instance->connection);

		if (moreResult == 1) {
			args.GetReturnValue().Set(TRUE);
		}
		else {
			args.GetReturnValue().Set(FALSE);
		}


	}

	void NodeMysql::do_mysql_real_query(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();

		if (args.Length() < 1 || args[0]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "You must enter Mysql Query")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}

		std::string query = std::string(*v8::String::Utf8Value(args[0]->ToString()));
		int res = mysql_real_query(NodeMysql::instance->connection, query.c_str(), strlen(query.c_str()));

		if (res == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);
	}

	void NodeMysql::do_mysql_multiple_statement(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();
		MYSQL_RES *result;
		Local<Array> multiple_result = Array::New(isolate);
		unsigned int a = 0;
		int status;

		do {
			NodeMysql::instance->res_set = mysql_store_result(NodeMysql::instance->connection);

			if (NodeMysql::instance->res_set)
			{

				Local<Array> select_Res = NodeMysql::instance->get_mysql_fetch_data(isolate);
				multiple_result->Set(String::NewFromUtf8(isolate, "RESULT"), select_Res);
				mysql_free_result(NodeMysql::instance->res_set);
			}
			else
			{
				if (mysql_field_count(NodeMysql::instance->connection) == 0)
				{
					my_ulonglong affected_row = mysql_affected_rows(NodeMysql::instance->connection);
					multiple_result->Set(String::NewFromUtf8(isolate, "AFFECTED_ROWS"), Number::New(isolate, affected_row));
				}
				else
				{
					args.GetReturnValue().Set(String::NewFromUtf8(isolate, "COULD_NOT_RETRIEVE_RESULT_SET"));
					break;
				}
			}
			status = mysql_next_result(NodeMysql::instance->connection);
			a++;
		} while (status == 0);

		args.GetReturnValue().Set(multiple_result);
	}

	void NodeMysql::do_mysql_num_fields(const FunctionCallbackInfo<Value> &args) {
		unsigned int numFields = mysql_num_fields(NodeMysql::instance->res_set);
		args.GetReturnValue().Set(numFields);
	}

	void NodeMysql::do_mysql_num_rows(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();

		my_ulonglong numRows = mysql_num_rows(NodeMysql::instance->res_set);
		args.GetReturnValue().Set(v8::Uint32::New(isolate, numRows));
	}

	void NodeMysql::do_mysql_reload(const FunctionCallbackInfo<Value> &args) {
		int relode = mysql_reload(NodeMysql::instance->connection);

		if (relode == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);
	}


	void NodeMysql::do_mysql_rollback(const FunctionCallbackInfo<Value> &args) {
		int relode = mysql_rollback(NodeMysql::instance->connection);

		if (relode == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);
	}
	void NodeMysql::do_mysql_select_db(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();

		if (args.Length() < 1 || args[0]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "You must add Database name")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}


		std::string db = std::string(*v8::String::Utf8Value(args[0]->ToString()));
		int sDb = mysql_select_db(NodeMysql::instance->connection, db.c_str());

		if (sDb == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);


	}

	void NodeMysql::do_mysql_reset_connection(const FunctionCallbackInfo<Value> &args) {
		int relode = mysql_reset_connection(NodeMysql::instance->connection);

		if (relode == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);
	}

	void NodeMysql::do_mysql_set_local_infile_default(const FunctionCallbackInfo<Value> &args) {
		mysql_set_local_infile_default(NodeMysql::instance->connection);
	}
	void NodeMysql::do_mysql_sqlstate(const FunctionCallbackInfo<Value> &args) {

		Isolate *isolate = args.GetIsolate();

		const char *state = mysql_sqlstate(NodeMysql::instance->connection);
		args.GetReturnValue().Set(String::NewFromUtf8(isolate, state));

	}
	void NodeMysql::do_mysql_ssl_set(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();

		if (args.Length() < 5) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Wrong Number of arguments")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}

		if (!args[0]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid path name to the key file")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		if (!args[1]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid  path name to the certificate file")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		if (!args[2]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid path name to the certificate authority file")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		if (!args[3]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid path name to a directory that contains trusted SSL CA certificates in PEM format")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		if (!args[4]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid list of permissible ciphers to use for SSL encryption")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		std::string key = std::string(*v8::String::Utf8Value(args[0]->ToString()));
		std::string cert = std::string(*v8::String::Utf8Value(args[1]->ToString()));
		std::string ca = std::string(*v8::String::Utf8Value(args[2]->ToString()));
		std::string capath = std::string(*v8::String::Utf8Value(args[3]->ToString()));
		std::string cipher = std::string(*v8::String::Utf8Value(args[4]->ToString()));

		my_bool ssl_set = mysql_ssl_set(NodeMysql::instance->connection, key.c_str()
			, cert.c_str(), ca.c_str(), capath.c_str(), cipher.c_str());


		if (ssl_set == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);

	}

	void NodeMysql::do_mysql_change_user(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();

		if (args.Length() < 3) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Wrong Number of arguments")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
			return;
		}

		if (!args[0]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid Username")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		if (!args[1]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid  Password")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		if (!args[2]->IsUndefined()) {
			isolate->ThrowException(Exception::TypeError(
				String::NewFromUtf8(isolate, "Invalid Database name")));
			args.GetReturnValue().Set(v8::Boolean::New(isolate, FALSE));
		}

		std::string username = std::string(*v8::String::Utf8Value(args[0]->ToString()));
		std::string password = std::string(*v8::String::Utf8Value(args[1]->ToString()));
		std::string database = std::string(*v8::String::Utf8Value(args[2]->ToString()));

		my_bool ssl_set = mysql_change_user(NodeMysql::instance->connection, username.c_str()
			, password.c_str(), database.c_str());


		if (ssl_set == 0) {
			args.GetReturnValue().Set(TRUE);
			return;
		}
		args.GetReturnValue().Set(FALSE);
	}

	void NodeMysql::do_mysql_stat(const FunctionCallbackInfo<Value> &args) {
		Isolate *isolate = args.GetIsolate();
		const char *stat = mysql_stat(NodeMysql::instance->connection);
		args.GetReturnValue().Set(v8::String::NewFromUtf8(isolate, stat));
	}

	void NodeMysql::do_mysql_warning_count(const FunctionCallbackInfo<Value> &args) {
		unsigned int warningCount = mysql_warning_count(NodeMysql::instance->connection);
		args.GetReturnValue().Set(warningCount);
	}

	void NodeMysql::do_mysql_use_result(const FunctionCallbackInfo<Value> &args) {

		MYSQL_RES *resSet = mysql_use_result(NodeMysql::instance->connection);

		if (resSet == NULL) {
			args.GetReturnValue().Set(FALSE);
			return;
		}

		NodeMysql::instance->res_set = resSet;

		args.GetReturnValue().Set(TRUE);
	}

	void NodeMysql::do_mysql_free_result(const FunctionCallbackInfo<Value> &args) {
		mysql_free_result(NodeMysql::instance->res_set);
	}

	void NodeMysql::do_disconnect(const FunctionCallbackInfo<Value>& args)
	{
		mysql_close(NodeMysql::instance->connection);
	}

	v8::Local<v8::Object> NodeMysql::do_fetch_field_object(MYSQL_FIELD *field, Isolate *isolate) {

		v8::Local<v8::Object> obj = Object::New(isolate);

		if (field->name) {
			obj->Set(String::NewFromUtf8(isolate, "name"), String::NewFromUtf8(isolate, field->name));
		}
		if (field->org_name) {
			obj->Set(String::NewFromUtf8(isolate, "org_name"), String::NewFromUtf8(isolate, field->org_name));
		}
		if (field->table) {
			obj->Set(String::NewFromUtf8(isolate, "table"), String::NewFromUtf8(isolate, field->table));
		}
		if (field->org_table) {
			obj->Set(String::NewFromUtf8(isolate, "org_table"), String::NewFromUtf8(isolate, field->org_table));
		}
		if (field->db) {
			obj->Set(String::NewFromUtf8(isolate, "db"), String::NewFromUtf8(isolate, field->db));
		}
		if (field->catalog) {
			obj->Set(String::NewFromUtf8(isolate, "catalog"), String::NewFromUtf8(isolate, field->catalog));
		}

		if (field->def) {
			obj->Set(String::NewFromUtf8(isolate, "def"), String::NewFromUtf8(isolate, field->def));
		}
		if (field->length) {
			obj->Set(String::NewFromUtf8(isolate, "length"), Number::New(isolate, field->length));
		}
		if (field->max_length) {
			obj->Set(String::NewFromUtf8(isolate, "max_length"), Number::New(isolate, field->max_length));
		}
		if (field->name_length) {
			obj->Set(String::NewFromUtf8(isolate, "name_length"), Number::New(isolate, field->name_length));
		}
		if (field->org_name_length) {
			obj->Set(String::NewFromUtf8(isolate, "org_name_length"), Number::New(isolate, field->org_name_length));
		}
		if (field->table_length) {
			obj->Set(String::NewFromUtf8(isolate, "table_length"), Number::New(isolate, field->table_length));
		}
		if (field->org_table_length) {
			obj->Set(String::NewFromUtf8(isolate, "org_table_length"), Number::New(isolate, field->org_table_length));
		}
		if (field->db_length) {
			obj->Set(String::NewFromUtf8(isolate, "db_length"), Number::New(isolate, field->db_length));
		}
		if (field->catalog_length) {
			obj->Set(String::NewFromUtf8(isolate, "catalog_length"), Number::New(isolate, field->catalog_length));
		}
		if (field->def_length) {
			obj->Set(String::NewFromUtf8(isolate, "def_length"), Number::New(isolate, field->def_length));
		}
		if (field->flags) {
			obj->Set(String::NewFromUtf8(isolate, "flags"), Number::New(isolate, field->flags));
		}
		if (field->decimals) {
			obj->Set(String::NewFromUtf8(isolate, "decimals"), Number::New(isolate, field->decimals));
		}
		if (field->charsetnr) {
			obj->Set(String::NewFromUtf8(isolate, "charsetnr"), Number::New(isolate, field->charsetnr));
		}
		if (field->type) {
			obj->Set(String::NewFromUtf8(isolate, "type"), Number::New(isolate, field->type));
		}

		return obj;
	}



}