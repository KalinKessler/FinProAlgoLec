// Final Project AlgoProg
// Albertus Giovanni
// LA20
// 2602076866
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

//mereturn baris dimana nama yang dicari, apabila tidak ada return -1
int cariNama(char nama[105])
{
	char namaFormat[105]="Nama              : ";
	strcat(namaFormat, nama);
	strcat(namaFormat, "\n");
	
	int lineNama = -1;
	int line = 0;
	char tmp[105];
	FILE *fptr = fopen("bbideal.txt","r");
	while(fgets(tmp,sizeof(tmp),fptr))
	{
		++line;
		if(strcmp(namaFormat,tmp) == 0)
		{
			lineNama = line;
			break;
		}
	}
	fclose(fptr);
	return lineNama;
}

//untuk print agar rapi
void printDesign(char s[205])
{
	printf("| ");
	for(int i=0;i<strlen(s)-1;i++) printf("%c",s[i]);
	for(int i=0;i<97-strlen(s);i++) printf(" ");
	printf(" |\n");
}

int main()
{
	FILE *fptr;
	FILE *fptr2;
	char tmp[105];
	char nama[105];
	int tinggi, berat;
	double bmi;
	
	fptr = fopen("bbideal.txt","a");
	fclose(fptr);
	
	while(1)
	{
		//display menu
		printf("1. Tambah Data Baru\n");
		printf("2. Lihat Semua Data\n");
		printf("3. Sort Data (Berdasarkan Nama)\n");
		printf("4. Cari Data Orang\n");
		printf("5. Modify Data\n");
		printf("6. Hapus Data\n");
		printf("7. Exit\n");
		printf("Choice: ");
		
		int choice;
		scanf("%d",&choice);
		printf("\n");
		gets(tmp);
		
		//menambah data baru
		if(choice == 1)
		{
			system("cls");
			printf("Silahkan input data berikut.\n");
			printf("Nama: ");
			gets(nama);
			
			if(cariNama(nama) != -1)
			{
				printf("Nama sudah ada di dalam data, silahkan ke menu modify data.\n\n");
				system("pause");
				system("cls");
				continue;
			}
			
			printf("Tinggi badan (dalam cm): ");
			scanf("%d",&tinggi);
			printf("Berat badan (dalam kg): ");
			scanf("%d",&berat);
			
			//hitung bmi dan range bb ideal
			bmi = (double) berat / (tinggi / 100.0) / (tinggi / 100.0);
			double bbIdealMinimum = 18.5 * (tinggi / 100.0) * (tinggi / 100.0);
			double bbIdealMaximum = 24.9 * (tinggi / 100.0) * (tinggi / 100.0);
			
			//tulis ke dalam file
			fptr = fopen("bbideal.txt","a");
			
			fprintf(fptr,"Nama              : %s\n",nama);
			fprintf(fptr,"Tinggi badan      : %d cm\n",tinggi);
			fprintf(fptr,"Berat badan       : %d kg\n",berat);
			fprintf(fptr,"BMI               : %.2f\n",bmi);
			fprintf(fptr,"Berat badan ideal : %.2f - %.2f kg\n",bbIdealMinimum, bbIdealMaximum);
			
			if(bmi < 18.5) fprintf(fptr,"Status            : Under Weight\n");
			else if(bmi < 25) fprintf(fptr,"Status            : Normal\n");
			else if(bmi < 30) fprintf(fptr,"Status            : Over Weight\n");
			else if(bmi < 35) fprintf(fptr,"Status            : Obesity (Class I)\n");
			else if(bmi < 40) fprintf(fptr,"Status            : Obesity (Class II)\n");
			else fprintf(fptr,"Status            : Extreme Obesity\n");
			
			fprintf(fptr,"\n");
			
			fclose(fptr);
			
			printf("\n");
			system("pause");
			system("cls");
		}
		//menampilkan semua data
		else if(choice == 2)
		{
			system("cls");
			printf("====================================================================================================\n");
			printf("|                                                                                                  |\n");
			printf("|                             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                         |\n");
			printf("|                             ~  DATA BERAT BADAN IDEAL  ~                                         |\n");
			printf("|                             ~~~~~~~~~~~~~~~~~~~~~~~~~~~~                                         |\n");
			printf("|                                                                                                  |\n");
			printf("====================================================================================================\n");
			
			fptr = fopen("bbideal.txt","r");
			
			while(fgets(tmp,sizeof(tmp),fptr))
			{
				printDesign(tmp);
			}
			
			fclose(fptr);
			
			printf("====================================================================================================\n\n");
			system("pause");
			system("cls");
		}
		//sort data berdasarkan nama
		else if(choice == 3)
		{
			system("cls");
			char isiBaris[1005][105];
			int baris = 0;
			
			//simpan isi file dalam array isiBaris
			fptr = fopen("bbideal.txt","r");
			
			while(fgets(tmp,sizeof(tmp),fptr))
			{
				baris++;
				strcpy(isiBaris[baris],tmp);
			}
			
			fclose(fptr);
			
			//cari banyak orang dan baris awal dan akhir data nama orang tersebut
			int banyakOrang = 0;
			int barisMulai[1005];
			int barisAkhir[1005];
			
			for(int i=1;i<=baris;i++)
			{
				if(isiBaris[i][0] == 'N')
				{
					banyakOrang++;
					barisMulai[banyakOrang] = i;
				}
			}
			for(int i=1;i<banyakOrang;i++) barisAkhir[i] = barisMulai[i+1] - 1;
			barisAkhir[banyakOrang] = baris;
			
			//proses sorting berdasarkan nama
			for(int i=1;i<banyakOrang;i++)
			{
				for(int j=1;j<banyakOrang;j++)
				{
					if(strcmp(isiBaris[barisMulai[j]],isiBaris[barisMulai[j+1]]) > 0)
					{
						int tmpint = barisMulai[j];
						barisMulai[j] = barisMulai[j+1];
						barisMulai[j+1] = tmpint;
						
						tmpint = barisAkhir[j];
						barisAkhir[j] = barisAkhir[j+1];
						barisAkhir[j+1] = tmpint;
					}
				}
			}
			
			//isi ke file baru nama yang sudah disort
			fptr2 = fopen("bbideal2.txt","a");
			for(int i=1;i<=banyakOrang;i++)
			{
				for(int j=barisMulai[i];j<=barisAkhir[i];j++)
				{
					fprintf(fptr2,"%s",isiBaris[j]);
				}
			}
			fclose(fptr2);
			
			//file lama direplace dengan file baru
			remove("bbideal.txt");
			rename("bbideal2.txt","bbideal.txt");
			
			printf("Data berhasil disort berdasarkan nama.\n\n");
			system("pause");
			system("cls");
		}
		//cari data orang tertentu 
		else if(choice == 4)
		{
			system("cls");
			printf("Nama yang ingin dicari: ");
			gets(nama);
			
			if(cariNama(nama) == -1)
			{
				printf("Nama tidak ada.\n\n");
				continue;
			}
			
			int barisNama = cariNama(nama);
			int baris = 0;
			
			printf("====================================================================================================\n");
			
			fptr = fopen("bbideal.txt","r");
			
			while(fgets(tmp,sizeof(tmp),fptr))
			{
				baris++;
				if(baris == barisNama)
				{
					printDesign(tmp);
					while(fgets(tmp,sizeof(tmp),fptr))
					{	
						if(tmp[0] == '\n') break;
						printDesign(tmp);	
					}
					break;
				}
			}
			
			fclose(fptr);
			
			printf("====================================================================================================\n\n");
			system("pause");
			system("cls");
		}
		//modify data orang tertentu
		else if(choice == 5)
		{
			system("cls");
			printf("Nama yang ingin dimodify datanya: ");
			gets(nama);
			
			if(cariNama(nama) == -1)
			{
				printf("Nama tidak ada.\n\n");
				continue;
			}
			
			printf("Tinggi badan (dalam cm): ");
			scanf("%d",&tinggi);
			printf("Berat badan (dalam kg): ");
			scanf("%d",&berat);
			
			//hitung bmi dan range bb ideal
			bmi = (double) berat / (tinggi / 100.0) / (tinggi / 100.0);
			double bbIdealMinimum = 18.5 * (tinggi / 100.0) * (tinggi / 100.0);
			double bbIdealMaximum = 24.9 * (tinggi / 100.0) * (tinggi / 100.0);
			
			int barisNama = cariNama(nama);
			int baris = 0;
			
			fptr = fopen("bbideal.txt","r");
			fptr2 = fopen("bbideal2.txt","a");
			
			while(fgets(tmp,sizeof(tmp),fptr))
			{
				baris++;
				
				if(baris == barisNama)
				{
					fprintf(fptr2,"%s",tmp);
					while(fgets(tmp,sizeof(tmp),fptr))
					{
						baris++;
						//tambahkan data pada tempat nama yang dicari
						if(tmp[0] == '\n')
						{
							fprintf(fptr2,"Tinggi badan      : %d cm\n",tinggi);
							fprintf(fptr2,"Berat badan       : %d kg\n",berat);
							fprintf(fptr2,"BMI               : %.2f\n",bmi);
							fprintf(fptr2,"Berat badan ideal : %.2f - %.2f kg\n",bbIdealMinimum, bbIdealMaximum);
							
							if(bmi < 18.5) fprintf(fptr2,"Status            : Under Weight\n");
							else if(bmi < 25) fprintf(fptr2,"Status            : Normal\n");
							else if(bmi < 30) fprintf(fptr2,"Status            : Over Weight\n");
							else if(bmi < 35) fprintf(fptr2,"Status            : Obesity (Class I)\n");
							else if(bmi < 40) fprintf(fptr2,"Status            : Obesity (Class II)\n");
							else fprintf(fptr2,"Status            : Extreme Obesity\n");
							
							fprintf(fptr2,"\n");
							break;
						}
						fprintf(fptr2,"%s",tmp);
					}
				}
				else
				{
					fprintf(fptr2,"%s",tmp);
				}
			}
			
			fclose(fptr);
			fclose(fptr2);
			
			//replace file lama dengan file baru
			remove("bbideal.txt");
			rename("bbideal2.txt","bbideal.txt");
			
			printf("Data berhasil dimodify.\n\n");
			system("pause");
			system("cls");
		}
		//hapus data orang tertentu
		else if(choice == 6)
		{
			system("cls");
			printf("Nama yang ingin dihapus: ");
			gets(nama);
			
			if(cariNama(nama) == -1)
			{
				printf("Nama tidak ada.\n\n");
				continue;
			}
			
			int barisNama = cariNama(nama);
			int baris = 0;
			
			fptr = fopen("bbideal.txt","r");
			fptr2 = fopen("bbideal2.txt","a");
			
			while(fgets(tmp,sizeof(tmp),fptr))
			{
				baris++;
				
				if(baris == barisNama)
				{
					while(fgets(tmp,sizeof(tmp),fptr))
					{
						baris++;
						if(tmp[0]=='\n') break;
					}
				}
				else
				{
					fprintf(fptr2,"%s",tmp);
				}
			}
			
			fclose(fptr);
			fclose(fptr2);
			
			//replace file lama dengan file baru
			remove("bbideal.txt");
			rename("bbideal2.txt","bbideal.txt");
			
			printf("Data berhasil terhapus.\n\n");
			system("pause");
			system("cls");
		}
		//exit program
		else if(choice == 7)
		{
			printf("Program berakhir.\n");
			break;
		}
	}
}
