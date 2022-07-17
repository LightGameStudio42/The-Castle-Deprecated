#include<SFML\Graphics.hpp>
#include<sfml/Audio.hpp>
#include"map.h"
#include"camera.h"
#include"Missions.h"
#include<cstring>
#include<iostream>
#include<sstream>
#include<conio.h>

#define STAY 5
#define FIGHT 4
#define LEFT 3 
#define UP 0
#define DOWN 2
#define RIGHT 1
#define DRAGON 6
#define MENU 7

#define DRAGON_ACTION 0
#define PLAYER_ACTION 1

//for inventory[]
#define POTION 1// 0-nothing
#define ALUMINIUM 2
#define ALUMINIUM 3
#define BRONZE 4
#define SILVER 5
#define GOLD 6

using namespace std;
using namespace sf;

int Action = PLAYER_ACTION;
bool isMenu = false;
bool isLife=true;
bool isShowQuest = true;
int NumberOfDragon;//number of dragon for fight
int CountDragons = 40;

int inventory[8] = {0,0,0,0,0,0,0,0};
struct Item
{
//	enum object {aluminium, bronze, gold, silver,};//+iron
};
class Dragons
{
public:
	int x, y;
    int damage;
	int lives;
	Text strLive;
	Dragons(){};
	Dragons(int X, int Y, int D, int L)
	{
		x = X, y = Y, damage = D, lives = L;
	};
};
class Player
{
public:

#pragma region r1
	int State = 0;
	float x, y, dx, dy, speed = 0;
	int w, h;
	int Cash = 0;
	int dir = 0;
	string File;
	Image image;
	Texture texture;
	Sprite sprite;
	int live;
	int Damage;
	Text strLive;
#pragma endregion r1
	Player(){};
	Player(string F, float X, float Y, int W, int H)
	{
		File = F;
		x = X; y = Y;
		w = W; h = H;
		image.loadFromFile(File);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		live = 12;
		Damage = 3;
	};
	void input()
	{
		if (Keyboard::isKeyPressed(Keyboard::A))
		{
			State = LEFT;
			dir = 1; speed = 0.2f;
		};
		 if (Keyboard::isKeyPressed(Keyboard::D)) //ВПРАВО
		{
			State = RIGHT;
			dir = 0; speed = 0.2f;
		};
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			State = UP;
			dir = 2; speed = -0.2f;
		};
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			State = DOWN;
			dir = 3; speed = -0.2f;
		};
	}
};
struct Object
{
	Image image;
	Texture texture;
	Sprite sprite;
	 string name;
	Object( string NAME)
	{
		name = NAME;
		image.loadFromFile(name);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
	}
};
class GameEngine
{
public:
	int GameState=0;
	float frame = 0;
	Player player;
	Dragons* dragon[40];
	Object Map;
	Object Castle;
	Object Menu;
	Object Menu2;
	Object Lose;
	Object Inventory;
	Object King;
	Object Text1;
	Object Guide;
	GameEngine() : player(Player("images//knight2.png", 128, 128, 51, 64)),
		Map("images/map.png"), Castle("images/castle.png"),
		Menu("images/menu.png"), Menu2("images/menu2.png"),
		Lose("images/lose.png"), Inventory("images/inventory.png"), King("images/king.png"),
		Text1("images/text1.png"), Guide("images/guide.png")
	{
		player.sprite.setTexture(player.texture);
		//
		//Inventory.sprite.scale(0.5f, 0.5f);
		
	}//Костыль

    bool fight(Dragons *FightDragon)
{
	if (Action==PLAYER_ACTION)
	{
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			FightDragon->lives -= random(player.Damage);
			if (FightDragon->lives <= 0)
			{
				player.speed = 0;
				//iDROP
				TileMap[FightDragon->x][FightDragon->y] = ' ';
				if (random(3) == 1){ TileMap[FightDragon->x + random(2)][FightDragon->y + random_tmp(2) - 3] = 'p'; inventory[0] = POTION; }
				else if (random(2)){ TileMap[FightDragon->x][FightDragon->y] = '0'; }
				delete FightDragon;
				CountDragons--;
				player.State = LEFT;//not fight
			}
			Action = DRAGON_ACTION;
		}
	}//Player action
			 if (Action == DRAGON_ACTION && FightDragon->lives>0)
			{
				//ИИ ДРАКОНА
				Sleep(90);
				player.live -= random(FightDragon->damage);
				if (player.live <= 0){ player.live = 0; isLife = false; }
				Action = PLAYER_ACTION;
			}
		return 0;
}
	void Init()
	{
		generate();
		for (int k = 0; k < CountDragons; k++)
		{
			dragon[k] = new Dragons(random(33) + 1, random(39)+1, random(2) + 2, random(5) + 6);
			TileMap[dragon[k]->x][dragon[k]->y] = 'd';
		}

	}
	int Update(int time)	
		{
			for (int i = player.y / BlockSize; i < (player.y + player.h) / BlockSize; i++)
			{
				for (int j = player.x / BlockSize; j < (player.x + player.w) / BlockSize; j++)
					
				{
	#pragma region  if(TileMap[i][j]=='0')
					if (TileMap[i][j] == '0')//Камень
					{
						if (player.dy > 0)//если мы шли вниз
						{
							player.y = i * BlockSize - player.h;//смопорим Y персонажа. сначала получаем коорд квадратa на карте(стены),  вычитаем из h персонажа.
						}
						if (player.dy < 0)
						{
							player.y = i * BlockSize + BlockSize;//аналогично с ходьбой вверх. dy<0,=> мы идем вверх
						}
						if (player.dx > 0)
						{
							player.x = j * BlockSize - player.w;//если идем вправо, то координата Х = стена 0минус ширина персонажа
						}
						if (player.dx < 0)
						{
							player.x = j * BlockSize + BlockSize;//аналогично идем влево
						}
					}//Камень
	#pragma endregion if(TileMap[i][j]=='0')
	#pragma region else if(TileMap[i][j]=='d')
					if (TileMap[i][j] == 'd')
					{
						for (int k = 0; k < 40; k++)
						{
							if (dragon[k]->y == j && dragon[k]->x == i)
							{
								player.State = FIGHT;
								NumberOfDragon = k;
							}; 
	
						}
					}
	#pragma endregion if(TileMap[i][j]=='d')
	#pragma region else if(TileMap[i][j]=='s')
					if (TileMap[i][j] == 's')
					{
						player.Cash++;
						TileMap[i][j] = ' ';
					}
	#pragma endregion if(TileMap[i][j]=='s')
#pragma region else if(TileMap[i][j]=='p')
					else if (TileMap[i][j] == 'p')
					{ 
						inventory[0]+=1;
						TileMap[i][j] = ' ';
					}
#pragma endregion else if(TileMap[i][j]=='p')
				}
			}
			switch (player.State)
			{
			case FIGHT:fight(dragon[NumberOfDragon]); return dragon[NumberOfDragon]->lives; break;
			case RIGHT:player.sprite.setTextureRect(IntRect(15, 128, 36, 64)); player.dx = player.speed; player.dy = 0; break;
			case LEFT:player.sprite.setTextureRect(IntRect(0, 192, 36, 64)); player.dx = -player.speed; player.dy = 0;   break;
			case UP:player.sprite.setTextureRect(IntRect(0, 64, 51, 64)); player.dx = 0; player.dy = player.speed;   break;
			case DOWN:player.sprite.setTextureRect(IntRect(0,0,51,64)); player.dx = 0; player.dy = -player.speed;   break;
			case MENU:; break;
			}
	
			player.x += player.dx*time;
			player.y += player.dy*time;
	
			player.speed = 0;
			player.sprite.setPosition(player.x, player.y);
		}
	void render(RenderWindow &window)
	{
		Inventory.sprite.setPosition(view.getCenter().x - 240, view.getCenter().y +320);//view.getCenter().y + 320);
		window.draw(Inventory.sprite);
		if (inventory[0] >= 1)
		{
			Map.sprite.setTextureRect(IntRect(256, 0, BlockSize, BlockSize));
			Map.sprite.setPosition(view.getCenter().x - 240, view.getCenter().y + 320);//240 320
			window.draw(Map.sprite);
		}
		window.draw(player.sprite);
		if (isMenu)
		{
			Menu2.sprite.setPosition(view.getCenter().x +316, view.getCenter().y - 350);//316 350
			window.draw(Menu2.sprite);
		}
		if (isShowQuest)
		{ 
			King.sprite.setPosition(view.getCenter().x - 240, view.getCenter().y + 224);//240 224
			window.draw(King.sprite);
			if (CountDragons > 37){
				Text1.sprite.setPosition(view.getCenter().x - 144, view.getCenter().y + 224);//144 224
				window.draw(Text1.sprite);
			}
			else{
				Guide.sprite.setPosition(view.getCenter().x -144, view.getCenter().y + 224); window.draw(Guide.sprite);
				window.draw(Guide.sprite);
			}
		}//if (isShowQuest)


		if (!isLife){ Lose.sprite.setPosition(view.getCenter().x - 200, view.getCenter().y - 150); window.draw(Lose.sprite); }//200 150
	}
};
int main()
{
	RenderWindow window(sf::VideoMode(933, 700), "The Castle");  //Инициализация окна
	view.reset(sf::FloatRect(0, 0, Width, Height));
	
	//window.setSize(Vector2u(800, 600));
	//-sf::SoundBuffer buffer;
	//buffer.loadFromFile()

	GameEngine game;
	game.Init();  //Game init

	Clock clock;

	Font font;                             
	font.loadFromFile("Candarab.ttf");
	Text CashText("", font, 31);
	CashText.setStyle(Text::Bold);
	CashText.setColor(Color::Color(20,0,0));

	Text strLive("", font, 28);
	strLive.setColor(Color::Black);
	strLive.setStyle(Text::StrikeThrough);

	Text strDragonLive("", font, 28);
	strDragonLive.setColor(Color::Black);
	strDragonLive.setStyle(Text::StrikeThrough);

	Object Map("images/map.png");    //Загрузка карты
	Object Castle("images/castle.png");//Загрузка  замка
	Object Menu("images/menu.png");

	float Frame = 0;  //Область картинки для спрайта
	
	sf::Event event;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 500;

		while (window.pollEvent(event))
		{
			if (event.type == Event::Resized)
			{window.setSize(Vector2u(800,600));}

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code==Keyboard::Tab)
				{
					if (isShowQuest==true){isShowQuest = false;}
					else if (isShowQuest == false){isShowQuest = true;}
				}//Tab
			}//Key
			if (event.type == Event::MouseButtonPressed)
			{
				
				if (event.key.code == Mouse::Left)
				{
					if (inventory[0] > 0){
						if (IntRect(244,634 , 70, 80).//220 500		
                   	contains(event.mouseButton.x, event.mouseButton.y))
						{
							beep();
							inventory[0]--;
							game.player.live += 2;
						}
					}
					if (IntRect(window.getSize().x - 32, 0, 32, 32).contains(event.mouseButton.x , event.mouseButton.y))
					{
						beep();
						if (!isMenu) { isMenu = true; beep(); }
						else if (isMenu) { isMenu = false; }
					}

				}
			};
				if (event.type == sf::Event::Closed) window.close();
			}
     /////////////////////////////////////////////////////////////////////////////////////////////////////////
		game.player.input();
		game.Update(time);
		window.clear();
 //Map's rendering
		for (int i = 0; i < HEIGHT_MAP; i++){
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == ' ')  Map.sprite.setTextureRect(IntRect(0, 0, BlockSize, BlockSize));
				else if (TileMap[i][j] == '0')  Map.sprite.setTextureRect(IntRect(64, 0, BlockSize, BlockSize));
				else if ((TileMap[i][j] == 's')) Map.sprite.setTextureRect(IntRect(128, 0, BlockSize, BlockSize));
				else if ((TileMap[i][j] == 'd'))  Map.sprite.setTextureRect(IntRect(192, 0, BlockSize, BlockSize));
				if ((TileMap[i][j] == 'p'))
				{
					Map.sprite.setTextureRect(IntRect(0, 0, BlockSize, BlockSize));
					Map.sprite.setPosition(j * BlockSize, i * BlockSize);
					window.draw(Map.sprite); Map.sprite.setTextureRect(IntRect(256, 0, BlockSize, BlockSize));
				}
				Map.sprite.setPosition(j * BlockSize, i * BlockSize);
				window.draw(Map.sprite);
			}
		}

		CashText.setPosition(view.getCenter().x - 500, view.getCenter().y - 370);//позиция всего этого текстового блока 500 370
		CashText.setString("Cash: " + to_string(game.player.Cash));//задаем

		strLive.setPosition(view.getCenter().x - 500, view.getCenter().y +330);//500 370
		strLive.setString("Your Health: " + to_string(game.player.live));

		if (game.player.State == FIGHT){
			strDragonLive.setPosition(view.getCenter().x + 270, view.getCenter().y + 330);//270 330
			strDragonLive.setString("Dragon's health: " + to_string(game.dragon[NumberOfDragon]->lives));
			window.draw(strDragonLive);
		}


		//rrrrrrrrrrrrrrrrrrrendering!
		SetCamera(game.player.x, game.player.y);
		window.setView(view);
		Menu.sprite.setPosition(view.getCenter().x+490, view.getCenter().y-384);//490 384
		game.render(window);
		window.draw(Menu.sprite);
		window.draw(strLive);
		window.draw(CashText);
		window.display();
	}

	return 0;
}
