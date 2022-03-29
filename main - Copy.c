
/*
0123456789012345678901234567890123456789012345678901234567890123456789012345678901
*/
/********************************************************************************/
/*                                                                              */
/* GSH - 2022/03/28                                                             */
/* Note (1)                                                                     */
/*  You need to separate out the debug aspect of this code first!               */
/*                                                                              */
/********************************************************************************/

/********************************************************************************/
/*                                                                              */
/* GSH - 2022/03/24                                                             */
/*                                                                              */
/* Purpose is to create test transaction data for my Accounts processing        */
/* project.                                                                     */
/*                                                                              */
/* Data format:                                                                 */
/*                                                                              */
/* [Date] [TA Description] [TA Real 1] [TA Real 2]                              */
/* [Date]           - Date of the tranaction format dd/mm/yyyy                  */
/* [TA Description] - Transaction (TA) Description <= [30]                      */
/* [TA Real 1]         - Real value of TA                                       */
/* [TA Real 2]         - Resultant Current Account ( CA) Balance (B)            */
/* Example Data                                                                 */
/*                                                                              */
/* 24/03/2022 aCompanyName -100.00 5000.00                                      */
/*                                                                              */
/* So TA debit by "aCompanyName" on 24/03/2022 for € 100,CA at € 5000.00        */
/*                                                                              */
/* Notes:                                                                       */
/*                                                                              */
/* 1) There are no string quotes " or '                                         */
/* 2) There must be a minimum of 3 blank spaces                                 */
/*                                                                              */
/********************************************************************************/

/********************************************************************************/
/*                                                                              */
/* Structure of the code                                                        */
/* Decide on Data data ... simple 01/01/2021 to 31/12/2021                      */
/* Create random [TA Description], [TA Real 1], [TA Real2]                      */
/*                                                                              */
/* ordered data ?                                                               */
/*                                                                              */
/* Random Date between [Date 1] and [Date 2], [Date 1]<=[Date 2]                */
/* Random [TA Real 1] <= € 10000.00                                             */
/* Random seed for CAB  => Implications on complete records                     */
/* CAB <= € 20,000 CAB >=0 (so our TA must add up too                           */
/* Initially only need to test Phase 1 of release which is adding in            */
/* '"' Quotes for text field ... so import to Google Sheets and name the        */
/* values.                                                                      */
/*                                                                              */
/********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

/* Constant values */

#define MAX_TA 20 /* MAX number of TA per day                */
#define MAX_RND 100 /* Max random number                     */
#define MAX_DAYS 365 /* Not a leap year                      */
#define MAX_MONTHS 30 /* Max number of months                */
#define MAX_BALANCE 100000 /* Max current account balance >0 */
#define MAX_TA_DESC 15 /* Max # for random selection for picking random TA Descriptions */

/* Globals - do not call using them as local variables ! Stack Overflow (SO) GSH 26/03/2022 */
int iDebug = 0;

/* Globals for calling function name and building traces */

/*
    How to reset the calling function name ? GSH 26/03/2022
*/

char sDT[100]="Undefined Trace"; /* Debug Trace (DT)                                                            */
char sFN[50] ="Unnamed Function"; /* Function Name (FN)                                                         */
char sYearDays[365][11]; /* Hold each day of the year - GSH 26/02/2022 not implement as maybe not necessary ??? */

/* Dimensions must be exact - counter starts at [0], not the memory allocation! GSH 2022/03/29 */
char cDays[31][3] =
{
    "01","02","03","04","05","06","07","08","09","10","11","12","13","14","15",
    "16","17","18","19","20","21","22","23","24","25","26","27","28","29","30","31"
};

char cMonths[12][3] =
{
    "01","02","03","04","05","06","07","08","09","10","11","12"
};

char cTAText[15][50] =
{
    "Bank Withdraw (Cash)","xCompany Purchase (Home)","yCompany Purchase (Spain)", "Money Transfer (NY)","Internet TA",
    "Phone Topup","ABC Shopping","Car Service at myGarrage","Car Insurance","TV Licence",
    "RIPOffBank Charges", "HardWork Payment! myDosh","HighMaintence Home Insurance", "myPC Store - Class Tech", "Bank Transfer"
};

int iTAData[15]=
{
    -1,-1,-1,+1,+1,
    -1,-1,-1,-1,-1,
    -1,+1,-1,-1,-1
};

/* Hold each number of days for each month in 2021 - not a leap year! */
int iMonths[12]=
{
    31, 28, 31, 30, 31, 30,
    31, 31, 30, 31, 30, 31
};

/* Switch my debug on */
void myDebugOn(char myFN[0])
{
    /* Set global to True */
    iDebug = 1;

    /* Set global name of calling function */
    strcpy(sFN,myFN);
}

/* Switch my debug off */
void myDebugOff(void)
{
    iDebug = 0;
}

/* Print trace for calling function - Simple Trace (ST) */
void myDebugST(char sMyDebug[0])
{

    /* This is the trace statement */
    sprintf(sDT,"%s: %s.\n",sFN,sMyDebug);
    printf(sDT);
}

/* Print trace for calling function - Detailed Trace (DT) */
void myDebugDT(void)
{
    char cLT[200]; /* My Local Trace */

    sprintf(cLT,"%s: %s.\n",sFN,sDT);

    if (strlen(cLT) > 100)
    {
        printf("Warning Trace string greater than 500!\n");
    }
    printf(cLT);
}

/* Get integer date range - use pointers !*/
void GetIDateRange(int *iStartDate,int *iEndDate)
{
    /* Switch on debug */
    if(iDebug) {myDebugOn("GetIDateRange");}

    /* Seed rand() with current time to ensure random"ness" */
    srand(time(NULL)); /* only call once ! */

    /* Select random start date from [2021] - Do we need +1 for iStartDay ? GSH 29/03/29 */
    *iStartDate = (int) rand()% MAX_DAYS;
    *iEndDate = (int) (*iStartDate + rand() % (MAX_DAYS-(*iStartDate)));

    if(iDebug)
    {
        sprintf(sDT,"iStartDate(%d),iEndDate(%d)",*iStartDate,*iEndDate);
        myDebugDT();
    }

    if(*iEndDate < *iStartDate)
    {
        sprintf(sDT,"Warning - StartDate(%d) is after EndDate(%d)!",*iStartDate,*iEndDate);
        myDebugDT();
    }

    if(iDebug){ myDebugST("Exit function");}
}

/* Use pointers and remember to use(*) for return values and calculations ! */
void GetSDateRange(int iStartDate,int iEndDate,char cStartDate[0],char cEndDate[0],
                   int *iStartDay,int *iEndDay,int *iStartMonth,int *iEndMonth)
{
    int nMonths = MAX_MONTHS;

    char cStartDay[3],cEndDay[3];

    /* Switch on debug and set calling function name */
    myDebugOn("GetSDateRange");

    /* Convert to a Date our integer Dates - iStartDate, iEndDate to our date format DD/MM/YYYY */

    /* Find the approximate day of the month. Test data does not have to be THAT precise (use 30 days) */
    *iStartMonth = (int) iStartDate/nMonths;
    *iEndMonth = (int) iEndDate/nMonths;

    sprintf(sDT,"iStartMonth(%d),iEndMonth(%d)",*iStartMonth,*iEndMonth);
    myDebugDT();

    /* What happens in the month of February ? - GSH 28/03/2022 */

    *iStartDay =  iStartDate - 30*(*iStartMonth);
    *iEndDay= iEndDate - 30*(*iEndMonth);

    if(iDebug)
    {
        sprintf(sDT,"iStartDay(%d),iStartMonth(%d),iEndDate(%d),iEndMonth(%d)",*iStartDay,*iStartMonth,*iEndDay,*iEndMonth);
        myDebugDT();
    }

    /*
        Initalise the strings for StartDay and EndDay - have to declare array size to be sLength + 1 for Null
        terminator "\0"
    */
    strcpy(cStartDay,"01");
    strcpy(cEndDay,"28");

    /* Special case 01/01/2021 */
    if ((*iStartDay !=0) && (*iEndDay !=0))
    {
        strcpy(cStartDay, cDays[*iStartDay-1]);
        strcpy(cEndDay, cDays[*iEndDay-1]);
    }
    else if (*iStartDay == 0)
    {
        strcpy(cStartDay,"01");

    }
    else if (*iEndDay == 0 )
    {
        strcpy(cEndDay,"01");
    }

    if(iDebug)
    {
        sprintf(sDT,"cStartDay(%s),cEndDay(%s)",cStartDay,cEndDay);
        myDebugDT();
    }

    /* Convert to Date format: DD/MM/YYYY */
    sprintf(cStartDate,"%s/%s/2022",cStartDay,cMonths[*iStartMonth]);
    sprintf(cEndDate,"%s/%s/2022",cEndDay,cMonths[*iEndMonth]);

    if(iDebug)
    {
        sprintf(sDT,"cStartDate(%s),cEndDate(%s)",cStartDate,cEndDate);
        myDebugDT();

        myDebugST("Exit function");
    }
}

void PopTAData(int iStartDate,int iEndDate,char cStartDate[0],char cEndDate[0],int iStartDay,int iEndDay,int iStartMonth,int iEndMonth)
{

    FILE *fTAData;

    int iTA,nTA;
    int iDay,nDay;
    int iMth,nMth;
    int iRnd;

    char cThisMth[3];
    char cThisTADay[3];
    char cThisTADate[11];
    char cThisTAText[50];
    char cThisTALine[100];

    float rCABalance;
    float rThisTA;

    if(iDebug)
    {
        myDebugOn("PopTAData");
        myDebugST("Start");
    }

    /* Open file myTAData.txt */
    fTAData = fopen("myTAData.txt","w");

    /* Initialise while loops for first TA (iTA = 0) */
    iTA =0;

    /* Calculate the number of transaction days */
    nTA = iEndDate - iStartDate; /* 0 counts as +1, at least 1 TA! */

    if(iDebug)
    {
        sprintf(sDT,"iTA(%d),nTA(%d)",iTA,nTA);
        myDebugDT();
    }

    /* Initialise for first day */
    strcpy(cThisTADate,cStartDate);

    iMth=iStartMonth;
    nMth=iEndMonth;
    iDay=iStartDay;
    nDay = iMonths[iMth];
    /* Calculate random initial Current Account Balance (CAB) */
    rCABalance = rand()% MAX_BALANCE;


    if(iDebug)
    {
        sprintf(sDT,"iTA(%d): iDay(%d),nDay(%d),iMth(%d),nMth(%d),nTD(%d),cThisTADate(%s)",iTA,iDay,nDay,iMth,nMth,nTA,cThisTADate);
        myDebugDT();
    }

    /* for each month */
    while (iMth<=nMth)
    {
        /* Get char for months from int array cMonths */
        strcpy(cThisMth,cMonths[iMth]);

        /* Set number of days in this month */
        nDay = iMonths[iMth];

        sprintf(sDT,"nDay(%d)",nDay);
        myDebugDT();

        /* Reset for each new month ! */
        iDay = 0;

        /* for each day of the month */
        while (iDay<nDay)
        {

            /* For each transaction TA on each day we need the TA Date, TA Description, TA Value, new CA balance */
            /* Lets assume 1 TA per Day. Revist to develop the code :-). Yes more work for you G!                */
            if (iDebug)
            {
                sprintf(sDT,"Start iTA(%d): iMth(%d),iDay(%d),nMth(%d),nDay(%d),nTA(%d)",iTA,iMth,iDay,nMth,nDay,nTA);
                myDebugDT();
            }

            /* Generate random TA including: Transaction description, value and current balance for each transation */

            /* Get a random TA Desc. */
            iRnd = (int) rand()% MAX_TA_DESC;
            strcpy(cThisTAText,cTAText[iRnd]);

            /* Get a Random TA value */
            rThisTA = (iTAData[iRnd])*rand()% MAX_TA;

            /* Update our current CAB based on this TA */
            rCABalance = rCABalance - rThisTA;

            /* Bug empty TA Description - GSH 29/03/2022 - fix with warning */
            if(strlen(cThisTAText)==0)
            {
                strcpy(cThisTAText,"Empty TA Description!");
                if(iDebug)
                {
                    myDebugST("Warning: empty TA Description!");
                }
            }
            sprintf(cThisTALine,"%s %s %.2f %.2f\n",cThisTADate,cThisTAText,rThisTA,rCABalance);

            /* Output the line to debug */
            if (iDebug)
            {
                sprintf(sDT,"%s %s %.2f %.2f",cThisTADate,cThisTAText,rThisTA,rCABalance);
                myDebugDT();
            }
            fprintf(fTAData,"%s",cThisTALine);

            /* Increment the day counter */
            iDay++;

            /* Set next TA Day */
            strcpy(cThisTADay,cDays[iDay]);
            sprintf(cThisTADate,"%s/%s/2022",cThisTADay,cMonths[iMth]);

            if(iDebug)
            {
                sprintf(sDT,"cThisTADay(%s),cThisTADate(%s)",cThisTADay,cThisTADate);
                myDebugDT();
            }

            /* Increment the TA counter */
            iTA++;

            if (iDebug)
            {
                sprintf(sDT,"End iTA(%d): iMth(%d),iDay(%d),nMth(%d),nDay(%d),nTA(%d)",iTA,iMth,iDay,nMth,nDay,nTA);
                myDebugDT();
            }

            /* Completed all TA for each day */
            if (iTA>nTA)
            {
                break;
            }
        }
        /* Next month */
        iMth++;
    }

    /* Close the file */
    fclose(fTAData);

    myDebugST("Exit function");
}
int main()
{
    int iReturn;
    int iStartDate,iEndDate;
    int iStartDay,iEndDay,iStartMonth,iEndMonth;

    char cStartDate[11],cEndDate[11];

    /* Switch debug on and set calling function name - sFN */

    if(iDebug){
        myDebugOn("main");
        myDebugST("Program is running!");
    }

    /* Set return */
    iReturn = 1;

    /* Get a random date range - first integer then string */
    GetIDateRange(&iStartDate,&iEndDate);

    if(iDebug)
    {
        myDebugOn("main 1");
        sprintf(sDT,"iStartDate(%d),iEndDate(%d)",iStartDate,iEndDate);
        myDebugDT();
    }

    /* Now convert integers to strings - send the address for updates! */
    GetSDateRange(iStartDate,iEndDate,cStartDate,cEndDate,&iStartDay,&iEndDay,&iStartMonth,&iEndMonth);

    if(iDebug){
        myDebugOn("main 2");

        sprintf(sDT,"iStartDate(%d),iEndDate(%d),cStartDate(%s),cEndDate(%s),iStartMonth(%d),iEndMonth(%d)",iStartDate,iEndDate,cStartDate,cEndDate,iStartMonth,iEndMonth);
        myDebugDT();

        myDebugOn("main 3");
    }

    /* Populate and write TA Data */
    PopTAData(iStartDate,iEndDate,cStartDate,cEndDate,iStartDay,iEndDay,iStartMonth,iEndMonth);

    /* Return 1 for successful completion */
    if(iDebug)
    {
        myDebugST("Exit Main");
    }

    return iReturn;
}
