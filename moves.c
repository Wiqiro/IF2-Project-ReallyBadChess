#include <game.h>


bool CollisionTest(square** board, int size, int startx, int starty, int targx, int targy) {
    //printf("dgfkqsdgf");
    int movex = targx-startx;
    int movey = targy-starty;
    int dx, dy;

    if (movex == 0) {
        dx = 0;
    } else {
        dx = movex/abs(movex);
    }
    if (movey == 0) {
        dy = 0;
    } else {
        dy = movey/abs(movey);
    }
    //printf("%d  %d\n\n\n", dx, dy);

    int i=0;
        while (i+1 < fmax(abs(movex),abs(movey)) && board[startx+dx*(i+1)][starty+dy*(i+1)].type == empty) {
        i++;
        //printf("%d  %d\n",startx+dx*(i+1), starty+dy*(i+1));
        //getchar();

    }
    if (i == fmax(abs(movex),abs(movey))-1) {
        return true; //returns true if the way is free (if there is only empty squares in the path of the bishop)
    } else {
        return false;
    }
}


/**
 * @brief Test if a move is possible by appending a MoveTest function depending on the type of the piece
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is possible
 * @return false if the move is not possible
 */
bool MoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
    
    switch (board[startx][starty].type) {
    case pawn:
        return PawnMoveTest(board, size, startx, starty, targx, targy);
        break;
    case bishop:
        return BishopMoveTest(board, size, startx, starty, targx, targy);
        break;
    case knight:
        return KnightMoveTest(board, size, startx, starty, targx, targy);
        break;
    case rook:
        return RookMoveTest(board, size, startx, starty, targx, targy);
        break;
    case queen:
        return QueenMoveTest(board, size, startx, starty, targx, targy);
        break;
    case king:
        return KingMoveTest(board, size, startx, starty, targx, targy);
        break;
    
    default:
        return false;
        break;
    }
}

/**
 * @brief Test if the move of a specified pawn is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool PawnMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {

    int movex = targx-startx;
    int movey = targy-starty;

    if ((board[startx][starty].color == black && movey == 1) || (board[startx][starty].color == white && movey == -1)) {
        if (movex == 0 && board[targx][targy].type == empty) {
            return true;
        } else if (abs(movex) == 1 && board[targx][targy].type != empty) {
            return true;
        }

    } else if (movex == 0 && ((board[startx][starty].color == black && targy == 3) || (board[startx][starty].color == white && targy == size-4))) {
        return true;
    }

    return false;
}


/**
 * @brief Test if the move of a specified bishop is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed 
 */
bool BishopMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {

    if (abs(targx-startx) == abs(targy-starty)) {
        return CollisionTest(board, size, startx, starty, targx, targy);
    } else {
        return false;
    }
}


/**
 * @brief Test if the move of a specified knight is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool KnightMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
    int movex = targx-startx;
    int movey = targy-starty;

    if ((abs(movex) == 2 && abs(movey) == 1) || (abs(movex) == 1 && abs(movey) == 2)) {
        return true;
    } else {
        return false;
    }
}


/**
 * @brief Test if the move of a specified rook is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool RookMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {

    if (targx-startx == 0 || targy-starty == 0) {
        return CollisionTest(board, size, startx, starty, targx, targy);
    } else {
        return false;
    }
}


/**
 * @brief Test if the move of a specified queen is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool QueenMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {

    if (abs(targx-startx) == abs(targy-starty) || targx-startx == 0 || targy-starty == 0) {
        return CollisionTest(board, size, startx, starty, targx, targy);
    } else {
        return false;
    }
}


/**
 * @brief Test if the king move is possible --> has to check if the targetted move would result in a Check
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startx The starting column of the piece
 * @param starty The starting row of the piece
 * @param targx The targetted column of move
 * @param targy The targetted row of move
 * @return true if the move is possible
 * @return false if the move is not possible
 */
bool KingMoveTest(square** board, int size, int startx, int starty, int targx, int targy) {
    int movex = targx-startx;
    int movey = targy-starty;

    if (abs(movex) > 1 || abs(movey) > 1) {
        return false;
    } else {
        return true;
    }
}


/**
 * @brief Test if the king is in a Check position --> has to scan the entire board to determine if a piece can capture the king
 * 
 * @param board 
 * @param size 
 * @param kingposx 
 * @param kingposy 
 * @return true Check 
 * @return false no Check
 */
bool CheckTest(square** board, int size, int pieceposx, int pieceposy, color piececolor) {
    bool check = false;
    int x = 0;
    int y = 0;
    while (y < size && check == false) {
        x = 0;
        while (x < size && check == false) {
            if (board[x][y].type != empty && board[x][y].type != king && (board[x][y].color != piececolor)) {
                check = MoveTest(board, size, x, y, pieceposx, pieceposy);
                //printf("\nTesté  %d  %d", x, y);
            } else {
               //printf("\nNon testé  %d  %d", x, y);
            }
            //printf("       %d %d  Résultat: %d   ", board[x][y].color, piececolor, check);
            x++;
        }
    y++;
    }
    return check;
}

bool RescueTest(square** board, int size, int startx, int starty, int kingposx, int kingposy) {

    int movex = kingposx-startx;
    int movey = kingposy-starty;
    int dx, dy;
    color kingcolor = board[kingposx][kingposy].color;

    if (movex == 0) {
        dx = 0;
    } else {
        dx = movex/abs(movex);
    }
    if (movey == 0) {
        dy = 0;
    } else {
        dy = movey/abs(movey);
    }

    int i=0;
    bool rescue = false;
    while (i < (int)fmax(abs(movex),abs(movey)) && (rescue = CheckTest(board, size, startx+(dx*i), starty+(dy*i), !kingcolor)) == false) {
        i++;
    }
    return rescue;
}



/**
 * @brief Test if the king is in a Checkmate position
 * 
 * @param board 
 * @param size 
 * @param kingposx 
 * @param kingposy 
 * @return true Checkmate position
 * @return false no Checkmate position
 */
bool CheckMateTest(square** board, int size, int kingposx, int kingposy) {
    bool checkmate = true;
    int x = kingposx-1;
    int y = kingposy-1;
    color kingcolor = board[kingposx][kingposy].color;

    while (x <= kingposx+1 && checkmate == true) {
        y = kingposy-1;
        while (y <= kingposy+1 && checkmate == true) {
            if (x >= 0 && x < size && y >= 0 && y < size) {
                
                if (board[x][y].color != kingcolor || board[x][y].type == empty) {
                    checkmate = CheckTest(board, size, x, y, kingcolor);
                    //printf("Test de l'échec en %d  %d (couleur %d): %d\n", x, y, kingcolor, checkmate);
                }
            }
            y++;
        }
        x++;
    }
    //printf("\n\nPremiere phase de test de l'echec et mat passée: %d\n\n", checkmate);
    if (checkmate == true) {
        for (y = 0; y < size; y++) {
            for (x = 0; x < size; x++) {
                if (board[x][y].type != empty && board[x][y].color != kingcolor && MoveTest(board, size, x, y, kingposx, kingposy) == true) {

                    if (board[x][y].type == bishop || board[x][y].type == rook || board[x][y].type == queen) {
                        checkmate = !RescueTest(board, size, x, y, kingposx, kingposy);
                        //printf("Test mise en échec par grosse pièce en %d  %d:  %d\n",x, y, checkmate);
                    } else {
                        checkmate = CheckTest(board, size, x, y, !kingcolor);
                        //printf("Test mise en échec par une pièce de merde; %d\n", checkmate);
                    }
                }
            }
        }
    }
    return checkmate;
}

/**
 * @brief Execute a move (no legit move verification : has to be checked before)
 * 
 * @param board 
 * @param size 
 * @param startx 
 * @param starty 
 * @param targx 
 * @param targy 
 */
void MoveExecute(square** board, int size, int startx, int starty, int targx, int targy) {
    board[targx][targy] = board[startx][starty];
    board[startx][starty].type = empty;
}