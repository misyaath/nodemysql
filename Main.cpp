#include <node.h>
#include <mysql.h>
#include <string>
#include "common.h"

namespace NodeSql {


	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using v8::Exception;


	
	void nodeMysqlInit(const FunctionCallbackInfo<Value>& args) {
		NodeMysql::NewInstance(args);
	}

	void InitAll(Local<Object> exports, Local<Object> module) {

		NodeMysql::Init(exports->GetIsolate());
		NODE_SET_METHOD(module, "exports", nodeMysqlInit);
	}

	NODE_MODULE(nodemysql, InitAll)

}