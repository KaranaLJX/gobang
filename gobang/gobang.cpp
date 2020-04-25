#include"gobang.h"
//gobang.h 中定义的画，由于gobang被引用了多次，所以就会导致重复定义。
const  unordered_map<string, int> gobang::score_type{
	{"01100",50},{"00110",50},{"11010",200},{"00111",500},
	{"11100",500},{"01110",5000},{"010110",5000},
	{"011010",5000},{"11101",5000},{"10111",5000},
	{"11110",5000},{"01111",5000},{"11011",5000},
	{"011110",50000},{"11111",99999999}
};
gobang::gobang() {
	//bool iswin;
	//bool isaiwin;
	//bool aiturn;
	//stack<p> aiChesspoint;
	//stack<p> humanChesspoint;
	//p nextpoint;
	//p lastpoint;
	//bitset<col + 1> aichess[col + 1];
	//bitset<col + 1> humanchess[col + 1];
	iswin = false;
	isaiwin = false;
	aiturn = false;
	cal_score_win = false;

}

bool gobang::winGame(bool isai, short x, short y) {
	int dx[4]{ 0,1,1,-1 };
	int dy[4]{ 1,0,1,1 };
	auto& mychess = isai ? aichess : humanchess;
	auto& hischess = isai ? humanchess : aichess;
	bool flag = false;
	for (int i = 0; i < 4; i++) {
		flag = false;
		for (int j = -4; j < 1; j++) {
			short xx = x + j * dx[i];
			short yy = y + j * dy[i];
			if (xx<0 || xx>col || yy<0 || yy>col || !mychess[xx][yy]) {
				flag = true;
				break;
			}
		}
		if (!flag) return true;
		flag = false;
		for (int j = 0; j < 5; j++) {
			short xx = x + j * dx[i];
			short yy = y + j * dy[i];
			if (xx<0 || xx>col || yy<0 || yy>col || !mychess[xx][yy]) {
				flag = true;
				break;

			}
		}
		if (!flag) return true;
	}
	return false;
}


int gobang::negmax(bool isai, int depth, int alpha, int beta, p mylastpoint) {
	if (!aiChesspoint.size()) {
		nextpoint = p(lastpoint.first + 1, lastpoint.second);
		return 0;

	}
	if (winGame(!isai, mylastpoint.first, mylastpoint.second))
		return -MAXSCORE;
	if (!depth) {
		int res = evaluate(isai);
		return res;
	}
	bitset<col + 1> vis[col + 1];
	queue<p> que;
	for (auto it=aiChesspoint.rbegin();it!=aiChesspoint.rend();it++) {
		que.push(*it);
	}
	for (auto it = humanChesspoint.rbegin(); it != humanChesspoint.rend(); it++) {
		que.push(*it);
	}


	const int dx[] = { -1, 1, 0, 0 }, dy[] = { 0, 0, -1, 1 };
	vector<p> pending;
	bool flag[16][16];
	memset(flag, 0, sizeof(flag));
	int len = humanChesspoint.size() + aiChesspoint.size();
	while (!que.empty() && pending.size()<=4*len) {
		auto [x, y] = que.front(); que.pop();
		flag[x][y] = 1;
		if (!aichess[x][y] && !humanchess[x][y]) {
			pending.push_back({ x,y });
		}
		for (int i = 0; i < 4; ++i) {
			int tx = x + dx[i], ty = y + dy[i];
			if (tx < 0 || ty < 0 || tx > 15 || ty > 15)	continue;
			if (flag[tx][ty])	continue;
			que.push({ tx,ty });
		}
	}
	for (auto& point : pending) {
		auto [x, y] = point;
		//	vis[x][y] = 1;
		if (isai) {
			aiChesspoint.push_back(p(x, y));
			aichess[x][y] = 1;
		}
		else {
			humanchess[x][y] = 1;
			humanChesspoint.push_back(p(x, y));
		}
		int score = -negmax(!isai, depth - 1, -beta, -alpha, point);
		if (isai) {
			aiChesspoint.pop_back();
			aichess[x][y] = 0;
		}
		else {
			humanChesspoint.pop_back();
			humanchess[x][y] = 0;
		}
		if (score > alpha) {
			alpha = score;
			if (depth == DEPTH) {
				nextpoint = point;
				if (score == MAXSCORE) {
					//这地方是要返回alpha吗？
					isaiwin = true;
					iswin = true;
					return MAXSCORE;
				}
			}
			if (score > beta)
				return beta;
		}

	}
	return alpha;
}
/**
 判断是否递归结束（有人赢了或者到达递归深度0）
	如果递归结束
		返回评分值
	否则
		从最新的落点开始bfs
		for each 候选节点x：
			如果isai
				将x加入aiChess
			否则
				将x加入humanchess
			将x加入allchess
			value=-negmax(!isai,depth-1,-beta,-alpha);
			回溯恢复：
			如果isai
				将x从aichess删去
			否则
				将x从humanchess删除
			将x从allchess删除
**/
int  gobang::evaluate(bool isai) {


	int dx[4] = { 0,1,-1,1 };
	int dy[4] = { 1,0,1,1 };

	list<pair<long long, scoreshape>> shape_score;

	long long myscore = 0;
	int len = humanChesspoint.size();
	for (const p& pt : humanChesspoint)
		for (int i = 0; i < 4; i++)
			myscore += cal_score(pt.first, pt.second, dx[i], dy[i],
				shape_score, false);

	//修正：1.scoreshape的定义为什么在cpp和h里同时出现？
	// 2.给scoreshape加上了默认构造函数

	// 3. 现在你可以使用vsc的快捷键了

	long long enemyscore = 0;
	len = aiChesspoint.size();
	shape_score.clear();
	for (const p& pt : aiChesspoint)
		for (int i = 0; i < 4; i++)
			enemyscore += cal_score(pt.first, pt.second, dx[i], dy[i],
				shape_score, true);
	return int(myscore - 0.1 * enemyscore);
}

ll gobang::cal_score(short m, short n, short x_decrict,
	short y_derice, list<pair<ll, scoreshape>>& vec, bool isai) {
	auto& mychess = isai ? aichess : humanchess;
	auto& hischess = isai ? humanchess : aichess;
	for (const auto& shape : vec) {
		if (shape.second.inequal(m, n, x_decrict, y_derice))
			return 0;
	}
	scoreshape maxscoreshape;
	ll maxscore = 0;
	ll addscore = 0;
	for (short offset = -5; offset < 1; offset++) {
		string strshape5;
		int score5 = 0;
		int score6 = 0;
		for (short i = 0; i < 5; i++) {
			short xx = m + (offset + i) * x_decrict;
			short yy = n + (offset + i) * y_derice;
			if (xx<0 || xx>col || yy<0 || yy>col || hischess[xx][yy])
				break;
			strshape5.push_back(mychess[xx][yy] + '0');
		}
		if (strshape5.size() == 5) {
			auto it = score_type.find(strshape5);
			if (it != score_type.end())
				score5 = it->second;
			short xx = m + (offset + 5) * x_decrict;
			short yy = n + (offset + 5) * y_derice;
			if (xx<0 || xx>col || yy<0 || yy>col || hischess[xx][yy])
				score6 = 0;
			else {
				strshape5.push_back(mychess[xx][yy] + '0');
				it = score_type.find(strshape5);
				if (it != score_type.end())
					score6 = it->second;
			}
			if (score5 > maxscore || score6 > maxscore) {
				maxscore = max(score5, score6);
				maxscoreshape = scoreshape(m, n, x_decrict, y_derice, offset);
			}
		}
	}
	if (maxscore) {
		p point[5];
		for (int i = 0; i < 5; i++) {
			point[i] = p(maxscoreshape.x + (maxscoreshape.offset + i) * x_decrict,
				maxscoreshape.y + (maxscoreshape.offset + i) * y_derice);
		}
		for (const auto& shape : vec) {
			for (int i = 0; i < 4; i++)
				if (shape.second.in(point[i].first, point[i].second))
					addscore += (maxscore + shape.first);
		}
		vec.push_back(pair<ll, scoreshape>(maxscore, maxscoreshape));
	}
	return maxscore + addscore;
}


