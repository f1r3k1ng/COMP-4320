#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/types.h>
#include <fstream>
#include <time.h>

#define PORT 4320
#define MAX 1024

//Group Members:
//Ethan Johnson
//Chase Dumbacher
//Shen Ou

using namespace std;
void SegementMessageAndSend(string, struct sockaddr_in, socklen_t, int, string, int, int);
string SumOf(string Packet);
string ReadFile(string);
string Gremlin(string, int, int);
int main(int argc, char *argv[]) {
	srand(time(0));
	string FileString = ReadFile((string)argv[2]);
	int sockftp = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in server_address;
	char buffer[MAX];
	const char* Packet;
	char* MesSeg;
	int n;
	double DamageProb = stod((string)(argv[3])) * 100;
	double LostProb = stod((string)(argv[4])) * 100;
	string Command = (string)argv[1] + " " + (string)argv[2];
    socklen_t length;

	if (sockftp == 0) {
		cout << "Socket Creation Failed" << endl;
	}
	
	memset(&server_address, 0, sizeof(server_address));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr("192.168.238.135"); 
   	server_address.sin_port = htons( PORT );
	
	length = sizeof(server_address);

	//Command Check
	if ((string)argv[1] != "PUT")
		cout << "Invalid Command" << endl;
	else 
		SegementMessageAndSend(FileString, server_address, length, sockftp, Command, DamageProb, LostProb);

	n = recvfrom(sockftp, (char*)buffer, MAX, MSG_WAITALL, (struct sockaddr*)&server_address, &length);
	buffer[n] = '\0';
	printf("Server : %s\n", buffer);
	close(sockftp);

	return 0; 
}

string ReadFile(string fileName) {
	cout << "Reading File" << endl;
	string result;
	ifstream fileStream(fileName);
	string line;
	if (fileStream.is_open() ) {
		while ( getline (fileStream, line) ) {
			result += line;
		}
		fileStream.close();
	}
	return result;
}

void SegementMessageAndSend(string Message, struct sockaddr_in server_address, socklen_t length, int sockftp, string Command, int DamageProb, int LostProb) {
	const char* Packet;
	string NullPad = "";
	string MesSeg = "";
	string Sequence = "0000";
	string SumCheck = "";
	int n;
	char buffer[MAX];

	//Sending initial packet as the command e.g GET, PUT, etc.
	//const char* CommandChar = Command.c_str();
	MesSeg = SumOf(Command).c_str() + Sequence + Command;
	Packet = MesSeg.c_str();
	Sequence = "0001";
	
	sendto(sockftp, (const char*)Packet, strlen(Packet), MSG_CONFIRM, (const struct sockaddr*)&server_address, length);
	cout << "Request sent: " << Command << endl;
	cout << Packet << endl;
	MesSeg = "";
	for(int i = 0; i < Message.length(); i++) {
		MesSeg += Message[i];

		// Every Packet is 128 total bytes max - 8 for header data. so i % 120 will segment file into packets.
		if ((i + 1) % 119 == 0 && i != 0 || i == Message.length() - 1) {
			// NullPad
			if (i == Message.length() - 1) {
				for (int x = 0; x < 119 - MesSeg.length(); x++) {
					NullPad += "0";
				}
			}

			// SumCheck
			SumCheck = SumOf(MesSeg);
			
			//Gremlin
			MesSeg = Gremlin(MesSeg, DamageProb, LostProb);
			

			MesSeg = SumCheck + Sequence + MesSeg + NullPad;
			Packet = MesSeg.c_str();
			
			if (MesSeg.substr(9, 11) == "Lost Packet") {
				cout << "Lost Packet" << endl;


			}

			else {
				sendto(sockftp, (const char*)Packet, strlen(Packet), MSG_CONFIRM, (const struct sockaddr*)&server_address, length);
				cout << Packet << endl;
			}
			if (stoi(Sequence) < 9) {
				Sequence = "000" + to_string(stoi(Sequence) + 1);
			}
			else if (stoi(Sequence) < 99) {
				Sequence = "00" + to_string(stoi(Sequence) + 1);
			}
			else if (stoi(Sequence) < 999) {
				Sequence = "0" +to_string(stoi(Sequence) +1);
			}
			else {
				Sequence = to_string(stoi(Sequence) + 1);
			}
			MesSeg = "";
		}
	}
}

string SumOf(string Packet) {
	int Sum = 0;
	for (int i = 0; i < Packet.length(); i++) {
		Sum += (int)(Packet[i]);
	}
	string result = to_string(Sum);
	if (result.length() == 5)
		return result;
	else if (result.length() == 4)
		return "0" + result;
	else if (result.length() == 3)
		return "00" + result;
	else if (result.length() == 2)
		return "000" + result;
	else if (result.length() == 1)
		return "0000" + result;
	return NULL;
}

string Gremlin(string Packet, int Damaged, int Lost) {
	int DmgRoll = rand() % 100;
	int LostRoll = rand() % 100;
	int BitIndex;
	int CorruptRoll;
	int BitNumRoll = rand() % 100;
	int BitNum = 0;

	if (BitNumRoll <= 70) {
		BitNum = 1;
	}
	if (BitNumRoll > 70 && BitNumRoll <= 90) {
		BitNum = 2;
	}
	if (BitNumRoll > 90) {
		BitNum = 3;
	}
	if(LostRoll <= Lost) {
		Packet = "Lost Packet";
	}
	else if (DmgRoll <= Damaged) {
		for (int i = 0; i < BitNum; i++) {
			BitIndex = rand() % (Packet.length());
			CorruptRoll = rand() % 126 + 32;
			Packet[BitIndex] = (char)CorruptRoll;
		}
	}
	return Packet;
}









