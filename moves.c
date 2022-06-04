#include <game.h>


bool CollisionTest(square** board, int size, coords startpos, coords targpos) {
    //printf("dgfkqsdgf");
    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;
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

    int i=0;
        while (i+1 < fmax(abs(movex),abs(movey)) && board[startpos.x+dx*(i+1)][startpos.y+dy*(i+1)].type == empty) {
        i++;
        //printf("%d  %d\n",startpos.x+dx*(i+1), startpos.y+dy*(i+1));
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
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true  if the move is possible
 * @return false if the move is not possible
 */
bool MoveTest(square** board, int size, coords startpos, coords targpos) {
    
    switch (board[startpos.x][startpos.y].type) {
    case pawn:
        return PawnMoveTest(board, size, startpos, targpos);
        break;
    case bishop:
        return BishopMoveTest(board, size, startpos, targpos);
        break;
    case knight:
        return KnightMoveTest(board, size, startpos, targpos);
        break;
    case rook:
        return RookMoveTest(board, size, startpos, targpos);
        break;
    case queen:
        return QueenMoveTest(board, size, startpos, targpos);
        break;
    case king:
        return KingMoveTest(board, size, startpos, targpos);
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
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool PawnMoveTest(square** board, int size, coords startpos, coords targpos) {

    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;

    if ((board[startpos.x][startpos.y].color == black && movey == 1) || (board[startpos.x][startpos.y].color == white && movey == -1)) {
        if (movex == 0 && board[targpos.x][targpos.y].type == empty) {
            return true;
        } else if (abs(movex) == 1 && board[targpos.x][targpos.y].type != empty) {
            return true;
        }

    } else if (movex == 0 && ((board[startpos.x][startpos.y].color == black && targpos.y == 3) || (board[startpos.x][startpos.y].color == white && targpos.y == size-4))) {
        return true;
    }

    return false;
}


/**
 * @brief Test if the move of a specified bishop is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed 
 */
bool BishopMoveTest(square** board, int size, coords startpos, coords targpos) {

    if (abs(targpos.x-startpos.x) == abs(targpos.y-startpos.y)) {
        return CollisionTest(board, size, startpos, targpos);
    } else {
        return false;
    }
}


/**
 * @brief Test if the move of a specified knight is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool KnightMoveTest(square** board, int size, coords startpos, coords targpos) {
    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;

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
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool RookMoveTest(square** board, int size, coords startpos, coords targpos) {

    if (targpos.x-startpos.x == 0 || targpos.y-startpos.y == 0) {
        return CollisionTest(board, size, startpos, targpos);
    } else {
        return false;
    }
}


/**
 * @brief Test if the move of a specified queen is possible
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true  if the move is allowed
 * @return false if the move is not allowed
 */
bool QueenMoveTest(square** board, int size, coords startpos, coords targpos) {

    if (abs(targpos.x-startpos.x) == abs(targpos.y-startpos.y) || targpos.x-startpos.x == 0 || targpos.y-startpos.y == 0) {
        return CollisionTest(board, size, startpos, targpos);
    } else {
        return false;
    }
}


/**
 * @brief Test if the king move is possible --> has to check if the targetted move would result in a Check
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param startpos.x The starting column of the piece
 * @param startpos.y The starting row of the piece
 * @param targpos.x The targetted column of move
 * @param targpos.y The targetted row of move
 * @return true if the move is possible
 * @return false if the move is not possible
 */
bool KingMoveTest(square** board, int size, coords startpos, coords targpos) {
    int movex = targpos.x-startpos.x;
    int movey = targpos.y-startpos.y;

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
bool CheckTest(square** board, int size, coords piecepos, color piececolor) {
    bool check = false;
    coords testpos;
    testpos.y = 0;
    while (testpos.y < size && check == false) {
        testpos.x = 0;
        while (testpos.x < size && check == false) {
            if (board[testpos.x][testpos.y].type != empty && board[testpos.x][testpos.y].type != king && (board[testpos.x][testpos.y].color != piececolor)) {
                check = MoveTest(board, size, testpos, piecepos);
                //printf("\nTesté  %d  %d", testpos.x, testpos.y);
            } else {
                //printf("\nNon testé  %d  %d", testpos.x, testpos.y);
            }
            //printf("       %d %d  Résultat: %d   ", board[testpos.x][testpos.y].color, piececolor, check);
            testpos.x++;
        }
    testpos.y++;
    }
    return check;
}

bool RescueTest(square** board, int size, coords startpos,  coords kingpos) {

    color kingcolor = board[kingpos.x][kingpos.y].color;
    int movex = kingpos.x-startpos.x;
    int movey = kingpos.y-startpos.y;
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

    int i=0;
    bool rescue = false;
    coords testcoords = startpos;
    
    while (i < (int)fmax(abs(movex),abs(movey)) && (rescue = CheckTest(board, size, testcoords, !kingcolor)) == false) {
        testcoords.x += dx;
        testcoords.y += dy;
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
bool CheckMateTest(square** board, int size, coords kingpos) {
    bool checkmate = true;
    coords testcoords;
    testcoords.x = kingpos.x-1;

    color kingcolor = board[kingpos.x][kingpos.y].color;

    while (testcoords.x <= kingpos.x+1 && checkmate == true) {
        testcoords.y = kingpos.y-1;
        while (testcoords.y <= kingpos.y+1 && checkmate == true) {
            if (testcoords.x >= 0 && testcoords.x < size && testcoords.y >= 0 && testcoords.y < size) {
                
                if (board[testcoords.x][testcoords.y].color != kingcolor || board[testcoords.x][testcoords.y].type == empty) {
                    checkmate = CheckTest(board, size, testcoords, kingcolor);
                    //printf("Test de l'échec en %d  %d (couleur %d): %d\n", testcoords.x, testcoords.y, kingcolor, checkmate);
                }
            }
            testcoords.y++;
        }
        testcoords.x++;
    }
    //printf("\n\nPremiere phase de test de l'echec et mat passée: %d\n\n", checkmate);
    if (checkmate == true) {
        for (testcoords.y = 0; testcoords.y < size; testcoords.y++) {
            for (testcoords.x = 0; testcoords.x < size; testcoords.x++) {
                if (board[testcoords.x][testcoords.y].type != empty && board[testcoords.x][testcoords.y].color != kingcolor && MoveTest(board, size, testcoords, kingpos) == true) {

                    if (board[testcoords.x][testcoords.y].type == bishop || board[testcoords.x][testcoords.y].type == rook || board[testcoords.x][testcoords.y].type == queen) {
                        checkmate = !RescueTest(board, size, testcoords, kingpos);
                        //printf("Test mise en échec par grosse pièce en %d  %d:  %d\n",testcoords.x, testcoords.y, checkmate);
                    } else {
                        checkmate = !CheckTest(board, size, testcoords, !kingcolor);
                        //printf("Test mise en échec par petite pièce en %d  %d:  %d\n",testcoords.x, testcoords.y, checkmate);
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
 * @param startpos.x 
 * @param startpos.y 
 * @param targpos.x 
 * @param targpos.y 
 */
void MoveExecute(square** board, int size, coords startpos, coords targpos) {
    board[targpos.x][targpos.y] = board[startpos.x][startpos.y];
    board[startpos.x][startpos.y].type = empty;
}

bool CheckTestAfterMove(square** board, int size, coords startpos, coords targpos, coords kingpos, color kingcolor) {

    square startpiece = board[startpos.x][startpos.y];
    square targpiece = board[targpos.x][targpos.y];
    MoveExecute(board, size, startpos, targpos);
    bool check = CheckTest(board, size, kingpos, kingcolor);

    board[startpos.x][startpos.y] = startpiece;
    board[targpos.x][targpos.y] = targpiece;

    return check;
}