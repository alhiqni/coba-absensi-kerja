#include <iostream>
#include <fstream>
#include <string>

void namaNbulan()
{
	//nama
	printf("\tDAKA\t\t");
	//bulan
	printf("April");
}
int sum (int a,int b)
{ 
	int hasil;
	hasil = a+b;
	return hasil;
}
void checkDatabase(std::fstream &data)
{
	data.open("data.bin", std::ios::out | std::ios::in | std::ios::binary);
	//pengecekan data ada atau tidak
	//command untuk mengecek data ada atau tidak :
	// ~~~~~~~~~v~~~~~~~
	if (data.is_open())
	{
		printf("Database: O\n");
	}
	else
	{
		printf("Database: X\n");
		data.close();
		data.open("data.bin", std::ios::trunc | std::ios::out | std::ios::in | std::ios::binary);
	}
}
int getOption()
{	
	std::fstream data;
	int input;
	system("cls");
	checkDatabase(data);
	namaNbulan();
	printf("\n\t_____________________________\n");
	printf("\t| Program Absensi Sederhana |\n");
	printf("\t|===========================|\n");
	printf("\t|1. Tambahkan jam kerja     |\n");
	printf("\t|2. Tampilkan jam kerja     |\n");
	printf("\t|3. Ubah jam kerja          |\n");
	printf("\t|4. Reset jam kerja         |\n");
	printf("\t|5. Selesai                 |\n");
	printf("\t|===========================|\n\n");
	printf("Pilih[1-5] : ");
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
	return input;
}

void writeData(std::fstream &data,int posisi,Pekerja &inputPekerja)
{
	data.seekp((posisi-1)*sizeof(inputPekerja),std::ios::beg);
	data.write(reinterpret_cast<char*>(&inputPekerja),sizeof(Pekerja));
}
int getDataSize(std::fstream &data)
{
	int start, end;
	data.seekg(0,std::ios::beg);
	start = data.tellg();
	data.seekg(0,std::ios::end);
	end = data.tellg();
	return (end-start)/sizeof(Pekerja);
}
Pekerja readData(std::fstream &data, int posisi)
{
	Pekerja readPekerja;
	data.seekg((posisi - 1)*sizeof(Pekerja), std::ios::beg);
	data.read(reinterpret_cast<char*>(&readPekerja),sizeof(Pekerja));	
	return readPekerja;
}

void tambahDataPekerja(std::fstream &data)
{
	Pekerja inputPekerja, lastPekerja;
	int a,b;

	int size= getDataSize(data);
	std::cout << "Tanggal: " << size + 1 << "\t\t";
	std::cout << "Jumlah Data: " << size << "\t";
	if(size == 0)
	{
		inputPekerja.pk = 1;
	}
	else
	{
		lastPekerja = readData(data,size);
		std::cout << "pk = " << lastPekerja.pk << std::endl;
		inputPekerja.pk = lastPekerja.pk + 1;
	}
	printf("\nJam Masuk: ");
	std::cin >> inputPekerja.jam1;
	printf("Jam Keluar: ");
	std::cin >> inputPekerja.jam2;
	a = inputPekerja.jam1;
	b = inputPekerja.jam2;
	std::cout << a << " " << b << std::endl;
	inputPekerja.jam3 = b-a ;

	writeData(data,size + 1,inputPekerja);
}

void displayDataPekerja(std::fstream &data)
{
	int hasil = 0,size = getDataSize(data);
	Pekerja showPekerja;
	printf("Tanggal\t\tMasuk\t\tKeluar\t\tkerja\t\tpk.\n");
	for (int i = 1;i <= size; i++)
	{
		showPekerja = readData(data,i);
		std::cout << i << "\t\t";
		std::cout << showPekerja.jam1 << "\t\t";
		std::cout << showPekerja.jam2 << "\t\t";
		std::cout << showPekerja.jam3 << " jam"<< "\t\t";
		std::cout << showPekerja.pk << std::endl;
		hasil = sum(hasil,(int)showPekerja.jam3);
	}
	std::cout << "\t\t\t\t\t" << "Total:  " <<  hasil << " jam" << std::endl;
	std::cout << "Penghasilan: Rp. " << hasil*6000 << std::endl;
}

void updateRecord(std::fstream &data)
{
	int nomor;
	Pekerja updatePekerja;
	std::cout << "pilih no: ";
	std::cin >> nomor;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

	updatePekerja = readData(data,nomor);
	std::cout << "\n\npilihan data: " << std::endl;
	std::cout << "Jam Masuk : " << updatePekerja.jam1 << std::endl;
	std::cout << "Jam Keluar : " << updatePekerja.jam2 << std::endl;
	std::cout << "Total : " << updatePekerja.jam3 << std::endl;

	std::cout << "\nMerubah data: "<< std::endl;
	std::cout << "Jam Masuk: ";
	std::cin >> updatePekerja.jam1;
	std::cout << "Jam Keluar: ";
	std::cin >> updatePekerja.jam2;
	updatePekerja.jam3 = updatePekerja.jam2 - updatePekerja.jam1;
	writeData(data,nomor,updatePekerja);
}