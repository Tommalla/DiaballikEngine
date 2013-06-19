#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <cassert>
#include <string>
#include <sstream>
#include "enums.h"
#include "Game.h"

using namespace std;

namespace engine {
	inline void printDebug(const string& str) {
		#ifndef NDEBUG
		fputs(("dbg: " + str + "\n").c_str(), stderr);
		#endif
	}
	
	inline int sgn(const int x) {
		return (x == 0) ? 0 : ((x < 0) ? -1 : 1);
	}
	
	//enums-related:
	
	inline GamePlayer getOppositePlayer (const GamePlayer& player) {
		//engine::printDebug(string("Game::getOppositePlayer(") + string({(char)((char)player + '0')})  + string(")"));
		if (player == NONE)
			return NONE;
		return (player == GAME_PLAYER_A) ? GAME_PLAYER_B : GAME_PLAYER_A;
	}
	
	inline GamePlayer getPlayerFor (const FieldState& field) {
		//engine::printDebug(string("Game::getPlayerFor(") + string({(char)((char)field + '0')})  + string(")"));
		
		if (field == EMPTY)
			return NONE;
		if (field >= PLAYER_A && field <= BALL_A)
			return GAME_PLAYER_A;
		return GAME_PLAYER_B;
	}
	
	/**
	 * @brief Returns an identificator for the player in GTP
	 **/
	inline const string getIdFor (const GamePlayer& player) {
		if (player == GAME_PLAYER_A)
			return "b";
		return "w";
	}
	
	inline const vector< string > splitString(const string& str) {
		vector<string> res;
		
		istringstream iss(str);
		
		do {
			string sub;
			iss >> sub;
			if (sub.empty() == false)
				res.push_back(sub);
		} while (iss);
		
		return res;
	}
	
	inline const pair<const string, const string> convertFromMove(const Move& move) {
		assert(move.from.x >= 0 && move.from.x <= 6);
		assert(move.from.y >= 0 && move.from.y <= 6);
		assert(move.to.x >= 0 && move.to.x <= 6);
		assert(move.to.y >= 0 && move.to.y <= 6);
		
		return {string( {char('a' + move.from.x), char('1' + (6 - move.from.y))} ),	//Tricky hack - making 2-elements-long tables of chars
		string( {char('a' + move.to.x), char('1' + (6 - move.to.y))} )};
	}
	
	inline const Move convertToMove(const string& from, const string& to) {
		assert(from.length() == 2 && to.length() == 2);
		assert(from[0] >= 'a' && from[0] <= 'g');
		assert(from[1] >= '1' && from[1] <= '7');
		assert(to[0] >= 'a' && to[0] <= 'g');
		assert(to[1] >= '1' && to[1] <= '7');
		
		return Move(Point(from[0] - 'a', 6 - (from[1] - '1')), 
			    Point(to[0] - 'a', 6 - (to[1] - '1')) );
	}
	
	inline const string convertFromPoint(const Point& p) {
		assert(p.x >= 0 && p.x <= 6);
		assert(p.y >= 0 && p.y <= 6);
		
		return string( {char(p.x + 'a'), char(6 - p.y + '1')});
	}
	
	inline const vector<Point> convertToPoints(const string& str) {
		vector<Point> res;
		
		for (int i = 0; i + 1 < (int)str.size(); i += 2)
			res.push_back(Point(str[i] - 'a', 6 - str[i + 1] + '1'));
		return res;
	}
	
	inline const vector< Move > convertToMoves (const string& arg) {
		string from, to;
		vector<Move> res;
		
		for(int i = 0; i + 3 < (int)arg.size(); i += 4) {
			from.clear();
			to.clear();
			from.push_back(arg[i]);
			from.push_back(arg[i + 1]);
			
			to.push_back(arg[i + 2]);
			to.push_back(arg[i + 3]);
			
			res.push_back(convertToMove(from, to));
		}
		
		return res;
	}
	
	
	static const Point winInOneTurnMoves[3][4][2] = {
		{{Point(-1, 0), Point(-1, 0)}, {Point(1, 0), Point(1, 0)}, {Point(0, 0), Point(0, 0)}, {Point(0, 0), Point(0, 0)}},	//0 fields away
		{{Point(-1, 0), Point(0, 1)}, {Point(0, 1), Point(-1, 0)}, {Point(0, 1), Point(1, 0)}, {Point(1, 0), Point(0, 1)}},	//one up, one lr
		{{Point(0, 1), Point(0, 1)}, {Point(0,0), Point(0, 0)}, {Point(0, 0), Point(0,0)}, {Point(0, 0), Point(0, 0)}}	//2 fields up/down
	};
	
	static const int winInOneTurnLen[3] = {2, 4, 1};
	
	inline bool canWinInOneTurn (const Game& tmpGame, const GamePlayer player) {
		vector<Point> pawns = tmpGame.getPawnsOf(player);
		Point holder;
		
		for (int i = 0; i < (int)pawns.size(); ++i)
			if (tmpGame.getFieldAt(pawns[i]) == BALL_A || tmpGame.getFieldAt(pawns[i]) == BALL_B) {
				holder = pawns[i];
				swap(pawns[i], pawns[pawns.size() - 1]);
				pawns.pop_back();
				break;
			}
			
			int lineY = (player == GAME_PLAYER_A) ? 6 : 0;
		
		for (Point pawn : pawns)
			if (abs(lineY - pawn.y) <= 2) {	//can possibly reach the line
				
				#ifndef NDEBUG
				fprintf(stderr, "%s\n", tmpGame.toString().c_str());
				#endif
				int variant = abs(lineY - pawn.y);	//which variant - 2, 1 or 0 field from line
				
				for (int i = 0; i < winInOneTurnLen[variant]; ++i) {
					Game tmp2 = tmpGame;
					Point tmpPawn = pawn;
					Point dstPawn, diff;
					
					for (int j = 0; j < 2; ++j) {
						if (tmpPawn.y == lineY && tmp2.isMoveValid(holder, tmpPawn))	//can pass to line
							return true;
						
						diff = winInOneTurnMoves[variant][i][j];
						diff.y *= ((lineY - pawn.y > 0) ? 1 : -1);
						dstPawn = tmpPawn + diff;
						
						if (tmp2.isMoveValid(tmpPawn, dstPawn)) {
							tmp2.makeMove(tmpPawn, dstPawn);
							tmpPawn = dstPawn;
						} else
							break;
					}
					
					if (tmpPawn.y == lineY && tmp2.isMoveValid(holder, tmpPawn))	//can pass to line
						return true;
					
				}
			}
			
			return false;	//everything else failed
	
		
	}
	
	
	
}

#endif