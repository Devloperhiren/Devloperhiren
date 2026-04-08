// DETAILS..
/*

- It includes Account no, pin, amount, otp to check and stay valid.
- Sufficient User defined functios for all the manu.
- valid check by storing in file.


Limitations..

- As it is only c program and doesn't has backend, it not sends otp to user phone.
- User can create account cause there is no banking system to ensure bank accounts.

*/

// DESIGNER: Hiren Gondaliya

#include<stdio.h>
#include<stdlib.h>
#include<time.h>


// DEFINING NECESSARY MACRO
#define otp_size 6                      // FOR OTP SIZE
#define DEF_AMOUNT 25000                // CAUSE WE CAN'T HAVE AMOUNT AS DEFAULT 

static long acc_no;
static long pin;
static long amount;
static long otp;
static int temp=0;

struct student
{
    long acc_no;
    long pin;
    long amount;
}s;



// FUNCTIONS..


// GENERATING RANDOM 6 DIGIT OTP
int otp_generate(){
long otp;
srand(time(NULL));

otp=rand() % 900000 + 100000;  // TO GET OTP IN BETWEEN 0-999999

    return otp;
}


// GET DETAILS
void details(long acc_no){
int t=0;
    FILE *atm;
atm=fopen("ACCOUNT_DATA.bin","rb");

if(atm == NULL){
    printf("\nERROR IN OPENING FILE.");
    return;
}

while((fread(&s,sizeof(struct student),1,atm))==1){

    if(s.acc_no==acc_no){
printf("\nACCOUNT NO: %ld",s.acc_no);
printf("\nPIN: %ld",s.pin);
amount=s.amount;
t=1;
        }
     

}
if(t==0){
printf("\nACCOUNT NOT REACHED.");
}
if(fclose(atm) != 0){
    printf("\nERROR IN CLOSING FILE.");
}
}





// CHECK VALID ACCOUNT
int ac_check(long acc_no, long pin){
FILE *atm;
atm=fopen("ACCOUNT_DATA.bin","rb");

if(atm == NULL){
    printf("\nERROR IN OPENING FILE.");
    return 0;
}

while((fread(&s,sizeof(struct student),1,atm))==1){

    if(s.acc_no==acc_no){
        temp=1;
        if(s.pin==pin){
if(fclose(atm) != 0){
printf("\nERROR IN CLOSING FILE.");
return 0;
}
return 1;
        }
    }
    
    
}

if(fclose(atm) != 0){
printf("\nERROR IN CLOSING FILE.");
return 0;
}

}


// GET INFO OF ACCOUNT
long get(long acc_no, long pin){
FILE *atm;
atm=fopen("ACCOUNT_DATA.bin","rb");

if(atm == NULL){
    printf("\nERROR IN OPENING FILE.");
    return 0;
}

while((fread(&s,sizeof(struct student),1,atm))==1){

    if(s.acc_no==acc_no){
        if(s.pin==pin){
        acc_no=s.acc_no;
        pin=s.pin;
if(fclose(atm) != 0){
printf("\nERROR IN CLOSING FILE.");
return 0;
}
        return s.amount;
        }
        else{
if(fclose(atm) != 0){
printf("\nERROR IN CLOSING FILE.");
return 0;
}
        return 0;
        }
    }
}

if(fclose(atm) != 0){
printf("\nERROR IN CLOSING FILE.");
return 0;
}

}


// CHANGE INFO UNDER FILE
int change(long acc_no, long pin, long amount){
FILE *atm;

if((atm=fopen("ACCOUNT_DATA.bin","rb+")) == NULL){
printf("\nERROR IN OPENING FILE.");
return 0;
}

long total,size;
fseek(atm,0,SEEK_END);


size=ftell(atm);
total=size / sizeof(struct student);


for(int i=0; i<total; i++){
fseek(atm,i*sizeof(struct student), SEEK_SET);   
fread(&s,sizeof(struct student),1,atm); 
if(s.acc_no==acc_no){

s.pin=pin;
s.amount=amount;

fseek(atm,i*sizeof(struct student),SEEK_SET);
fwrite(&s,sizeof(struct student),1,atm);
if(fclose(atm) != 0){
printf("\nERROR IN CLOSING FILE.");
return 0;
}
return 1;
}
}

}



// CREATING BANK ACCOUNT

void b_account(){
printf("\nENTER ACCOUNT NO: ");
scanf("%ld",&acc_no);

if(acc_no > 99999 || acc_no < 10000){
    system("cls");
printf("\nPLEASE ENTER VALID ACCOUNT_NO.");
return;
}

printf("\nENTER PIN: ");
scanf("%ld",&pin);

if(pin>9999 || pin < 1000){
    system("cls");
printf("\nPLEASE ENTER VALID PIN.");
return;
}

if(((ac_check(acc_no,pin))==1)  || temp==1 ){
    system("cls");
    printf("\nACCOUNT ALREADY EXISTS.");
    temp=0;
    return;
}

FILE *atm;
atm=fopen("ACCOUNT_DATA.bin","ab+");

if(atm == NULL){
    system("cls");
    printf("\nERROR WHILE OPENING A FILE.");
    return;
}

s.amount=DEF_AMOUNT;
s.acc_no=acc_no;
s.pin=pin;
fwrite(&s,sizeof(struct student),1,atm);

if(fclose(atm) != 0){
    system("cls");
printf("\nERROR IN CLOSING FILE.");
return;
}
system("cls");
printf("\nREMEMBER YOUR ACCOUNT NO: %ld \n                     PIN: %ld",acc_no,pin);

printf("\nACCOUNT CREATED SUCCESSFULLY. THANK YOU FOR VISITING.");

}



// CHECK BALANCE
void c_balance(){
    printf("\nENTER ACCOUNT NO: ");
    scanf("%ld",&acc_no);

    printf("\nENTER PIN: ");
    scanf("%ld",&pin);

    if((ac_check(acc_no,pin))==1){
        system("cls");
printf("\nAMOUNT IN YOU ACCOUNT: %ld",get(acc_no,pin));
    }
    else if((ac_check(acc_no,pin))==0){
        system("cls");
        printf("\nWRONG PIN.");
        return;
    }
    else{
        system("cls");
        printf("\nACCOUNT DOESN'T EXISTS.");
        return;
    }
}

// WITHDRAW AMOUNT
void withdraw(){

    printf("\nENTER ACCOUNT NO: ");
    scanf("%ld",&acc_no);

    printf("\nENTER PIN: ");
    scanf("%ld",&pin);

    if((ac_check(acc_no,pin))==1){
printf("\nYOUR CURRENT BALANCE: %ld",get(acc_no,pin));

printf("\nENTER AMOUNT TO WITHDRAW: ");
scanf("%ld",&amount);

if(amount < 0){
printf("\nPLEASE ENTER VALID AMOUNT.");
return;
}
if(amount<get(acc_no,pin)){
amount=s.amount-amount;
    if((change(acc_no,pin,amount))==1){
        system("cls");
        printf("\nAMOUNT SUCESSFULLY WITHDRAWN.");
        return;
    }
    else{
        system("cls");
        printf("\nSOME ISSUES OCCURED. TRY AGAIN LATER.");
        return;
    }
}
else{
    system("cls");
    printf("\nPLEASE ENTER VALID AMOUNT.");
    return;
}
}
    else{
        printf("\nACCOUNT DOESN'T EXISTS OR WRONG PIN.");
        return;
    }

}

// CHANGE PIN
void pinchange(){
int opt;
long cmp_otp;
    printf("\nENTER ACCOUNT N0: ");
    scanf("%ld",&acc_no);

    printf("\nCHOOSE ONE: ");
    printf("\n1. CHANGE BY ENTERING PIN.");
    printf("\n2. CHANGE BY ENTERING OTP.\n");
    scanf("%d",&opt);

    switch (opt)
    {
    case 1:
    printf("\nENTER VALID PIN: ");
    scanf("%ld",&pin);

    if((ac_check(acc_no,pin)) == 1){
        details(acc_no);
printf("\nENTER NEW PIN: ");
scanf("%ld",&pin);

if((change(acc_no,pin,amount))==1){
printf("\nPIN HAS CHANGED.");
  }
else{
    printf("\nPIN NOT CHANGED.");
}
    break;

    case 2:
    cmp_otp=otp_generate(); 
    printf("\nOTP: %ld",cmp_otp);
    printf("\nENTER OTP: ");
    scanf("%ld",&otp);


    if(otp==cmp_otp){
    details(acc_no);
    printf("\nENTER NEW PIN: ");
scanf("%ld",&pin);

if((change(acc_no,pin,amount))==1){
printf("\nPIN HAS CHANGED.");
    }
}
    }
}
}

//DEPOSITE
void deposite(){
long tem1;

    printf("\nENTER ACCOUNT NO: ");
    scanf("%ld",&acc_no);

    printf("\nENTER PIN: ");
    scanf("%ld",&pin);

    if((ac_check(acc_no,pin))==1){
printf("\nYOUR CURRENT BALANCE: %ld",get(acc_no,pin));
    
printf("\nINSERT CASH AND INPUT THE TOTAL AMOUNT INSERTED: ");
scanf("%ld",&tem1);

printf("\nRE-INPUT CASH: ");
scanf("%ld",&amount);

if(tem1 < 0 || amount < 0){
printf("\n ARE YOU COMEDY ME ?");
printf("\nPLEASE ENTER VALID AMOUNT.");
return;
}
if(tem1 == amount){
amount=amount+get(acc_no,pin);

if((change(acc_no,pin,amount))==1){
printf("\nYOUR AMOUNT DEPOSITED.");
  }
else{
    printf("\nAMOUNT NOT CHANGED.");
}
  
}
else{
    printf("\nYOUR INPUTED AMOUNTS ARE DIFFERENT.");
}
}

}



int main(){
    // TAKING NECESSARY VARIABLES AND STRINGS

int choice=0; 
                // FOR SWITCHING MANU


while(choice != 6){

printf("\n                                      WELCOME TO BANK OF BARCILONA\n\n\n");


// BUILDING MAIN MANU

printf("CHOOSE YOUR ACTIVITY TO PERFORM:\n");
printf("\n1. CREATE ACCOUNT.");
printf("\n2. CHECK BALANCE.");
printf("\n3. WITHDRAW AMOUNT.");
printf("\n4. CHANGE PIN/UPDATE PIN.");
printf("\n5. DEPOSITE AMOUNT.");
printf("\n6. EXIT.\n\n");
scanf("%d",&choice);


switch (choice)
{


case 1:  // FUNCTION: CREATE ACCOUNT
system("cls");
b_account();
break;



case 2: // FUNCTION: CHECK BALANCE
system("cls");
c_balance();
break;



case 3: // FUNCTION: WITHDRAW AMOUNT
system("cls");
withdraw();
break;



case 4: // FUNCTION: CHANGE/UPDATE PIN
system("cls");
pinchange();
break;



case 5: // FUNCTION: DEPOSITE AMOUNT
system("cls");
deposite();
break;



default:            // DEFAULT CAUSE WE CAN'T SET BUTTONS HERE LIKE PHYSICAL ATMs
system("cls");   
printf("\nPLEASE CHOOSE FROM 1 TO 5.\n");
printf("\nTHANKS FOR VISITING..");
break;
}

}

return 0;
}








