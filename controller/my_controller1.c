#include <webots/distance_sensor.h>
#include <webots/motor.h>
#include <webots/position_sensor.h>
#include <webots/robot.h>

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#define TIME_STEP 32

enum State { WAITING, GRASPING, ROTATING, RELEASING, ROTATING_BACK };

void move_to_column (int column){

int i;

 const double tokens_position[6] = {-2.1, -1.6, 2.3, -1.5, 0, -1.5};
 
 const double pre_target_position1[6] = {-2.1, -1.2, 2.3, -1.5, 0, -1.5};
 const double pre_target_position[6] = {-1.6, -2.5, 2.3, -1.5, 0, -1.5};
 
 const double target_positions [7][6] = {
     // 0 = shoulder lift
     // 1 = elbow
     // 2 = wrist 1
     // 3 = wrist 2
     // 4 = wrist 3
     // 5 = shoulder pan 
     {-1.4, 0.4, 5.6, -1.4, -0.85, -2.30}, //col 1
     {-1.6, 0.5, 5.8, -1.4, -1.3, -2.7}, //col 2
     {-2.0, 0.95, 6, -1.4, -1.5, -3.15}, // col 3
     {-1.1, -0.85, 3.8, 1.6, -1.15, 0.5}, //col 4
     {-1.4, -0.6, 3.8, 1.6, -1.65, -0.2}, //col 5
     {-1.6, -0.5, 4.0, 1.6, -2.3, -0.7},// col 6
     {-1.8, -0.3, 4.2, 1.6, -2.6, -1},//col 7
      };

   double speed = 1.0;
 
    WbDeviceTag hand_motors[3];
      hand_motors[0] = wb_robot_get_device("finger_1_joint_1");
      hand_motors[1] = wb_robot_get_device("finger_2_joint_1");
      hand_motors[2] = wb_robot_get_device("finger_middle_joint_1");
  
    WbDeviceTag ur_motors[6];
      ur_motors[0] = wb_robot_get_device("shoulder_lift_joint");
      ur_motors[1] = wb_robot_get_device("elbow_joint");
      ur_motors[2] = wb_robot_get_device("wrist_1_joint");
      ur_motors[3] = wb_robot_get_device("wrist_2_joint");
      ur_motors[4] = wb_robot_get_device("wrist_3_joint");
      ur_motors[5] = wb_robot_get_device("shoulder_pan_joint");
  
    for(i = 0; i < 6; i++)
    wb_motor_set_velocity(ur_motors[i], speed);
    
    
       WbDeviceTag distance_sensor = wb_robot_get_device("distance sensor");
        wb_distance_sensor_enable(distance_sensor, TIME_STEP);

       WbDeviceTag position_sensor = wb_robot_get_device("wrist_1_joint_sensor");
        wb_position_sensor_enable(position_sensor, TIME_STEP);

        wb_robot_step (32);

  //deschide degetele
 
    for(i=0;i<3;i++){
       wb_motor_set_position(hand_motors[i], wb_motor_get_min_position(hand_motors[i]));};
       
       //bratul deasupra piesei
       wb_robot_step (1000);
       
    for (i = 0; i < 6; ++i){
       wb_motor_set_position(ur_motors[i], tokens_position[i]);}
  
       wb_motor_set_position(ur_motors[1], tokens_position[1]-0.2);
       
       
  printf("down for token");
        
// PAS 2 - robotul ia piesa
       wb_robot_step (2500);
         
       wb_motor_set_position(ur_motors[0], -1.6);
       wb_motor_set_position(ur_motors[1], -2.2); 

   for(i=0;i<3;i++)
       wb_motor_set_position(hand_motors[i], wb_motor_get_max_position(hand_motors[i]));
      
           
// PAS 3 - robotul ridica bratul
        
       //ridica elbow
        
       wb_robot_step (1000);
           
       wb_motor_set_position(ur_motors[1], 0);
    
       //muta deasupra jocului
       wb_robot_step (1000);
      
    for (i = 0; i < 6; ++i)
         wb_motor_set_position(ur_motors[i], target_positions[column][i]);
            
//PAS 4 - robotul lasa piesa

      //switch- ajustări ale poziției
      
     switch(column){
       case 4: wb_robot_step (3000);
               wb_motor_set_position(ur_motors[2], 3.6);
               break; 
       case 5: wb_robot_step (3000);
               wb_motor_set_position(ur_motors[2], 3.65);
               break;
       case 0: wb_robot_step (3000);  
               wb_motor_set_position(ur_motors[2], 5.8);
               break;
       case 1: wb_robot_step (3000);
               break;
         
       case 2: wb_robot_step (3000);
               wb_motor_set_position(ur_motors[2], 5.7);
               break;
       case 3: wb_robot_step (3000);
        
         };
         
         wb_robot_step (3000);
         
    for(i=0;i<3;i++)
         wb_motor_set_position(hand_motors[i], wb_motor_get_min_position(hand_motors[i]));
       
//PAS 5 - robotul ridica bratul
      //switch- ajustari ale pozitiei de ridicare  
    switch(column){
       case 6: wb_robot_step (3000);
               wb_motor_set_position(ur_motors[2], 4.8);
               wb_robot_step (1000);
               wb_motor_set_position(ur_motors[0], -1);
               break; 
       case 4: wb_robot_step (1000);
               wb_motor_set_position(ur_motors[0], -1);
               break;
       case 0: wb_motor_set_position(ur_motors[2], 4);     
               wb_motor_set_position(ur_motors[1], 0);
               break;
       case 1: wb_motor_set_position(ur_motors[2], 4);     
               wb_motor_set_position(ur_motors[1], 0);
               break;
       case 2: wb_motor_set_position(ur_motors[2], 4);     
               wb_motor_set_position(ur_motors[1], 0);
               break;
       case 3: wb_robot_step (2000);
               wb_motor_set_position(ur_motors[5], -1.5);
        
         };
       
        printf("next token");
 
        wb_robot_step (3000);
       
//PAS 6 - robotul se mută pe pozitie pentru urmatoarea piesă

    for(i = 0;i < 6; i++){
         wb_motor_set_position(ur_motors[i], pre_target_position[i]);}
  
         wb_robot_step (1000);
         
    for(i = 0;i < 6; i++){
         wb_motor_set_position(ur_motors[i], pre_target_position1[i]);}
      //ajustări finale    
    if((column == 6)||(column==4)||(column==5)||(column==3)){
         wb_robot_step (3000);};

}

#define MAX_ROW 6
#define MAX_COL 7
#define MIN_ROW_COL 0
int ai_player;

int is_valid_row_col(int row , int col)
{
    return (MIN_ROW_COL <= row && row < MAX_ROW && MIN_ROW_COL <= col && col < MAX_COL);
}

int is_valid_move(int board[MAX_ROW][MAX_COL], int row, int col)
{
    return (board[row][col] == 0 && is_valid_row_col(row, col));
}

int count_direction(int board[MAX_ROW][MAX_COL], int row , int col , int rowinc, int colinc , int player)
{
    int count = 0;
    while(is_valid_row_col(row, col) && board[row][col] == player)
    {
            count++;
            col += colinc;
            row += rowinc;
    }

    return count;
}

int get_horizontal_connectivity(int board[MAX_ROW][MAX_COL], int player)
{
    int row , col;
    int length = 0;
    int aux;

    for(row = MIN_ROW_COL; row < MAX_ROW; row++)
        for(col = MIN_ROW_COL; col < MAX_COL - 1; col++) // -1 as I don't need to check the last column as there is nothing on the right
            {
                aux = count_direction(board, row, col , 0 , 1 , player);
                length += aux; //there is no need to check on the left as it will be checked beforehand 123 234 345 etc
                //col += aux - 1; // the -1 is there for safety reasons since the for will also increment it by 1 and to skip double counting
            }

    return length;
}

int get_vertical_connectivity(int board[MAX_ROW][MAX_COL], int player)
{
    int row, col, aux; // this aux stuff I am no longer sure about and I don't feel like checking so I'm leaving it here
    int length = 0;
    for(col = MIN_ROW_COL; col < MAX_COL; col++)
        for(row = MIN_ROW_COL; row < MAX_ROW - 1; row++) // -1 as I don't need to check the last row as there is nothing above it
                {
                    aux = count_direction(board, row , col , 1 , 0, player);
                    length += aux;
                    // row += aux -1; since the vertical connection is considered to be the most important, by counting it like this the value will be bigger since a connection of 3 will actually increment length by 6
                }   // and therefore vertical connectivity will be valued more than horizontal, but do add that expression as it improves performance slightly but it devalues verticality making a connection of 3 worth 3
    return length;
}

int get_diagonal_connectivity(int board[MAX_ROW][MAX_COL], int player, int up_or_down, int left_or_right)
{
    int row, col, aux;
    int length = 0;
    for(row = MIN_ROW_COL; row < MAX_ROW - 1; row++)
        for(col = MIN_ROW_COL; col < MAX_COL - 1; col++) // same thing as before
        {
            aux = count_direction(board, row, col, up_or_down , left_or_right, player);
            switch(aux)
            {
            case 1: //this means that there is no diagonal so we don't increment it
                    break;
            case 2: // since the diagonal does exist we increment the length
                    length += aux;
                    break;
            case 3:
                    length += aux -1;   // the -1 is there because it will end up doing case 2 as well when it goes to the next row
                    break;              // the reason why it adds up to 4 and not 3 is because diagonal connections of 3 are way more valuable and I want to represent that
            }
        }
    return length;
}

// this functions checks for how good a player's connectivity is, simple as that
// however, it doesn't count how many pieces are connected, that just sounds painful to code
// instead it counts how many connections it has and their lenghts
// the bigger the player_connectivity is, the higher the chances of all the played pieces being connected are
int get_player_connectivity(int board[MAX_ROW][MAX_COL] , int player)
{
    int row , col;
    int length = 0;
    int aux;
    length += get_horizontal_connectivity(board, player);
    length += get_vertical_connectivity(board, player);
    length += get_diagonal_connectivity(board, player, 1, 1);
    length += get_diagonal_connectivity(board, player, 1, -1);
    return length;
}

//it checks if a the played piece would end up winning the game
int check_win_piece_wise(int board[MAX_ROW][MAX_COL], int row, int col , int player)
{
    // the reason those +1 and -1 are there is because I already know that the starting piece is of a favourable colour
    // this way I won't have to initalise board[row][col] in the other functions
    if (count_direction(board, row, col, 0, 1, player) >= 4) //horizontal connectivity on the right
            return 1;
    if(count_direction(board, row, col, 0, -1, player) >= 4) //horizontal connectivity on the left
            return 1;
    if (count_direction(board, row, col, 1, 0, player) >= 4) //vertical up connectivity
            return 1;
    if (count_direction(board, row , col, -1, 0, player) >= 4) //vertical down connectivity
            return 1;
    if (count_direction(board, row, col, 1, 1, player) >= 4) //diagonal right-up connectivity
            return 1;
    if (count_direction(board, row , col, -1, -1, player) >= 4) //diagonal left-down connectivity
            return 1;
    if (count_direction(board, row , col, 1, -1, player) >= 4) //diagonal left-up connectivity
            return 1;
    if (count_direction(board, row , col, -1, 1, player) >= 4) //diagonal right-down connectivity
            return 1;
    return 0;
}

//it's meant to be used in the evaluate function, that's why it's separate from the one before
// I also check only the top piece since the others should have been checked before so it should help make it faster
int check_win(int board[MAX_ROW][MAX_COL])
{
    int row, col;
    for(col = MIN_ROW_COL; col < MAX_COL; col++)
        for(row = MIN_ROW_COL; row < MAX_ROW; row++)
        {
            if((board[row + 1][col] == 0 && row < MAX_ROW - 1) || (row == MAX_ROW - 1 && board[row][col] == 0))
            {
                if(check_win_piece_wise(board, row, col, 1))
                    return 1;
                if(check_win_piece_wise(board, row, col, 2))
                    return 2;
                break;
            }
        }
    return 0;
}

//this function checks how many pieces are connected in a certain point
int count_ind_connectivity(int board[MAX_ROW][MAX_COL], int row, int col, int player)
{
    int length = 1; //we start with 1 in order to count board[row][col]
    length += count_direction(board, row, col + 1, 0, 1, player); //horizontal connectivity on the right

    length += count_direction(board, row, col - 1, 0, -1, player); //horizontal connectivity on the left

    length += count_direction(board, row + 1, col , 1, 0, player); //vertical up connectivity

    length += count_direction(board, row - 1, col, - 1, 0, player); //vertical down connectivity

    length += count_direction(board, row + 1, col - 1, 1, -1, player); //diagonal left-up connectivity

    length += count_direction(board, row - 1, col + 1, -1, 1, player); //diagonal right-down connectivity

    length += count_direction(board, row + 1, col + 1, 1, 1, player); //diagonal right-up connectivity

    length += count_direction(board, row - 1, col - 1, -1, -1, player); //diagonal left-down connectivity

    return length;
}

int is_move_isolated (int board[MAX_ROW][MAX_COL] , int row, int col, int player)
{
    return count_ind_connectivity(board, row, col, player) == 1;
}

// this function also returns the row it made the move on so you can later undo the move or just utilise it in other functions
int make_move_on_column(int board[MAX_ROW][MAX_COL], int player, int col)
{
    int row;
    for(row = MIN_ROW_COL; row < MAX_ROW; row++)
        if(is_valid_move(board, row, col))
            {
                board[row][col] = player;
                return row;
            }

    return -1; // if it can't make a move then it will return -1 signifing an ERROR
}

// I want to see how many not isolated moves the player can make in order to see just how many options the player has
// I could further develop it by also providing the useful_moves and have the AI check only those, which might make the program run smoother
// keep this one for evaluating the current board
int get_mobility(int board[MAX_ROW][MAX_COL], int player)
{
    int col;
    int useful_moves = 0; // this represents just how many moves aren't isolated
    for(col = MIN_ROW_COL; col < MAX_COL; col++)
        {
            int row;
            row = make_move_on_column(board, player, col); // we check what would happen if this move was made
            if(row != -1)
            {
                if(is_move_isolated(board, row, col, player) == 0) useful_moves++;
                board[row][col] = 0; // we go back to before
            }
        }

    return useful_moves;
}

#define SCORE_OF_TWO_CONNECTIONS 12
#define SCORE_OF_THREE_CONNECTIONS 17
#define SCORE_OF_FOUR_CONNECTIONS 26
// two or more different connections of three sharing a piece is obviously very good as it could lead to cornering the opponent
float get_score_of_connected_triple_connections(int board[MAX_ROW][MAX_COL], int player)
{
    int row, col;
    float score = 0;
    int number_of_three_connections;
    for(col = MIN_ROW_COL; col < MAX_COL; col++)
        for(row = MIN_ROW_COL; row < MAX_ROW; row++)
        {
            if(board[row][col] == 0) break;
            number_of_three_connections = 0;

            //it starts checking all the directions to see how cnnected it is

            if(count_direction(board, row, col, 1, 1, player) == 3) number_of_three_connections++; // right diagonal

            if(count_direction(board, row, col, 1, -1, player) == 3) number_of_three_connections++; // left diagonal

            if(count_direction(board, row, col, 0, 1, player) == 3) number_of_three_connections++; // horizontal

            if(count_direction(board, row, col, 1, 0, player) == 3) number_of_three_connections++; // vertical

            //and now it assigns the score depending of the number of triple connections
            switch (number_of_three_connections)
            {
            case 2:
                score += SCORE_OF_TWO_CONNECTIONS;
                break;
            case 3:
                score += SCORE_OF_THREE_CONNECTIONS;
                break;
             case 4:
                score += SCORE_OF_FOUR_CONNECTIONS;
                break;
            }
        }

    return score;
}

// in case you want to change the values that help with the scoring of the next function, just change any of these and it should be fine
// it also makes it easier to assign greater importance, you know?
float score_divider (int value)
{
    switch(value)
    {
        case 1:
            return 1; // I'm too lazy to declare other variables for these things, just change the values directly
        case 2:
            return 2;
        case 3:
            return 3;
        case 4:
            return 4;
        case 5:
            return 5;
        case 6:
            return 6;
    }
}

#define IGNORE_COLUMN_VALUE 50
// it's supposed to help the AI not make a stupid move since sometimes you can win if the opponent were to make an obviously bad move
// if it were to make the move it should be picked up by the MINIMAX algorithm and score it lower then other moves, so hopefully the AI won't make it
float ignore_column (int board[MAX_ROW][MAX_COL], int player)
{
    int row, col;
    float score = 0;
    for(col = MIN_ROW_COL; col < MAX_COL; col++)
    {
        int row;
        row = make_move_on_column(board, player, col);
        if(row != -1) // if it made a move then it will continue with this + I don't like continue so I am doing this
        {
            for(int next_rows = row; next_rows < MAX_ROW; next_rows++) //it checks the next rows to see just how many moves there need to be made in order to win
                if(check_win_piece_wise(board, next_rows, col, player))
                    score += IGNORE_COLUMN_VALUE/score_divider(next_rows - row + 1); //less moves to reach the victory, the higher the score
            board[row][col] = 0;
        }
    }

    return score;
}

//center control, a simple but important aspect of the game, I guess. There really isn't anything special about this function
float get_center_control( int board[MAX_ROW][MAX_COL], int player)
{
    float score = 0;
    int row , col;

    for(col = MIN_ROW_COL + 2; col < MAX_COL - 1; col++)
        for(row = MIN_ROW_COL; row < MAX_ROW; row++)
            if(board[row][col] == player) score++;
            else if(board[row][col] == 0) break;

    return score;
}

// edge control is also pretty useful for obvious reasons, it simply counts how many pieces the player has placed there, it's a decent indicator
float get_edge_control(int board[MAX_ROW][MAX_COL], int player)
{
    float score = 0;
    int row, col;

    for(col = MIN_ROW_COL; col < MIN_ROW_COL + 2; col++)
        for(row = MIN_ROW_COL; row < MAX_ROW; row++)
            if(board[row][col] == player) score++;
            else if(board[row][col] == 0) break;

    for(col = MAX_COL - 1; col > MAX_COL - 3; col--)
        for(row = MIN_ROW_COL; row < MAX_ROW; row++)
            if(board[row][col] == player) score++;
            else if(board[row][col] == 0) break;

    return score;
}

#define CONNECTIVITY_MULTIPLIER 10
#define MOBILITY_MULTIPLIER 5
#define CENTER_CONTROL_MULTIPLIER 7
#define CONNECTED_TRIPLE_CONNECTIONS_MULTIPLIER 10
#define EDGE_CONTROL_MULTIPLIER 4

//the evaluation function, it uses all the functions before it to determine the score of the position, pretty simple to understand
float evaluate_board(int board[MAX_ROW][MAX_COL])
{
    int opponent = 3 - ai_player;

    int winner;
    winner = check_win(board);

    if(winner == ai_player)
        return 10000;

    if(winner == opponent)
        return -10000;

    float score = 0;

    float player_connectivity;
    float opponent_connectivity;

    player_connectivity = get_player_connectivity(board, ai_player);
    opponent_connectivity = get_player_connectivity(board, opponent);

    score += (player_connectivity - opponent_connectivity) * CONNECTIVITY_MULTIPLIER;

    float player_mobility;
    float opponent_mobility;
    player_mobility = get_mobility(board, ai_player);
    opponent_mobility = get_mobility(board, opponent);

    score += (player_mobility - opponent_mobility) * MOBILITY_MULTIPLIER;

    float player_connected_triple_connections;
    float opponent_connected_triple_connections;
    player_connected_triple_connections = get_score_of_connected_triple_connections(board, ai_player);
    opponent_connected_triple_connections = get_score_of_connected_triple_connections(board, opponent);

    score += (player_connected_triple_connections - opponent_connected_triple_connections) * CONNECTED_TRIPLE_CONNECTIONS_MULTIPLIER;

    float player_ignore_column;
    float opponent_ignore_column;
    player_ignore_column = ignore_column(board, ai_player);
    opponent_ignore_column = ignore_column(board, opponent);

    score += (player_ignore_column - opponent_ignore_column); //has its own multiplier and way of scoring

    float player_center_control;
    float opponent_center_control;
    player_center_control = get_center_control(board, ai_player);
    opponent_center_control = get_center_control(board, opponent);

    score += (player_center_control - opponent_center_control) * CENTER_CONTROL_MULTIPLIER;

    float player_edge_control;
    float opponent_edge_control;
    player_edge_control = get_edge_control(board, ai_player);
    opponent_edge_control = get_edge_control(board, opponent);

    score += (player_edge_control - opponent_edge_control) * EDGE_CONTROL_MULTIPLIER;

    return score;
}

//the minimax algorithm, it could have been better, I could have also used a negamax instead but I found out about it after I was almost done with this one so I decided not to implement the negamax variant
//it also is combined with alpha-beta prunning to make  it a bit better
int minimax(int board[MAX_ROW][MAX_COL], int depth, int maximizing_player, int alpha, int beta)
{
    if(depth == 0)
        return evaluate_board(board);

    if(check_win(board))
        return evaluate_board(board);

    if(maximizing_player)
    {
        int max_eval = INT_MIN;
        for(int col = MIN_ROW_COL + 2; col < MAX_COL - 2; col++) // I am first checking the middle since it's more likely for the best move to be here and combined with alpha beta prunning and it helps a bit with the speed
            {
                int eval, row;
                row = make_move_on_column(board, ai_player, col); //checking this move

                if(row == -1) continue; // if it can't make a move on this column then it can't be checked and I know what I said, however here it just makes it more readable
                eval = minimax(board, depth - 1, 0, alpha, beta);

                board[row][col] = 0; // undoing the move

                if(max_eval < eval) max_eval = eval;
                if(alpha < eval) alpha = eval; // the whole alpha beta spiel

                if(alpha <= beta) break;
            }

        for(int col = MIN_ROW_COL; col < MIN_ROW_COL + 2; col++) // I am now checking the edges since they might be what I am looking for
            {
                int eval, row;
                row = make_move_on_column(board, ai_player, col); //checking this move

                if(row == -1) continue; // if it can't make a move on this column then it can't be checked and I know what I said, however here it just makes it more readable

                eval = minimax(board, depth - 1, 0, alpha, beta); // now to evaluate the position by checking the next positions

                board[row][col] = 0; // undoing the move

                if(max_eval < eval) max_eval = eval;
                if(alpha < eval) alpha = eval; // the whole alpha beta spiel

                if(alpha <= beta) break;
            }

        for(int col = MAX_COL - 2; col < MAX_COL; col++) // the other edge
            {
                int eval, row;
                row = make_move_on_column(board, ai_player, col); //checking this move

                if(row == -1) continue; // if it can't make a move on this column then it can't be checked and I know what I said, however here it just makes it more readable

                eval = minimax(board, depth - 1, 0, alpha, beta);

                board[row][col] = 0; // undoing the move

                if(max_eval < eval) max_eval = eval;
                if(alpha < eval) alpha = eval; // the whole alpha beta spiel

                if(alpha <= beta) break;
            }
        return max_eval;
    }

    else // Minimizer's turn
    {
        int min_eval = INT_MAX;
        for(int col = MIN_ROW_COL + 2; col < MAX_COL - 2; col++) //the center usually contains the best moves
            {
                int eval, row;
                row = make_move_on_column(board, 3 - ai_player, col);
                if(row == -1) continue;

                eval = minimax(board, depth - 1, 1, alpha, beta);

                board[row][col] = 0; //undoing the move

                if(min_eval > eval) min_eval = eval;
                if(beta > eval) beta = eval;

                if(beta <= alpha) break;
            }

        for(int col = MIN_ROW_COL; col < MIN_ROW_COL + 2; col++) //now I'm checking the left edge
            {
                int eval, row;
                row = make_move_on_column(board, 3 - ai_player, col);
                if(row == -1) continue;

                eval = minimax(board, depth - 1, 1, alpha, beta);

                board[row][col] = 0; // undoing the move

                if(min_eval > eval) min_eval = eval;
                if(beta > eval) beta = eval;

                if(beta <= alpha) break;
            }

        for(int col = MAX_COL - 2; col < MAX_COL; col++) //and now I'm checking the right edge
            {
                int eval, row;
                row = make_move_on_column(board, 3 - ai_player, col);
                if(row == -1) continue;

                eval = minimax(board, depth - 1, 1, alpha, beta);

                board[row][col] = 0; //undoing the move

                if(min_eval > eval) min_eval = eval;
                if(beta > eval) beta = eval;

                if(beta <= alpha) break;
            }
        return min_eval;
    }
}

// the first part of the minimax algorithm, why is it separate? good question, guess I was too tired to think about it originally,
// but I am not willing to risk breaking the algorithm again
int get_best_move(int board[MAX_ROW][MAX_COL], int depth)
{
    int best_move = 0;
    int max_eval = INT_MIN;

    for(int col = MIN_ROW_COL; col < MAX_COL; col++)
        {
            int row;
            row = make_move_on_column(board, ai_player, col);
            if(row == -1) continue;

            int eval;
            eval = minimax(board, depth - 1, 0, INT_MIN, INT_MAX);

            board[row][col] = 0; //undoing the move

            if(eval > max_eval)
            {
                max_eval = eval;
                best_move = col;
            }
        }
    return best_move;
}

int random_number_generator()
{
    srand(time(0));
    return (rand() % 10) / 3; // it will take only the last digit and return 0, 1 or 2 but sometimes 3
}

#define DEPTH_LIMIT 7
int main(int argc, char **argv)
{
    int ais_first_two_moves = 2; //it checks to see if it's the ai's first two moves, it's more fun this way and the AI also works a bit better ( maybe ), I just wanted to do it in all fairness
    int board[MAX_ROW][MAX_COL] = {};
    printf("Please choose who you want to play as: \nPlayer 1 or Player 2\n");
    int player;
    scanf("%d", &player);
    ai_player = 3 - player;
    printf("You've chosen Player %d", player);

    int turn = 1;
    int is_it_players_turn;
    if(player == 1) is_it_players_turn = 1;
    else is_it_players_turn = 0;
    int winner = 0;

    wb_robot_init(); //starting the robot
    while(turn < 42)
    {
        printf("\nTurn %d", turn);
        if(is_it_players_turn)
        {
            printf("\nIt's your turn");

            int did_it_make_a_move = 0;
            while(did_it_make_a_move == 0) // this is here just in case the player inputs an incorrect move
            {
                printf("\nPlease make your move: ");
                int move_made;
                scanf("%d", &move_made);
                move_made--;
                int row;

                row = make_move_on_column(board, player, move_made);
                if(row == -1)
                    printf("\nPlease make a valid move");
                else did_it_make_a_move = 1; //could be more elegant but this won't be in the robot, just a test version
                move_to_column(move_made);
            }
        }

        else
        {
            int best_move;
            if(ais_first_two_moves)
            {
                best_move = 2;
                best_move += random_number_generator(); //yep, random number generation to spice things up a bit for the first two moves so the AI isn't completely boring
                ais_first_two_moves--;
                if(best_move == 5) best_move--; // random_number_generator can also return 3 and I don't want that so I am getting rid of that possibility like so. It could be more elegant but eh, it's not that big of a deal
            }
            else best_move = get_best_move(board, DEPTH_LIMIT);
            make_move_on_column(board, ai_player, best_move);
            move_to_column(best_move);
        }

        if(is_it_players_turn == 1) is_it_players_turn = 0;
        else is_it_players_turn = 1;

        winner = check_win(board);

        if(winner == 1)
        {
            printf("\nPlayer 1 has won!");
            break;
        }

        else if(winner == 2)
        {
            printf("\nPlayer 2 has won!");
            break;
        }

        turn++;
    }
    if(winner == 0)
        printf("Draw");
    wb_robot_cleanup();
    return 0;
}
