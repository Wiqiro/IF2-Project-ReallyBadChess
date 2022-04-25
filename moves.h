#ifndef _MOVES_HEADER_
#define _MOVES_HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <moves.h>


bool Move(case** board, int size, int startx, int starty, int targx, int targy); //envoie vers le mouvcheck 

bool PawnMove(case** board, int size, int startx, int starty, int targx, int targy);

bool BishopMove(case** board, int size, int startx, int starty, int targx, int targy);

bool KnightMove(case** board, int size, int startx, int starty, int targx, int targy);

bool RookMove(case** board, int size, int startx, int starty, int targx, int targy);

bool QueenMove(case** board, int size, int startx, int starty, int targx, int targy);

bool KingMove(case** board, int size, int startx, int starty, int targx, int targy); // séparer toute les fonctions en fonction check et executer le mouv. 
//kingmove scan all the board
// make 14 bool
// 






#endif


