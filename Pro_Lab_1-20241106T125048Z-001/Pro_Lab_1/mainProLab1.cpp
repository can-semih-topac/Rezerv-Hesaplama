#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>
int maliyet_hesapla(float maliyet[5])
{
	float uygun_maliyet=maliyet[0];
	int uygun_olan=0;
	for(int i=1;i<5;i++)
	{
		if(maliyet[i]<uygun_maliyet)
		{
			uygun_maliyet=maliyet[i];
			uygun_olan = i;
		}
	}
	return (uygun_olan); // bu bize hangi indexteki ihtimalin en uygun olduðunu dondurecek.	
}

int boyali_mi(int x,int y,int renk)
{
	if(getpixel(x,y)==BLUE)
	{
		return 1;
	}	
		return 0;
}
int kontrol(int enkucuk_x,int enkucuk_y,int blok_buyuklugu,float birim_sondaj,float birim_platform,int ideal)
{
		setcolor(4);
		int kontrol1=0;
		int kontrol2=0;
		int kontrol3=0;
		int kontrol4=0;
		for(int i=0;i<=(blok_buyuklugu/2)*10;i++)//1. kare
		{
			for(int j=0;j<=(blok_buyuklugu/2)*10;j++)
			{
			if(boyali_mi((enkucuk_x*10)+j,(enkucuk_y*10)+i,1))
				{
				kontrol1=1;
				}
			}
		}
		for(int i=(blok_buyuklugu/2)*10;i<=blok_buyuklugu*10;i++)//2.kare
			{
			for(int j=0;j<=(blok_buyuklugu/2)*10;j++)
			{
			if(boyali_mi((enkucuk_x*10)+j,(enkucuk_y*10)+i,1))
				{	
				kontrol2=1;
				}
			}
		}
		for(int i=0;i<=(blok_buyuklugu/2)*10;i++)//3. kare
		{
			for(int j=(blok_buyuklugu/2)*10;j<=blok_buyuklugu*10;j++)
			{
			if(boyali_mi((enkucuk_x*10)+j,(enkucuk_y*10)+i,1))
				{
				kontrol3=1;
				}
			}
		}
		for(int i=(blok_buyuklugu/2)*10;i<=blok_buyuklugu*10;i++)//4. kare
		{
			for(int j=(blok_buyuklugu/2)*10;j<=blok_buyuklugu*10;j++)
			{
			if(boyali_mi((enkucuk_x*10)+j,(enkucuk_y*10)+i,1))
				{
				kontrol4=1;
				}
			}
		}
		int kare_sayisi=kontrol1+kontrol2+kontrol3+kontrol4;
		if(((kare_sayisi*birim_sondaj*pow(blok_buyuklugu/2,2))+(kare_sayisi*birim_platform) < (birim_sondaj*pow(blok_buyuklugu,2)+birim_platform)) && kare_sayisi<4)
		{	if(ideal)
			{
				if(kontrol1)
				{
					rectangle(enkucuk_x*10,enkucuk_y*10,(enkucuk_x+blok_buyuklugu/2)*10,(enkucuk_y+blok_buyuklugu/2)*10);	
				}
				if(kontrol2)
				{
					rectangle(enkucuk_x*10,(enkucuk_y+blok_buyuklugu/2)*10,(enkucuk_x+blok_buyuklugu/2)*10,(enkucuk_y+blok_buyuklugu)*10);	
				}				
				if(kontrol3)
				{
					rectangle((enkucuk_x+blok_buyuklugu/2)*10,enkucuk_y*10,(enkucuk_x+blok_buyuklugu)*10,(enkucuk_y+blok_buyuklugu/2)*10);	
				}
				if(kontrol4)
				{
					rectangle((enkucuk_x+blok_buyuklugu/2)*10,(enkucuk_y+blok_buyuklugu/2)*10,(enkucuk_x+blok_buyuklugu)*10,(enkucuk_y+blok_buyuklugu)*10);	
				}	
			}
			return kare_sayisi;
		}
	//rectangle(enkucuk_x*10,(enkucuk_y+blok_buyuklugu)*10,(enkucuk_x+blok_buyuklugu)*10,enkucuk_y*10);
	return 	4;
}

void ciz_i(int mini_dizi[],int nokta_sayisi[],int sekil_sayisi)
{
	setfillstyle(SOLID_FILL,BLUE);
	fillpoly(nokta_sayisi[sekil_sayisi]-1, mini_dizi);
}
void mini_dizi_yap(int konum[10][10][10],int nokta_sayisi[10],int sekil_sayisi,int mini_dizi[])
{
	int sira=0;
	for(int i=0;i<nokta_sayisi[sekil_sayisi]-1;i++)
	{
		mini_dizi[sira]=konum[0][i][sekil_sayisi]*10;	
		sira++;
		mini_dizi[sira]=konum[1][i][sekil_sayisi]*10;
		sira++;
	}
}

int kare_ciz(int enkucuk_x,int enkucuk_y,int blok_buyuklugu,int renk,float birim_sondaj,float birim_platform,int index,float toplam_alan[5],int ideal )
{
		
	for(int i=0;i<=blok_buyuklugu*10;i++)
	{
		for(int j=0;j<=blok_buyuklugu*10;j++)
		{
			if(boyali_mi((enkucuk_x*10)+j,(enkucuk_y*10)+i,renk))
			{
				setcolor(4);
				if(kontrol(enkucuk_x,enkucuk_y,blok_buyuklugu,birim_sondaj,birim_platform,ideal)==4||blok_buyuklugu==1)
				{
				toplam_alan[index]+=pow(blok_buyuklugu,2);	
					if(ideal)
					{
						rectangle(enkucuk_x*10,enkucuk_y*10,(enkucuk_x+blok_buyuklugu)*10,(enkucuk_y+blok_buyuklugu)*10);
					}
				return 1;
				}
				toplam_alan[index]+=kontrol(enkucuk_x,enkucuk_y,blok_buyuklugu,birim_sondaj,birim_platform,ideal)*pow(blok_buyuklugu/2,2);
				return kontrol(enkucuk_x,enkucuk_y,blok_buyuklugu,birim_sondaj,birim_platform,ideal);
			}
		}	
	}	
	return 0;		
}

int dortgen(int konum[2][10][10],int nokta_sayisi[10],int sekil_sayisi,int blok_buyuklugu,float birim_sondaj,float birim_platform,int index,float toplam_alan[5],int ideal,float uygun_olanlar[5])
{
	int kare_sayisi=0;
	int enkucuk_x=konum[0][0][sekil_sayisi];
	int enkucuk_y=konum[1][0][sekil_sayisi];
	int enbuyuk_x=konum[0][0][sekil_sayisi];
	int enbuyuk_y=konum[1][0][sekil_sayisi];
	//****************************************************************************************************************************
	for(int i=1;i<nokta_sayisi[sekil_sayisi]-1;i++)
	{
				// en kucuk x
				if(enkucuk_x>konum[0][i][sekil_sayisi])
		{
			enkucuk_x=konum[0][i][sekil_sayisi];
		}
				//en kucuk y
				if(enkucuk_y>konum[1][i][sekil_sayisi])
		{
			enkucuk_y=konum[1][i][sekil_sayisi];
		}
				//en buyuk x
				if(enbuyuk_x<konum[0][i][sekil_sayisi])
		{
			enbuyuk_x=konum[0][i][sekil_sayisi];
		}
				//en buyuk y
				if(enbuyuk_y<konum[1][i][sekil_sayisi])
		{
			enbuyuk_y=konum[1][i][sekil_sayisi];
		}
	}	
	//****************************************************************************************************************************
		for(int i=enkucuk_x;i<enbuyuk_x;i+=blok_buyuklugu)
		{
			for(int j=enkucuk_y;j<enbuyuk_y;j+=blok_buyuklugu)
			{
				kare_sayisi+=kare_ciz(i,j,blok_buyuklugu,1,birim_sondaj,birim_platform,index,toplam_alan,ideal);
			}
		}
		uygun_olanlar[0]=toplam_alan[index];
		uygun_olanlar[1]=kare_sayisi;
		uygun_olanlar[2]=toplam_alan[index]*birim_sondaj;
		uygun_olanlar[3]=kare_sayisi*birim_platform;
		uygun_olanlar[4]=(toplam_alan[index]*birim_sondaj)+(kare_sayisi*birim_platform);
	return (toplam_alan[index]*birim_sondaj)+(kare_sayisi*birim_platform);		
}

void kareli_koordinat(int init_uzunlugu)
{
	setcolor(8);
	for(int i=10;i<init_uzunlugu;i+=10)
	{
		line(i,0,i,init_uzunlugu);
		line(0,i,init_uzunlugu,i);
	}
}
void cizme(int konum[2][10][10],int nokta_sayisi[10],int sekil_sayisi)
{
	setcolor(1);
	for(int i=0;i<sekil_sayisi;i++)
	{
		for(int j=0;j<nokta_sayisi[i]-1;j++)
		{
			line(konum[0][j][i]*10,konum[1][j][i]*10,konum[0][j+1][i]*10,konum[1][j+1][i]*10);
		}
	}
}

float alan_hesapla(int konum[10][10][10],int sekil_sayisi,int nokta_sayisi[])
{
    float toplam_alan=0;

    toplam_alan+=konum[0][0][sekil_sayisi]*(konum[1][1][sekil_sayisi]-konum[1][nokta_sayisi[sekil_sayisi]-2][sekil_sayisi]);
    toplam_alan+=konum[0][nokta_sayisi[sekil_sayisi]-2][sekil_sayisi]*(konum[1][0][sekil_sayisi]-konum[1][nokta_sayisi[sekil_sayisi]-3][sekil_sayisi]);

    for(int j=1; j<nokta_sayisi[sekil_sayisi]-2; j++)
    {
        toplam_alan+=konum[0][j][sekil_sayisi]*(konum[1][j+1][sekil_sayisi]-konum[1][j-1][sekil_sayisi]);
    }    
    return toplam_alan/2;
}

int main()
{
    
    system("curl https://bilgisayar.kocaeli.edu.tr/prolab1/prolab1.txt > veri.txt");
    FILE *dosya;
    char dizi[109];
    int istenilen_satir;
    dosya = fopen("veri.txt", "r");
    float toplam_alan[5]={0};
    int index=0;
    int ideal=0;
    float birim_sondaj,birim_platform;
    int mini_dizi[20]={0};
    
    if(dosya!=NULL)
	{
		printf("\nHangi satiri istiyorsunuz: ");
		scanf("%d", &istenilen_satir);
        for(int i=0;i<istenilen_satir;i++)
		{	
            fscanf(dosya,"%s",dizi); 
		}
    }
    	else
		{
       	printf("Dosya bos ne Malesef");
		return 1;
    	}
    // printf("%s",dizi); // dizinin alinabildiginden emin olmak icin
    
    int konum[2][10][10]={0};
    char *Nokta_adresi=strtok(dizi,"()");
    int x_ekseni;
    int y_ekseni;
    char dummy;
    int j;
    int sekil_sayisi=0;
    Nokta_adresi=strtok(NULL,"()");
    int nokta_sayisi [4]={0}; //burada verilen nokta sayýsý köþe sayýsýnýn 1 fazlasý
    float uygun_olanlar[5];
    int son_kare_sayisi[10];
    int son_toplam_kare_sayisi=0;
	

    for(int i=0; strcmp(Nokta_adresi,"F")==-1||strcmp(Nokta_adresi,"F")==1; i++)
    {

        for( j=0; j<2; j++)
        {

            sscanf(Nokta_adresi,"%d %c %d",&x_ekseni,&dummy,&y_ekseni);
            konum[0][j][i]=x_ekseni; // xy,nokta_sayisi,sekil_sayisi
            konum[1][j][i]=y_ekseni;
            Nokta_adresi=strtok(NULL,"()");
            nokta_sayisi[sekil_sayisi]++;

        }

        while((konum[0][0][i]==x_ekseni && konum[1][0][i]==y_ekseni)==0)
        {

            sscanf(Nokta_adresi,"%d %c %d",&x_ekseni,&dummy,&y_ekseni);
            konum[0][j][i]=x_ekseni;
            konum[1][j][i]=y_ekseni;
            Nokta_adresi=strtok(NULL,"()");
            j++;
            nokta_sayisi[sekil_sayisi]++;
        }

        sekil_sayisi++;
    }
    initwindow(600,600);   //1. pencereyi açýyor
    
    setcolor(9);
    kareli_koordinat(600);
   //  cizme(konum,nokta_sayisi,sekil_sayisi);
    for(int i=0;i<sekil_sayisi;i++)
	{
		mini_dizi_yap(konum,nokta_sayisi,i,mini_dizi);
		ciz_i(mini_dizi,nokta_sayisi,i);
	}
    for(int i=0;i<sekil_sayisi;i++)
		{
    	dortgen(konum,nokta_sayisi,i,1,birim_sondaj,birim_platform,index,toplam_alan,1,uygun_olanlar);
		son_kare_sayisi[i]=(int)uygun_olanlar[1];
		}
    getch();
    closegraph();
    float alanlar[10];
    for(int i=0;i<sekil_sayisi;i++)
    {
    	printf("\n");
    	alanlar[i]= alan_hesapla(konum,i,nokta_sayisi);
    	printf("\n");
    	printf("\n%d. seklin alani: %d\n",i+1,son_kare_sayisi[i]);
    	printf("%d. seklin rejerv miktari %d dir",i+1,son_kare_sayisi[i]*10);
	}
	toplam_alan[0]=0;
	
	//*********************************************************  2 asama baslangic yeri.
	
    mini_dizi_yap(konum,nokta_sayisi,0,mini_dizi);
    
    
    printf("\n\nBirim sondaj maliyetini girin (1 ile 10 arasinda):");
    scanf("%f",&birim_sondaj);
	while(birim_sondaj<1||birim_sondaj>10)
	{
	printf("\n %.2f Dogru aralikta bir deger degildir.\n",birim_sondaj);
	printf("Birim sondaj maliyetini tekrar girin (1 ile 10 arasinda):");
    scanf("%f",&birim_sondaj);	
	}
	printf("Birim Platform maliyetini girin:");
    scanf("%f",&birim_platform);
    // printf("%.2f %.2f",birim_sondaj,birim_platform);
    
    
    
	initwindow(700,700);
	kareli_koordinat(700);
	for(int i=0;i<sekil_sayisi;i++)
	{
		mini_dizi_yap(konum,nokta_sayisi,i,mini_dizi);
		ciz_i(mini_dizi,nokta_sayisi,i);
	}
	//cizme(konum,nokta_sayisi,sekil_sayisi);
    //kareli_koordinat(600);
   	//kareli_koordinat(700);
   	float gecici_maliyet=0,maliyet[5]={0};
	for(int i2=1;i2<17;i2*=2)
	{
		for(int i=0;i<sekil_sayisi;i++)
		{
    	gecici_maliyet+= dortgen(konum,nokta_sayisi,i,i2,birim_sondaj,birim_platform,index,toplam_alan,0,uygun_olanlar); // çizdirmediðimiz dörtgen
		}
		maliyet[index] =gecici_maliyet;
		index++;
		gecici_maliyet=0;
	}
	int uygun_index = maliyet_hesapla(maliyet);
	
	int blok_dizisi[5]={1,2,4,8,16};
	for(int i=0;i<sekil_sayisi;i++)
		{
    	dortgen(konum,nokta_sayisi,i,blok_dizisi[uygun_index],birim_sondaj,birim_platform,index,toplam_alan,1,uygun_olanlar);
		son_toplam_kare_sayisi+=uygun_olanlar[1];
		}
    //cizme(konum,nokta_sayisi,sekil_sayisi);
	getch();
    closegraph();
    
    printf("\nToplam platform sayisi :%d\n",son_toplam_kare_sayisi); 
    printf("Toplam sondaj sayisi(sondaj alani) :%.2f\n",uygun_olanlar[0]); // toplam_alanlar[uygun_index]
    printf("Toplam platform maliyeti :%.2f\n",son_toplam_kare_sayisi*birim_platform);
    printf("Toplam sondaj maliyeti :%.2f\n",uygun_olanlar[2]);
    printf("Toplam maliyet :%.2f\n",uygun_olanlar[2]+(son_toplam_kare_sayisi*birim_platform));
    
	float kar= (toplam_alan[0]*10)-uygun_olanlar[4]; // alan*10-uygun=kar;
    printf("Kar miktari :%.2f\n",kar);
    return 0;
	}
