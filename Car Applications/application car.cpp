#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma pack(1)
typedef struct 
{
	char plate[10];
	char brand[30];
	int year;
	float price;
	int status;
} Car;
int menu()
{
	int choice,k;
	do
	{
		printf("----MENU-----\n");
		printf("1. Record\n");
		printf("2. Rent A Car\n");
		printf("3. Return a Car\n");
		printf("4. Deleting a Car\n");
		printf("5. Updating a Record\n");
		printf("6. Listing All Cars\n");
		printf("7. Listing Available Cars\n");
		printf("8. Listing Rented Cars\n");
		printf("9. Exit\n");
		printf("----->Your Selection:");
		k=scanf("%d",&choice);
		fflush(stdin);
		if(k<1 | choice >9) printf("\nInvalid selection. Please select again!\n");
	} while(k<1 || choice>9);
	return choice;
}
void removeEnter(char *str)
{
	str[strlen(str)-1]='\0';
	return;
}
void recordCar(char *fname)
{
	FILE *fp;
	fp=fopen(fname,"ab");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	Car car;
	printf("Enter Plate Number:");
	fgets(car.plate,10,stdin);
	removeEnter(car.plate);
	printf("Enter Brand :");
	fgets(car.brand,30,stdin);
	removeEnter(car.brand);
	printf("Enter year:");
	scanf("%d",&car.year);
	fflush(stdin);
	printf("Enter price:");
	scanf("%f",&car.price);
	fflush(stdin);
	car.status=0;
	fwrite(&car,sizeof(Car),1,fp);
	fclose(fp);
	return;
}
void listAllCars(char *fname)
{
	FILE *fp;
	Car car;
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	while(!feof(fp))
	{
		fread(&car,sizeof(car),1,fp);
		if(feof(fp)) break;
		printf("%s\t%s\t%d\t%f\t%d\n",car.plate,car.brand,car.year,car.price,car.status);
	}
	fclose(fp);
	return;
}
void rentCar(char *fname)
{
	FILE *fp;
	Car car;
	int k,i;
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Car);
	fseek(fp,0,SEEK_SET);
	for(i=0;i<k;i++)
	{
		fread(&car,sizeof(Car),1,fp);
		if(car.status==0)
		{
			printf("Plate:%s\n",car.plate);
			printf("Brand:%s\n",car.brand);
			printf("Year :%d\n",car.year);
			printf("Price:%f\n",car.price);
			car.status=1;
			fseek(fp,i*sizeof(Car),SEEK_SET);
			fwrite(&car,sizeof(Car),1,fp);
			fclose(fp);
			printf("\nThe car is rented\n");
			return;
		}
	}
	printf("\nThere is no car for renting\n");
	fclose(fp);
	return;
}
void returnCar(char *fname)
{
	FILE *fp;
	Car car;
	char plate[10];
	int k,i;
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	printf("Enter Plate Number:");
	fgets(plate,10,stdin);
	removeEnter(plate);
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Car);
	fseek(fp,0,SEEK_SET);
	for(i=0;i<k;i++)
	{
		fread(&car,sizeof(Car),1,fp);
		if(strcmp(plate,car.plate)==0 && car.status==1)
		{
			car.status=0;
			fseek(fp,i*sizeof(Car),SEEK_SET);
			fwrite(&car,sizeof(Car),1,fp);
			fclose(fp);
			printf("\nThe car is returned\n");
			return;
		}
	}
	printf("\nThe car plate is not found in the file\n");
	fclose(fp);
}
void deleteCar(char *fname)
{
	FILE *fp;
	Car *car;
	char plate[10];
	int k,i;
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	printf("Enter Plate Number:");
	fgets(plate,10,stdin);
	removeEnter(plate);
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Car);
	if(k==0) 
	{
		printf("There is no car in the file\n");
		fclose(fp);
		return;
	}
	fseek(fp,0,SEEK_SET);
	car=(Car*) malloc(k*sizeof(Car));
	if(car==NULL)
	{
		printf("Not enough memory");
		fclose(fp);
		return;
	}
	fread(car,sizeof(Car),k,fp);
	fclose(fp);
	fp=fopen(fname,"wb");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	for(i=0;i<k;i++)
		if(strcmp(plate,car[i].plate)!=0) fwrite(&car[i],sizeof(Car),1,fp);
	printf("The car is deleted\n");
	fclose(fp);
	return;
}
void updateCar(char *fname)
{
	FILE *fp;
	Car car;
	char plate[10];
	int k,i;
	fp=fopen(fname,"r+b");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	printf("Enter Plate Number:");
	fgets(plate,10,stdin);
	removeEnter(plate);
	fseek(fp,0,SEEK_END);
	k=ftell(fp)/sizeof(Car);
	fseek(fp,0,SEEK_SET);
	for(i=0;i<k;i++)
    {
    	fread(&car,sizeof(car),1,fp);
    	if(strcmp(plate,car.plate)==0)
    	{
    		printf("Enter Plate Number:");
			fgets(car.plate,10,stdin);
			removeEnter(car.plate);
			printf("Enter Brand :");
			fgets(car.brand,30,stdin);
			removeEnter(car.brand);
			printf("Enter year:");
			scanf("%d",&car.year);
			fflush(stdin);
			printf("Enter price:");
			scanf("%f",&car.price);
			fflush(stdin);
			printf("Enter status:");
			scanf("%d",&car.status);
			fflush(stdin);
			fseek(fp,i*sizeof(Car),SEEK_SET);
			fwrite(&car,sizeof(Car),1,fp);
			fclose(fp);
			return;
		}
	}
	printf("\nThe car is not found for updating\n");
	fclose(fp);
	return;
}
void listAvailableCars(char *fname)
{
	FILE *fp;
	Car car;
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	while(!feof(fp))
	{
		fread(&car,sizeof(car),1,fp);
		if(feof(fp)) break;
		if(car.status==0)printf("%s\t%s\t%d\t%f\t%d\n",car.plate,car.brand,car.year,car.price,car.status);
	}
	fclose(fp);
	return;
}
void listRentedCars(char *fname)
{
	FILE *fp;
	Car car;
	fp=fopen(fname,"rb");
	if(fp==NULL)
	{
		printf("File opening error");
		return;
	}
	while(!feof(fp))
	{
		fread(&car,sizeof(car),1,fp);
		if(feof(fp)) break;
		if(car.status==1)printf("%s\t%s\t%d\t%f\t%d\n",car.plate,car.brand,car.year,car.price,car.status);
	}
	fclose(fp);
	return;
}
int main()
{
	int choice;
	char *fname="car.bin";
	do
	{
		choice=menu();
		switch(choice)
		{
			case 1:
				recordCar(fname);
				break;
			case 2:
				rentCar(fname);
				break;
			case 3:
				returnCar(fname);
				break;
			case 4:
				deleteCar(fname);
				break;
			case 5: 
			    updateCar(fname);
			    break;
			case 6:
				listAllCars(fname);
				break;
			case 7:
				listAvailableCars(fname);
				break;
			case 8:
				listRentedCars(fname);
				break;
			case 9:
				break;
		} 
	}while(choice!=9);
	return 0;
}

