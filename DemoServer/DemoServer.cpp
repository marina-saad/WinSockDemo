#include <future>
#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include "DemoServer.h"

using namespace std;

int main()
{
	WSADATA wsa_data;
	SOCKADDR_IN server_addr, client_addr;

	WSAStartup(MAKEWORD(2, 2), &wsa_data);
	const auto server = socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(5555);

	::bind(server, reinterpret_cast<SOCKADDR *>(&server_addr), sizeof(server_addr));
	listen(server, 0);

	cout << "Listening for incoming connections..." << endl;

	int client_addr_size = sizeof(client_addr);

	for (;;)
	{
		SOCKET client;

		if ((client = accept(server, reinterpret_cast<SOCKADDR *>(&client_addr), &client_addr_size)) != INVALID_SOCKET)
		{
			auto fut = async(launch::async, on_client_connect, client);
		}

		const auto last_error = WSAGetLastError();
		
		if(last_error > 0)
		{
			cout << "Error: " << last_error << endl;
		}
	}
}
float toC(float F)
{
	return ((F - 32) * 5) / 9;
}
void on_client_connect(SOCKET client)
{
	char buffer[50];
	string buf = "FROM Server";
	cout << "Client connected!" << endl;
	recv(client, buffer, sizeof(buffer), 0);

	cout << "Client says: " << buffer << endl;
	ZeroMemory(buffer, sizeof(buffer));
	int Seconds = 1;
	
	while (true) {
	//	std::this_thread::sleep_for(std::chrono::seconds(60));
		// call your c++ code
		Sleep(1);
		float tempInF = ((float)rand() / (RAND_MAX + 1)) * (104 - 0 + 1) + 0;
		string tempInC = to_string( toC(tempInF));
		send(client, tempInC.c_str()+1, tempInC.length(), 0);
		Seconds++;
	}
	
	//closesocket(client);
	//cout << "Client disconnected." << endl;
}