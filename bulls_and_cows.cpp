// A little guessing game called
//    (for some obscure reason) <<Bulls and Cows>>.

#include "../lib/std_lib_facilities.h"
#include <set>

int count (const vector<char>& digits, char d)
{
  int k{};

  for (int i = 0; i < digits.size(); ++i)
    if (digits[i] == d)
      ++k;

  return k;
}

void validate (const vector<char>& number)
{
  for (int i = 0; i < number.size(); ++i)
  {
    if (number[i] < '0' || '9' < number[i])
      error("the number contains not a digit");

    if (count(number, number[i]) != 1)
      error("digits of the number are not unique");
  }
}

vector<char> user_guess ()
{
  vector<char> number(4);

  cout << "guess the number: ";
  for (int i = 0; i < number.size(); ++i)
    cin >> number[i];

  if (!cin)
    error("invalid input");

  validate(number);

  return number;
}

vector<char> create_numbers_line ()
{
  set<char> number;
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> distlib('0', '9');
  while (number.size() < 4){
    number.insert(distlib(gen));
  }
  vector<char> res(number.begin(), number.end());
  shuffle(res.begin(), res.end(), gen);
  return res;
}

vector<vector<char>> line_digits(){
  vector<vector<char>> digits;
  for (char a = '0'; a <= '9'; ++a){
    for (char b = '0'; b <= '9'; ++b){
      if (a == b) continue;
      for (char c = '0'; c <= '9'; ++c){
        if (c==a || c==b) continue;
        for (char d = '0'; d <= '9'; ++d){
          if (d==a || d==b || d==c) continue;
          digits.push_back({a, b, c, d});
        }
      }
    }
  }
  return digits;
}

vector<vector<char>> new_digits(int bulls, int cows, vector<char> number, vector<vector<char>> digits){
  vector<vector<char>> new_digits;
  for (auto a : digits){
    int new_bulls = 0;
    int new_cows = 0;
    for (int i = 0; i < a.size(); ++i){
      if (a[i] == number[i])
        ++new_bulls;
      else if (count(number, a[i]) == 1)
        ++new_cows;
    }
    if (new_bulls == bulls && new_cows == cows){
      new_digits.push_back(a);
    }
  }
  return new_digits;
}
int main ()
try
{
  cout << "<<Bulls and Cows>>\n"
       << "Computer sets a number of 4 unique digits.\n"
       << "Try to guess it.\n"
       << "<Bull> means right digit in the right position.\n"
       << "<Cow> means right digit in the wrong position.\n"
       << "\n"
       << "game is on" << endl;

  vector<char> number = create_numbers_line();

  vector<char> number_player;

  cout << "Think of a number.\n";
  int bulls1{};
  int bulls2{};
  auto digits = line_digits();
  do
  {
    
    bulls1 = bulls2 = 0;
    int cows1{};
    int cows2{};

    vector<char> uguess1 = user_guess();
    vector<char> uguess2 = digits[0];

    for (int i = 0; i < uguess1.size(); ++i)
    {
      if (uguess1[i] == number[i])
        ++bulls1;
      else if (count(number, uguess1[i]) == 1)
        ++cows1;
    }

    cout << "You have " << bulls1 << " bull(s) and " << cows1 << " cow(s)" << endl;
    
    if (bulls1 == 4) break;

    cout << "Computer number: ";
      for (char a : uguess2){
        cout << a;
      }
    cout << endl;
    
    cin >> bulls2 >> cows2;

    digits = new_digits(bulls2, cows2, uguess2, digits);
  }
  while (bulls1 != 4 && bulls2 != 4);
  if (bulls1 == 4) cout << "Game is over. Player win" << endl;
  else if (bulls2 == 4) cout << "Game is over. Computer win" << endl;
}
catch (exception& e)
{
  cerr << e.what() << endl;
  return 1;
}
catch (...)
{
  cerr << "Oops, something went wrong..." << endl;
  return 2;
}