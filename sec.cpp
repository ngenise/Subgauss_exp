#include <iostream>
#include <math.h>

using namespace std;

/* compile with g++ -std=c++11 sec.cpp -o test
 * run with ./test n m log2(q) bool(s) */
int main(int argc, const char * argv[]){
	//Set parameters, we only use sqrt(n log q)/sqrt(log delta) columns
	cout.precision(6);
	
	unsigned int n = atoi(argv[1]); unsigned int m = atoi(argv[2]); long long q = pow(2,atoi(argv[3]));
	bool pick_s = atoi(argv[4]);
	double scale = 0.0;

	if(pick_s){scale = 1/sqrt(2.0);}else{scale = 1.0;}
	//unsigned int s = atoi(argv[4]);
    	
	double delta_min = 0.0;

	//Find s
	unsigned int m_bar = m - n*ceil(log2( double(q) ));
	double s_1 = scale*( sqrt(double(m_bar)) + sqrt(n*log2(double(q))) );
	double s = 4.5*sqrt(5*(s_1*s_1 + 1));

    	cerr << "n = " << n << endl;
    	cerr << "m = " << m << endl;
    	cerr << "q = " << q << endl;
    	cerr << "s = " << s << endl;
	
	double bound = s*sqrt(double(m));
	cerr << "bound = "<< bound << endl;

	double edelta = bound; double delta = 0.0;
	unsigned int BKZ_block = m;//start with the largest beta/block size for BKZ
	
	for(unsigned int i = floor(1.0*double(n)); i <= m; i += 10){// i is the SIS subspace dimension

		double lambda1 = sqrt(i/(8*atan(1.0)*exp(1.0)) )*pow( double(q), double(n)/double(i));//Shortest vector (MR09).

		edelta = edelta/pow( double(q), double(n)/double(i) );//bound/det^1/dim = delta^dim
		edelta = pow(edelta, 1/double(i));//expected delta needed to break
		
		//Find the smallest k which breaks SIS. 
		for(int k = 20; k<= m; k++){
			//given block size k, what is delta?
			
			delta = pow(4*atan(1.0)*k, 1.0/k); 
			delta = delta*k/(2*4*atan(1.0)*exp(1.0));
			delta = pow(delta, 1.0/(2*(k-1)) );
			
			if(delta <= edelta and k <= BKZ_block and lambda1 <= bound){//we beat delta/block size and a short enough vector exists.	
				
				BKZ_block = k;
				delta_min = delta;
									
			}
		}
		edelta = bound;// reset to min bound to break
	}
	cout<<.292*BKZ_block<<" classical and "<<.265*BKZ_block<<" quantum bits of security."<<endl;
	cout<<"block size "<<BKZ_block<<"delta = "<<delta_min<<endl;

	return 0;

}
