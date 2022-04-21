#include "game_core.h"
#include "Arduino.h"
#include "config.h"
#include "led_board.h"
#include "user_console.h"
#include <avr/sleep.h>

#define MAX_IDLE_TIME 10000
#define TIME_IN_GAME_OVER 2000
#define INITIAL_MAX_TIME_BALL_IN_POS 200
#define INITIAL_MAX_MOVING_DURATION 4000
#define INITIAL_MAX_WAITING_TIME 5000

/* current position of the ball */
int ball_position;

/* direction */
int ball_move_step = 1;

/* when the ball entered in the new pos */
long new_pos_time;

/* how long the ball can stay in a pos */
long current_max_time_ball_in_pos;

/* how long moving last */
int current_moving_duration;

/* how long we wait for the player to move */
long current_max_waiting;

/* difficulty level */
int difficulty_level;

/* difficulty scaling factor */
double difficulty_scaling_factor = 1;

/* the score */
long score = 0;

/* current game state */
int game_state;

/* time in which the game entered in the game state */
long entered_state_time;

/* how long it the game is in current state */
long current_time_in_state;

/* =========== procedures about the ball ======== */

void reset_ball_pos(){
  ball_position = 0;
  new_pos_time = millis();
  current_max_time_ball_in_pos = INITIAL_MAX_TIME_BALL_IN_POS;
  switch_on_led(ball_position);
}

void move_ball(){
  long current_t = millis();
  if (current_t - new_pos_time > current_max_time_ball_in_pos) {   
    new_pos_time = current_t;
    switch_off_led(ball_position);
    ball_position += ball_move_step;
    if (ball_position > LAST_POS) {
      ball_move_step = -1;
      ball_position = LAST_POS - 1;
    } else if (ball_position < 0) {
      ball_move_step = 1;
      ball_position = 1;
    }
  } 
  switch_on_led(ball_position);
}

/* =========== procedures about game state ======== */

void change_game_state(int new_state){
  game_state = new_state;
  entered_state_time = millis();
}

void update_game_state_time(){
  current_time_in_state = millis() - entered_state_time;
}

void check_difficulty_level(){
  int new_difficulty_level = read_difficulty_level();
  if (new_difficulty_level != difficulty_level){
    difficulty_level = new_difficulty_level;
    print_on_console(String("New difficulty Level: ") + difficulty_level);  
  } 
}

void game_intro(){
  reset_led_board();   
  print_on_console("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start");
  reset_pulsing();
  change_game_state(GAME_WAIT_TO_START);
}

void game_wait_to_start(){
  if (current_time_in_state < MAX_IDLE_TIME){
    go_on_pulsing();
    check_difficulty_level();
    if (player_input_started()){
      change_game_state(GAME_INIT);
    }
  } else {
    change_game_state(GAME_SLEEP);
  }
}

void game_sleep(){
  // log("Going to sleep..");
  reset_pulsing();
  delay(500);
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
  sleep_enable();
  sleep_mode();  
  sleep_disable();   
  change_game_state(GAME_INTRO);
}

void game_init(){
  reset_pulsing();

  difficulty_level = read_difficulty_level();
  difficulty_scaling_factor = 1.0 + difficulty_level*0.1;
  //log(String("Scaling F: ") + difficulty_scaling_factor);
  
  score = 0;
  reset_ball_pos();
  current_moving_duration = random(INITIAL_MAX_MOVING_DURATION, INITIAL_MAX_MOVING_DURATION + 1000);
  current_max_waiting = INITIAL_MAX_WAITING_TIME;
  change_game_state(GAME_LOOP_MOVING);
  print_on_console("Go!");  
}

void game_loop_moving(){
  if (current_time_in_state < current_moving_duration){
    move_ball();
  } else {
    reset_player_input();
    change_game_state(GAME_LOOP_WAITING_PLAYER_CHOICE);
  }
}

void change_to_game_over(){
  print_on_console(String("Game Over - Final Score: ") + score);  
  change_game_state(GAME_OVER);
}

void game_loop_wait_player_choice(){  
  if (current_time_in_state < current_max_waiting){
     int index = get_button_pressed_index();
     if (index != NO_SELECTION){
        if (index == ball_position){
          score++;
          print_on_console(String("New point! Score: ") + score);
          current_max_waiting /= difficulty_scaling_factor;
          
          long updated_moving_duration = current_moving_duration / difficulty_scaling_factor;          
          current_moving_duration = random(updated_moving_duration, updated_moving_duration + 1000);

          current_max_time_ball_in_pos /= difficulty_scaling_factor;
          change_game_state(GAME_LOOP_MOVING);
        } else {
          change_to_game_over();
        }
     }
  } else {
    change_to_game_over();
  }
}

void game_over(){
  if (current_time_in_state > TIME_IN_GAME_OVER){
     change_game_state(GAME_INTRO);
  }
}

/* =========== procedures about tests ======== */

void game_test(){
  test_led_board();
  test_player_input();
}
