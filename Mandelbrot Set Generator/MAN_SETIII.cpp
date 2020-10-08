#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

	
/*void WRITE(bool **inarray, ofstream outfile, int r, int c){
	for (int row = 0; row < r; row++){
		string s = "";
		for (int col = 0; col < c; col++){
			if (inarray[row][col])
				s += "*";
			else s += "O";
		}
		outfile << s << endl;
	}	
}*/

struct complex{
		double real;
		double imag;
		double magnitude;
	};
	
struct plane{
	complex z;
};


complex MAND(complex z, complex c){
	complex result;
	result.real = (z.real*z.real-z.imag*z.imag)+c.real;
	result.imag = (2*z.real*z.imag) + c.imag;
	result.magnitude = hypot(result.real,result.imag);
	return result ;
}

bool DetCON(complex n, complex origin, int maxItterations, int radius){
	complex c = n;
	
	n = MAND(origin,n); // itteration 1
	for (int IT = 2; IT <= maxItterations; IT++){
		n = MAND(n,c);	
	}
	
	if (n.magnitude <= radius)
		return true;
	else return false;
	
}

int main(){
	
	const float PIX = 1000; //discrete points for measurements
	const int ITT = 100; //itterations before convergence is determined
	const int CON = 2; //radius of convergence
	const string filename = "RESULT.txt";
	const float axis = 0.003;
	
	float SR=-2, SC=-1.0, ER=0.5, EC=1.0;
	//cout << "Enter SR,ER,SC,EC" << endl;
	//cin >> SR >> ER >> SC >> EC;
	cout <<
	"========================"<<endl<<
	"Mandelbrot Set Generator"<<endl<<
	"========================"<<endl;
	
	complex origin;
	origin.real = 0;
	origin.imag = 0;
	origin.magnitude = 0;
	
	cout << "Processing Started"<<endl;
	
	float dr = (ER-SR)/PIX, dc = (EC-SC)/PIX;
	
	ofstream OUT;
	OUT.open(filename.c_str());
	for (float r = ER; r >= SR; r-=dr){
		string s = "";
		for (float c = SC; c <= EC; c+=dc){
			
			complex z;
			z.real = r;
			z.imag = c;
			z.magnitude = hypot(r,c);

					
			if (((r>-axis)&&(r<axis))||((c>-axis)&&(c<axis)))
				s += "+";	
			else {
			if (DetCON(z, origin, ITT, CON)){
					char c = '*';
					s += c;
				}
				else s += " ";
			}
		}
		OUT << s << endl;			
	}
	
	OUT.close();
	
	cout << "Processing Complete"<<endl;
	
	 
	return 0;
}
