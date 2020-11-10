using System;
using System.Runtime.InteropServices;
using System.Text;

namespace SimpTestCS
{
    class Program
    {
        public delegate void OnServerCloseDelegate(bool success);
        public delegate void RequestHandle(string request, string method, StringBuilder response, StringBuilder type);

        private const string DllPath = @"E:\Visual Studio Application\SimpleNamedHttplib\x64\Release\SimpleNamedHttplib.dll";
        [DllImport(DllPath)]
        static extern void CreateClient(string client_name, string host, int port);

        [DllImport(DllPath)]
        static extern string ClientGet(string client_name, string path);
        [DllImport(DllPath)]
        static extern int ClientCount();
        [DllImport(DllPath)]


        static extern void CreateServer(string server_name, string host, int port);
        [DllImport(DllPath)]
        static extern void ServerListen(string server_name);
        [DllImport(DllPath)]
        static extern void ServerStop(string server_name);
        [DllImport(DllPath)]
        static extern void SetServerCloseDelegate(string server_name, OnServerCloseDelegate on_close);
        [DllImport(DllPath)]
        static extern int ServerCount();
        [DllImport(DllPath)]
        static extern bool ServerRunning(string server_name);
        [DllImport(DllPath)]
        static extern bool ServerPost(string server_name, string pattern, RequestHandle handle);
        [DllImport(DllPath)]
        static extern bool ServerGet(string server_name, string pattern, RequestHandle handle);
        [DllImport(DllPath)]
        static extern string Version();
        [DllImport(DllPath)]
        static extern string LastCompileTime();

        static void Main(string[] args)
        {
            Console.WriteLine(Version());
            Console.WriteLine(LastCompileTime());
            CreateServer("ser", "localhost", 8708);
            SetServerCloseDelegate("ser", (bool success) => { Console.WriteLine(success ? "yes" : "no"); });
            ServerGet("ser", "/close"
                , (string request, string method, StringBuilder response, StringBuilder type) =>
                {
                    ServerStop("ser");
                });

            ServerGet("ser", "/hi"
                , (string request, string method, StringBuilder response, StringBuilder type) =>
                {
                    response.AppendFormat(@"<title>Simple Named Httplib</title><h3>Hi! {0}</h3>", "Simple Named Httplib");
                    type.Append("text/html");
                });
            ServerGet("ser", "/"
                , (string request, string method, StringBuilder response, StringBuilder type) =>
                {
                    response.AppendFormat(@"<title>Simple Named Httplib</title><h3>Welcome! {0}</h3>", "Simple Named Httplib");
                    type.Append("text/html");
                });


            Console.WriteLine("run");
            ServerListen("ser");
        }
    }
}
