// including
#include <fstream>
#include <istream>
#include <iostream>
#include <string.h>
#include <vector>
#include "BlockCipher.h"

// using
using namespace std;

// variables
vector<unsigned int> keyValuesBlock;
vector<unsigned int> inputValuesBlock;
vector<unsigned int> xorValuesBlock;

// constructor
BlockCipher::BlockCipher(FILE *input, FILE *output, FILE *key){

	inputFile = input;
	outputFile = output;
	keyFile = key;

}

int BlockCipher::readKeyFile(){
	
	for(int i = 0; i < 8; i++){
		int keyValue = fgetc(keyFile);
		if(keyValue == EOF){
			cerr << "ERROR: Key file is not 64 bits." << endl;
			return -1;
		}
		else{
			keyValuesBlock.push_back(keyValue);
		}
	}

	return 0;	
}

int BlockCipher::readInputFile(){

	int count = 0;	
	int inputValue;
	bool flag = false;

	while(flag == false){
		inputValue = fgetc(inputFile);
		if(inputValue != EOF){
			count++;
			inputValuesBlock.push_back(inputValue);
		}
		else{
			if(count == 0){
				return 1;
			}
			else{
				while((count % 8) != 0){
					inputValuesBlock.push_back(128);
					count++;
				}
				flag = true;
			}
		}
	}

	return 0;
}

int BlockCipher::writeOutputFile(){

	for(unsigned int i = 0; i < xorValuesBlock.size(); i++){
		fputc(xorValuesBlock[i], outputFile);
	}
	
	fclose(outputFile);

	return 0;
}

int BlockCipher::xorKeyAndValues(){

	int numBlocks = inputValuesBlock.size()/8;
	int count = 0;

	for(int i = 0; i < numBlocks; i++){
		for(int j = 0; j < 8; j++){
			unsigned int key = keyValuesBlock[j];
			unsigned int input = inputValuesBlock[count];
			unsigned int xorVal = key ^ input;
			xorValuesBlock.push_back(xorVal);
			count++;
		}
	}

	return 0;
}

int BlockCipher::encryptSwap(){

	int start = 0;
	int end = xorValuesBlock.size()-1;
	int count = 0;
	bool flag = false;

	while(flag == false){
		if((keyValuesBlock[count]%2) == 0){
			start++;
		}
		else{
			unsigned int temp = xorValuesBlock[end];
			xorValuesBlock[end] = xorValuesBlock[start];
			xorValuesBlock[start] = temp;
			start++;
			end--;
		}

		if(count == 7){
			count = 0;
		}
		else{
			count++;
		}
		
		if((start == end) || (start > end)){
			flag = true;
		}
	}

	return 0;
}

int BlockCipher::decryptSwap(){

	int start = 0;
	int end = inputValuesBlock.size()-1;
	int count = 0;
	bool flag = false;

	while(flag == false){
		if((keyValuesBlock[count]%2) == 0){
			start++;
		}
		else{
			unsigned int temp = inputValuesBlock[end];
			inputValuesBlock[end] = inputValuesBlock[start];
			inputValuesBlock[start] = temp;
			start++;
			end--;
		}

		if(count == 7){
			count = 0;
		}
		else{
			count++;
		}
		
		if((start == end) || (start > end)){
			flag = true;
		}
	}

	return 0;
}

int BlockCipher::removePadding(){

	bool flag = false;
	int index = xorValuesBlock.size()-1;

	while(flag == false){
		if(xorValuesBlock[index] == 128){
			xorValuesBlock.pop_back();
			index--;
		}
		else{
			flag = true;
		}
	}

	return 0;
}

int BlockCipher::encrypt(){

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
		// swap values
		encryptSwap();	
		// write output file
		writeOutputFile();
	}

	return 0;
}

int BlockCipher::decrypt(){

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
		// swap values
		decryptSwap();	
		// xor key values with input values
		xorKeyAndValues();
		// remove padding
		removePadding();
		// write output file
		writeOutputFile();
	}
	
	return 0;
}

