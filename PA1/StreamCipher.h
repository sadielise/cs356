// including
#include <fstream>
#include <istream>
#include <iostream>
#include <string>

// using
using namespace std;

class StreamCipher
{

	public:
		StreamCipher(FILE *input, FILE *output, FILE *key); //constructor
		int readKeyFile();
		int readInputFile();
		int writeOutputFile();
		int xorKeyAndValues();
		int encrypt();
		int decrypt();

	private:
		FILE *inputFile;
		FILE *outputFile;
		FILE *keyFile;

};
