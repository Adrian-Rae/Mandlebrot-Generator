#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

	
void WRITE(bool inarray[PIX][PIX], ofstream outfile, int r, int c){
	for (int row = 0; row < r; row++){
		string s = "";
		for (int col = 0; col < c; col++){
			if (inarray[row][col])
				s += "*";
			else s += "O";
		}
		outfile << s << endl;
	}	
}

struct complex{
		double real;
		double imag;
		double magnitude;
	};

complex MAND(complex z, complex c){
	complex result;
	result.real = (z.real*z.real-z.imag*z.imag)+c.real;
	result.imag = (2*z.real*z.imag) + c.imag;
	result.magnitude = hypot(result.real,result.imag);
	return result ;
}

bool DetCON(complex n, int maxItterations, int radius){
	complex origin;
	
	origin.real = 0;
	origin.imag = 0;
	origin.magnitude = 0;
	
	n = MAND(origin,n); // itteration 1
	for (int ITT = 2; ITT <= maxItterations; ITT++){
		n = MAND(n,n);	
	}
	
	if (n.magnitude <= radius)
		return true;
	else return false;
	
}

int main(){
	
	const int PIX = 1000; //discrete points for measurements
	const int ITT = 1000; //itterations before convergence is determined
	const int CON = 2; //radius of convergence
	const string filename = "RESULT.txt";
	
	float SR, SC, ER, EC;
	cout << "Enter SR,ER,SC,EC" << endl;
	cin >> SR >> ER >> SC >> EC;
	cout << "Processing Started"<<endl;
	
	bool CONVERGENCETABLE[PIX][PIX];
	
	float dr = (ER-SR)/PIX, dc = (EC-SC)/PIX;
	
	int row = 0;
	int col = 0;
	for (float r = SR; r <= ER; r+=dr){
		col = 0;
		for (float c = SC; c <= EC; c+=dc){
			complex z;
			z.real = r;
			z.imag = c;
			z.magnitude = hypot(r,c);
			CONVERGENCETABLE[row][col] = DetCON(z, ITT, CON);
			col++;			
		}
		row++;	
	}
	cout << "Processing Complete"<<endl;
	
	ofstream OUT;
	OUT.open(filename.c_str());
	WRITE(CONVERGENCETABLE, OUT, row, col);
	OUT.close();
	
	 
	return 0;
}
