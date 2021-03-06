//
// Book : Version du chapitre 25 de l'ouvrage.
// "Programming -- Principles and Practice Using C++" de Bjarne Stroustrup (2ème édition : 2014)
// Commit initial : 22/09/2018 
// Commit en cours : 22/09/2018 - Exo 3
// Note : compilé avec l'option C++17 à cause de l'utilisation de if constexpr pour simuler du SFINAE dans le template d'addition de matrices
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @

#include "pch.h"		// En-tête indispensable sous Windows et VC++
#include "MyHeader.h"	// Header personnel (en partie dérivé de std_lib_facilities de BS)

#include <bitset>
#include <iomanip>
#include <vector>

using namespace std;

// To treat all integer values types uniformly (page 965)
template<typename T>
void print(T i) { cout << i << endl; }
void print(char i) { cout << int (i) << endl; }
void print(signed char i) { cout << int(i) << endl; }
void print(unsigned char i) { cout << int(i) << endl; }

struct PPN {  
	unsigned int PFN : 22;
	int : 3;
	unsigned int CCA : 3;
	bool nonreachable : 1;
	bool dirty : 1;
	bool valid : 1;
	bool global : 1;
	   	 
};

void encipher(const unsigned long* const v, unsigned long *const w, const unsigned long *const k)
{  
	static_assert(sizeof(long) == 4, "size of long wrong for TEA");

	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0;
	const unsigned long delta = 0x9E3779B9;

	for (unsigned long n=32;n-->0;) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		
	}
	w[0] = y;
	w[1] = z;

}

void decipher(const unsigned long* const v, unsigned long *const w, const unsigned long *const k)
{
	static_assert(sizeof(long) == 4, "size of long wrong for TEA");

	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0xC6EF3720;
	const unsigned long delta = 0x9E3779B9;

	for (unsigned long n = 32; n-- > 0;) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum>>11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];

	}
	w[0] = y;
	w[1] = z;

}

bool is_valid_action(char c)	noexcept	// Helper pour TEA
{
	for (const char w : "eEdD")
		if (c == w)return true;
	return false;

}

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
		cout << bitset<8 * sizeof(short unsigned int)>{string{ "0" }} << endl;					// the lowest byte set (équivalent à v1.reset() qui remet tous les bits à 0)
		cout << bitset<8 * sizeof(short unsigned int)>{v1} << endl;								// the highest byte set (équivalent à v1.set() qui remet tous les bits à 1)
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
		bitset<8 * sizeof(signed int)>v7{ string{ "0" } };
		print(v7);
		print(~v7);
		
		// exos 5&6 : boucle infinie car i ne peut jamais atteindre max
		// unsigned char max = 160;
		// for (signed char i = 0; i < max; ++i) cout << int(i) << endl;

		// exo 7
		cout << " --------------------------------------------------------------------" << endl;
		for (int i = 0; i <= 400 ; ++i)
			cout << hex << i << " ";
		cout << endl;
		cout << " --------------------------------------------------------------------" << endl;

		for (int i = -200; i <= 200; ++i)
			cout << hex << i << " ";
		cout << endl;
		cout << " --------------------------------------------------------------------" << endl;

		// Exo 8
		//cout << dec<<"Saisir un caractère du clavier " << endl;
		//char x{};
		//while (cin >> x)
		//	print(x);

		// Exos 10&11 : 32 bits
		PPN pn{};
		cout << pn.PFN << " " << pn.CCA << " " << pn.nonreachable << " " << pn.dirty << " " << pn.valid << " " << pn.global << endl;
		pn.PFN = 458;
		pn.CCA = 6;
		pn.nonreachable=true;
		pn.dirty = false;
		pn.valid = true;
		pn.global = false;
		cout << pn.PFN << " " << pn.CCA << " " << pn.nonreachable << " " << pn.dirty << " " << pn.valid << " " << pn.global << endl;
		
		string PFN{ "101010110101010101010" };
		string unused{ "000" };
		string CCA{ "101" };
		bitset<32>v9{ string(PFN+unused+CCA+"1010") };
		print(v9);
		unsigned long n = v9.to_ulong();
		cout << dec<<"n = " << n << endl;
		
		bitset<32>v10{ 0x7 };
		bitset<32>v11{ (v9 >> 4)&v10 };
		cout << v11 << endl;	// Le champ CCA est bien isolé et ressort à la bonne valeur, soit 101
		


		// Exo 13 : encryption
		const int nchar = 2 * sizeof(long);
		const int kchar = 2 * nchar;

		string op{};
		string key{};
		string infile{};
		string outfile{};
		char action{};

		cout << "Enter input file name, output file name, key and (Encrypt or Decrypt) :" << endl;
		cin >> infile >> outfile >> key>>action;

		while (key.size() < kchar) key += '0';
		ifstream inf(infile);
		ofstream outf(outfile);
		if (!inf || !outf) My_error("bad file name");
		if (!is_valid_action(action)) My_error("invalid action");

		const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

		switch (action)
		{
			case 'E':
			case 'e':
			{  
				
				unsigned long outptr[2];
				char inbuf[nchar];
				unsigned long* inptr = reinterpret_cast<unsigned long *>(inbuf);
				int count = 0;

				while (inf.get(inbuf[count])) {
					outf << hex;
					if (++count == nchar) {
						encipher(inptr, outptr, k);
						outf << setw(8) << setfill('0') << outptr[0] << ' ' << setw(8) << setfill('0') << outptr[1] << ' ';
						count = 0;
					}

				}

				if (count) {
					while (count != nchar)inbuf[count++] = '0';
					encipher(inptr, outptr, k);
					outf << outptr[0] << ' ' << outptr[1] << ' ';

				}
				cout << "file encrypted" << endl;
				break;
			}

			case 'D':
			case 'd':
			{  
				unsigned long inptr[2];
				char outbuf[nchar + 1];
				outbuf[nchar] = 0;
				unsigned long* outptr = reinterpret_cast<unsigned long *>(outbuf);
				inf.setf(ios_base::hex, ios_base::basefield);

				while (inf>>inptr[0]>>inptr[1]) {
					decipher(inptr, outptr, k);
					outf << outbuf;
						
				}
				cout << "file decrypted" << endl;
				break;
			}
		
		default:
			break;
		}
		
		

		// Exo 15
		vector<int*>p(10000);

		RunAndMeasure([&]() { 
		
		
			// Création de 10 000 objets d'une taille aléatoire sur le tas
			for (unsigned int i=0;i<10000;++i) {
				p[i] = new int[random_number(0,1000)];		// Allocate n ints on free store
			
			}
		
		});

		RunAndMeasure([&]() {
			// Destruction de ces mêmes objets : en moyenne, le delete est deux fois plus rapide que le new
			for (unsigned int i = 0; i < 10000; ++i) {
				delete p[i];
			}

		});
		

		keep_window_open();

		return 0;
	}


	catch (runtime_error& e)
	{	// this code is to produce error messages
		cout << e.what() << '\n';
		keep_window_open("q");	// For some Windows(tm) setups
	}
}