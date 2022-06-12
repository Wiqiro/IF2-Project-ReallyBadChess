#include <game.h>

/**
 * @brief Test if there is a a piece between two positions in the board (only for straight or diagonal moves)
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the way is free
 * @return false if there is an obstacle
 */
bool collisionTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;
    int dx, dy;

    if (move_x == 0) {
        dx = 0;
    } else { 
        dx = move_x/abs(move_x);
    }

    if (move_y == 0) {
        dy = 0;
    } else {
        dy = move_y/abs(move_y);
    }

    int i=0;
        while (i+1 < fmax(abs(move_x),abs(move_y)) && board[start_pos.x+dx*(i+1)][start_pos.y+dy*(i+1)].type == empty) {
        i++;
    }
    if (i == fmax(abs(move_x),abs(move_y))-1) {
        return true; //returns true if the way is free (if there is only empty squares in the path of the bishop)
    } else {
        return false;
    }
}

/**
 * @brief Test if a move is allowed by calling the appropriate function corresponding to the type od the piece
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool moveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    switch (board[start_pos.x][start_pos.y].type) {
    case pawn:
        return pawnMoveTest(board, size, start_pos, targ_pos);
        break;
    case bishop:
        return bishopMoveTest(board, size, start_pos, targ_pos);
        break;
    case knight:
        return knightMoveTest(board, size, start_pos, targ_pos);
        break;
    case rook:
        return rookMoveTest(board, size, start_pos, targ_pos);
        break;
    case queen:
        return queenMoveTest(board, size, start_pos, targ_pos);
        break;
    case king:
        return kingMoveTest(board, size, start_pos, targ_pos);
        break;
    
    default:
        return false;
        break;
    }
}

/**
 * @brief Test if the specified move is allowed for a pawn
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool pawnMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;

    if ((board[start_pos.x][start_pos.y].color == black && move_y == 1) || (board[start_pos.x][start_pos.y].color == white && move_y == -1)) {
        if (move_x == 0 && board[targ_pos.x][targ_pos.y].type == empty) {
            return true;
        } else if (abs(move_x) == 1 && board[targ_pos.x][targ_pos.y].type != empty) {
            return true;
        }

    } else if (move_x == 0 && ((board[start_pos.x][start_pos.y].color == black && targ_pos.y == 3) || (board[start_pos.x][start_pos.y].color == white && targ_pos.y == size-4))) {
        return true;
    }

    return false;
}

/**
 * @brief Test if the specified move is allowed for a bishop by calling the collisionTest function
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool bishopMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    if (abs(targ_pos.x-start_pos.x) == abs(targ_pos.y-start_pos.y)) {
        return collisionTest(board, size, start_pos, targ_pos);
    } else {
        return false;
    }
}

/**
 * @brief Test if the specified move is allowed for a knight
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool knightMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {
    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;

    if ((abs(move_x) == 2 && abs(move_y) == 1) || (abs(move_x) == 1 && abs(move_y) == 2)) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Test if the specified move is allowed for a rook by calling the collisionTest function
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool rookMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    if (targ_pos.x-start_pos.x == 0 || targ_pos.y-start_pos.y == 0) {
        return collisionTest(board, size, start_pos, targ_pos);
    } else {
        return false;
    }
}

/**
 * @brief Test if the specified move is allowed for a queen by calling the collisionTest function
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool queenMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {

    if (abs(targ_pos.x-start_pos.x) == abs(targ_pos.y-start_pos.y) || targ_pos.x-start_pos.x == 0 || targ_pos.y-start_pos.y == 0) {
        return collisionTest(board, size, start_pos, targ_pos);
    } else {
        return false;
    }
}

/**
 * @brief Test if the specified move is allowed for a king
 * 
 * @param board Board where the move has to be tested
 * @param size Size of the board
 * @param start_pos Start coordinates of the piece
 * @param targ_pos Target coordinates of the piece
 * @return true if the move is allowed
 * @return false if the move is not allowed
 */
bool kingMoveTest(Square** board, int size, Coords start_pos, Coords targ_pos) {
    int move_x = targ_pos.x-start_pos.x;
    int move_y = targ_pos.y-start_pos.y;

    if (abs(move_x) > 1 || abs(move_y) > 1) {
        return false;
    } else {
        return true;
    }
}

/**
 * @brief Test if a piece is in a check position (can be else than a king)
 * 
 * @param board Board where the check has to be tested
 * @param size Size of the board
 * @param king_pos Position of the king (or another piece)
 * @param piece_color Color of the piece
 * @return true if the piece is in  a check position
 * @return false if the piece is not in a check position
 */
bool checkTest(Square** board, int size, Coords piece_pos, Color piece_color) {
    bool check = false;
    Coords test_pos;
    test_pos.y = 0;
    while (test_pos.y < size && check == false) {
        test_pos.x = 0;
        while (test_pos.x < size && check == false) {
            if (board[test_pos.x][test_pos.y].type != empty && board[test_pos.x][test_pos.y].type != king && (board[test_pos.x][test_pos.y].color != piece_color)) {
                check = moveTest(board, size, test_pos, piece_pos);
            }
            test_pos.x++;
        }
        test_pos.y++;
    }
    return check;
}

/**
 * @brief Test if a piece can intercept a check by moving it in the path of the check
 * 
 * @param board The board where the move has to be tested
 * @param size The size of the board
 * @param start_pos The position of the menacing piece
 * @param king_pos The position of the king
 * @return true If a rescue is possible
 * @return false If a rescue is not possible
 */
bool RescueTest(Square** board, int size, Coords start_pos,  Coords king_pos) {

    Color kingcolor = board[king_pos.x][king_pos.y].color;
    int move_x = king_pos.x-start_pos.x;
    int move_y = king_pos.y-start_pos.y;
    int dx, dy;

    if (move_x == 0) {
        dx = 0;
    } else {
        dx = move_x/abs(move_x);
    }
    if (move_y == 0) {
        dy = 0;
    } else {
        dy = move_y/abs(move_y);
    }

    int i=0;
    bool rescue = false;
    Coords test_coords = start_pos;
    
    while (i < (int)fmax(abs(move_x),abs(move_y)) && (rescue = checkTest(board, size, test_coords, !kingcolor)) == false) {
        test_coords.x += dx;
        test_coords.y += dy;
        i++;
    }

    return rescue;
}

/**
 * @brief Test if the specified king is in a checkmate position
 * 
 * @param board Board where the checkmate has to be tested
 * @param size Size of the board
 * @param king_pos Position of the king
 * @return true if the king is on a checkmate position
 * @return false if the king is not in a checkmate position
 */
bool checkMateTest(Square** board, int size, Coords king_pos) {
    bool checkmate = true;
    Coords test_coords;
    test_coords.x = king_pos.x-1;

    Color kingcolor = board[king_pos.x][king_pos.y].color;

    while (test_coords.x <= king_pos.x+1 && checkmate == true) {
        test_coords.y = king_pos.y-1;
        while (test_coords.y <= king_pos.y+1 && checkmate == true) {
            if (test_coords.x >= 0 && test_coords.x < size && test_coords.y >= 0 && test_coords.y < size) {
                
                if (board[test_coords.x][test_coords.y].color != kingcolor || board[test_coords.x][test_coords.y].type == empty) {
                    checkmate = checkTest(board, size, test_coords, kingcolor);
                }
            }
            test_coords.y++;
        }
        test_coords.x++;
    }
    if (checkmate == true) {
        bool already_tested = false;
        for (test_coords.y = 0; test_coords.y < size; test_coords.y++) {
            for (test_coords.x = 0; test_coords.x < size; test_coords.x++) {
                if (board[test_coords.x][test_coords.y].type != empty && board[test_coords.x][test_coords.y].color != kingcolor && moveTest(board, size, test_coords, king_pos) == true) {
                    if (already_tested == true) {
                        checkmate = false;
                    } else if (board[test_coords.x][test_coords.y].type == bishop || board[test_coords.x][test_coords.y].type == rook || board[test_coords.x][test_coords.y].type == queen) {
                        checkmate = !RescueTest(board, size, test_coords, king_pos);
                        already_tested = true;
                    } else {
                        checkmate = !checkTest(board, size, test_coords, !kingcolor);
                        already_tested = true;
                    }
                }
            }
        }
    }
    return checkmate;
}

/**
 * @brief Execute the specified move (doesn't check if a move is legal or not)
 * 
 * @param board Board where the move has to be executed
 * @param size Size of the board
 * @param start_pos Start coordinates of the move
 * @param targ_pos Target coordinates of a move
 */
void moveExecute(Square** board, int size, Coords start_pos, Coords targ_pos) {
    board[targ_pos.x][targ_pos.y] = board[start_pos.x][start_pos.y];
    board[start_pos.x][start_pos.y].type = empty;
}

/**
 * @brief Test if the specified move would put the specified king in a checkmate position
 * 
 * @param board Board where the checkmate has to be checked
 * @param size Size of the board
 * @param start_pos Start coordinates of the move
 * @param targ_pos Target coordinates of the move
 * @param king_pos Position of the king
 * @param kingcolor Color of the king
 * @return true if the move would put the king in a checkmate position
 * @return false if the move would not put the king in a checkmate position
 */
bool checkTestAfterMove(Square** board, int size, Coords start_pos, Coords targ_pos, Coords king_pos, Color kingcolor) {

    Square startpiece = board[start_pos.x][start_pos.y];
    Square targpiece = board[targ_pos.x][targ_pos.y];
    moveExecute(board, size, start_pos, targ_pos);
    bool check = checkTest(board, size, king_pos, kingcolor);

    board[start_pos.x][start_pos.y] = startpiece;
    board[targ_pos.x][targ_pos.y] = targpiece;

    return check;
}