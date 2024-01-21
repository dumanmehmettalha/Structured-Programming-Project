#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define N 10
#define MAX 20
/*
skor tutualacak ve gösterilecek
*/

struct kullanici{
	char ad[20],soyad[10],kullanici_adi[12],sifre[8];
	int skor;
};

char** haritaOlustur(char* fileName,int* boyut1,int* boyut2) ; 
int hesapOlustur(struct kullanici kullanicilar[],int kullanici_sayisi);
void anaMenu(struct kullanici kullanicilar[],int kullanici_sayisi,int* cikis);
void playManual();
void playAuto();
void skorYazdir(struct kullanici kullanicilar[]);
int baslangic(struct kullanici* kullanicilar,int* kullanici_sayisi);
void findEntry(char** matris, int* boyut1, int* boyut2, int* entryRow, int* entryCol);
void freeMatris(char** matris,int boyut);
void printMatrix(char** matris,int boyut1,int boyut2);
void sort(int arr[],int boyut);

int main(){
	int kullanici_sayisi=0;
	int control=0;
	int cikis=0;
	//char p=80,ap=112,e=101,ae=69; // matristeki karakterler p=P ap=p ae=e e=E
	struct kullanici kullanicilar[N]; 
	do{
		control=baslangic(kullanicilar,&kullanici_sayisi); // login ve hesap oluþturma
		cikis=control;
		//perror("burdaaa");
		while(cikis==0 && control==0){
			anaMenu(kullanicilar,kullanici_sayisi,&cikis); // ana menü buradaki seçime göre hareket edilecek
			//printf("Cikis yapiliyor....");
		
		}
	}while(control==0);
	return 0;
}

char** haritaOlustur(char* fileName, int* boyut1, int* boyut2) {
    int i, j;
    char temp;
    char** matris;

    FILE* fp = fopen(fileName, "r");
    if (!fp) {
        printf("Dosya Acilamadi!");
        return NULL;
    }

    fscanf(fp, "%d %d", boyut1, boyut2);

    matris = (char**)malloc(*boyut1 * sizeof(char*));
    if (matris == NULL) {
        printf("%s:%d> Can not allocate memory for the array...\n", __FILE__, __LINE__);
        return NULL;
    }

    for (i = 0; i < *boyut1; i++) {
        matris[i] = (char*)malloc(*boyut2 * sizeof(char));
    }
    
    while (fscanf(fp, "%d %d %c\n", &i, &j, &temp) == 3) {
        if (i < *boyut1 && j < *boyut2) {
            matris[i][j] = temp;
        } else {
            printf("Hatali indis: %d %d\n", i, j);
        }
    }

    fclose(fp);
    return matris;
}


int baslangic(struct kullanici* kullanicilar, int* kullanici_sayisi) {
    int ctrl, flag = 1, i; // flag baþlangýçta 1 olmalýdýr.
    char kull_adi[20], sifre[20];

    printf("Karsit Madde Labirentine Hosgeldiniz.\nHesabiniz varsa giris yapmak icin 1'e, yoksa hesap olusturmak icin 2'ye basiniz.\n");
    scanf("%d", &ctrl);

    if (ctrl == 1) {
        printf("\nKullanici adinizi giriniz: ");
        scanf("%s", kull_adi);

        for (i = 0; i < *kullanici_sayisi; i++) {
        //	perror("Enters For Loop");
            if (strcmp(kull_adi, kullanicilar[i].kullanici_adi) == 0) {
                printf("\nSifrenizi giriniz: ");
                scanf("%s", sifre);
                if (strcmp(sifre, kullanicilar[i].sifre) == 0) {
                    printf("\nBasariyla giris yapildi.");
                    flag = 0;
                    return flag;
                } else {
                    printf("\nSifre hatali.");
                }
                break; // Kullanýcý bulunduðunda döngüden çýk
            }
        }

        if (flag == 1) {
            printf("\nGirmis oldugunuz kullanici adinda bir kullanici bulunamadi.\nCikis Yapiliyor....");
            return flag;
        }
    } else if (ctrl == 2) {
        *kullanici_sayisi=hesapOlustur(kullanicilar, *kullanici_sayisi);
        //printf("%d 2",*kullanici_sayisi);
        if(kullanici_sayisi>=0){
			return 0; //hata yok devam
		}
		return 1; // hata var döngüyü kýr 
    } else {
        printf("Hatali bir sayi girdiniz.\nLutfen Ana Menu'de 5 i tuslayiniz..");
        return 0;
    }

    return -1; // Hata durumunu temsil eden bir deðer
}

void playManual(struct kullanici* kul){ // oyunu manual oynama kodunu yaz 
	int control,i,k,j,cikis=1,antiP=0,pCount=0,antiE=0,eCount=0,skor=0;
	char fileName[50];
	char a,tmp;
	char** matris;
	int boyut1,boyut2;
	printf("Matrisi dosyadan okumak icin 1, hazir matrisi kullanmak icin herhangi bir rakam giriniz.");
	scanf("%d",&control);
	if(control==1){
		printf("Lutfen harita dosyasinin ismini giriniz.");
		scanf("%s",fileName);
		matris=haritaOlustur(fileName, &boyut1, &boyut2);
	}
	else {
    boyut1 = 6;
    boyut2 = 10;
	matris = (char**)malloc(boyut1 * sizeof(char*));
    for (i = 0; i < boyut1; i++) {
        matris[i] = malloc(boyut2 * sizeof(char));
    }

    char exampleMatris[6][10] = {
        {'0', '0', '1', '0', 'P', '0', 'e', '0', 'p', '0'},
        {'1', '0', 'p', '0', '1', 'E', '1', '0', '1', '0'},
        {'1', 'G', '1', '0', '1', '0', '1', '0', '0', 'K'},
        {'0', '0', 'P', '0', 'p', '0', '0', '0', '1', '0'},
        {'0', '1', '1', '0', 'K', 'C', '1', '0', '1', '0'},
        {'0', '0', '0', '0', '1', '0', 'p', '0', '0', '0'}
    };

    for (i = 0; i < boyut1; i++) {
        for (j = 0; j < boyut2; j++) {
            matris[i][j] = exampleMatris[i][j];
        }
    }
	}
	findEntry(matris,&boyut1,&boyut2,&k,&j);

	printMatrix(matris,boyut1,boyut2);
	i=20;
	while(i>0&&cikis==1){
		printf("Geri Sayim:%d\n",i);
		a = getch();
		if (a==27){ //esc ise çýk
			printf("Cikis\n");
			freeMatris(matris,boyut1);
			break;
		}
		else{
			a = getch();
			printf("Bastiginiz ok tusu:%d\n",a); //w:119 a:97 s:115,d:100
		}
		if(a==72){
		//	perror("w");
			k--; // bir yukarý
			if(matris[k][j]=='1'){
				k++;
			}
		}
		else if(a==75){
		//	perror("a");
			j--; // bir sol
			if(matris[k][j]=='1'){
				j++;
			}
		}
		else if(a==80){
		//	perror("s");
			k++; // bir alt
			if(matris[k][j]=='1'){
				k--;
			}
		}
		else if(a==77){
		//	perror("d");
			j++; // bir sað
			if(matris[k][j]=='1'){
				j--;
			}
		}
		else{
			printf("Hatali yon tusu");
		}
		if((k<boyut1&&j<boyut2) && (k>=0&&j>=0)){ // sýnýrlarý aþmýyorsak gir
				if(matris[k][j]=='K'){
					printf("\nKaradelige girdin, kaybettin.\n");
					freeMatris(matris,boyut1);
					cikis=0;
				}else if(matris[k][j]=='C'){
					printf("\nCikisa ulastiniz.\n");
					if(antiP<antiE){
						printf("\n %d adet karsit madde uretildi.",antiP);
						kul->skor=(antiP*2)+eCount+pCount;
					}else{
						printf("\n %d adet karsit madde uretildi.",antiE);
						kul->skor=(antiE*2)+eCount+pCount;
					}
					printf("\nSkorunuz: %d\n",kul->skor);
					freeMatris(matris,boyut1);
					cikis=0;
				}else{
					tmp=matris[k][j];
					matris[k][j]='X';
					printMatrix(matris,boyut1,boyut2);
					matris[k][j]=tmp;
				}
		}else{
			if(k>=boyut1||k<0){
				if(k>=boyut1){
					k=boyut1-1;
				}else if(k<0){
					k=0;
				}
			}
			else if(j>=boyut2||j<0){
				if(j>=boyut2){
					j=boyut2-1;
				}
				else if(j<0){
					j=0;
				}
			}
			printf("\nLutfen oyun tahtasi sinirlarina dikkat edin. \n");
			//printMatrix(matris,boyut1,boyut2);
		}
		// matristeki karakterler p=P ap=p ae=e e=E
		if(matris[k][j]=='P'){
			pCount++;
			printf("\nBir proton elde ettiniz.\n");
		}
		else if(matris[k][j]=='p'){
			antiP++;
			printf("\nBir karsit proton elde ettiniz.\n");

		}
		else if(matris[k][j]=='e'){
			eCount++;
			printf("\nBir elektron elde ettiniz.\n");

		}else if(matris[k][j]=='E'){
			antiE++;
			printf("\nBir karsit elektron elde ettiniz.\n");

		}
		sleep(1);
		i--;
		system("cls"); 
	}
	
}
void playAuto(){
	printf("\nHenuz otomatik oynama kodu yazilmadi.\n");
}
void anaMenu(struct kullanici kullanicilar[],int kullanici_sayisi,int* cikis){ // düzenle
	int secim;
	printf("\nANA MENU\n");
//	printf("En yuksek skorlar: \n");
	printf("Lutfen menu seciminizi yapiniz.\n1.Nasil Oynanir\n2.Skor Tablosu\n3.Kendin Oyna\n4.Otomatik Oyna\n5.Ust Menu\n6.Oyundan Cik\nSecim: ");
	scanf("%d",&secim);
	switch(secim) {
		case 1:
			printf("\nG:giris, C:cikis, X:konum, K:Karadelik, P:karsit proton, p:proton, E:karsit elektron, e:elektron, 1:duvar, 0:yol\nYon tuslari ile hareket ederek karsit e ve p toplamaya calisin, K dan kacinin.\n"); 
			break;
		case 2:
			skorYazdir(kullanicilar);
			break;
		case 3: 
			playManual(&kullanicilar[kullanici_sayisi-1]);
			break;
		case 4:
			playAuto();
			break;
		case 5:
			*cikis=1;
			break;
		case 6:
			exit(1);
			break;
	}
}

void findEntry(char** matris, int* boyut1, int* boyut2, int* entryRow, int* entryCol) {
    int i, j,found=0;
    for (i = 0; i < *boyut1; i++) {
        for (j = 0; j < *boyut2; j++) {
            if (matris[i][j] == 'G') { // kontrolde bir sýkýntý var 
                *entryRow = i;
                *entryCol = j;
                found=1;
            }
        }
    }
    // G bulunmazsa -1 döndür
    if(found==0){
    *entryRow = -1;
    *entryCol = -1;}
}

int hesapOlustur(struct kullanici kullanicilar[],int kullanici_sayisi){
	char ad[20],soyad[10],kullanici_adi[12],sifre[8];
	struct kullanici k;
	int i=0,index;
	printf("Hesap olusturma ekranina hosgeldiniz.\n");
	printf("Isminizi giriniz:");
	scanf("%s",ad);
	printf("\nSoy isminizi giriniz:");
	scanf("%s",soyad);
	printf("\nKullanici adi giriniz: ");
	scanf("%s",kullanici_adi);	
	for(i=0;i<kullanici_sayisi;i++){
		if(strcmp(kullanicilar[i].kullanici_adi,kullanici_adi)==0){
			printf("Girdiginiz kullanici adina sahip bir kullanici bulunuyor.\nLutfen baska bir kullanici adi giriniz: ");
			scanf("%s",kullanici_adi);
			strcpy(k.kullanici_adi,kullanici_adi);
		}
	}
	printf("\nSifre giriniz:");
	scanf("%s",sifre);
	strcpy(k.ad,ad);
	strcpy(k.soyad,soyad);
	strcpy(k.kullanici_adi,kullanici_adi);
	strcpy(k.sifre,sifre);
	k.skor=0;
	//printf("%d %d",kullanici_sayisi,N);
	if (kullanici_sayisi < N) {
    	//perror("Kayýtt.");
    	kullanicilar[kullanici_sayisi] = k;  
    	return ++kullanici_sayisi; 
	} else {
		printf("Maximum kullanici sayisina ulasildi.\n");
		return -1;
	}

}

void skorYazdir(struct kullanici kullanicilar[]){
	int i;
	int arr[N]={0};
	for(i=0;i<N;i++){
		arr[i]=kullanicilar[i].skor;
	//	printf("\n\nkull skor: %d\n\n",kullanicilar[i].skor);
	}
	sort(arr,N-1);
	for(i=0;i<5;i++){
		printf("%d. %d\n",i+1,arr[i]);
	}
}
void printMatrix(char** matris,int boyut1,int boyut2){
	int i,j;
	for(i=0;i<boyut1;i++){
		for(j=0;j<boyut2;j++){
			printf(" %c ",matris[i][j]);
		}
		printf("\n");
	}
}
void freeMatris(char** matris,int boyut){
	int i;
	for(i=0;i<boyut;i++){
		free(matris[i]);
	}
	free(matris);
	printf("\nMatris alaný bosaltildi.\n");
}
void sort(int arr[], int boyut) {
    int i, j, tmp;
    for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut - i - 1; j++) {
        	if(arr[j]>=100){ //garbage value dan kurtulmak için 
        		arr[j]=0;
			}
            if (arr[j] < arr[j+1]) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}


