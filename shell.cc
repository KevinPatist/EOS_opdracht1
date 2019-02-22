#include "shell.hh"
#include <sys/wait.h>
#include <iostream>
#include <unistd.h>  // syscall()
#include <sys/syscall.h> // SysCall nummers
#include <fcntl.h>   // O_RDONLY
#include <sys/stat.h>
#include <sys/types.h>


using std::string;
using std::cout;
using std::endl;

int main() { 
	string input;
	string prompt;
	
	
	while(true) { 
		cout << "--$";                   // Print het prompt
		std::getline(std::cin, input);         // Lees een regel
		if (input == "new_file") new_file();   // Kies de functie
		else if (input == "ls") list();        //   op basis van
		else if (input == "src") src();        //   de invoer
		else if (input == "find") find();
		else if (input == "python") python();
		else if (input == "exit") return 0;
		else if (input == "quit") return 0;
		else if (input == "error") return 1;

		if (std::cin.eof()) { 
			return 0; 
		} 
	}      // EOF is een exit
}

void new_file() {// ToDo: Implementeer volgens specificatie.
//WERKT NOG NIET
	string fileNameS;
	string fileContentS;
	const char *fileName;
	const char *fileContent;
	
	cout << "Geef een filename: " << endl;
		
	std::getline(std::cin, fileNameS);
	fileNameS += ".txt";
	fileName = fileNameS.c_str();
	
	int fd = creat(fileName, 0777);
	
	cout << "Geef de file content: " << endl;
	std::getline(std::cin, fileContentS);
	fileContent = fileContentS.c_str();
	
	char size = fileContentS.length();
	
	//int fd = syscall(SYS_open, fileNameS, O_RDWR);
	write(fd, fileContent, size);
	
	close(fd);
	
}

void list() {
	int pid = fork();
	if(pid == 0) {
		char *args[] = {(char *) "/bin/ls", (char *) "-la", (char *) 0};
		execv("/bin/ls", args);
	} else {
		int exit_status;
		wait(&exit_status);
	}
}

void find() {// ToDo: Implementeer volgens specificatie.
	//WERKT NOG NIET
	cout << "Wat wil je zoeken?" << endl;
	string input;
	std::getline(std::cin, input);
	
	int pipeboy[2];
	int status;
	int check;

	check = pipe(pipeboy);
	
	if(check == -1) {
		perror("Pipe");
		exit(1);
	}
	
	
	pid_t pid = fork();
	if(pid == 0) {
		char *args1[] = {(char*) "find", (char*) "./", (char*) NULL};
		close(pipeboy[0]);
		dup2(pipeboy[1], STDOUT_FILENO);
		execv("/usr/bin/find", args1);
	}
	
	pid = fork();
	if(pid == 0) {
		char *parm[] = {(char*) "grep", (char*) input.c_str(), (char*) NULL};
		close(pipeboy[1]);
		dup2(pipeboy[0], STDIN_FILENO);
		execv("/bin/grep", parm);
	}
	
	close(pipeboy[0]);
	close(pipeboy[1]);
	
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

void python() {
	int pid = fork();
	if(pid == 0) {
		char *args[] = {(char *) "/usr/bin/python", (char*) 0};
		execv("/usr/bin/python", args);
	} else {
		int exit_status;
		wait(&exit_status);
	}
}

void src() {// Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
	int fd = syscall(SYS_open, "shell.cpp", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
	char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
	while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    cout << byte; 
}                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
