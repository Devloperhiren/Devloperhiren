#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int sear=5;

struct contact_info
{
    char name[100];
    long long mobile_no;
}c;

void get_info(); 
void store_info(char str[],long long num );
void check_info(char name[], long long m_no);
void show_all();
void search();

int main(){
system("cls");
int temp=0;

while(temp != 4){
printf("\n\n\nCHOOSE ONE FROM BELOW.\n1. ADD NEW CONTACT\n2. ALL CONTACTS\n3. SEARCH CONTACT\n4. EXIT.\n\n");
scanf("%d",&temp);
if(temp==1){get_info();}
else if(temp==2){show_all();}
else if(temp==3){search();}
else{
printf("\nCONTACT CLOSED.");
}
} 
return 0;
}


void get_info(){
int temp;  // to check if user want to store save contact or no
int temp2;
char name[100];
long long m_no;

printf("\nENTER NAME: ");
scanf(" %[^\n]",name);

printf("\nENTER MOBILE_NO: ");
scanf("%lld",&m_no);

check_info(name,m_no);

temp=sear;
sear=5;

if(temp==0){
    strcpy(c.name,name);
    c.mobile_no=m_no;

printf("\nCONTACT INFO: \n");
printf("\nNAME   :  %s",c.name);
printf("\nNUMBER :  %lld",c.mobile_no);

printf("\n\nCHOOSE FROM BELOW. \n1. SAVE CONTACT.\n2. DON'T SAVE CONTACT.\n\n");
scanf("%d",&temp2);

if(temp2==1){ store_info(c.name,c.mobile_no);}

else if(temp2==2){ printf("\nYOUR CONTACT NOT SAVED.");}

else{ printf("\n ENTER VALID CHOICE.");}
}
else if(temp==1){
printf("\n\nCONTACT ALREADY EXISTS.");
return;
}
else{
printf("\nFILE ERROR.");
}
}


void store_info(char str[], long long num){
FILE *fptr;

if((fptr=fopen("CONTACT_INFO.bin","ab+")) == NULL){
printf("\nERROR IN OPENING FILE.");
return;
}

fwrite(&c,sizeof(struct contact_info),1,fptr);
printf("\nINFO STORED.");
if(fclose(fptr) != 0){
printf("\nERROR IN CLOSING FILE.");
return;
}

return;
}

void show_all(){
    system("cls");
    FILE *fptr;
    int i=1;
    if((fptr=fopen("CONTACT_INFO.bin","rb")) == NULL){
    printf("\nERROR IN OPENING FILE.");
    return;
    }

    while((fread(&c,sizeof(struct contact_info),1,fptr)) == 1){
        printf("\n\nCONTACT %d:",i);
        printf("\nNAME:      %s",c.name);
        printf("\nMOBILE NO: %lld",c.mobile_no);
        i++;
    }

    if(fclose(fptr) != 0){
    printf("\nERROR IN CLOSING FILE.");
    return;
    }
}

void check_info(char name[], long long m_no){
    FILE *fptr;
   
    if((fptr=fopen("CONTACT_INFO.bin","rb")) == NULL){
    printf("\nERROR IN OPENING FILE.");
    sear=2;
    return;
    }

    while((fread(&c,sizeof(struct contact_info),1,fptr)) == 1){
        if(m_no == c.mobile_no){
            printf("\nCONTACT DETAIL: ");
            printf("\nNAME:      %s",c.name);
            printf("\nMOBILE NO: %lld",c.mobile_no);
            sear=1;
            return;
        }
        else if((strcmp(name,c.name))==0){
            printf("\nCONTACT DETAIL: ");
            printf("\nNAME:      %s",c.name);
            printf("\nMOBILE NO: %lld",c.mobile_no);
            sear=1;
            return;
        }
        else{
            continue;
        }
    }

    
    if(fclose(fptr) != 0){
    printf("\nERROR IN CLOSING FILE.");
    sear=2;
    return;
    }
    sear=0;
    return;

}

void search(){
char name[100];
long long m_no;
int temp=0;

printf("\nNAME: ");
scanf(" %[^\n]",name);

m_no=0;

check_info(name,m_no);

temp=sear;
if(temp==1){
    printf("\n\nCONTACT FOUND.");
    return;
}
else if(temp==0){
printf("\nDETAILS NOT FOUND.");
return;
}
else{
printf("\nERRROR IN FILE OPERATION.");
return;
}
}