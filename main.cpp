#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include "struct_Pekerja.h"
#include "func_p.h"

 // using namespace std;





// int sum (int a,int b);
// int getOption();
// void checkDatabase(std::fstream &data);
// void writeData(std::fstream &data,int posisi,Pekerja &inputPekerja);
// int getDataSize(std::fstream &data);
// Pekerja readData(std::fstream &data, int posisi);
// void tambahDataPekerja(std::fstream &data);
// void displayDataPekerja(std::fstream &data);
// void updateRecord(std::fstream &data);

int main()
{
	std::fstream data;
	// checkDatabase(data);
	int pilihan = getOption();
	char is_continue;
	enum opsi{Buat=1, Baca, Ubah, Hapus, Selesai };

	while( pilihan != Selesai)
	{
		switch(pilihan)
		{
			case Buat:
				printf("Tambahkan jam kerja\n");
				tambahDataPekerja(data);
				break; 
			case Baca:
				printf("Tampilkan jam kerja\n");
				displayDataPekerja(data);
				break; 
			case Ubah:
				printf("Ubah jam kerja\n");
				displayDataPekerja(data);
				updateRecord(data);
				displayDataPekerja(data);
				break; 
			case Hapus:
				printf("Reset jam kerja\n");
				kesinilagi:
				printf("Apakah anda yakin? (y/n): ");
				std::cin >> is_continue;
				if ( (is_continue== 'y') | (is_continue == 'Y') )
				{
					data.close();
					data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);
				}
				else if ( (is_continue== 'n') | (is_continue == 'N') )
				{
					break;
				}
				else 
				{
				goto kesinilagi;
				}

				break; 
			default: 
				printf("Pilihan tidak ditemukan\n");
				break;
		}

		kesini:
		printf("Lanjutkan? (y/n) : ");
		std::cin >> is_continue;
		if ( (is_continue== 'y') | (is_continue == 'Y') )
			{
				pilihan = getOption();
			}
		else if ( (is_continue== 'n') | (is_continue == 'N') )
			{
				break;
			}
		else 
			{
				goto kesini;
			}
	}
	printf("ahir dari program\n");
	std::cin.get();
	return 0;
}
