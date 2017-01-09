#include <stdio.h>
#include <mysql.h>
#include <string>
#include <node.h>
#include <node_object_wrap.h>

namespace NodeSql {


	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using v8::Exception;


	class NodeMysql : public node::ObjectWrap
	{
	public:

		static void Init(Isolate *isolate);
		static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);


	private:

		std::string host_name;
		std::string user_name;
		std::string password;
		std::string db_name;
		unsigned int port_num;
		std::string socket_name;
		unsigned int flags;
		MYSQL * connection;
		static v8::Persistent<v8::Function> constructor;
		static NodeMysql *instance;
		MYSQL_RES *res_set;
		MYSQL_FIELD_OFFSET *field_offset;
		v8::Local<v8::Array> fetch_lengths;

		NodeMysql(std::string host_name, std::string user_name, std::string password, std::string db_name,
			unsigned int port_num, std::string socket_name, unsigned int flags);
		~NodeMysql();
		unsigned int get_option(int flag);
		static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
		static std::string get_mysql_Error(MYSQL *conn);
		static void do_connect(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_disconnect(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysqlQuery(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_store_Result(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_free_result(const v8::FunctionCallbackInfo<v8::Value> &args);
		std::vector<std::string> get_result_set_fileds();
		static void do_mysql_fetch_row(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_affected_rows(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_character_set_name(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_commit(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_data_seek(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_debug(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_dump_debug_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_errno(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_error(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_fetch_field(const v8::FunctionCallbackInfo<v8::Value> &args);
		v8::Local<v8::Object> do_fetch_field_object(MYSQL_FIELD *field, Isolate *isolate);
		static void do_mysql_fetch_field_direct(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_fetch_fields(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_field_count(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_character_set_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_client_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_client_version(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_host_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_proto_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_server_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_server_version(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_get_ssl_cipher(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_info(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_insert_id(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_more_results(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_num_fields(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_num_rows(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_real_query(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_reload(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_reset_connection(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_rollback(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_select_db(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_set_local_infile_default(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_sqlstate(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_ssl_set(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_stat(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_use_result(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_warning_count(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_change_user(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_fetch_lengths(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_autocommit(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_real_escape_string(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_ping(const v8::FunctionCallbackInfo<v8::Value> &args);
		static void do_mysql_multiple_statement(const v8::FunctionCallbackInfo<v8::Value> &args);
		v8::Local<v8::Array> get_mysql_fetch_data(v8::Isolate *isolate);
		static unsigned int get_flag(v8::Local<v8::Array> arr);


	};



}