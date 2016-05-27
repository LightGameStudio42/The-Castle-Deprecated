#include <SFML\Graphics.hpp>
#include<standart.h>
const int HEIGHT_MAP = 35;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 
#define BlockSize 64//Размер тексутры
#define BlockSize_2x 2*BlockSize
#define BlockSize_3x 3*BlockSize
#define BlockSize_4x 4*BlockSize

sf::String TileMap[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
};
void generate()
{
	for (int i = 1; i <= HEIGHT_MAP - 2; i++)
 {
		for (int j = 1; j <= WIDTH_MAP - 2; j++)
		{
			if (random(12) == 1) { TileMap[i][j] = 's'; }
			else if(random(30)==1)  { TileMap[i][j] = '0'; }
			else if (random(99) == 1){ TileMap[i][j] = 'p'; }
		}

 }
}