#include "core.h"
#include <string>
#include "md5wrapper.h"
#include <time.h>
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

md5wrapper MD5;

void Core::printHelp (){
	cout << endl << "Usage: MD5Cracker.exe -d <dictionary filename> -m <crack modus> -l <max length> -h <MD5-hash>" << endl << endl;
	cout << "-d <dictionary filename> : filename of the directory file (1 word per line) [OPTIONAL]" << endl;
	cout << "-m <crack modus>		: -a (lowercase). [OPTIONAL]" << endl;
	cout << "				: -A (uppercase). [OPTIONAL]" << endl;
	cout << "				: -0 (numerical). [OPTIONAL]" << endl;

	cout << endl<< "-l <max length>	: the maximum length of the cracked string. [OPTIONAL]" << endl;

	cout << "-h <MD5-hash>	: the hash to crack!" << endl;

	cout << endl << "Example: MD5Cracker.exe -m -a -0 -l 10 -d dict.txt -h c5506b8b3a470886ab41171229d37410" << endl;

}

void Core::printArgSummary(switches sw){
	cout << "Going to crack " << sw.hash << " now..." << endl << endl;
}

void Core::crackDict(switches sw){
	std::string word;
	//Make new input stream
	ifstream dict(sw.dict.c_str());
	//Check if file exists
	if (dict.is_open()){
		cout << "Dictionary cracking..." << endl;
		//Process all lines of the dictionary
		while(!dict.eof()){
			//Fetch new line from dictionary file
			getline(dict, word);
			//Remove newline at the end of word
			word = word.substr(0, word.length()-1);
			//Compare hashes
			checkHash(word, sw);
		}
	}else{
		cout << "I/O ERROR: could not open dictionary file, skipping dictionary attack." << endl;
	}
}

void Core::crackHash(switches sw){
		/*Check if maximum length was provided. If not, default is set to 8 */
		if(sw.maxLength == 0){
			sw.maxLength = 8;
			cout << "Cracking passwords up to 8 characters (default)" << endl;
		}
	
		/*If dictionary mode is enabled, try that first. The filename of the dictionary file
		is stored in sw.dict */
		if(sw.useDict){
			crackDict(sw);
		}
	
		if(! (sw.alpha | sw.numeric | sw.caps)){
			cout << "No alphabet specified using the -m switch, cracking lowercase only." << endl;
			sw.alpha = true;
		}
	
		initializeAlfabet(sw);

		int len = 1;
		sw.pos = 0;
		bool extend;
		char pass[256];
		
		char firstChar = getFirstChar(sw);
		char lastChar = getLastChar(sw);

		string passStr;
		pass[0] = firstChar ;
		pass[0]--;

		while(len <= sw.maxLength){
			/*Check if we have overflow*/
			extend = false;

			for(int i = 0; i < len ; i++){
				if(pass[i]  == lastChar){
					/*This index of the pass is about to overflow */
					extend = true;
				}else{
					extend = false;
					break;
				}
			}/*Process next character in pass */
		
			if(!extend){
				/*Increase password with 1*/
				int incrIndex = len-1; //Increase LSB*/
				
				while(pass[incrIndex] == lastChar){
					pass[incrIndex] = firstChar; //overflow, let's increase more significant bits	
					incrIndex--;
				}

				//If we arive here we need to ADD for the last time to a number that is NOT overflowing

				//pass[incrIndex]++;
				incrementChar(pass[incrIndex], sw);
				
				pass[len] = '\0';

				/*Check if password is cracked!*/
				checkHash(pass, sw);
				//cout << pass << endl;

			}else{
				len++;

				for (int i =0; i <len ; i++){
					pass[i] = firstChar;
				}
				
				/*SPECIAL CASE WHERE PASSWORD IS STRING OF TYPE AAAAA*/
				checkHash(pass, sw);

				cout << "Cracking length " << len-1 << " done! [" << ((float)(len-1)/(float(sw.maxLength))*100) << "%]" << endl;
			}
		}/*End while*/
}

void Core::checkHash(string pass, switches sw){
	if(MD5.getHashFromString(pass).compare(sw.hash) == 0){
			cout << "----------------------------" << endl;
			cout << "DONE: " << pass << endl;
			cout << "----------------------------" << endl;
				
			exit(0);
	}
}
void Core::incrementChar(char &ch, switches &sw){
	ch = sw.mapping[ch];
}

int Core::getFirstChar(switches sw){
	return sw.alfabet[0];
}

int Core::getLastChar(switches sw){
	return sw.alfabet[sw.alfabetSize-1];
}

void Core::initializeAlfabet(switches &sw){
	int startIndex = 0; 
	if(sw.alpha){
		for(char c = 'a' ; c <= 'z' ; c++){
			sw.alfabet[startIndex] = c;
			startIndex++;
		}
	}

	if(sw.numeric){
		for(int i = '0' ; i <= '9' ; i++){
			sw.alfabet[startIndex] = i;
			startIndex++;
		}
	}

	if(sw.caps){
		for(char c = 'A' ; c <= 'Z' ; c++){
			sw.alfabet[startIndex] = c;
			startIndex++;
		}
	}

	sw.alfabetSize = startIndex;

	sw.mapping['`'] = 'a';
	sw.mapping['a'] = 'b';
	sw.mapping['b'] = 'c';
	sw.mapping['c'] = 'd';
	sw.mapping['d'] = 'e';
	sw.mapping['e'] = 'f';
	sw.mapping['f'] = 'g';
	sw.mapping['g'] = 'h';
	sw.mapping['h'] = 'i';
	sw.mapping['i'] = 'j';
	sw.mapping['j'] = 'k';
	sw.mapping['k'] = 'l';
	sw.mapping['l'] = 'm';
	sw.mapping['m'] = 'n';
	sw.mapping['n'] = 'o';
	sw.mapping['o'] = 'p';
	sw.mapping['p'] = 'q';
	sw.mapping['q'] = 'r';
	sw.mapping['r'] = 's';
	sw.mapping['s'] = 't';
	sw.mapping['t'] = 'u';
	sw.mapping['u'] = 'v';
	sw.mapping['v'] = 'w';
	sw.mapping['w'] = 'x';
	sw.mapping['x'] = 'y';
	sw.mapping['y'] = 'z';
	sw.mapping['z'] = '0';
	sw.mapping['/'] = '0';
	sw.mapping['0'] = '1';
	sw.mapping['1'] = '2';
	sw.mapping['2'] = '3';
	sw.mapping['3'] = '4';
	sw.mapping['4'] = '5';
	sw.mapping['5'] = '6';
	sw.mapping['6'] = '7';
	sw.mapping['7'] = '8';
	sw.mapping['8'] = '9';
	sw.mapping['9'] = 'A';
	sw.mapping['@'] = 'A';
	sw.mapping['A'] = 'B';
	sw.mapping['B'] = 'C';
	sw.mapping['C'] = 'D';
	sw.mapping['D'] = 'E';
	sw.mapping['E'] = 'F';
	sw.mapping['F'] = 'G';
	sw.mapping['G'] = 'H';
	sw.mapping['H'] = 'I';
	sw.mapping['I'] = 'J';
	sw.mapping['J'] = 'K';
	sw.mapping['K'] = 'L';
	sw.mapping['L'] = 'M';
	sw.mapping['M'] = 'N';
	sw.mapping['N'] = 'O';
	sw.mapping['O'] = 'P';
	sw.mapping['P'] = 'Q';
	sw.mapping['Q'] = 'R';
	sw.mapping['R'] = 'S';
	sw.mapping['S'] = 'T';
	sw.mapping['T'] = 'U';
	sw.mapping['U'] = 'V';
	sw.mapping['V'] = 'W';
	sw.mapping['W'] = 'X';
	sw.mapping['X'] = 'Y';
	sw.mapping['Y'] = 'Z';
	sw.mapping['Z'] = '-';

}