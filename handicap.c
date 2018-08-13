#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct{
	char player[150];
	float handicap;
	int scores[20];
	int times_out;
	int played;
} golfer;
typedef struct{
	char club[150];
	int slope;
	float rating;
} golfcourse;
	
void course_entry(golfcourse *gc);
void calculator(golfcourse *gc, golfer *p);
void name_entry(golfer *p);
void save_golfer(golfer *p, golfer *q);
void look_up(golfer *p, golfer *q);
int check_variance (golfer *p);


int main()
{
	golfer player1, player2;
	golfcourse entry;
	
	int counter = 0, selection;
			//Main Menu//
	while (counter == 0){
		printf("Welcome to a handicap calculator with no graphics.\n"
			"In order to calculate handicap, please enter course info "
			"first, then score entry.\n"
			"Please make a selection using numbers.\n"
			"1. Course Entry\n"
			"2. Handicap Entry\n"
			"3. Lookup\n"
			"4. Exit\n");
		
		scanf("%d", &selection);
			//Main Menu Selection//
		switch (selection){
			case 1:
				course_entry(&entry);
				break;
			case 2:
				name_entry(&player1);
				calculator(&entry, &player1);
				save_golfer(&player1, &player2);
				break;
			case 3:
				printf("Did you wish to look up a golfer or" 
				" the current course?\n"
				"1. Player\n"
				"2. Course\n");
				scanf("%d", &selection);
					if (selection == 1){
						look_up(&player1, &player2);
						break;
					}
					if (selection == 2){
						printf("%s: \nSlope:%d \nRating:%.1f\n\n\n", entry.club,
						entry.slope, entry.rating);
						break;
					}
					else {
					 printf("Invalid selection. Please try again\n");
					break;
					}
			case 4:
				printf("Thank you for using the graphicless " 
						"handicap system.\n");
				counter++;
				break;
			default:
				printf("Invalid selection. Please try again\n");
				break;
			}
		}	
	return 0;
}

void course_entry(golfcourse *gc){
	int counter = 0, i = 0;
	
	while (counter == 0){
		printf("Enter the name of the Golf Course:\n");
		scanf(" %[^\t\n]s", gc->club);
		printf("Enter the slope:\n");
		scanf("%d", &gc->slope);
		//Checking if entry is valid for course//
			if (gc->slope > 155 || gc->slope < 55){
				printf("This is an invalide slope. Please try again.\n");
				break;
				}
		printf("Enter the rating\n");
		scanf("%f", &gc->rating);
		//Checking if entry is valid for course//
			if (gc->rating > 85 || gc->rating < 50){
				printf("This is an invalide rating. Please try again.\n");
				break;
				}
		printf("Is this information correct:\n"
			   "Name: %s\nSlope: %d\nRating: %.1f\n"
			   "1 for yes, 2 for no.\n",
			   gc->club, gc->slope, gc->rating);
		scanf("%d", &i);
			if (i == 1){
				printf("\n\n\n");
				counter++;
				continue;
				}
			if (i != 2){
				printf("You have made an invalid selection. Try again.\n");
				continue; 
				}
	}
}
		
void name_entry(golfer *p){
		int counter = 0, i;
	while (counter == 0){
		printf("Enter your first and last name:\n");
		scanf(" %[^\n]s", p->player);
		printf("Is this information correct:\n"
			   "1 for yes, 2 for no.\n"
			   "Name: %s\n", p->player);
		scanf("%d", &i);
			if (i == 1){
				counter++;
				break;}
			if (i == 2)
				continue;
			else {
				printf("You have made an invalid selection. Try again.\n");
				continue; }			
		}
}
	
int check_variance(golfer *p){
	int i, counter = 1, variance;
	p->played = 0;
	
	while (counter != 0){
		printf("Please enter your 18 hole scores. 0 to exit.\n");
		for (i = 0; i < 20; i++){
			scanf("%d", &p->scores[i]);
			if (p->scores[i] == 0)
				break;
			if (p->scores[i] < 55){
				printf("\nThis is for 18 holes, not nine." 
				" Please continue.\n");
				i--;
				continue;}
			else
				p->played++;
			}
		counter = 0;
	switch (p->played){
		case 5:
		case 6:
			variance = 1;
			break;		
		case 7:
		case 8:
			variance = 2;
			break;
		case 9:
		case 10:
			variance = 3;
			break;
		case 11:
		case 12:
			variance = 4;
			break;
		case 13:
		case 14:
			variance = 5;
			break;
		case 15:
		case 16:
			variance = 6;
			break;
		case 17:
			variance = 7;
			break;
		case 18:
			variance = 8;
			break;
		case 19:
			variance = 9;
			break;
		case 20:
			variance = 10;
			break;
		default:
		printf("You entered less than five scores. Please enter more.");
		counter = 1;
		continue;
	  }
	}
	return variance;
}

void calculator(golfcourse *g, golfer *p){
	int amount = check_variance(p);
	float variance[amount], sum = 0;
	int i,j, temp;
	
	//Reordering entered scores lowest to highest//
	for (i = 0; i < p->played; i++){
			for (j = i+1; j < p->played; j++){
			if (p->scores[i] > p->scores[j]){
				temp = p->scores[i];
				p->scores[i] = p->scores[j];
				p->scores[j] = temp;
				}
			}
		}	
	//Actual Calculation//
	for (i = 0; i < amount; i++){
		variance[i] = ((p->scores[i] - g->rating)*113)/g->slope;
	}
	//Add Scores Up//
	for (i = 0; i < amount; i++){
		sum = sum + variance[i];
	}
	//Divide and get handicap//
	p->handicap = (sum/amount)* .96;
	
	printf("Your handicap index is %.1f.\n\n\n", p->handicap); 
}

void save_golfer (golfer *p, golfer *q){
	int i;
	strcpy(q->player, p->player);
	q->handicap = p->handicap;
	for (i=0; i< 20; i++){
		if (p->scores[i] == 0)
			break;
		else{
			q->scores[i] = p->scores[i];}
			}
}

void look_up (golfer *p, golfer *q){
	int i, result, counter=0;
	while (counter == 0){
		printf("Enter golfer name you wish to look up.\n");
		scanf(" %[\t\n]s", p->player);
		//Player name comparison//
		result = strcmp(p->player, q->player);
		if (result == 0){
			printf("%s\n", q->player);
			printf("Scores:\n");
			for (i = 0; i <20; i++){
				if (q->scores[i] == 0)
					break;
				else
					printf("%d\n", q->scores[i]);
				}
			printf("Handicap Index:\n%.2f\n", q->handicap);
			break;
			}	
		else {
			printf("Player not found. Try again.\n");
			counter++;}
		}	
}
			

			
					
				
			
			
		
	
	
	
		
	
	
	
			
		
			
	
	
	
				
	
