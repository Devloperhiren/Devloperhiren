// COMMAND LINE BASED CALCULATOR

/*

ABOUT THIS CODE...
---------------------------------
=> It follows BODMAS RULE TO DEMONSTRATE ARITHMETIC OPERATIONS.
=> It allows dynamic size vectors so user can input independent operation (Not input _ op _).
=> It saves Calculation history in file as real calculator tools.

Limitations...
---------------------------------
=> User have to use -* for multiplication cause command line or terminal doesn't support * default.
=> It only supports BODMAS operations.

How to use...
---------------------------------

=> .\CALCULATOR.exe num1 operation1 num2 operation2....

=> TO SEE HISTORY- .\CALCULATOR.exe -H or -h 

*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// DEFINING VARIABLES WHICH STORE TOTAL OPERATOR AND NUMBERS
static int num_c;
static int o_c;

// DEFINING FUNCTIONS
void arr(float **a,int num_c);  // to create array of size total numbers
void opera(char ***c,int o_c);  // to create character array for total operations
void hist();

int main(int argc, char *argv[]){
float *a;
char **c;
char *gar;

FILE *history;
history=fopen("cal_history.txt","a+");

if(history == NULL){
printf("\n ERROR IN ACCESSING HISTORY.");
return 0;
}


// GIVING HISTORY IF USER WANT
if(((strcmp(argv[1],"-h"))==0) || ((strcmp(argv[1],"-H"))==0))
{
hist();
return 0;
}


// exit if input is not appropreate
if((argc %2 != 0) || (argc <4)){
printf("\nPLEASE INPUT VALID ARITHMETIC.");
return 0;
}

// assigning to variables
num_c=argc/2;
o_c=(argc/2)-1;

// creating array and string
arr(&a,num_c);
opera(&c,o_c);


// assigning value to array of numbers
int temp=1;
for(int i=0; i<num_c; i++){

    a[i]=strtof(argv[temp],&gar);

    if(*gar != '\0'){
        printf("\nASSIGN SUITABLE VALUE.");
        return 0;
    }

    temp+=2;
}


// assigning value to string of operations
temp=2;
for(int i=0; i<o_c; i++){

    c[i]=argv[temp];

    if(((strcmp(c[i],"+")) != 0) && ((strcmp(c[i],"-")) != 0) && ((strcmp(c[i],"-*")) != 0) && ((strcmp(c[i],"/")) != 0)){
         printf("\nASSIGN SUITABLE VALUE TO OPERATOR.");
         return 0;
    }


    temp+=2;
}


// to show user what he/she input
printf("\nYOUR OPERATION: ");
for(int i=0; i<o_c; i++){
if(i==0){
    printf("%.2f %s %.2f", a[i] , c[i] , a[i+1]);
    fprintf(history,"\n%.2f %s %.2f", a[i], c[i], a[i+1]);
}
else{
    printf(" %s %.2f",c[i],a[i+1]);
    fprintf(history," %s %.2f",c[i],a[i+1]);
    
}
}

// As bodmas, first doint multiplication and division
int operate;
for(int i=0; i<o_c;){
operate=0;
    if(((strcmp(c[i],"-*"))==0) || ((strcmp(c[i],"/"))==0)){

        if((strcmp(c[i],"-*"))==0){ a[i]=a[i] * a[i+1]; operate=1;}
    
        else if((strcmp(c[i],"/"))==0){
            if(a[i+1] == 0){
                printf("\n DIVIDE BY 0 ERROR.");
                return 0;
            }
            a[i]=a[i]/a[i+1]; operate=1;}

            if(operate==1){
            if(i < o_c-1){
            for (int j = i; j < o_c-1; j++)
    {
        a[j+1]=a[j+2];
        c[j]=c[j+1];
    }
}
}

}
if(operate==1){
o_c--;
num_c--;    
}
else{
i++;
}

     
}


// as bodmas, now doing remaining operations
for(int i=0; i<o_c;){
operate=0;
    
if(((strcmp(c[i],"+"))==0) || ((strcmp(c[i],"-"))==0)){
       
        if((strcmp(c[i],"+"))==0){ a[i]=a[i] + a[i+1]; operate=1;}
        
       else if((strcmp(c[i],"-"))==0){

            a[i]=a[i]-a[i+1]; operate=1;}

            if(operate==1){
            if(i < o_c-1){
            for (int j = i; j < o_c-1; j++)
    {
        a[j+1]=a[j+2];
        c[j]=c[j+1];
    }
}

}    
}
if(operate==1){
o_c--;
num_c--;    
}
else{
i++;
}
}


// showing result
printf("\nANSWER: %.2f",a[0]);
fprintf(history,"\nANSWER: %.2f",a[0]);

if(fclose(history) != 0){
printf("\nERROR IN CLOSING HISTORY FILE.");
return 0;
}

free(a);
free(c);

    return 0;
}



void arr(float **a,int num_c){
    *a=(float*)malloc(num_c*sizeof(float));
}

void opera(char ***c, int o_c){
    *c=(char**)malloc(o_c*sizeof(char*));
}

void hist(){
    int c;
FILE *history;
if((history=fopen("cal_history.txt","r")) == NULL){
printf("\nERROR WHILE ACCESSING HISTORY FILE");
return;
}

while((c=getc(history)) != EOF){
printf("%c",c);
    }

if(fclose(history) != 0){
printf("\nERROR IN CLOSING HISTORY FILE.");
}
}