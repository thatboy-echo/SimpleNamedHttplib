#pragma once
#ifdef _WINDLL
#define _SIMPLE_NAMED_HTTPLIB_API_ extern "C" __declspec(dllexport)
#elif defined UNIT_TEST
#define _SIMPLE_NAMED_HTTPLIB_API_
#else
#define _SIMPLE_NAMED_HTTPLIB_API_ extern "C" __declspec(dllimport)
#endif

using String = const char*;
using OutString = char*;

typedef void OnServerCloseDelegate(bool);
typedef void RequestHandle(String request, String method, OutString response, OutString type);

_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall CreateClient(String client_name, String host, int port);
_SIMPLE_NAMED_HTTPLIB_API_ String _stdcall ClientPost(String client_name, String path, String body, String content_type);
_SIMPLE_NAMED_HTTPLIB_API_ String _stdcall ClientGet(String client_name, String path);
_SIMPLE_NAMED_HTTPLIB_API_ int _stdcall ClientCount();
_SIMPLE_NAMED_HTTPLIB_API_ bool _stdcall ClientContain(String client_name);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ClientRemove(String client_name);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ClientClear();
_SIMPLE_NAMED_HTTPLIB_API_ bool _stdcall TestServer(String host, int port);

_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall CreateServer(String server_name, String host, int port);
_SIMPLE_NAMED_HTTPLIB_API_ bool _stdcall ServerListen(String server_name);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ServerStop(String server_name);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall SetServerCloseDelegate(String server_name, OnServerCloseDelegate on_close);
_SIMPLE_NAMED_HTTPLIB_API_ int _stdcall ServerCount();
_SIMPLE_NAMED_HTTPLIB_API_ bool _stdcall ServerContain(String server_name);
_SIMPLE_NAMED_HTTPLIB_API_ bool _stdcall ServerRunning(String server_name);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ServerRemove(String server_name);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ServerClear();

_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ServerPost(String server_name, String pattern, RequestHandle handle);
_SIMPLE_NAMED_HTTPLIB_API_ void _stdcall ServerGet(String server_name, String pattern, RequestHandle handle);

_SIMPLE_NAMED_HTTPLIB_API_ String _stdcall Version();
_SIMPLE_NAMED_HTTPLIB_API_ String _stdcall LastCompileTime();
#undef _SIMPLE_NAMED_HTTPLIB_API_