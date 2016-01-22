#ifndef bTracker_HPP
#define bTracker_HPP
#include "Player.hpp"
#include "Enemy.hpp"
#include <math.h>

class bTracker{
	
	struct Bullet{
		sf::Sprite Sprite;
		int Speed;
		double Direction;
		std::string Owner;
		bool Active;
	};
	
	public:
		Bullet Bullets[1000];
		int bNum;
		
		bTracker(){
			bNum = 0;
			for(int i = 0; i < 1000; ++i){
				Bullets[i].Active = false;
			}
		}
		int FindInactive(){
			for(int i = 0; i < 1000; ++i){
				if(!Bullets[i].Active){
					return i;
				}
			}
			return -1;
		}
		void FireNew(Player& p, int speed, double angle){
			int i = FindInactive();
			if(i != -1){
				Bullets[i].Active = true;
				Bullets[i].Owner = p.Name;
				Bullets[i].Sprite.SetImage(p.iBullet);
				Bullets[i].Sprite.SetPosition(p.Sprite.GetPosition().x, p.Sprite.GetPosition().y);
				Bullets[i].Sprite.SetCenter(16,16);
				Bullets[i].Speed = speed;
				Bullets[i].Direction = angle;
				bNum += 1;
			}else{ std::cout << "TOO MANY!!!\n"; }
		}
		void FireNew(Enemy& e, int speed, double angle){
			int i = FindInactive();
			if(i != -1){
				Bullets[i].Active = true;
				Bullets[i].Owner = e.Name;
				Bullets[i].Sprite.SetImage(e.iBullet);
				Bullets[i].Sprite.SetPosition(e.Sprite.GetPosition().x, e.Sprite.GetPosition().y);
				Bullets[i].Sprite.SetCenter(16,16);
				Bullets[i].Speed = speed;
				Bullets[i].Direction = angle;
				bNum += 1;
			}else{ std::cout << "TOO MANY!!!\n"; }
		}
		void Update(double e){
			//std::cout << "Number of bullets: " << bNum << "\n";
			for(int i = 0; i < 1000; ++i){
				if(Bullets[i].Active){
					Bullets[i].Sprite.Move(cos(Bullets[i].Direction) * -Bullets[i].Speed*e, sin(Bullets[i].Direction) * -Bullets[i].Speed*e);
				}
			}
		}
		void Remove(int i){
			Bullets[i].Active = false;
			bNum -= 1;
		}
		void HitCheck(Player& p){
			if(p.Active){
				for(int i = 0; i < 1000; ++i){
					if(Bullets[i].Active && Bullets[i].Owner != p.Name){
						int x1 = p.Sprite.GetPosition().x,x2 = Bullets[i].Sprite.GetPosition().x, y1 = p.Sprite.GetPosition().y,y2 = Bullets[i].Sprite.GetPosition().y;
						if(abs((int)(sqrt(pow(x2 - x1,2) + pow(y2 - y1,2))) <= 32)){
							Remove(i);
							p.Health -= 10;
							if(p.Health <= 0){
								p.Active = false;
							}
							std::cout << p.Health << "\n";
						}
					}
				}
			}
		}
		void HitCheck(Enemy& e){
			if(e.Active){
				for(int i = 0; i < 1000; ++i){
					if(Bullets[i].Active && Bullets[i].Owner != e.Name){
						int x1 = e.Sprite.GetPosition().x,x2 = Bullets[i].Sprite.GetPosition().x, y1 = e.Sprite.GetPosition().y,y2 = Bullets[i].Sprite.GetPosition().y;
						if(abs((int)(sqrt(pow(x2 - x1,2) + pow(y2 - y1,2))) <= 32)){
							Remove(i);
							e.Health -= 10;
							if(e.Health <= 0){
								e.Active = false;
							}
							std::cout << e.Health << "\n";
						}
					}
				}
			}
		}
		void WallCheck(Map& map){
			int pX, pY, gPX, gPY, d,disX1, disX2, disY1, disY2;
			for(int i = 0; i < 1000; ++i){
				if(Bullets[i].Active){
					pX = Bullets[i].Sprite.GetPosition().x;		
					pY = Bullets[i].Sprite.GetPosition().y;
					gPX = pX/128;
					gPY = pY/128;
					d = map.tS/2+16;
				
					disY1 = pY-map.M[gPX][gPY-1].GetPosition().y;
					disY2 = pY-map.M[gPX][gPY+1].GetPosition().y;
					disX1 = pX-map.M[gPX-1][gPY].GetPosition().x;
					disX2 = pX-map.M[gPX+1][gPY].GetPosition().x;
				
					if(map.mArray[gPX][gPY-1] == 0 && abs(disY1) <= d){
						Remove(i);
					}
					else if(map.mArray[gPX][gPY+1] == 0 && abs(disY2) <= d){
						Remove(i);
					}
					else if(map.mArray[gPX-1][gPY] == 0 && abs(disX1) <= d){
						Remove(i);
					}
					else if(map.mArray[gPX+1][gPY] == 0 && abs(disX2) <= d){
						Remove(i);
					}
				}
			}
		}
	protected:	
};

#endif
