// including
#include <fstream>
#include <istream>
#include <iostream>
#include <string.h>
#include <vector>
#include "StreamCipher.h"

// using
using namespace std;

// variables
vector<unsigned int> keyValuesStream;
vector<unsigned int> inputValuesStream;
vector<unsigned int> xorValuesStream;

// constructor
StreamCipher::StreamCipher(FILE *input, FILE *output, FILE *key){

	inputFile = input;
	outputFile = output;
	keyFile = key;

}

int StreamCipher::readKeyFile(){
	
	int count = 0;
	bool flag = false;

	while(flag == false){
		int keyValue = fgetc(keyFile);
		if(keyValue == EOF){
			flag = true;
		}
		else{
			keyValuesStream.push_back(keyValue);
			count++;
		}
	}

	if(count == 0){
		cerr << "ERROR: Key file is empty." << endl;
		return -1;
	}

	return 0;	
}

int StreamCipher::readInputFile(){

	int count = 0;	
	int inputValue;
	bool flag = false;

	while(flag == false){
		inputValue = fgetc(inputFile);
		if(inputValue != EOF){
			count++;
			inputValuesStream.push_back(inputValue);
		}
		else{
			if(count == 0){
				return 1;
			}
			flag = true;
		}
	}

	return 0;
}

int StreamCipher::writeOutputFile(){

	for(unsigned int i = 0; i < xorValuesStream.size(); i++){
		fputc(xorValuesStream[i], outputFile);
	}
	
	fclose(outputFile);

	return 0;
}

int StreamCipher::xorKeyAndValues(){

	unsigned int count = 0;

	for(unsigned int i = 0; i < inputValuesStream.size(); i++){
		unsigned int key = keyValuesStream[count];
		unsigned int input = inputValuesStream[i];
		unsigned int xorVal = key ^ input;
		xorValuesStream.push_back(xorVal);

		if(count == keyValuesStream.size()-1){
			count = 0;
		}
		else{
			count++;
		}
	}

	return 0;
}

int StreamCipher::encrypt(){

	// read key file
	int readKey = readKeyFile();
	if(readKey == -1){
		return -1;
	}
	
	// read input file
	int readInput = readInputFile();
	// exit if input file cannot be read
	if(readInput == -1){
		return -1;
	}
	else if(readInput == 1){
		// close empty output file if input empty
		fclose(outputFile);
		return 0;
	}
	// handle standard input file
	else{
		// xor key values with input values
		xorKeyAndValues();	
		// write output file
		writeOutputFile();
	}

	return 0;
}

int StreamCipher::decrypt(){

	// read key file
	int readKey = readKeyFile();
	if(readKey == -1){
		return -1;
	}
	
	// read input file
	int readInput = readInputFile();
	// exit if input file cannot be read
	if(readInput == -1){
		return -1;
	}
	else if(readInput == 1){
		// close empty output file if input empty
		fclose(outputFile);
		return 0;
	}
	// handle standard input file
	else{
		// xor key values with input values
		xorKeyAndValues();	
		// write output file
		writeOutputFile();
	}

	return 0;
}
