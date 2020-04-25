#include"gobang.h"

//画棋盘
void init();
void drawchess(int, int, bool);
int main() {
	init();
	gobang go;
	while (!go.iswin) {
		if (go.aiturn) {
			go.negmax(true, gobang::DEPTH, -gobang::MAXSCORE, gobang::MAXSCORE,
				go.lastpoint);
			go.aiChesspoint.push_back(go.nextpoint);
			go.aichess[go.nextpoint.first][go.nextpoint.second] = 1;
			go.lastpoint = go.nextpoint;
			drawchess(go.nextpoint.first, go.nextpoint.second, true);

			
			
		}
		else {
			while(true) {
				MOUSEMSG mouse = GetMouseMsg();
				if (mouse.mkLButton) {	//右键下棋？
					short x = short(round(float(mouse.x) / gobang::gridwidth));
					short y = short(round(float(mouse.y) / gobang::gridwidth));
					if (!go.aichess[x][y] && !go.humanchess[x][y]) {
						go.lastpoint = p(x, y);
						go.humanchess[x][y] = 1;
						go.humanChesspoint.push_back(p(x, y));
						drawchess(x, y,false);
						if (go.winGame(false,x,y))
							go.iswin = true;
						break;
					}
				
				}
			}
		}
		go.aiturn = !go.aiturn;

	}
	system("pause");

}
void drawchess(int x,int y,bool isai) {
	if (isai)
		setfillcolor(WHITE);
	else
		setfillcolor(BLACK);
	
	solidcircle(x * gobang::gridwidth, y * gobang::gridwidth,
		gobang::radis);

}
void init() {

	initgraph(gobang::graphwidth + 5, gobang::graphwidth + 5);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	setbkcolor(YELLOW);
	cleardevice();
	for (int i = 0; i <= gobang::graphwidth; i = i + gobang::gridwidth) {
		line(i, 0, i, gobang::graphwidth);
		line(0, i, gobang::graphwidth, i);
	}
}
//while (que.size()) {
//	p point = que.front();
//	que.pop();
//	short x = point.first; short y = point.second;
//	if (vis[x][y] || aichess[x][y] || humanchess[x][y]) {
//		vis[x][y] = true;
//		continue;
//	}
//	vis[x][y] = 1;
//	if (isai) {
//		aiChesspoint.push_back(p(x, y));
//		aichess[x][y] = 1;
//	}
//	else {
//		humanchess[x][y] = 1;
//		humanChesspoint.push_back(p(x, y));
//	}
//	int score = -negmax(!isai, depth - 1, -beta, -alpha, point);
//	if (isai) {
//		aiChesspoint.pop_back();
//		aichess[x][y] = 0;
//	}
//	else {
//		humanChesspoint.pop_back();
//		humanchess[x][y] = 0;
//	}
//	if (score > alpha) {
//		alpha = score;
//		if (depth == DEPTH) {
//			nextpoint = point;
//			if (score == MAXSCORE) {
//				//这地方是要返回alpha吗？
//				isaiwin = true;
//				iswin = true;
//				return MAXSCORE;
//			}
//		}
//		if (score > beta)
//			return beta;

//	}
//}
