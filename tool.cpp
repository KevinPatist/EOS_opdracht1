<<<<<<< HEAD
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
	std::string woord = argv[1];
	int input;
	std::string inputS;
	
	std::cout << "Geef een caesar sleutel: ";
	std::getline(std::cin, inputS);
	input << stoi(inputS);	

	if(argc != 2) {
		std::cerr << "Geef argument dan niffauw!\n";
		return -1; 	
	}
	
	for(int i=0; i < input; i++) {
		for(int j=0; j < woord.length(); j++) {
			char letter = woord[j];
			letter += 1;
			if(letter == '{') {
				letter = 'a';
			}
			woord[j] = letter;		
		} 
	}
	std::cout << woord << std::endl;
	
}
=======
#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::cin;
using std::endl;

int main(int argc, char *argv[]) {
	string woord = argv[1];
	int input;
	string inputS;
	
	cout << "Geef een Caesar sleutel: ";
	std::getline(cin, inputS);
	input << stoi(inputS);
	
	if(argc != 2) {
		cout << "Geef argument niffauw" << endl;
	}
	
	for(int i=0; i < input; i++) {
		for(int j=0; j < woord.length(); j++) {
			char letter = woord[j];
			letter += 1;
			if(letter == '{') {
				letter = 'a';
			}
			woord[j] = letter;
		}
	}
	cout << woord << endl;
}
>>>>>>> edceaa27a0a087e8489e8bdc0a0538fafdbc494f
