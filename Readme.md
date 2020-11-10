# Simple Named Httplib

基于[cpp-httplib](https://github.com/yhirose/cpp-httplib)Windows平台Http库，服务器和客户端均通过名字来索引，并支持自定义Get Post方法，可以添加回调/委托。



以`C#`引入创建服务器函数为例:

```c#
[DllImport(DllPath)]
static extern void CreateServer(string server_name, string host, int port);
```

创建服务器只需`CreateServer("ser", "localhost", 8708);`

添加服务器Get方法:

```c#
ServerGet("ser", "/", (string request, string method, StringBuilder response, StringBuilder type) =>
{
  response.AppendFormat(@"<title>Simple Named Httplib</title><h3>Welcome! {0}</h3>", "Simple Named Httplib");
  type.Append("text/html");
});
```

`C++`可以直接引入头文件，函数定义如下

```cpp
using String = const char*;
using OutString = char*;

typedef void OnServerCloseDelegate(bool);
typedef void RequestHandle(String request, String method, OutString response, OutString type);

void CreateClient(String client_name, String host, int port);
String ClientPost(String client_name, String path, String body, String content_type);
String ClientGet(String client_name, String path);
int ClientCount();
bool ClientContain(String client_name);
void ClientRemove(String client_name);
void ClientClear();
bool TestServer(String host, int port);

void CreateServer(String server_name, String host, int port);
bool ServerListen(String server_name);
void ServerStop(String server_name);
void SetServerCloseDelegate(String server_name, OnServerCloseDelegate on_close);
int ServerCount();
bool ServerContain(String server_name);
bool ServerRunning(String server_name);
void ServerRemove(String server_name);
void ServerClear();

void ServerPost(String server_name, String pattern, RequestHandle handle);
void ServerGet(String server_name, String pattern, RequestHandle handle);

String Version();
String LastCompileTime();
```

