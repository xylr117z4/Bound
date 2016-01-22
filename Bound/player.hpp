#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player{
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
		Player(){
		}
		Player(std::string f){
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
			Speed = 300;
			bSpeed = 600;
		}
		void Update(){
			
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
	protected:
};

#endif // PLAYER_HPP
