#ifndef Enemy_HPP
#define Enemy_HPP
#include <math.h>
#include <iostream>
#include <sstream>
#define _USE_MATH_DEFINES

class Enemy{
	public:
		std::string Name;
		sf::Image Image;
		std::string ImageLoc;
		sf::Image iBullet; //bullet image
		int bSpeed;
		sf::Sprite Sprite;
		int Health;
		int x, y;
		int sX, sY;
		int Speed;
		bool Active;
		//Weapon
		//Armor
		//Stats
		//Abilities
		Enemy(){
		}
		Enemy(std::string f){
			ImageLoc = f;
			Image.LoadFromFile(f);
			Sprite.SetImage(Image);
			iBullet.LoadFromFile("Images/Bullet.png");
			x = Sprite.GetPosition().x;
			y = Sprite.GetPosition().y;
			sX = Sprite.GetSize().x/2;
			sY = Sprite.GetSize().y/2;
			Sprite.SetCenter(sX, sY);
			Active = true;
			Speed = 200;
			bSpeed = 400;
		}
		void SetSpriteImage(std::string f){
			ImageLoc = f;
			Image.LoadFromFile(f);
			Sprite.SetImage(Image);
			x = Sprite.GetPosition().x;
			y = Sprite.GetPosition().y;
			sX = Sprite.GetSize().x/2;
			sY = Sprite.GetSize().y/2;
			Sprite.SetCenter(sX, sY);
		}
		bool Sight(){
			
		}
		std::string Ai(Player& g, double& t, float e){
			int x1 = g.Sprite.GetPosition().x, x2 = Sprite.GetPosition().x, y1 = g.Sprite.GetPosition().y, y2 = Sprite.GetPosition().y;
			double aA = x1 - x2;
			double aB = y1 - y2;
			double aC = sqrt(pow(aA, 2) + pow(aB,2));
			double angle = atan2(aA, aB);
			int rot = Sprite.GetRotation();
			double vis = abs(angle*(180/M_PI)+180);
			double angRot = abs(vis-rot);
			double sAngRot = sin((vis-rot)*(M_PI/180));
			std::stringstream ss;
			if(aC <= 448){
				if(angRot <= 45 || angRot >= 315){
					if(sAngRot > 0){//left
						Sprite.Rotate(66*e);
					}
					else if(sAngRot < 0){//right
						Sprite.Rotate(-66*e);
					}
					else if(aC >= 192){
						Sprite.Move(sin(angle) * 200*e, cos(angle) * 200*e);
					}
				}
			}
						
			
			ss << "\nangRot: " << angRot << "\nsin(angRot): " << sin((vis-rot)*(M_PI/180));
			return ss.str();
		}
	protected:
};

#endif // Enemy_HPP
