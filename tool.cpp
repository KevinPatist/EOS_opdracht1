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