/*
Varun Grover
- 
*/

#include<stdio.h>
#include<stdbool.h>


typedef struct coordinates{
    int x,y;
} coordinates;

char char_grid[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char player1_choice, player2_choice;

void code_runner(int );
void print_grid();
void checking_space(int, int, int);
coordinates get_coordinates(int move);
int take_input(int);
int terminator(int);


int main(){
    
    input:
    // input for X or O
    printf("\nEnter the choice for player 1 ( X or O ): ");
    scanf(" %c", &player1_choice);

    if(player1_choice == 'X' || player1_choice == 'x'){
        player1_choice = 'X';
        player2_choice = 'O';
    }
    else if(player1_choice == 'O' || player1_choice == 'o'){
        player1_choice = 'O';
        player2_choice = 'X';
    }
    else{
        printf("\nWrong input!!! Please ener the right input again.....\n");
        goto input;
    }

    printf("\nPlayer 1 has %c", player1_choice);
    printf("\nPlayer 2 has %c", player2_choice);

    /*-----------------------------------------------------------------------*/

    // steps
    int step, player_turn;

    for(step=1; step<10; step++){
        // int_grid_print();

        player_turn = (step%2) != 0 ?  1 :  2;
        code_runner(player_turn);

        if(step==9){
            printf("\nTIES");
            break;
        }

        if(step>3){
            int result = terminator(player_turn);
            if(result == 1){ // one wins
                print_grid();
                printf("\nPlayer %d wins", player_turn);
                break;
            }
            else if(result == 0){ // continue
                print_grid();
                continue;
            }
            
        }
    }
  
    return 0;
}

void code_runner(int player_turn){
    // printing grid
    print_grid();

    // taking input
    int move = take_input(player_turn);

    // GETTING CO-ORDINATES
    coordinates c1;
    c1 = get_coordinates(move); 
    /* printf("x = %d y = %d", c1.x, c1.y); */

    // checking space available
    checking_space(c1.x, c1.y, player_turn);
}


void print_grid(){
    printf("\n\n");
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(j==1 || j==2)
                printf("|");
            printf(" %c ", char_grid[i][j]);
        }
        if(i==2)
            break;
        printf("\n-------------\n\n");
    }
}

int take_input(int player){
    int move;
    do{
        printf("\nPlease enter the move for player %d : ", player);
        scanf("%d", &move);
    }while(move<1 || move >9); // out of range condition

    return move;
}

void checking_space(int x, int y, int player_turn){
    // changing the O and X based on player 1 or 2
    char input = player_turn == 1 ? player1_choice : player2_choice;

    // sum values
    int sum_value = player_turn == 1 ? 5 : 2; // player 1 = 5 and player 2 = 2

    // checking the condition to enter X/O in grid
    if((char_grid[x][y] >= 49) && (char_grid[x][y] <= 57) ){ // ASCII value of 1 = 49 and 9 = 57
        char_grid[x][y] = input;
        // int_grid[x][y] = sum_value;
        // printf("\nint_grid[%d][%d] = %d\n", x,y,int_grid[x][y]);
    }
    else{
        printf("\nWrong move...... Space already filled!!");
        printf("\nPlease try again....");
        code_runner(player_turn); // FUNCTION CALL TO TAKE INPUT AGAIN
    }

}

coordinates get_coordinates(int move){
    coordinates c;

    switch(move){
        case 1: c.x=0, c.y=0;
            break;
        case 2: c.x=0, c.y=1;
            break;
        case 3: c.x=0, c.y=2;
            break;
        case 4: c.x=1, c.y=0;
            break;
        case 5: c.x=1, c.y=1;
            break;
        case 6: c.x=1, c.y=2;
            break;
        case 7: c.x=2, c.y=0;
            break;
        case 8: c.x=2, c.y=1;
            break;
        case 9: c.x=2, c.y=2;
            break;
    }
    return c; // returns 2 variable (x and y)
}

int terminator(int player_turn){
    int result = 0; // continue

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            int sum_row=0, col_sum=0, rdiagonal_sum=0, ldiagonal_sum =0; 
            ldiagonal_sum = char_grid[0][2] + char_grid[1][1] + char_grid[2][0];
            sum_row += char_grid[i][j];
            col_sum += char_grid[j][i];
            rdiagonal_sum += char_grid[i][i];

            if(sum_row==264 || sum_row==237 || col_sum==264 || col_sum== 237 || rdiagonal_sum==264 || rdiagonal_sum==237 || ldiagonal_sum==237 || ldiagonal_sum==264){
                printf("\nrow = %d\ncol = %d\nld = %d\nrd = %d", sum_row, col_sum, rdiagonal_sum, ldiagonal_sum);
                result = 1; // one player wins
                break;
            }
        }
    }
    return result;
}