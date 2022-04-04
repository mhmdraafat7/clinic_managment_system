/*****************************************************************************************************************************************/
/*                                                        owner: mhmdraafat7                                                             */
/*****************************************************************************************************************************************/
#include <stdio.h>
#include "std_types.h"
#define SIZE 10


typedef struct nwPatient
{
	u8 name[10];
	u8 age;
	u8 gender;
	u8 id;	
} patient;

patient nwRecord [SIZE];

/* Zero in slots means that the slot is reserved */
static u8 slots[6]  = {0,1, 2, 3, 4, 5};

/* Zero in slotLog means that the slot is not reserved */
static u8 slotLog [SIZE] = {0};

u8 addFlag = 0;

void UI (void);
u8 addPatient  (void);
void editPatient (u8 idIn);
void reserveSlot (u8 idIn);
void cancelSlot  (u8 idIn);
void viewPatient (u8 idIn);
void viewResLog  (void);

void main (void)
{
	u8 i;
	u8 feature = 0, featureUser = 0, id;
	u8 idIn;
	u32 mode = 0, adminPass, passIn = 1234, passInFlag = 0;
	
	while (mode <= 2)
	{
		printf("There are two modes:\n1. Admin Mode.\n2. User Mode.\n");
		printf("Please enter mode number: ");
		scanf("%d", &mode);
		
		switch (mode)
		{
			case 1:  passInFlag = 0;
					 passIn = 1234;
					 while (passInFlag < 3)
					 {
						passInFlag++;
						printf("Please enter ADMIN mode Password: ");
						scanf("%d", &adminPass);
						printf("password trial number %d /3 \n", passInFlag);
						if (adminPass == passIn)
							{   
						       printf("Feature: %d\n", feature);
							   feature = 0;
								while (feature <= 4)
									{   
										printf("Admin mode features:\n1. Add new patient record.\n2. Edit patient record."
											   "\n3. Reserve a slot with the doctor.\n4. Cancel reservation.\n");
										printf("Choose feature: ");
										scanf("%d", &feature);
				
										switch (feature)
										{
											case 1: id = addPatient  ();
													printf("New patient is added successfully, with ID = %d\n", id);
													break;
											case 2: printf("Please enter your ID: ");
													scanf("%d", &idIn);
													editPatient (idIn);
													break;
											case 3: printf("Please enter your ID3: ");
													scanf("%d", &idIn);
													reserveSlot(idIn);
													break;
											case 4: printf("Please enter your ID4: ");
													scanf("%d", &idIn);
													cancelSlot(idIn);
													break;
											default: printf("No corresponding feature!!\n");
										}
									}
									break;
								}
						else
						{ printf("Trial is failed, try again please!\n"); }
					 }
					 break;
			case 2: 
					featureUser = 0;
					while (featureUser <= 2)
					{
						printf("User mode features are:\n1. View patient record."
							   "\n2. View reservation log.\n");
						printf("Choose feature: ");
						scanf("%d", &featureUser);
						
						switch (featureUser)
						{
							case 1: printf("Please enter your ID: ");
									scanf("%d", &idIn);
									viewPatient(idIn);
									break;
							case 2: viewResLog ();
							        break;
							default: printf("No corresponding feature!!\n");
						}
					}
					break;
					
			default: printf("Unavailable Choice!!\n");
		}
	}
}

u8 addPatient  ()
{
	u8 i;
	addFlag++;
	/* Name */
	printf("Enter patient name: ");
    fflush(stdin);
	scanf("%s", nwRecord[addFlag].name);
    /* Age */
    printf("Enter patient age: ");
    fflush(stdin);
	scanf("%d", &nwRecord[addFlag].age);
    /* Gender */
	printf("Enter patient gender: ");
    fflush(stdin);
	scanf("%c", &nwRecord[addFlag].gender);
    /* ID */
	nwRecord[addFlag].id = addFlag;
	
	for (i = 1; i <= addFlag; i++)
	{ 
		printf("Patient[%d].name   : %s\n", i, nwRecord[i].name);
		printf("Patient[%d].age    : %d\n", i, nwRecord[i].age);
		printf("Patient[%d].gender : %c\n", i, nwRecord[i].gender);
		printf("Patient[%d].id     : %d\n", i, nwRecord[i].id);
    }
	
    return nwRecord[addFlag].id;	
}

void editPatient (u8 idIn)
{
	u8 edit, i;
	
	if (idIn != 0 && idIn <= addFlag)
	{
		printf("Your data: \n");
		printf("Name   : %s\n", nwRecord[idIn].name);
		printf("Age    : %d\n", nwRecord[idIn].age);
		printf("Gender : %c\n", nwRecord[idIn].gender);
		printf("To edit, press 1.\n");
		
        printf("Enter edited name: ");
		fflush(stdin);
	    scanf("%s", nwRecord[idIn].name);
        /* Age */
        printf("Enter edited age: ");
        fflush(stdin);
	    scanf("%d", &nwRecord[idIn].age);
        /* Gender */
        printf("Enter edited gender: ");
        fflush(stdin);
	    scanf("%c", &nwRecord[idIn].gender);
		nwRecord[addFlag].id = addFlag;
	    
	}
	else
	{ printf("Incorrect ID!!\n"); }

	for (i = 1; i <= addFlag; i++)
	{ 
		printf("Patient[%d].name   : %s\n", i, nwRecord[i].name);
		printf("Patient[%d].age    : %d\n", i, nwRecord[i].age);
		printf("Patient[%d].gender : %c\n", i, nwRecord[i].gender);
		printf("Patient[%d].id     : %d\n", i, nwRecord[i].id);
    }

}


void reserveSlot (u8 idIn)
{
	static u8 flag  = 0;
	static u8 choice;
	u8 i;
	
	if (idIn != 0 && idIn <= addFlag)
	{	
		if (flag == 0)
		{
			printf("Available Slots are: \n1. 2pm to 2:30pm.\n2. 2:30pm to 3pm.\n"
				   "4. 3:30pm to 4pm.\n5. 4pm to 4:30pm.\n");
			
			printf("\nPlease choose slot number0: ");
			scanf("%d", &choice);
			
			if (choice >= 1 && choice <= 5)
			{
				slots[choice] = 0;
				slotLog[idIn] = choice;
				flag++;
			}
			else 
			{ printf("There are only 5 slots!!\n"); }
		}
		
		else 
		{
			printf("Available slots are: \n");
			
			for (i = 1; i <= 5; i++)
			{
			   printf("%d. %d\n", i, slots[i]);
			}			  
			   
			printf("Please choose slot number1: ");
			scanf("%d", &choice);
			
			if (choice >= 1 && choice <= 5)
			{
				if (slots[choice] == 0)
				{ printf("Slot is not available!!\n"); }
				else
				{ 
					slots[choice] = 0;
					slotLog[idIn] = choice;			
				}
			}
			else 
			{ printf("There are only 5 slots!!\n"); }
		}
	}
	else
	{ printf("Incorrect ID!!\n"); }

	for (i = 1; i <= 5; i++)
	{ printf("Slots1-%d: %d\n", i, slots[i]); }
	for (i = 1; i <= addFlag; i++)
	{ printf("ID1: %4d, Slot1: %4d\n", i, slotLog[i]); }
	
}

void cancelSlot  (u8 idIn)
{
	u8 slotNum, i;
	
	if (idIn != 0 && idIn <= addFlag)
	{
		if (slotLog[idIn] == 0)
		{ printf("No previous reservation!!\n"); }
		else
		{
			slotNum = slotLog[idIn];
			slots[slotNum] = slotNum;
			slotLog[idIn] = 0;
		}
	}
	else
	{ printf("Incorrect ID!!\n"); }
	
	for (i = 1; i <= 5; i++)
	{ printf("Slots1-%d: %d\n", i, slots[i]); }
	for (i = 1; i <= addFlag; i++)
	{ printf("ID2: %4d, Slot2: %4d\n", i, slotLog[i]); }
}

void viewPatient (u8 idIn)
{
	printf("Name   : %s\n", nwRecord[idIn].name);
	printf("Age    : %d\n", nwRecord[idIn].age);
	printf("Gender : %c\n", nwRecord[idIn].gender);
	printf("ID     : %d\n", nwRecord[idIn].id);
}

void viewResLog  (void)
{
	u8 i;
	
	for (i = 1; i <= addFlag; i++)
	{ 
		printf( "ID: %4d, Slot: %4d\n", i, slotLog[i]); 
	}
}
