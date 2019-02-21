#include "shell.hh"
#include <sys/wait.h>

using std::string;
using std::cout;
using std::endl;

int main() { 
	string input;
	string prompt;
	char promptC[15];
	int fd = syscall(SYS_open, "config.txt", O_RDONLY, 0755);
	while(syscall(SYS_read, fd, promptC, 15))
	prompt = promptC;
	
	while(true) { 
		cout << prompt;                   // Print het prompt
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
	cout << "ToDo: Implementeer hier new_file()" << endl; 
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
	cout << "ToDo: Implementeer hier find()" << endl; 
}

void python() {// ToDo: Implementeer volgens specificatie.
	cout << "ToDo: Implementeer hier python()" << endl; 
}

void src() {// Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
	int fd = syscall(SYS_open, "shell.cpp", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
	char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
	while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
    cout << byte; 
}                                  //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.