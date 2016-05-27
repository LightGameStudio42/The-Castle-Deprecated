#include<SFML\Graphics.hpp>
#define Width 1024
#define Height 768 
using namespace sf;
sf::View view;
View SetCamera(float x, float y)
{
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < Width / 2.00001) tempX = Width / 2.00001;//убираем из вида левую сторону
	if (y < Height / 2) tempY = Height/2;//верхнюю сторону
	if (y > Height * 2.41) tempY = Height*2.41;//нижнюю сторону 
	if (x > Width * 2)tempX = Width * 2;

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
	return view;
}