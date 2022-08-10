#include <iostream>
#include <vector>
#include <numeric>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	string buffer = "hello.";
	char buf[50];

	if(argc > 1)
	{
		buffer = argv[1];
	}

	WSADATA wsa_data;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2, 0), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	InetPton(AF_INET, "127.0.0.1", &addr.sin_addr.s_addr);

	addr.sin_family = AF_INET;
	addr.sin_port = htons(5555);

	connect(server, reinterpret_cast<SOCKADDR *>(&addr), sizeof(addr));
	cout << "Connected to server!" << endl;

	send(server, buffer.c_str(), buffer.length(), 0);
	cout << "Message sent!" << endl;
	vector<string>test;
	while (true)
	{
		recv(server, buf, sizeof(buf), 0);
		test.push_back(buf);
		cout << "server says: " << buf << endl;
		if (test.size() == 5)
		{
			float sum = 0;
			for (int M = 0;M < test.size() ; M++)
			{
				sum += stof(test[M]);
			}
			cout << "Average: " << sum / 5;
			cout << "Accumlate: " << accumulate(test.begin(), test.end(), 0.0);
		}
		cout<<test.size()<<endl;
	}
	
	//closesocket(server);
}
