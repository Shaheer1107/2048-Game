#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<conio.h>

int Game[5][5]={0};//initialising to 0 and starting index from 1 and not 0;therefore, not declaring matrix by Game[4][4]
int score=0;
int win=2;//2 means game is continuing, whereas 1 means win and 0 means lose

int winner();//Decides winning part
void Screen();// Displays output on console screen
void Dropper();// Randomly creates a number(2 or 4) and keeps in random empty box
void Action();//Used to perform 4 moves (  UP, DOWN, RIGHT, LEFT)

int winner()//Decides winning if 1 is returned. 0 returned means lost
{
    int i,j,frequency=0;//frequency initialised to 0 assuming box is filled completely having no valid moves to be done.

    for(i=1;i<=4;i++)  // These 2 loops will find the number 2048 or empty space (for the game to get continued)
    {
        for(j=1;j<=4;j++)//linear search
        {
            if(Game[i][j]==2048)//If this number is genearated so user wins
            {
            	win=1;
            	return(win);
			}      
            if(Game[i][j]==0)//checks if space available
                frequency=1;//means box is not completely filled
        }
    }
    if(frequency==0) // if whole box is filled
    {
        for(i=1;i<=3;i++)//i(row) will not be <=4 beacuse index position of i is already being increased by 1.
    	{
        	for(j=1;j<=3;j++)  //j(column) will not be <=4 beacuse index position of j is already being increased by 1.
        	{
        		if(Game[i][j]==Game[i+1][j] || Game[i][j]==Game[i][j+1] ) //checks if any valid moves are possible
        		{
        			frequency=1;// if valid moves are possible so it will simply jump out of loop only to decrease no. of iteration
        			break;
				}
        	}
        	if(frequency==1)//extra statement to decrease no. of iteration
        		break;
        }
    }
    if(frequency==0)//Finally, if box is filled and no valid moves are possible so win=0
    	win=0;
    return win;
}
void Screen()//To Display Output in console Screen
{
    int i,j;
    system("cls");
    system("color 4E");//combination 
    printf("\n \t\t TWO - ZERO - FOUR - EIGHT (2048)\n");//HEADING
    printf("\n                            SCORE = %d\n\n\n\n",score);//to print score
    printf(" ___________________________\n");// to make upper line for border
    for(i=1;i<=4;i++)
    {
    	printf(" |");
        for(j=1;j<=4;j++)
        {
            if(Game[i][j]==0)
            {
                printf(":     ");//displaying empty space rather than showing zero
            }
            else
                printf("|%4d ",Game[i][j]);//4d represents 4 spaces
        }
        if(i!=4)
            printf(":| \n |                         |\n");
        else 
            printf(":|  ");//special condition for last row as not to print extra space and lines like previos rows 
    }						//becuase we have to make a new line below for bordering
    printf("\n |_________________________|\n\n\n");//to make below border line
    printf("Enter W to move up ,S to move down, A to move left and D to move right and 0 to exit");//instructions
}

void Dropper()//Drops number 2 or 4 to a random empty position
{
    int i,j;
	int count=1;//to add a counting variable to calculate random numbers for specific number of time.
    srand(time(0));
    i=1+rand()%4;  // row starting from index 1 to 4
   	j=1+rand()%4;  // column starting from index 1 to 4
   		
    while(Game[i][j]!=0)//will find a random space and drop 2 or 4 in it.
    {
   		i=1+rand()%4;  // row	
   		j=1+rand()%4;  // column
   		count++;
 		if (count==10)//don't want the loop to run high number of times
		    break;
    }
    if(count!=10)//This condition ensures that an empty space to drop the number is found
    {
        Game[i][j]=2;
       	if(count%3==0 )//used mod 3 to only show rare cases to drop 3, no special logic for this
     		Game[i][j]=4; //in rare moves, 4 is dropped besides of 2
    }
}

void action(char Arrow)//function to control moves
{
	int i,j,count;
	if (Arrow=='w')// Move UP
	{
		for(j=1;j<=4;j++)//will first work on column 1 and then move on column 2 till column 4
   		{
			for(count=1;count<=3;count++)//as there are 4 row blocks in a single column so UP needs to be applied
			{							   // -normally three times to avoid any output fault
   				for(i=1;i<=3;i++)//i(rows) are not <=4 because i+1 includes it in the below condition
   				{
   					if(Game[i][j]==0 || Game[i][j]==Game[i+1][j])//condition to check two same numbers or 0.
	   				{
	   					if((Game[i][j]==Game[i+1][j]) && Game[i][j]!=0)//condition to check two same nnumbers adding which should not include 0.
	   						score=score+Game[i][j]*2;//score is calulated by adding previos score to new number formed 
	   													//-By adding of SAME NUMBERS only,that's why it is multiplied by 2
   						Game[i][j]=Game[i][j]+Game[i+1][j];// will add (empty space with a number) or (empty space with itself) 
						   									//OR (it adds two same numbers)
   						Game[i+1][j]=0;// making other row empty 
					}			
				}
			}
		}
  		Dropper();// to call this function to drop a random number 
   		Screen();// to call this function to print game array on console screen
	}
	else if (Arrow=='s')//Move DOWN
	{
		for(j=1;j<=4;j++)	//will first work on column 1 and then move on column 2 till column 4
   		{
			for(count=1;count<=3;count++)//as there are 4 row blocks in a single column so DOWN needs to be applied
			{							   // -normally three times to avoid any output fault
   				for(i=4;i>=2;i--)//i(rows) are not >=1 because i-1 includes it in the below condition
   					if(Game[i][j]==0 || Game[i][j]==Game[i-1][j])//condition to check two same numbers or 0.
	   				{
	   					if((Game[i][j]==Game[i-1][j]) && Game[i][j]!=0)//condition to check two same nnumbers adding which should not include 0.
	   						score=score+Game[i][j]*2;//score is calulated by adding previos score to new number formed 
	   													//-By adding of SAME NUMBERS only,that's why it is multiplied by 2  
						Game[i][j]=Game[i][j]+Game[i-1][j];// will add (empty space with a number) or (empty space with itself) 
															// OR (it adds two same numbers)
   						Game[i-1][j]=0;// making other row empty
					}			
				}
			}
		
  		Dropper();// to call this function to drop a random number 
   		Screen();// to call this function to print game array on console screen
	}	

	else if (Arrow=='a')//Move LEFT
	{
		for(i=1;i<=4;i++)//will first work on Row 1 and then move on Row 2 till Row 4
   		{
			for(count=1;count<=3;count++)//as there are 4 row blocks in a single column so UP needs to be applied
			{							   // -normally three times to avoid any output fault							   
   				for(j=1;j<=3;j++)//j(column) is not <=4 because j+1 includes it in the below condition
   				{
   					if(Game[i][j]==0 || Game[i][j]==Game[i][j+1])//condition to check two same numbers or 0.
	   				{
	   					if((Game[i][j]==Game[i][j+1]) && Game[i][j]!=0)//condition to check two same nnumbers adding which should not include 0.
	   						score=score+Game[i][j]*2;//score is calulated by adding previos score to new number formed 
	   													//-By adding of SAME NUMBERS only,that's why it is multiplied by 2   						
						Game[i][j]=Game[i][j]+Game[i][j+1];// will add (empty space with a number) or (empty space with itself) 
															//OR (it adds two same numbers)
   						Game[i][j+1]=0;// making other row empty
					}			
				}
			}
		}
  		Dropper();// to call this function to drop a random number 
   		Screen();// to call this function to print game array on console screen
	}
	else if (Arrow=='d')//Move RIGHT
	{
		for(i=1;i<=4;i++)//will first work on Row 1 and then move on Row 2 till Row 4
   		{
			for(count=1;count<=3;count++)//as there are 4 column blocks in a single row so UP needs to be applied
			{							   // -normally three times to avoid any output fault							   
   				for(j=4;j>=2;j--)//j(column) is not >=1 because j-1 includes it in the below condition
   				{
   					if(Game[i][j]==0 || Game[i][j]==Game[i][j-1])//condition to check two same numbers or 0.
	   				{
	   					if((Game[i][j]==Game[i][j-1]) && Game[i][j]!=0)//condition to check two same nnumbers adding which should not include 0.
	   						score=score+Game[i][j]*2;//score is calulated by adding previos score to new number formed 
	   													//-By adding of SAME NUMBERS only,that's why it is multiplied by 2 
  						Game[i][j]=Game[i][j]+Game[i][j-1];// will add (empty space with a number) or (empty space with itself) 
  															//OR (it adds two same numbers)
   						Game[i][j-1]=0;// making other row empty
					}			
				}
			}
		}
   		Dropper();// to call this function to drop a random number 
   		Screen();// to call this function to print game array on console screen
	}
}
    
void main()
{
    char Arrow='q';// initialisation
    int i,j;
    srand(time(0));
    i=1+rand()%4;  // i	
   	j=1+rand()%4;  // j
    Game[i][j]=2;  // There are always initially 2 box filled in 2048 in which this is the first box we have filled
    i=1+rand()%4;  // i	
   	j=1+rand()%4;  // j
   	if(i%4==0 && j%4==0)	//Condition to add 4 when border values came, no special logic for this
   		Game[i][j]=4;
   	else
   		Game[i][j]=2;  		
    Screen();// will print game array in tabular form 
    while(Arrow!='0')  //game will run until '0' key is pressed or user wins or lose the game 
    {
        Arrow=getch();//will store character without even pressing 'enter key'
        action(Arrow);//only a,w,s,d will give output results due to if-else statement
        win=winner();//will usually return 2 showing game is continuing and user has not lost nor win
        if(win==1)
        {
            printf("\n\t\t\tYOU WON");
            printf("\n\n\t\t\t\tYOUR SCORE is  : %d",score);
            break;
        }
        if(win==0)
        {
            printf("\n\t\t\tSORRY !  GAME OVER\n");
            break;
        }
    }
}

