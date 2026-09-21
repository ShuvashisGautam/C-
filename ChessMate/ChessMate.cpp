#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cctype>
#include <cmath>

using namespace std;



enum class Color
{
    White,
    Black
};

enum class GameStatus
{
    Normal,
    Check,
    Checkmate,
    Stalemate
};

Color opposite(Color c)
{
    return (c == Color::White) ? Color::Black : Color::White;
}

string colorName(Color c)
{
    return (c == Color::White) ? "White" : "Black";
}


class Board; 

class Move
{
public:
    int  fromRow = 0;
    int  fromCol = 0;
    int  toRow   = 0;
    int  toCol   = 0;
    bool valid   = false;

    Move() = default;

    Move(const string& from, const string& to)
    {
        bool okFrom = parseSquare(from, fromRow, fromCol);
        bool okTo   = parseSquare(to,   toRow,   toCol);
        valid = okFrom && okTo;
    }

    bool isValid() const
    {
        return valid;
    }

    // "e2" -> row 6, col 4
    static bool parseSquare(const string& s, int& row, int& col)
    {
        if (s.size() != 2)
            return false;

        char file = (char)tolower((unsigned char)s[0]);
        char rank = s[1];

        if (file < 'a' || file > 'h')
            return false;
        if (rank < '1' || rank > '8')
            return false;

        col = file - 'a';
        row = 8 - (rank - '0');
        return true;
    }
};

class Piece
{
protected:
    Color color;
    int   row;
    int   col;

public:
    Piece(Color c, int r, int co) : color(c), row(r), col(co) {}

    virtual ~Piece() = default;

    Color getColor() const { return color; }
    int   getRow()   const { return row;   }
    int   getCol()   const { return col;   }

    void setPosition(int r, int c)
    {
        row = r;
        col = c;
    }

    virtual bool   isValidMove(const Board& b, int toRow, int toCol) const = 0;
    virtual string getSymbol() const = 0;
    virtual bool   isKing() const { return false; }
};


class Pawn : public Piece
{
public:
    Pawn(Color c, int r, int co) : Piece(c, r, co) {}
    bool   isValidMove(const Board& b, int toRow, int toCol) const override;
    string getSymbol() const override { return (color == Color::White) ? "P" : "p"; }
};

class Rook : public Piece
{
public:
    Rook(Color c, int r, int co) : Piece(c, r, co) {}
    bool   isValidMove(const Board& b, int toRow, int toCol) const override;
    string getSymbol() const override { return (color == Color::White) ? "R" : "r"; }
};

class Knight : public Piece
{
public:
    Knight(Color c, int r, int co) : Piece(c, r, co) {}
    bool   isValidMove(const Board& b, int toRow, int toCol) const override;
    string getSymbol() const override { return (color == Color::White) ? "N" : "n"; }
};

class Bishop : public Piece
{
public:
    Bishop(Color c, int r, int co) : Piece(c, r, co) {}
    bool   isValidMove(const Board& b, int toRow, int toCol) const override;
    string getSymbol() const override { return (color == Color::White) ? "B" : "b"; }
};

class Queen : public Piece
{
public:
    Queen(Color c, int r, int co) : Piece(c, r, co) {}
    bool   isValidMove(const Board& b, int toRow, int toCol) const override;
    string getSymbol() const override { return (color == Color::White) ? "Q" : "q"; }
};

class King : public Piece
{
public:
    King(Color c, int r, int co) : Piece(c, r, co) {}
    bool   isValidMove(const Board& b, int toRow, int toCol) const override;
    string getSymbol() const override { return (color == Color::White) ? "K" : "k"; }
    bool   isKing() const override { return true; }
};


class Board
{
private:
    Piece* grid[8][8] = {};               // nullptr means empty
    vector<string> capturedPieces;

    void setup();

public:
    Board();
    ~Board();

    Piece* getPiece(int r, int c) const
    {
        if (r < 0 || r > 7 || c < 0 || c > 7)
            return nullptr;
        return grid[r][c];
    }

    void display() const;

    bool       isPathClear(int fromRow, int fromCol, int toRow, int toCol) const;
    bool       isKingAttacked(Color side) const;
    bool       hasAnyLegalMove(Color side);
    GameStatus checkStatus(Color side);
    bool       movePiece(const Move& m);
};


bool Pawn::isValidMove(const Board& b, int toRow, int toCol) const
{
    if (toRow < 0 || toRow > 7 || toCol < 0 || toCol > 7)
        return false;

    int forward  = (color == Color::White) ? -1 : 1;
    int startRow = (color == Color::White) ?  6 : 1;

    int dr = toRow - row;
    int dc = toCol - col;

    Piece* target = b.getPiece(toRow, toCol);

    // Move straight forward
    if (dc == 0)
    {
        // One square
        if (dr == forward && target == nullptr)
            return true;

        // Two squares from the start row
        if (dr == 2 * forward && row == startRow && target == nullptr)
        {
            if (b.getPiece(row + forward, col) == nullptr)
                return true;
        }
        return false;
    }


    if (abs(dc) == 1 && dr == forward)
    {
        return (target != nullptr && target->getColor() != color);
    }

    return false;
}

bool Rook::isValidMove(const Board& b, int toRow, int toCol) const
{
    if (toRow == row && toCol == col) return false;      // stayed put
    if (toRow != row && toCol != col) return false;      // must be straight

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color)
        return false;                                     // own piece

    return b.isPathClear(row, col, toRow, toCol);
}

bool Bishop::isValidMove(const Board& b, int toRow, int toCol) const
{
    if (toRow == row && toCol == col) return false;

    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    if (dr != dc) return false;                           // must be diagonal

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color)
        return false;

    return b.isPathClear(row, col, toRow, toCol);
}

bool Queen::isValidMove(const Board& b, int toRow, int toCol) const
{
    if (toRow == row && toCol == col) return false;

    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    bool straight = (toRow == row || toCol == col);
    bool diagonal = (dr == dc);

    if (!straight && !diagonal) return false;

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color)
        return false;

    return b.isPathClear(row, col, toRow, toCol);
}

bool Knight::isValidMove(const Board& b, int toRow, int toCol) const
{
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    bool isL = (dr == 2 && dc == 1) || (dr == 1 && dc == 2);
    if (!isL) return false;

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color)
        return false;

    return true;                                          // knight jumps
}

bool King::isValidMove(const Board& b, int toRow, int toCol) const
{
    int dr = abs(toRow - row);
    int dc = abs(toCol - col);

    if (dr > 1 || dc > 1) return false;                   // one square only
    if (dr == 0 && dc == 0) return false;                 // stayed put

    Piece* target = b.getPiece(toRow, toCol);
    if (target != nullptr && target->getColor() == color)
        return false;

    return true;                                         
}


Board::Board()
{
    setup();
}

Board::~Board()
{
    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
            delete grid[r][c];
}

void Board::setup()
{

    grid[0][0] = new Rook  (Color::Black, 0, 0);
    grid[0][1] = new Knight(Color::Black, 0, 1);
    grid[0][2] = new Bishop(Color::Black, 0, 2);
    grid[0][3] = new Queen (Color::Black, 0, 3);
    grid[0][4] = new King  (Color::Black, 0, 4);
    grid[0][5] = new Bishop(Color::Black, 0, 5);
    grid[0][6] = new Knight(Color::Black, 0, 6);
    grid[0][7] = new Rook  (Color::Black, 0, 7);

    for (int c = 0; c < 8; ++c)
        grid[1][c] = new Pawn(Color::Black, 1, c);


    for (int c = 0; c < 8; ++c)
        grid[6][c] = new Pawn(Color::White, 6, c);

    grid[7][0] = new Rook  (Color::White, 7, 0);
    grid[7][1] = new Knight(Color::White, 7, 1);
    grid[7][2] = new Bishop(Color::White, 7, 2);
    grid[7][3] = new Queen (Color::White, 7, 3);
    grid[7][4] = new King  (Color::White, 7, 4);
    grid[7][5] = new Bishop(Color::White, 7, 5);
    grid[7][6] = new Knight(Color::White, 7, 6);
    grid[7][7] = new Rook  (Color::White, 7, 7);
}

void Board::display() const
{
    cout << "\n     a   b   c   d   e   f   g   h\n";
    cout << "   +---+---+---+---+---+---+---+---+\n";

    for (int r = 0; r < 8; ++r)
    {
        cout << " " << (8 - r) << " |";

        for (int c = 0; c < 8; ++c)
        {
            string symbol = (grid[r][c] != nullptr) ? grid[r][c]->getSymbol() : " ";
            cout << " " << symbol << " |";
        }

        cout << " " << (8 - r) << "\n";
        cout << "   +---+---+---+---+---+---+---+---+\n";
    }

    cout << "     a   b   c   d   e   f   g   h\n";

    cout << "Captured: ";
    if (capturedPieces.empty())
    {
        cout << "(none)";
    }
    else
    {
        for (size_t i = 0; i < capturedPieces.size(); ++i)
            cout << capturedPieces[i] << " ";
    }
    cout << "\n";
}

bool Board::isPathClear(int fromRow, int fromCol, int toRow, int toCol) const
{
    int stepRow = (toRow > fromRow) - (toRow < fromRow);  // -1, 0, or 1
    int stepCol = (toCol > fromCol) - (toCol < fromCol);

    int r = fromRow + stepRow;
    int c = fromCol + stepCol;

    while (r != toRow || c != toCol)
    {
        if (grid[r][c] != nullptr)
            return false;

        r += stepRow;
        c += stepCol;
    }

    return true;
}

bool Board::isKingAttacked(Color side) const
{
    // Find the king of the given side
    int kingRow = -1;
    int kingCol = -1;

    for (int r = 0; r < 8 && kingRow == -1; ++r)
    {
        for (int c = 0; c < 8; ++c)
        {
            Piece* p = grid[r][c];
            if (p != nullptr && p->getColor() == side && p->isKing())
            {
                kingRow = r;
                kingCol = c;
                break;
            }
        }
    }

    if (kingRow == -1)
        return false;

   
    Color enemy = opposite(side);

    for (int r = 0; r < 8; ++r)
        for (int c = 0; c < 8; ++c)
        {
            Piece* p = grid[r][c];
            if (p != nullptr && p->getColor() == enemy &&
                p->isValidMove(*this, kingRow, kingCol))
            {
                return true;
            }
        }

    return false;
}

bool Board::hasAnyLegalMove(Color side)
{
    for (int fromRow = 0; fromRow < 8; ++fromRow)
        for (int fromCol = 0; fromCol < 8; ++fromCol)
        {
            Piece* p = grid[fromRow][fromCol];
            if (p == nullptr || p->getColor() != side)
                continue;

            for (int toRow = 0; toRow < 8; ++toRow)
                for (int toCol = 0; toCol < 8; ++toCol)
                {
                    if (fromRow == toRow && fromCol == toCol)
                        continue;

                    if (!p->isValidMove(*this, toRow, toCol))
                        continue;

                    // Simulate the move
                    Piece* target = grid[toRow][toCol];
                    int oldRow = p->getRow();
                    int oldCol = p->getCol();

                    grid[toRow][toCol]     = p;
                    grid[fromRow][fromCol] = nullptr;
                    p->setPosition(toRow, toCol);

                    bool safe = !isKingAttacked(side);

                    // Undo
                    grid[fromRow][fromCol] = p;
                    grid[toRow][toCol]     = target;
                    p->setPosition(oldRow, oldCol);

                    if (safe)
                        return true;
                }
        }

    return false;
}

GameStatus Board::checkStatus(Color side)
{
    bool inCheck = isKingAttacked(side);
    bool hasMove = hasAnyLegalMove(side);

    if (!hasMove)
        return inCheck ? GameStatus::Checkmate : GameStatus::Stalemate;

    return inCheck ? GameStatus::Check : GameStatus::Normal;
}

bool Board::movePiece(const Move& m)
{
    Piece* p = grid[m.fromRow][m.fromCol];
    if (p == nullptr)
        return false;

    if (!p->isValidMove(*this, m.toRow, m.toCol))
        return false;

    Piece* target = grid[m.toRow][m.toCol];
    int oldRow = p->getRow();
    int oldCol = p->getCol();

    grid[m.toRow][m.toCol]     = p;
    grid[m.fromRow][m.fromCol] = nullptr;
    p->setPosition(m.toRow, m.toCol);

    // Reject if it leaves our own king in check
    if (isKingAttacked(p->getColor()))
    {
        grid[m.fromRow][m.fromCol] = p;
        grid[m.toRow][m.toCol]     = target;
        p->setPosition(oldRow, oldCol);
        return false;
    }

    if (target != nullptr)
    {
        string tag = target->getSymbol();
        tag += "(";
        tag += (target->getColor() == Color::White ? "W" : "B");
        tag += ")";

        capturedPieces.push_back(tag);
        delete target;
    }

    return true;
}


class Player
{
private:
    string name;
    Color  color;

public:
    Player(const string& n, Color c) : name(n), color(c) {}

    string getName()  const { return name;  }
    Color  getColor() const { return color; }
};


class Game
{
private:
    Board  board;
    Player white;
    Player black;

    int  currentTurn = 0;
    int  moveNumber  = 1;
    bool running     = true;

    vector<string> moveHistory;

    Player& currentPlayer()
    {
        return (currentTurn == 0) ? white : black;
    }

    bool processInput(const string& line);

public:
    Game()
        : board(),
          white("Player 1 (White)", Color::White),
          black("Player 2 (Black)", Color::Black)
    {
    }

    void start();
    void printHelp()    const;
    void printHistory() const;
    void saveHistory();
};

void Game::printHelp() const
{
    cout << "\n---------------- ChessMate Help ----------------\n";
    cout << "  Move format :  <from> <to>       e.g.  e2 e4\n";
    cout << "  Commands    :  help    - show this message\n";
    cout << "                 resign  - resign the game\n";
    cout << "                 quit    - exit the program\n";
    cout << "  Pieces      :  UPPERCASE = White, lowercase = Black\n";
    cout << "                 K/k King   Q/q Queen   R/r Rook\n";
    cout << "                 B/b Bishop N/n Knight  P/p Pawn\n";
    cout << "  Empty square:  (blank)\n";
    cout << "------------------------------------------------\n";
}

void Game::printHistory() const
{
    cout << "\n========== Move History ==========\n";

    if (moveHistory.empty())
    {
        cout << "(no moves played)\n";
    }
    else
    {
        for (size_t i = 0; i < moveHistory.size(); ++i)
            cout << moveHistory[i] << "\n";
    }

    cout << "==================================\n";
}

void Game::saveHistory()
{
    cout << "Save move history to a file? (y/n): ";

    string answer;
    if (!getline(cin, answer))
        return;

    if (answer.empty() || (answer[0] != 'y' && answer[0] != 'Y'))
        return;

    cout << "Enter filename (e.g. history.txt): ";
    string filename;
    if (!getline(cin, filename) || filename.empty())
        filename = "history.txt";

    ofstream out(filename);
    if (!out)
    {
        cout << "Could not open '" << filename << "'.\n";
        return;
    }

    out << "ChessMate - Move History\n";
    out << "========================\n";

    for (size_t i = 0; i < moveHistory.size(); ++i)
        out << moveHistory[i] << "\n";

    cout << "Move history saved to " << filename << "\n";
}

bool Game::processInput(const string& line)
{
    
    string lower = line;
    for (size_t i = 0; i < lower.size(); ++i)
        lower[i] = (char)tolower((unsigned char)lower[i]);

    if (lower == "help")
    {
        printHelp();
        return false;            // turn not consumed
    }

    if (lower == "quit" || lower == "exit")
    {
        cout << "\nGame aborted by the user.\n";
        running = false;
        return true;
    }

    if (lower == "resign")
    {
        Player& resigning = currentPlayer();
        Player& winner    = (currentTurn == 0) ? black : white;

        cout << "\n" << resigning.getName() << " resigns. "
             << winner.getName() << " wins!\n";

        running = false;
        return true;
    }

    istringstream iss(line);
    string fromSquare, toSquare, extra;

    if (!(iss >> fromSquare >> toSquare))
    {
        cout << "Invalid input. Use two squares, e.g. \"e2 e4\".\n";
        return false;
    }

    if (iss >> extra)
    {
        cout << "Invalid input: too many tokens. Use exactly \"e2 e4\".\n";
        return false;
    }

    Move m(fromSquare, toSquare);

    if (!m.isValid())
    {
        cout << "Invalid coordinates. Files are a-h, ranks are 1-8.\n";
        return false;
    }

    Player& player = currentPlayer();
    Piece*  piece  = board.getPiece(m.fromRow, m.fromCol);

    if (piece == nullptr)
    {
        cout << "No piece on " << fromSquare << ".\n";
        return false;
    }

    if (piece->getColor() != player.getColor())
    {
        cout << "That is not your piece (you are "
             << colorName(player.getColor()) << ").\n";
        return false;
    }

    if (!piece->isValidMove(board, m.toRow, m.toCol))
    {
        cout << "Illegal move for that piece.\n";
        return false;
    }

    if (!board.movePiece(m))
    {
        cout << "Move rejected: it would leave your king in check.\n";
        return false;
    }

    ostringstream entry;
    if (currentTurn == 0)
        entry << moveNumber << ". " << fromSquare << " " << toSquare;
    else
        entry << moveNumber << "... " << fromSquare << " " << toSquare;

    moveHistory.push_back(entry.str());
    if (currentTurn == 1)
        ++moveNumber;

    board.display();


    Color mover = player.getColor();
    Color opp   = opposite(mover);

    GameStatus status = board.checkStatus(opp);

    if (status == GameStatus::Checkmate)
    {
        cout << "\n*** Checkmate! " << colorName(mover)
             << " (" << player.getName() << ") wins. ***\n";
        running = false;
    }
    else if (status == GameStatus::Stalemate)
    {
        cout << "\n*** Stalemate! The game is a draw. ***\n";
        running = false;
    }
    else
    {
        if (status == GameStatus::Check)
            cout << "\n*** Check! " << colorName(opp)
                 << "'s king is under attack. ***\n";

        currentTurn = 1 - currentTurn;   // switch turns
    }

    return true;
}

void Game::start()
{
    cout << "==========================================\n";
    cout << "        ChessMate - Terminal Chess\n";
    cout << "==========================================\n";
    cout << "Enter moves like \"e2 e4\".\n";
    cout << "Commands: help, resign, quit.\n";
    cout << "UPPERCASE = White pieces. lowercase = Black pieces.\n";

    board.display();

    while (running)
    {
        Player& player = currentPlayer();

        cout << "\n" << player.getName()
             << "'s turn (" << colorName(player.getColor()) << ")\n";
        cout << "Enter move: ";

        string line;
        if (!getline(cin, line))
            break;

        // Trim leading and trailing whitespace
        while (!line.empty() && isspace((unsigned char)line[0]))
            line.erase(line.begin());
        while (!line.empty() && isspace((unsigned char)line[line.size() - 1]))
            line.erase(line.size() - 1);

        if (line.empty())
            continue;

        processInput(line);
    }

    printHistory();

    if (!moveHistory.empty())
        saveHistory();
}


int main()
{
    Game game;
    game.start();
    return 0;
}



