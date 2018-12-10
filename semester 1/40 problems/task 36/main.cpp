#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class GameM
{
private:
	int matches_count;
	int max_amount_to_take;

	int check_move(int on_board, int max_allowed);

public:
	GameM(const string filename)
	{
		ifstream in(filename);
		in >> matches_count >> max_amount_to_take;
	}

	GameM(int matches_count, int max_amount_to_take)
	{
	    this->matches_count = matches_count;
	    this->max_amount_to_take = max_amount_to_take;
	}

	void calc_first_move();
	void test();
};

//-------------------------------------------------------------------------------

int GameM::check_move(int on_board, int max_allowed)
{
	if (max_allowed >= on_board - 1)
    {
        return on_board - 1;
    }

	for (int i = 1; i < max_allowed + 1; i++)
    {
		int left_on_board = on_board - i;
		int next_move_allowed = i + 1;

		if (check_move(left_on_board, next_move_allowed) == 0)
        {
			return i;
		}
	}

	return 0;
}

void GameM::calc_first_move()
{
	int res = check_move(matches_count, max_amount_to_take);

	if (res)
    {
        cout << res << " match(es)" << endl;
    }
	else
    {
        cout << "You Lose(" << endl;
    }
}

void GameM::test()
{
    const int size = 30;
	for (int i = 1; i < size; i++)
    {
        for (int j = 1; j < i; j++)
        {
            GameM game(i, j);
            cout << "(" << i << ", " << j << "): ";
            game.calc_first_move();
        }
    }
}

//-------------------------------------------------------------------------------

int main()
{
	GameM matchGame("input.txt");
	matchGame.calc_first_move();
	//matchGame.test();
	return 0;
}
