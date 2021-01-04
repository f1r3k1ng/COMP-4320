#include <unistd.h>
#include <fstream>
#include <list>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>

#define PORT 4320
#define MAX 1024

//Group Members:
//Ethan Johnson
//Chase Dumbacher
//Shen Ou


using namespace std;
int Checksum(string packet);

int main() {
	int sockftp = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_address, client_address;
	char buffer[MAX];
	char buf[MAX];
	char *response = "PUT successfully completed";
	int n;
	socklen_t length;
	

	if (sockftp == 0) {
		cout << "Socket Creation Failed" << endl;
	}
	
	memset(&server_address, 0, sizeof(server_address));
	memset(&client_address, 0, sizeof(client_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY; 
   	server_address.sin_port = htons( PORT );
	
	if (bind(sockftp, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
		cout << "Bind Failed" << endl;
	}	
		
	length = sizeof(client_address);
	
	int x = recvfrom(sockftp, (char *)buf, MAX, MSG_WAITALL, (struct sockaddr *)&client_address, &length);
	buf[x] = '\0';
	string a = "";
	a.assign(buf);
	string file = a.substr(13);
	cout << file << endl;

	ofstream MyFile(file);
	int increment = 1;
	
	while(true) {
		n = recvfrom(sockftp, (char *)buffer, MAX, MSG_WAITALL, (struct sockaddr *)&client_address, &length);
		buffer[n] = '\0';
		
		string message = "";
		int sequence;
		
		message.assign(buffer);
		sequence = stoi(message.substr(5, 4));
		string data = message.substr(9, 48);
		int checkSum = stoi(message.substr(0, 5));
		string mesSeg = message.substr(9, 119);
		
		
		if (sequence == increment) {
			increment++;
		}

		else {
			while (sequence != increment) {
				cout << "Sequence: " << increment << " Packet Lost" << endl;
				increment += 1;
			}
			increment++;
		}

		if (message.back() == '0') {
			size_t found = mesSeg.find('0');
			mesSeg.erase(found);
			data.erase(found);
		}

		if (checkSum == Checksum(mesSeg)) {
			cout << "Packet is not corrupted\t" << "Sequence: " << sequence << " Data: " << data  << endl;
			MyFile << mesSeg;
		}

		else {
			cout << "Packet is corrupted\t" << "Sequence: " << sequence << endl;
			MyFile << mesSeg;
		}
		
		if (message.back() == '0') {
			break;
		}

	}

	MyFile.close();
	sendto(sockftp, (const char *)response, strlen(response), MSG_CONFIRM, (const struct sockaddr *)&client_address, length);
	printf("Response Message Sent. \n");

	return 0;
}


int  Checksum(string packet) {
	int Sum = 0;
	for (int i = 0; i < packet.length(); i++) {
		Sum += (int)(packet[i]);
	}
	return Sum;
}	


