#include <string>
#include <map>
#ifndef CORE_H
#define CORE_H


typedef struct{
		/*Alphabet switches*/
		bool alpha;
		bool caps;
		bool numeric;
		
		int alfabetSize;

		int pos;

		char alfabet[256];
		std::map<char, char> mapping;

		/*Control integer*/
		int done;

		/*MD5 hash to crack*/
		std::string hash;

		/*Maximum password length*/
		int maxLength;
	
		/*Save dictionary path*/
		std::string dict;
	
		/*Dictionary boolean*/
		bool useDict;
} switches;

class Core {
	public:

		/* Functions */
		void printHelp();
		void printArgSummary(switches sw);
		void crackHash(switches sw);
		void crackDict(switches sw);

		int getFirstChar(switches sw);
		int getLastChar(switches sw);
		void initializeAlfabet(switches &sw);
		void incrementChar(char &ch, switches &sw);

		void checkHash(std::string hash, switches sw);
};

#endif