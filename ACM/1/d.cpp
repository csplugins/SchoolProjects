#include <iostream>
#include <vector>

using namespace std;

class pairs{
public: int x, y;
};

int main(){
  int input;
  cin >> input;
  vector<pairs> pair = vector<pairs>();
  int last = input;
  pair.push_back(new pairs());
    pair.at(0).x = 1;
    pair.at(0).y = input;
  //for(int i = 0; i < pairs.size(); i++)
  //cout << pairs[i].x << " " << pairs[i].y << endl;
  /*for(int i = 2; i < input/2; i++){
    while(1){
      int temp = 0;
      for(int j = i; j > 0; j--){
	temp += 0;
      }
    }
    if(i >= last) break;
    }*/
  return 0;
}
