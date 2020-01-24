//Boyer-Moore法のHorspoolとSundayアルゴリズムの実装
//テキスト中からパターンにマッチする箇所を出力する(0-indexed)
//アスキーコード中の33('!') ~ 126('~')番目までの文字を入力として受け取ることを想定している

#include <iostream>
#include <string>
#include <map>

void HorspoolAlgorithm(std::string const &text, std::string const &pattern){

  int text_size = text.length(), pattern_size = pattern.length();

  //テキストのサイズよりパターンのサイズが大きい場合
  if(text_size < pattern_size){
    return;
  }

  //ずらし表
  std::map<char, int> table;

  for(char i = '!'; i <= '~'; ++i){
    table[i] = pattern_size;
  }

  for(int i = 0; i < pattern_size - 1; ++i){
    table[pattern[i]] = pattern_size - i - 1;
  }

  //探索
  int i = 0;
  while(i <= text_size - pattern_size){
    int j = pattern_size - 1;

    while(j >= 0 && text[i+j] == pattern[j]){
      j--;
    }
    
    if(j == -1){
      std::cout << i << std::endl;
    }
    
    i += table[text[i+pattern_size-1]];
  }

}

void SundayAlgorithm(std::string const &text, std::string const &pattern){

  int text_size = text.length(), pattern_size = pattern.length();

  //テキストのサイズよりパターンのサイズが大きい場合
  if(text_size < pattern_size){
    return;
  }

  //ずらし表
  std::map<char, int> table;

  for(char i = '!'; i <= '~'; ++i){
    table[i] = pattern_size;
  }

  for(int i = 0; i < pattern_size; ++i){
    table[pattern[i]] = pattern_size - i;
  }

  //探索
  int i = 0;
  while(i <= text_size - pattern_size){
    int j = pattern_size - 1;

    while(j >= 0 && text[i+j] == pattern[j]){
      j--;
    }
    
    if(j == -1){
      std::cout << i << std::endl;
    }
    
    if(i + pattern_size < text_size){
      i += table[text[i+pattern_size]];
    }else{
      break;
    }
  }

}

void BoyerMoore(std::string const &text, std::string const &pattern, int algorithm){
  if(algorithm == 0){
    HorspoolAlgorithm(text, pattern);
  }else if(algorithm == 1){
    SundayAlgorithm(text, pattern);
  }
}

int main(int argc, char *argv[]){

  int algorithm = 0;
  std::string text, pattern;

  //BMのアルゴリズの選択(デフォルトではHorspool)
  if(argc == 2){
    std::string s = argv[1];
    if(s != "0" && s != "1"){
      std::cerr << "Usage: program [algorithm (0: Horspool, 1:Sunday)]" << std::endl;
      return 2;
    }
    algorithm = stoi(s);
  }else if(argc > 2){
    std::cerr << "Usage: program [algorithm (0: Horspool, 1:Sunday)]" << std::endl;
    return 2;
  }

  std::cin >> text >> pattern;
  
  BoyerMoore(text, pattern, algorithm);
  
  return 0;
}
