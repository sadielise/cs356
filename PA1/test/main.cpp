// including
#include <iostream>
#include <fstream>
#include "BlockCipher.h"
#include "StreamCipher.h"

// using
using namespace std;

int main(int argc, char* argv[])
{
	// check number of args
	if (argc != 6){
		cerr << "ERROR: Incorrect number of arguments." << endl;
		cerr << "Number of arguments is " << argc << endl;
		return -1;
	}

	// check first argument 
	char *cipherType;
	cipherType = argv[1];
	if(!((*cipherType == 'B') || (*cipherType == 'S'))){
		cerr << "ERROR: First argument invalid. Enter B or S." << endl;
		return -1;
	}

	// check second argument
	string inputFileName;
	inputFileName = argv[2];
	FILE *inputFile = fopen(inputFileName.c_str(), "r");
	if(inputFile == NULL){
		cerr << "ERROR: Second argument invalid. File does not exist." << endl;
		return -1;
	}

	// get third argument
	string outputFileName;
	outputFileName = argv[3];
	FILE *outputFile = fopen(outputFileName.c_str(), "w");

	// check fourth argument
	string keyFileName;
	keyFileName = argv[4];
	FILE *keyFile = fopen(keyFileName.c_str(), "r");
	if(keyFile == NULL){
		cerr << "ERROR: Fourth argument invalid. File does not exist." << endl;
		return -1;
	}

	// check fifth argument
	char *operationMode;
	operationMode = argv[5];
	if(!((*operationMode == 'E') || (*operationMode == 'D'))){
		cerr << "ERROR: Fifth argument invalid. Enter E or D." << endl;
		return -1;
	}		

	// send data to appropriate cipher
	if((*cipherType == 'B') && (*operationMode == 'E')){
		BlockCipher block = BlockCipher(inputFile, outputFile, keyFile);
		return block.encrypt();
	}
	else if((*cipherType == 'B') && (*operationMode == 'D')){
		BlockCipher block = BlockCipher(inputFile, outputFile, keyFile);
		return block.decrypt();
	}
	else if((*cipherType == 'S') && (*operationMode == 'E')){
		StreamCipher stream = StreamCipher(inputFile, outputFile, keyFile);
		return stream.encrypt();
	}
	else if((*cipherType == 'S') && (*operationMode == 'D')){
		StreamCipher stream = StreamCipher(inputFile, outputFile, keyFile);
		return stream.decrypt();
	}

	return 0;

}
