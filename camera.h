#include<SFML\Graphics.hpp>
#define Width 1024
#define Height 768 
using namespace sf;
sf::View view;
View SetCamera(float x, float y)
{
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < Width / 2.00001) tempX = Width / 2.00001;//������� �� ���� ����� �������
	if (y < Height / 2) tempY = Height/2;//������� �������
	if (y > Height * 2.41) tempY = Height*2.41;//������ ������� 
	if (x > Width * 2)tempX = Width * 2;

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
	return view;
}