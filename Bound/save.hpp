#ifndef SAVE_HPP
#define SAVE_HPP
#include <iostream>
#include <fstream>

using namespace std;

class Save{
	public:
		Save(){
		}
		void SaveGuy(Player p){
			//equipment
			//stats
			//abilities
			stringstream location;
			location << "Guys/" << p.Name << ".dude";
			string loc = location.str();
			ofstream writer(loc.c_str());
			writer << "Name:" << p.Name << "\nHealth:" << p.Health << "\nImage:" << p.ImageLoc;
  			writer.close();			
		}
		void SaveGuy(Enemy p){
			//equipment
			//stats
			//abilities
			stringstream location;
			location << "Enemys/" << p.Name << ".dude";
			string loc = location.str();
			ofstream writer(loc.c_str());
			writer << "Name:" << p.Name << "\nHealth:" << p.Health << "\nImage:" << p.ImageLoc;
  			writer.close();
		}
		void LoadGuy(std::string pLoc, Player& p){
			stringstream location;
			location << "Guys/" << pLoc << ".dude";
			string loc = location.str();
			ifstream reader;
			reader.open(loc.c_str());
			string data = "";
			
			if (reader.is_open()){
    			for(int i = 0; i < 3; ++i){
			    	getline(reader,data);
					string stat = data.substr(data.find(":", 0)+1);
					switch(i){
						case 0:
							p.Name = stat;
							break;
						case 1:
							p.Health = atoi(stat.c_str());
							break;
						case 2:
							p.ImageLoc = stat;
							p.SetSpriteImage(stat);
							break;
					}
    			}
  			}  			
  			reader.close();
		}
		void LoadGuy(std::string pLoc, Enemy& p){
			stringstream location;
			location << "Enemys/" << pLoc << ".dude";
			string loc = location.str();
			ifstream reader;
			reader.open(loc.c_str());
			string data = "";
			
			if (reader.is_open()){
    			for(int i = 0; i < 3; ++i){
			    	getline(reader,data);
					string stat = data.substr(data.find(":", 0)+1);
					switch(i){
						case 0:
							p.Name = stat;
							break;
						case 1:
							p.Health = atoi(stat.c_str());
							break;
						case 2:
							p.ImageLoc = stat;
							p.SetSpriteImage(stat);
							break;
					}
    			}
  			}  			
  			reader.close();
		}
	protected:
};

#endif // SAVE_HPP
