#include <iostream>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "Map.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Save.hpp"
#include "bTracker.hpp"

int main(int argc, char *argv[]) {
	
    sf::RenderWindow App(sf::VideoMode(800, 600), "Bound");
    //App.UseVerticalSync(true);
    
    sf::Vector2f Center(400,300);
	sf::Vector2f HalfSize(400,300);
	sf::View vDefault(Center, HalfSize);
	
	Map Level;
    
    const sf::Input& Input = App.GetInput();
    bool gameIsRunning = false;
    
    sf::Font Arial;
    Arial.LoadFromFile("arial.ttf"); 
    
    
//Main Menu
    while (App.IsOpened())
    {        
        sf::Event Event;
        App.ShowMouseCursor(true);
        while (App.GetEvent(Event))
        {
            if ((Event.Type == sf::Event::Closed) || (Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
                 App.Close();
			}
        }
        
        int mX = Input.GetMouseX();
        int mY = Input.GetMouseY();
        
        sf::String Text("", Arial, 20);
        
        
    //Game
    	if(gameIsRunning){
			Save saver;
			Player guy("Images/Player.png");
			guy.Name = "xylr";
			guy.Health = 100;		
			//Player guy;
			//saver.LoadGuy("xylr", guy);
			Enemy baddy("Images/Enemy.png");
			baddy.Name = "baddy";
			baddy.Health = 100;
			sf::Image iSight;
			iSight.LoadFromFile("Images/Sight.png");
			sf::Sprite Sight(iSight);
			Sight.SetCenter(8,8);
			App.ShowMouseCursor(false);
			sf::View View(Center, HalfSize);
			//View.Zoom(0.1f);
			App.SetView(View);
			int sX, sY,tC;
			sX = sY = 50;
			tC = 500;
			sf::Shape badOut = sf::Shape::Circle(0, 0, 448, sf::Color(0,100,0,0), 1, sf::Color(0,100,0,255));
			sf::Shape badIn = sf::Shape::Circle(0, 0, 192, sf::Color(0,100,0,0), 1, sf::Color(100,0,0,255));
			sf::Shape badVis1 = sf::Shape::Line(0, 448, 0, 0, 1, sf::Color(0,0,100,255), 0, sf::Color(0,0,0,0));
			sf::Shape badVis2 = sf::Shape::Line(0, 448, 0, 0, 1, sf::Color(0,0,100,255), 0, sf::Color(0,0,0,0));
			baddy.Sprite.SetRotation(0);
			//int cT = Level.GenD(tC);
			int cT = Level.GenC(tC);
			guy.Sprite.SetPosition(Level.Spawn);
			baddy.Sprite.SetPosition(Level.Spawn.x+128,Level.Spawn.y);
			int vX, vY;
			vX = Level.Spawn.x-300;
			vY = Level.Spawn.y-300;
			View.Move(vX,vY);
			bTracker Bills;
			double fireCD = 0;
			float sec = 0;
			int fps = 0;
			double tim = 1;
			
        	while(gameIsRunning){
				float Elapsed = App.GetFrameTime();
				
				mX = Input.GetMouseX();
        		mY = Input.GetMouseY();
        		
        		sf::Vector2f mP = App.ConvertCoords(mX, mY);
				
				double aX = guy.Sprite.GetPosition().x - Sight.GetPosition().x;
				double aY = guy.Sprite.GetPosition().y - Sight.GetPosition().y;	
				double angle = atan2(aY,aX);	
				
				int lX = 0;
				int lY = 0;
				
				if(sec <= 0){
				std::cout << "fps: " << fps << "\n";
				sec = 1;
				fps = 0;
				}
				else if(sec > 0){
					sec -= Elapsed;
					++fps;
				}
				
				if(Input.IsKeyDown(sf::Key::W)){
					guy.Sprite.Move(0,-guy.Speed*Elapsed);
					View.Move(0,-guy.Speed*Elapsed);
				}
				if(Input.IsKeyDown(sf::Key::S)){
					guy.Sprite.Move(0,guy.Speed*Elapsed);
					View.Move(0,guy.Speed*Elapsed);
				}
				if(Input.IsKeyDown(sf::Key::A)){
					guy.Sprite.Move(-guy.Speed*Elapsed,0);
					View.Move(-guy.Speed*Elapsed,0);
				}
				if(Input.IsKeyDown(sf::Key::D)){
					guy.Sprite.Move(guy.Speed*Elapsed,0);
					View.Move(guy.Speed*Elapsed,0);
				}
				if(Input.IsMouseButtonDown(sf::Mouse::Left) && fireCD == 0){
					Bills.FireNew(guy, guy.bSpeed, angle);
					fireCD = 0.25;
				}
				if(fireCD > 0){
					fireCD -= Elapsed;
				}
				else if(fireCD < 0){
					fireCD = 0;
				}
				if(Input.IsKeyDown(sf::Key::Down)){
					baddy.Sprite.SetRotation(0);
				}
				if(Input.IsKeyDown(sf::Key::Left)){
					baddy.Sprite.Rotate(45*Elapsed);
				}
				if(Input.IsKeyDown(sf::Key::Right)){
					baddy.Sprite.Rotate(-45*Elapsed);
				}
				guy.Sprite.SetRotation(-angle * (180/3.14) + 90);
				Sight.SetPosition(mP);
				Bills.Update(Elapsed);
				Bills.WallCheck(Level);
				Bills.HitCheck(guy);
				Bills.HitCheck(baddy);
				Level.WallCheck(guy,View,Elapsed);
				Level.WallCheck(baddy,Elapsed);
				badIn.SetPosition(baddy.Sprite.GetPosition().x, baddy.Sprite.GetPosition().y);
				badOut.SetPosition(baddy.Sprite.GetPosition().x, baddy.Sprite.GetPosition().y);
				badVis1.SetPosition(baddy.Sprite.GetPosition().x, baddy.Sprite.GetPosition().y);
				badVis2.SetPosition(baddy.Sprite.GetPosition().x, baddy.Sprite.GetPosition().y);
				badVis1.SetRotation(135+baddy.Sprite.GetRotation());
				badVis2.SetRotation(225+baddy.Sprite.GetRotation());
					
				while (App.GetEvent(Event))
        		{
            		if((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)){
            	    	gameIsRunning = false;
					}
        		}
				
				std::stringstream ss;
   				ss << "mX: " << mX << "\nmY: " << mY << "\ncT: " << cT << "\n";
				
				if(baddy.Active){
					ss << baddy.Ai(guy, tim, Elapsed);	
				}
				
   				std::string mC = ss.str();    				
   				        
        		Text.SetText(mC);
        		sf::Vector2f tP = App.ConvertCoords(0,0);
        		Text.SetPosition(tP);
				
				App.Clear();
				int gX = (int)guy.Sprite.GetPosition().x/128, gY = (int)guy.Sprite.GetPosition().y/128;
				//sX, sY				
				for(int i = gX-4; i < gX+5; ++i){
					for(int c = gY-3; c < gY+4; ++c){
						App.Draw(Level.M[i%50][c%50]);
					}
				}
				for(int i = 0; i < 1000; ++i){
					if(Bills.Bullets[i].Active){
						App.Draw(Bills.Bullets[i].Sprite);
					}
				}
				if(guy.Active){
					App.Draw(guy.Sprite);
				}
				if(baddy.Active){
					App.Draw(baddy.Sprite);
					App.Draw(badIn);
					App.Draw(badOut);
					App.Draw(badVis1);
					App.Draw(badVis2);
				}
				
				App.Draw(Sight);
				App.Draw(Text);
				App.Display();
			}
			saver.SaveGuy(guy);
			App.SetView(vDefault);			
		}
		
		std::stringstream ss;
   		ss << "mX: " << mX << "\nmY: " << mY;
   		std::string mC = ss.str(); 
         
        App.Clear();
        Text.SetText("Start!");
        Text.SetPosition(25,150);
        
        if(mX > 25 && mX < 72 && mY > 155 && mY < 170){
			Text.SetColor(sf::Color(255,0,0));
			if(Input.IsMouseButtonDown(sf::Mouse::Left)){
				gameIsRunning = true;
			}
		}
		
        App.Draw(Text); 
        Text.SetText(mC);
        Text.SetPosition(0,0);
        Text.SetColor(sf::Color(255,255,255));
        App.Draw(Text);        
        App.Display();
    }
}
