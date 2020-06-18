#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <Windows.h>



using namespace std;


struct Point {
	int i;
	int j;

	Point() {}
	Point(int i, int j) {
		this->i = i;
		this->j = j;
	}
};

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};



HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void SetColor(ConsoleColor text, ConsoleColor background) {
	SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

int main() {
    system("color F0");
	fstream input("map.txt", fstream::in);

	Point start_point, end_point, boundary_point;
	vector<vector<int>> map;
	vector<int> row;
	int row_len;
	string line;
	int i = 0, j;
	while (getline(input, line)) {
		row.resize(line.length());
		for (j = 0; j < line.length(); j++) {
			row[j] = line[j] - '0';
			if (row[j] == 2) {
				start_point = Point(i, j);
				row[j] = 1;
			}
			else if (row[j] == 3) {
				end_point = Point(i, j);
				row[j] = 1;
			}
		}

		i++;
		map.push_back(row);
	}
	boundary_point.i = map.size() - 1;
	boundary_point.j = map[0].size() - 1;

	input.close();
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] == 0)
				SetColor(White, Black);
			else
				SetColor(Black, Green);

			cout << setw(4) << map[i][j];
		}
		cout << endl;
	}
	cout << endl;

	queue<Point> free_points;
	free_points.push(start_point);

	Point current;
	int d = 2;

	while (free_points.size() != 0) {


		int run_length = free_points.size();
		for (int k = 0; k < run_length; k++) {
			current = free_points.front();
			free_points.pop();
			i = current.i;
			j = current.j;

			if (j - 1 >= 0 && map[i][j - 1] == 1) {
				map[i][j - 1] = d;
				free_points.push(Point(i, j - 1));
			}
			if (j + 1 <= boundary_point.j && map[i][j + 1] == 1) {
				map[i][j + 1] = d;
				free_points.push(Point(i, j + 1));
			}
			if (i - 1 >= 0 && map[i - 1][j] == 1) {
				map[i - 1][j] = d;
				free_points.push(Point(i - 1, j));
			}
			if (i + 1 <= boundary_point.i && map[i + 1][j] == 1) {
				map[i + 1][j] = d;
				free_points.push(Point(i + 1, j));
			}
		}
		d += 1;

	}

	map[start_point.i][start_point.j] = 1;

	vector<Point> path;
	i = end_point.i, j = end_point.j;
	current = Point(end_point.i, end_point.j);
	vector<vector<int>> viewing_map(map);

	viewing_map[end_point.i][end_point.j] = d + 1;

	while (map[current.i][current.j] != 1) {
		if (current.j + 1 <= boundary_point.j && map[current.i][current.j + 1] == map[current.i][current.j] - 1) current.j += 1;
		else if (current.i + 1 <= boundary_point.i && map[current.i + 1][current.j] == map[current.i][current.j] - 1) current.i += 1;
		else if (current.i - 1 >= 0 && map[current.i - 1][current.j] == map[current.i][current.j] - 1) current.i -= 1;
		else if (current.j - 1 >= 0 && map[current.i][current.j - 1] == map[current.i][current.j] - 1) current.j -= 1;
		else
			cout << "Путь отсутствует!";

		path.push_back(current);
		viewing_map[current.i][current.j] = d + 1;
	}
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (viewing_map[i][j] == d + 1)
				SetColor(Black, Brown);
			else if (viewing_map[i][j] == 0)
				SetColor(White, Black);
			else
				SetColor(Black, Green);

			cout << setw(4) << map[i][j];
		}
		cout << endl;
	}
	return 0;
}
