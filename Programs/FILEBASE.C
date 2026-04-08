// DATABASE SYSTEM

/*

HOW TO USE:

QUERIE....
1. CREATE STRUCTURE  to create structure like table in db
2. CREATE FILE       to create file like database
3. INSERT INTO       to insert records into table
4. SELECT FROM       to see records from file


Limitations..

- IT ONLY MODIFY AND WORKS WITH ONE STRUCTURE SO USER HAVE TO CLEAN FILES MANUALLY TO APPEND ANOTHER STRUCTURE.

`
*/






#include<stdio.h>
#include<stdlib.h> 
#include<string.h>

static char file[100];
static int size;
static int total;

struct STRUCTURE{ 
    // TO STORE SIZE OF TOTAL VARIABLES
    int size;
    char name[100];      // TO STORE STRUCTURE NAME
    int total_data;      // TOTAL DATA TO ACCESS DATA FROM DATA FILE
    char dname[10][100];   // DATA NAME TO STORE DATA NAMES LIKE RNO, NAME.
    char vname[10][100];    // TO STORE VARIABLE NAMES LIKE INT, VARCHAR
    int t_var;
}S;

int CHECK();  // CHECK WHETHER FILE EXISTS
int C_S(char name[]); // CHECK WHETHER STRUCTURE EXISTS
void ins(char name[]); // TO INSERT DATA INTO FILE

int main(int argc,char *argv[]){
int temp=0;
int sum=0;
char **c;
char **d;
void **a;
char str[100], str2[100];

    if(argc < 3){
        printf("\nPLEASE ENTER VALID ARGUMENT.");
        return 0;
    }

    // create file
    if(((strcmp(argv[1],"CREATE"))==0) && ((strcmp(argv[2],"FILE"))==0) ){

        sprintf(file,"%s.bin",argv[3]);
        temp=CHECK();

        if(temp == 1 || temp == 2){
            printf("\nERROR WHILE CREATING FILE.");
            return 0;
        }
        else{
            printf("\nFILE %s.bin CREATED SUCCESSFULLY. ",argv[3]);
        }
    }

    // create structure
    else if(((strcmp(argv[1],"CREATE"))==0) && ((strcmp(argv[2],"STRUCTURE"))==0)){

        FILE *ptr;
        ptr=fopen("STRUCT.bin","ab+");
        fclose(ptr);

        printf("\nWELCOME TO WRITING MODE");
        printf("\nENTER NUMBERS OF VARIABLES: ");
        scanf("%d",&size);

        total = 0; 

        c=(char**)malloc(size*sizeof(char*));
        d=(char**)malloc(size*sizeof(char*));

        for(int i=0; i<size; i++){
            c[i]=(char*)malloc(100*sizeof(char));
            d[i]=(char*)malloc(100*sizeof(char));
        }

        a=(void**)malloc(size*sizeof(void*));

        printf("\nENTER STRUCTURE NAME: ");
        scanf(" %[^\n]",str);

        strcpy(S.name,str);

        if(C_S(str) == 0){
            printf("\nNAME EXISTS.");
            return 0;
        }

        for(int i=0; i<size; i++){

            printf("\nENTER VARIABLE %d (NAME TYPE): ",i+1);
            scanf("%s %s",str,str2);

            if(((strcmp(str2,"INT"))==0) || ((strcmp(str2,"int"))==0)){
                a[i]=(int*)malloc(sizeof(int));
                total+=sizeof(int);
                strcpy(c[i],"INT");
                strcpy(d[i],str);

                strcpy(S.dname[i],str);
                strcpy(S.vname[i],"INT");
            }

            else if(((strcmp(str2,"FLOAT"))==0) || ((strcmp(str2,"float"))==0)){
                a[i]=(float*)malloc(sizeof(float));
                total+=sizeof(float);
                strcpy(c[i],"FLOAT");
                strcpy(d[i],str);

                strcpy(S.dname[i],str);
                strcpy(S.vname[i],"FLOAT");
            }

            else if(((strcmp(str2,"CHAR"))==0) || ((strcmp(str2,"char"))==0)){
                a[i]=(char*)malloc(sizeof(char)); 
                total+=sizeof(char);
                strcpy(c[i],"CHAR");
                strcpy(d[i],str);

                strcpy(S.dname[i],str);
                strcpy(S.vname[i],"CHAR");
            }

            else if(((strcmp(str2,"VARCHAR"))==0) || ((strcmp(str2,"varchar"))==0)){
                a[i]=(char*)malloc(100*sizeof(char));
                total+=100;
                strcpy(c[i],"VARCHAR");
                strcpy(d[i],str);

                strcpy(S.dname[i],str);
                strcpy(S.vname[i],"VARCHAR");
            }

            else{
                printf("\nPLEASE ENTER VALID DATATYPE.");
                return 0;
            }
        }

        S.size=total;
        S.total_data=0;
        S.t_var=size;

        FILE *fbase = fopen("STRUCT.bin","ab+");

        if(fbase != NULL){
            fwrite(&S,sizeof(struct STRUCTURE),1,fbase);
        }

        fclose(fbase);
    }

    // to insert data
    else if(((strcmp(argv[1],"INSERT"))==0) && ((strcmp(argv[2],"INTO"))==0))
    {
        FILE *fbase;

        if((fbase=fopen("FILEBASE.bin","ab+")) == NULL ){
            printf("\nERROR IN OPENING FILE.");
            return 0;
        }

        printf("\nENTER STRUCTURE NAME: ");
        scanf(" %[^\n]",str);

        if(C_S(str) == 0){
            ins(str);
        }
        else{
            printf("\nNAME NOT FOUND.");
        }

        fclose(fbase);
    }

    else if(((strcmp(argv[1],"SELECT"))==0) && ((strcmp(argv[2],"FROM"))==0)){

        printf("\nENTER STRUCTURE NAME: ");
        scanf("%s",str);

        if(C_S(str) == 0){

            FILE *ptr=fopen("FILEBASE.bin","rb");
            FILE *FB=fopen("STRUCT.bin","rb");

            while(fread(&S,sizeof(struct STRUCTURE),1,FB)==1){

                if(strcmp(str,S.name)==0){

                    for(int j=0;j<S.total_data;j++){

                        for(int i=0;i<S.t_var;i++){

                            if(strcmp(S.vname[i],"INT")==0){
                                int x; 
                                fread(&x,sizeof(int),1,ptr);
                                printf("\n%s: %d",S.dname[i],x);
                            }

                            else if(strcmp(S.vname[i],"FLOAT")==0){
                                float b;
                                fread(&b,sizeof(float),1,ptr);
                                printf("\n%s: %.2f",S.dname[i],b);
                            }

                            else if(strcmp(S.vname[i],"CHAR")==0){
                                char c;
                                fread(&c,sizeof(char),1,ptr);
                                printf("\n%s: %c",S.dname[i],c);
                            }

                            else{
                                char temp[100]; // 
                                fread(temp,sizeof(char),100,ptr);
                                printf("\n%s: %s",S.dname[i],temp);
                            }
                        }
                    }
                }
            }

            fclose(ptr);
            fclose(FB);
        }
        else{
            printf("\nSTRUCTURE NOT FOUND.");
        }
    }

    return 0;
}   

int CHECK(){  
    FILE *fbase;

    if((fbase=fopen(file,"rb")) != NULL){
        fclose(fbase);
        return 1;
    }
    else if((fbase=fopen(file,"wb")) == NULL ){
        printf("\nERROR IN CREATING FILE.");
        return 2;
    }
    else{
        fclose(fbase);
        return 3;
    }
}

int C_S(char name[]){
    FILE *fbase = fopen("STRUCT.bin","rb");

    if(fbase == NULL){
        return 1;
    }

    while(fread(&S,sizeof(struct STRUCTURE),1,fbase)==1){
        if(strcmp(name,S.name)==0){
            fclose(fbase);
            return 0;
        }
    }

    fclose(fbase);
    return 1;
}

void ins(char name[]){
FILE *ptr=fopen("FILEBASE.bin","ab+");
FILE *FBASE=fopen("STRUCT.bin","rb");

int n,a;
float b;
char c,d[100];

printf("\nENTER NUMBERS OF RECORDS TO INSERT: ");
scanf("%d",&n);

while(fread(&S,sizeof(struct STRUCTURE),1,FBASE)==1){

if(strcmp(S.name,name)==0){

S.total_data+=n;

FILE *store=fopen("STRUCT.bin","rb+");
fseek(store,-(long)sizeof(struct STRUCTURE),SEEK_CUR);
fwrite(&S,sizeof(struct STRUCTURE),1,store);
fclose(store);

for(int j=0;j<n;j++){
for(int i=0;i<S.t_var;i++){

if(strcmp(S.vname[i],"INT")==0){
printf("\nENTER %s: ",S.dname[i]);
scanf("%d",&a);
fwrite(&a,sizeof(int),1,ptr);
}

else if(strcmp(S.vname[i],"FLOAT")==0){
printf("\nENTER %s: ",S.dname[i]);
scanf("%f",&b);
fwrite(&b,sizeof(float),1,ptr);
}

else if(strcmp(S.vname[i],"CHAR")==0){
printf("\nENTER %s: ",S.dname[i]);
scanf(" %c",&c); // 
fwrite(&c,sizeof(char),1,ptr);
}

else{
printf("\nENTER %s: ",S.dname[i]);
scanf("%s",d);
fwrite(d,sizeof(char),100,ptr); 
}
}
}
}
}

fclose(FBASE);
fclose(ptr);
printf("\nWRITTEN SUCCESSFULLY.");
}