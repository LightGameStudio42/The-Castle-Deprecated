#include<iostream>
int getMission(int x)
{
	int mission = 0;
	return mission;//�-��� ���������� ����� ������
}

/////////////////////////////////////����� ������/////////////////////////////////
std::string getTextMission(int currentMission) {

	std::string missionText = "";//����� ������ � ��� �������������

	switch (currentMission)//����������� ����� ������ � � ����������� �� ���� ���������� missionText ������������� ��������� �����
	{
	case 0: missionText = "\n��������� ���� � \n���������� � ����"; break;
	case 1: missionText = "\nMission 1\n\n��� ���� ������\n ������, ��\n ���� ������ \n���� ����� ���������\n ... ���-���-��� ..."; break;
	case 2: missionText = "\nMission 2\n ���������� ������\n ���������� �������,\n ����� ������ ������ "; break;
	case 3: missionText = "\n� ��� ����� \n� ���� ��������....."; break;
	}

	return missionText;
};