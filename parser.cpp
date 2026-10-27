#include"parser.hpp"

#include<iostream>
#include<vector>
#include<sstream>
#include<string>
using namespace std;

vector<string> separar(string linea)
{
  vector<string> tokens;
  for(size_t i = 0; i < linea.size(); i++)
  {
    if(linea[i] == ',' || linea[i] == ' ' || linea[i] == '\r' || linea[i] == '\t') continue;

    if(linea[i] == '\'')
    {
      i++;
      string token = "";

      while(i < linea.size() && linea[i] != '\'')
      {
        token += linea[i];
        i++;
      }
      // i queda en la comilla de cierre; el i++ del for la salta
      tokens.push_back(token);
    }
    else
    {
      string token = "";

      while(i < linea.size() && linea[i] != ' ' && linea[i] != ',' && linea[i] != '\r' && linea[i] != '\t')
      {
        token += linea[i];
        i++;
      }
      tokens.push_back(token);
    }
  }
  return tokens;
}