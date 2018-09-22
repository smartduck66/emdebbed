//
// Book : Version du chapitre 25 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 22/09/2018 
// Commit en cours : 22/09/2018 - Drill
// Note : compilé avec l'option C++17 à cause de l'utilisation de if constexpr pour simuler du SFINAE dans le template d'addition de matrices
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

#include "pch.h"		// En-tête indispensable sous Windows et VC++
#include "MyHeader.h"	// Header personnel (en partie dérivé de std_lib_facilities de BS)

#include <bitset>


using namespace std;

// To treat all integer values types uniformly (page 965)
template<typename T>
void print(T i) { cout << i << endl; }
void print(char i) { cout << int (i) << endl; }
void print(signed char i) { cout << int(i) << endl; }
void print(unsigned char i) { cout << int(i) << endl; }

int main()
{
	try
	{
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		// Drill page 984
		int v = 1;
		for (int i=0;i<sizeof(v)*8;++i) {
			cout << v << ' ';
			v <<= 1;
					
		
		}
		cout << endl<<endl;

		short unsigned int v1 = 65535; // 2^16 -1 (au delà, troncation)
		short signed int v2 = 32767; // 2^15 -1 (au delà, troncation)
		short signed int v3 = -32768; // -2^15 (au delà, troncation)
				
		cout << bitset<8 * sizeof(short unsigned int)>{v1} << endl;								// every bit set
		cout << bitset<8 * sizeof(short unsigned int)>{string{"1"}} << endl;					// the lowest (bit) set
		cout << bitset<8 * sizeof(short unsigned int)>{string{ "1000000000000000" }} << endl;	// the highest (bit) set
		cout << bitset<8 * sizeof(short unsigned int)>{string{ "0" }} << endl;					// the lowest byte set
		cout << bitset<8 * sizeof(short unsigned int)>{v1} << endl;								// the highest byte set
		cout << bitset<8 * sizeof(short unsigned int)>{string{"11"}} << endl;					// second bit set and the lowest bit 1
		cout << bitset<8 * sizeof(short unsigned int)>{string{ "10" }} << endl;					// second bit set and the lowest bit 0

		bitset<8 * sizeof(short unsigned int)>v4{ string{ "10" } };
		cout << dec << v4 <<"   -   "<< hex << "0x" << v4<<"   -   " << v4 << endl;

		cout << dec<<"---------------------------------------------" << endl;
		int si = 257;
		char c=si;
		unsigned char uc = si;
		signed char sc=si;
		print(si); print(c); print(uc); print(sc);
		cout << endl;
		si = 129;
		c = si;
		uc = si;
		sc = si;
		print(si); print(c); print(uc); print(sc);
		cout << endl;
		cout << dec << 0xab << endl;
		short unsigned int v5 = 0xff;
		short unsigned int v6 = -3;
		cout <<bitset<4 * sizeof(short unsigned int)>{v5} <<endl;
		print(v6);

		// exo 3 page 986



		keep_window_open();

		return 0;
	}


	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}