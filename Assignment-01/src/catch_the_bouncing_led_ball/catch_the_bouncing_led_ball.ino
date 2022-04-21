/*
 * ESIOT a.y. 2021/2022
 *
 * ASSIGNMENT #1 - CATCH THE BOUNCING LED BALL 
 * 
 * Author: A. Ricci
 * 
 */
#include "config.h"
#include "game_core.h"
#include "user_console.h" 
#include "led_board.h"

void setup() {
  init_player_console();
  init_led_board();
  change_game_state(GAME_INTRO);
}

void loop(){ 
  update_game_state_time();
  
  switch (game_state) { 
  case GAME_INTRO:
    game_intro();
    break;
  case GAME_WAIT_TO_START:
    game_wait_to_start();
    break;
  case GAME_INIT:
    game_init();
    break;
  case GAME_LOOP_MOVING:
    game_loop_moving();
    break;
  case GAME_LOOP_WAITING_PLAYER_CHOICE:
    game_loop_wait_player_choice();
    break;
  case GAME_OVER:
    game_over();
    break;
  case GAME_SLEEP:
    game_sleep();
    break;
  case GAME_TEST:
    game_test();
    break;
  }
}
