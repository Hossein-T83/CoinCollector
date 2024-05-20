#include "Checker.h"

Checker::Checker() {

}

bool Checker::winCheck(Player player1, Player player2) {
	return !((player1.getHp() != 0 && player2.getHp() != 0) && (player1.getScore() != 200 && player2.getScore() != 200));
}

bool Checker::enemyCheck(FloatRect detectionZoneEnemy, FloatRect detectionZonePlayer1, FloatRect detectionZonePlayer2) {
	
}