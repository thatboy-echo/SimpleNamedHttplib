#include "pch.h"
#include <httplib.h>
#include <memory>
#include "SimpleNamedHttplib.h"

/**
 * TODO 访问DLL栈触发异常
 */


const std::string SimpleNamedHttplibVersion = R"(Simple Named Httplib v0.0.1.0)";
const std::string LastCompileTimeStamp = __TIMESTAMP__;

using ServerType = std::shared_ptr<httplib::Server>;
using ClientType = std::shared_ptr<httplib::Client>;

std::map<std::string, ServerType> ServerList;
std::map<std::string, std::function<void(bool)>> ServerCloseDelegate;
std::map<std::string, ClientType> ClientList;

void _stdcall CreateClient(String client_name, String host, int port)
{
	ClientList.insert(std::make_pair(client_name, std::make_shared<httplib::Client>(host, port)));
}

String _stdcall ClientPost(String client_name, String path, String body, String content_type)
{
	static std::string ret_body;
	if (!ClientContain(client_name))
		return "";
	auto ret = ClientList[client_name]->Post(path, body, content_type);
	if (ret)
		ret_body = ret->body;
	else
		ret_body = "";
	return ret_body.c_str();
}

String _stdcall ClientGet(String client_name, String path)
{
	static std::string ret_body;
	if (!ClientContain(client_name))
		return "";
	auto ret = ClientList[client_name]->Get(path);

	if (ret)
		ret_body = ret->body;
	else
		ret_body = "";
	return ret_body.c_str();
}

int _stdcall ClientCount()
{
	return ClientList.size();
}

bool _stdcall ClientContain(String client_name)
{
	return ClientList.find(client_name) != ClientList.end();
}

void _stdcall ClientRemove(String client_name)
{
	if (!ClientContain(client_name))
		return;
	ClientList.erase(client_name);
}

void _stdcall ClientClear()
{
	ClientList.clear();
}

bool _stdcall TestServer(String host, int port)
{
	httplib::Client client(host, port);
	return client.Get("/");
}

void _stdcall CreateServer(const String server_name, const String host, int port)
{
	ServerList.insert(std::make_pair(server_name, std::make_shared<httplib::Server>()));
	ServerList[server_name]->set_base_dir(".");
	ServerList[server_name]->bind_to_port(host, port);
}

bool _stdcall ServerListen(const String server_name)
{
	if (!ServerContain(server_name))
		return false;
	bool ret = ServerList[server_name]->listen_after_bind();
	if (ServerCloseDelegate[server_name])
		ServerCloseDelegate[server_name](ret);
	return ret;
}

void _stdcall ServerStop(String server_name)
{
	if (!ServerContain(server_name))
		return;
	ServerList[server_name]->stop();
}

void _stdcall SetServerCloseDelegate(String server_name, OnServerCloseDelegate on_close)
{
	if (!ServerContain(server_name))
		return;
	ServerCloseDelegate[server_name] = on_close;
}

int _stdcall ServerCount()
{
	return ServerList.size();
}

bool _stdcall ServerContain(String server_name)
{
	return ServerList.find(server_name) != ServerList.end();
}

bool _stdcall ServerRunning(String server_name)
{
	return ServerContain(server_name) && ServerList[server_name]->is_running();
}

void _stdcall ServerRemove(String server_name)
{
	if (!ServerContain(server_name))
		return;
	ServerList.erase(server_name);
}

void _stdcall ServerClear()
{
	ServerList.clear();
}

void handleComponent(const httplib::Request& request, httplib::Response& response, RequestHandle handle)
{
	std::string response_buff(65536, '\0');
	std::string type_buff(256, '\0');
	handle(request.body.c_str(), request.method.c_str(), const_cast<char*>(response_buff.data()), const_cast<char*>(type_buff.data()));
	response.set_content(response_buff.c_str(), type_buff.c_str());	
}

void _stdcall ServerPost(String server_name, String pattern, RequestHandle handle)
{
	if (!ServerContain(server_name))
		return;
	ServerList[server_name]->Post(pattern
		, [handle](const httplib::Request& request, httplib::Response& response)
		{handleComponent(request, response, handle); });
}

void _stdcall ServerGet(String server_name, String pattern, RequestHandle handle)
{
	if (!ServerContain(server_name))
		return;
	ServerList[server_name]->Get(pattern
		, [handle](const httplib::Request& request, httplib::Response& response)
		{handleComponent(request, response, handle); });
}

String _stdcall Version()
{
	return SimpleNamedHttplibVersion.c_str();
}

String _stdcall LastCompileTime()
{
	return LastCompileTimeStamp.c_str();
}