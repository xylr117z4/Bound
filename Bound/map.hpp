#ifndef MAP_HPP
#define MAP_HPP
#include "Player.hpp"
#include "Enemy.hpp"
#include <stdlib.h>
#include <time.h>

class Map{
	
	struct Tile{
		int x, y;
	};
	
	public:
		int mArray[50][50];
		int tS;
		sf::Vector2f Spawn;
		sf::Sprite M[50][50];
		sf::Image iG;
		sf::Image iB;
		
		Map(){
			iG.LoadFromFile("Images/G.png");
			iB.LoadFromFile("Images/B.png");
			tS = 128;
		}
		void WallCheck(Player& a,sf::View& v, float e){
			int pX = a.Sprite.GetPosition().x;		
			int pY = a.Sprite.GetPosition().y;
			int gPX = pX/128;
			int gPY = pY/128;
			int dY = tS/2+a.sY;
			int dX = tS/2+a.sX;
			
			if(mArray[gPX][gPY-1] == 0 && abs(pY-M[gPX][gPY-1].GetPosition().y) <= dY){
				a.Sprite.Move(0,a.Speed*e);
				v.Move(0,a.Speed*e);
			}
			if(mArray[gPX][gPY+1] == 0 && abs(pY-M[gPX][gPY+1].GetPosition().y) <= dY){
				a.Sprite.Move(0,-a.Speed*e);
				v.Move(0,-a.Speed*e);
			}
			if(mArray[gPX-1][gPY] == 0 && abs(pX-M[gPX-1][gPY].GetPosition().x) <= dX){
				a.Sprite.Move(a.Speed*e,0);
				v.Move(a.Speed*e,0);
			}
			if(mArray[gPX+1][gPY] == 0 && abs(pX-M[gPX+1][gPY].GetPosition().x) <= dX){
				a.Sprite.Move(-a.Speed*e,0);
				v.Move(-a.Speed*e,0);
			}								
		}
		void WallCheck(Enemy& a, float e){
			int pX = a.Sprite.GetPosition().x;		
			int pY = a.Sprite.GetPosition().y;
			int gPX = pX/128;
			int gPY = pY/128;
			int dY = tS/2+a.sY;
			int dX = tS/2+a.sX;
			
			if(mArray[gPX][gPY-1] == 0 && abs(pY-M[gPX][gPY-1].GetPosition().y) <= dY){
				a.Sprite.Move(0,a.Speed*e);
			}
			if(mArray[gPX][gPY+1] == 0 && abs(pY-M[gPX][gPY+1].GetPosition().y) <= dY){
				a.Sprite.Move(0,-a.Speed*e);
			}
			if(mArray[gPX-1][gPY] == 0 && abs(pX-M[gPX-1][gPY].GetPosition().x) <= dX){
				a.Sprite.Move(a.Speed*e,0);
			}
			if(mArray[gPX+1][gPY] == 0 && abs(pX-M[gPX+1][gPY].GetPosition().x) <= dX){
				a.Sprite.Move(-a.Speed*e,0);
			}								
		}
		int GenC(int tC){
			for(int i = 0; i < 50; ++i){
				for(int c = 0; c < 50; ++c){
					mArray[i][c] = 0;
					sf::Image Blank;
					Blank.Create(1,1,sf::Color(100,100,100,255));
					M[i][c].SetImage(Blank);
				}
			}
    		bool Gen = true;   
			srand (time(NULL));
    		int aX = 24;
			int aY = 24;
			int cT = 0;
			int r = 0, r2 = 0, cn = 0;
			
			while(Gen){			
				Spawn.x = 0;
				Spawn.y = 0;		
			 	r = rand() % 4;
				
				if(r == 0 && aY > 1){ //up
					aY -= 1;
					tC -= 1;
				}
				else if(r == 1 && aX > 1){ //left
					aX -= 1;
					tC -= 1;
				}
				
				else if(r == 2 && aY < 48){ //down		
					aY += 1;
					tC -= 1;
				}
				else if(r == 3 && aX < 48){ //right
					aX += 1;
					tC -= 1;
				}
				mArray[aX][aY] = 1;
				if(tC == 0){
					r2 = rand() % 8;
					if(r2 > 0){
						++cn;
						tC = 50;
					}
					else{
						Gen = false;
					}
				}	
			}
			std::cout << cn << "\n";
			bool pS = true;
			
			for(int i = 0; i < 50; ++i){
				for(int c = 0; c < 50; ++c){
					if(mArray[i][c] == 1){
						if(pS){
							Spawn.x = (i*tS+tS/2);
							Spawn.y = (c*tS+tS/2);
							pS = false;
						}
						M[i][c].SetImage(iG);
						cT += 1;
					}
					else if(mArray[i][c] == 0){
						int x = 0;
						int y = 0;
						M[i][c].SetImage(iB);
						if(mArray[i-1][c] == 1 && mArray[i+1][c] == 1){
							x = 2;
						}
						else if(mArray[i-1][c] == 1){//left
							x = -1;
						}
						else if(mArray[i+1][c] == 1){//right
							x = 1;
						}
						if(mArray[i][c-1] == 1 && mArray[i][c+1] == 1){
							y = 2;
						}
						else if(mArray[i][c-1] == 1){//Up
							y = -1;
						}
						else if(mArray[i][c+1] == 1){//down
							y = 1;
						}

						sf::Rect<int> Tile(0,0,128,128);
					
					
						switch(x){
							case -1: //left
								Tile.Offset(0,0);
								break;
							case 0: //middle
								Tile.Offset(128, 0);
								break;
							case 1: //right
								Tile.Offset(256,0);
								break;
							case 2: //both
								Tile.Offset(384,0);
								break;
						}
						switch(y){
							case -1: //left
								Tile.Offset(0,0);
								break;
							case 0: //middle
								Tile.Offset(0,128);
								break;
							case 1: //right
								Tile.Offset(0,256);
								break;
							case 2: //both
								Tile.Offset(0,384);
								break;
						}
						M[i][c].SetSubRect(Tile);
					}
					
					if(i==0 && c == 0){
						M[i][c].SetPosition(64,64);
					}
					else{
						M[i][c].SetPosition((i*tS+tS/2),(c*tS+tS/2)); 
					}					
					M[i][c].SetCenter(tS/2,tS/2);
				}
			}
			return cT;
		}
	protected:
};

#endif // MAP_HPP

