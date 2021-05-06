#include<iostream>
#include<vector>
#include<string>
#include<time.h>
#include<bits/stdc++.h>

using namespace std;

float maximum(float, float, float);
int main(){
	float tranArr[5][5] = {0, 0.33, 0.33, 0.33, 0,
						   0, 0.75, 0.04, 0.20, 0.01,
						   0, 0.04, 0.85, 0.10, 0.01,
						   0, 0.30, 0.19, 0.50, 0.01,
						   0, 0, 0, 0, 0};
	
	float emArr[3][3] = {0.30, 0.60, 0.10,
						 0.35, 0.05, 0.60,
						 0.75, 0.15, 0.10};
	
	int choice;
	
	cout << "Pick from the following options:" << endl;
	cout << "1. Random generated sequence of events" << endl;
	cout << "2. Enter your own seqence of events" << endl;
	cout << "Choice: ";
	cin >> choice;
	int seqSize;
	char charArr[6];
	float emChoice;
	string seq;
	if (choice == 1){
		seq = "";
		seqSize = 6;
		srand((unsigned)time(NULL));
		for (int i = 0; i < seqSize; i++){
			emChoice = (float) rand()/RAND_MAX;
			if (emChoice <= 0.33)
				charArr[i] = 'S';
			else if (emChoice > 0.33 && emChoice <= 0.66)
				charArr[i] = 'Z';
			else
				charArr[i] = 'W';
		}
		for (int j = 0; j < seqSize; j++){
			seq = seq + charArr[j];
		}	
	}
	else if (choice == 2){
		cout << "Enter sequence (S = Shopping, Z = Sleeping, W = Walking): ";
		cin >> seq;
		seqSize = seq.size();
	}					 
	float seqArr[3][seqSize+2];
	float rain;
	float sun;
	float cloud;
	int em;
	float maxNum;
	
	for (int i = 0; i < 3; i++){
		seqArr[i][0] = 0.33;
	}
	
	for (int j = 1; j < seqSize+2; j++){
		if (j == seqSize + 1){
			for (int i = 0; i < 3; i++){
				if (i == 0){
					seqArr[i][j] = seqArr[i][j-1] * tranArr[1][4];
				}
				if (i == 1){
					seqArr[i][j] = seqArr[i][j-1] * tranArr[2][4];
				}
				if (i == 2){
					seqArr[i][j] = seqArr[i][j-1] * tranArr[3][4];
				}
			}
		}
		else{
			if (seq[j-1] == 'S')
				em = 0;
			else if (seq[j-1] == 'Z')
				em = 1;
			else
				em = 2;
			for(int i = 0; i < 3; i++){
				if (i == 0){
					rain = seqArr[i][j-1] * tranArr[1][1] * emArr[0][em];
					sun = seqArr[i+1][j-1] * tranArr[2][1] * emArr[0][em];
					cloud = seqArr[i+2][j-1] * tranArr[3][1] * emArr[0][em];
					seqArr[i][j] = maximum(rain, sun, cloud);
				}
				if (i == 1){
					rain = seqArr[i-1][j-1] * tranArr[1][2] * emArr[1][em];
					sun = seqArr[i][j-1] * tranArr[2][2] * emArr[1][em];
					cloud = seqArr[i+1][j-1] * tranArr[3][2] * emArr[1][em];
					seqArr[i][j] = maximum(rain, sun, cloud);
				}
				if (i == 2){
					rain = seqArr[i-2][j-1] * tranArr[1][3] * emArr[2][em];
					sun = seqArr[i-1][j-1] * tranArr[2][3] * emArr[2][em];
					cloud = seqArr[i][j-1] * tranArr[3][3] * emArr[2][em];
					seqArr[i][j] = maximum(rain, sun, cloud);
				}
			}
		}
	}
	
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < seqSize+2; j++){
			cout << seqArr[i][j] << " ";
		}
		cout << endl;
	}
	
	cout << endl << endl;
	float traceMax;
	int row = 0;
	vector<string> state;
	for (int j = seqSize+1; j >= 1; j--){
		if (j != seqSize+1){
			traceMax = maximum(seqArr[row][j], seqArr[row+1][j], seqArr[row+2][j]);
			if (seqArr[row][j] == traceMax)
				state.push_back("R");
			if (seqArr[row+1][j] == traceMax)
				state.push_back("S");
			if (seqArr[row+2][j] == traceMax)
				state.push_back("C");
			}
	}
	cout << "Emission: ";
	cout << setw(3);
	for (int i = 0; i < seqSize; i++){
		cout <<  seq[i] << "    ";
	}
	cout << endl;
	cout << "State: ";
	cout << setw(6);
	for (int i = state.size()-1; i >= 0; i--){
		cout << state[i] << "    ";
	}
	return 0;
}

float maximum(float a, float b, float c){ // function that finds maximum between 3 numbers
	float max = (a < b) ? b : a;
	return ( (max < c) ? c : max);
}
