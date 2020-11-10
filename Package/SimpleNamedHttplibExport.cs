using System;
using System.Runtime.InteropServices;

namespace SimpleNamedHttplibExport
{
    class SimpleNamedHttplib
    {
        public delegate void OnServerCloseDelegate(bool success);
        public delegate void RequestHandle(string request, string method, StringBuilder response, StringBuilder type);

        private const string DllPath = @"SimpleNamedHttplib.dll";

        [DllImport(DllPath)]
        static extern void _stdcall CreateClient(string client_name, string host, int port);
        [DllImport(DllPath)]
        static extern string _stdcall ClientPost(string client_name, string path, string body, string content_type);
        [DllImport(DllPath)]
        static extern string _stdcall ClientGet(string client_name, string path);
        [DllImport(DllPath)]
        static extern int _stdcall ClientCount();
        [DllImport(DllPath)]
        static extern bool _stdcall ClientContain(string client_name);
        [DllImport(DllPath)]
        static extern void _stdcall ClientRemove(string client_name);
        [DllImport(DllPath)]
        static extern void _stdcall ClientClear();
        [DllImport(DllPath)]
        static extern bool _stdcall TestServer(string host, int port);

        [DllImport(DllPath)]
        static extern void _stdcall CreateServer(string server_name, string host, int port);
        [DllImport(DllPath)]
        static extern bool _stdcall ServerListen(string server_name);
        [DllImport(DllPath)]
        static extern void _stdcall ServerStop(string server_name);
        [DllImport(DllPath)]
        static extern void _stdcall SetServerCloseDelegate(string server_name, OnServerCloseDelegate on_close);
        [DllImport(DllPath)]
        static extern int _stdcall ServerCount();
        [DllImport(DllPath)]
        static extern bool _stdcall ServerContain(string server_name);
        [DllImport(DllPath)]
        static extern bool _stdcall ServerRunning(string server_name);
        [DllImport(DllPath)]
        static extern void _stdcall ServerRemove(string server_name);
        [DllImport(DllPath)]
        static extern void _stdcall ServerClear();

        [DllImport(DllPath)]
        static extern void _stdcall ServerPost(string server_name, string pattern, RequestHandle handle);
        [DllImport(DllPath)]
        static extern void _stdcall ServerGet(string server_name, string pattern, RequestHandle handle);

        [DllImport(DllPath)]
        static extern string _stdcall Version();
        [DllImport(DllPath)]
        static extern string _stdcall LastCompileTime();
    }
}
