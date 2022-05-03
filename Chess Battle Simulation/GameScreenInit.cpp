#include "GameScreen.h"
#include "TextureHolder.h"
#include "GameSettings.h"
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <iostream>

using namespace std;

Vector2f GameSettings::MAP[8][8];
Node GameSettings::MOVEMENT_MAP[8][8];
FloatRect GameSettings::MAP_BOUNDS = FloatRect(409.f, 131.f, 1105.f, 710.f);
Vector2f GameSettings::SUBMAP[8];
FloatRect GameSettings::SUB_BOUNDS = FloatRect(329.f, 911.f, 1255.f, 143.f);
Model GameSettings::MODELS[6];

void GameScreen::init()
{
	if (!m_GameFirstStart)
		resetGame();
	if (m_GameFirstStart)
	{
		m_panels[0]->timeValue = waitTime;
		m_GameFirstStart = false;

		string line;
		ifstream file;
		ifstream file2;
		ifstream file3;
		file.open("maps/FieldMap.dat");

		string delim = ",";
		string delim2 = ".";

		if (!file.is_open())
		{
			perror("Error opening file!");
			exit(EXIT_FAILURE);
		}
		int i = 0;
		int j = 0;
		size_t pos = 0;
		string temp[8];
		while (getline(file, line))
		{
			j = 0;
			while ((pos = line.find(delim)) != string::npos)
			{
				temp[j] = line.substr(0, pos);
				line.erase(0, pos + delim.length());
				j++;
			}
			temp[7] = line;
			for (j = 0; j < 8; j++)
			{
				pos = temp[j].find(delim2);
				GameSettings::MAP[i][j].y = stof(temp[j].substr(0, pos));
				GameSettings::MAP[i][j].x = stof(temp[j].substr(pos + 1));
				GameSettings::MOVEMENT_MAP[i][j] = Node(i, j);
			}
			i++;
		}
		file.close();

		file2.open("maps/SubMap.dat");
		if (!file2.is_open())
		{
			perror("Error opening file!");
			exit(EXIT_FAILURE);
		}
		getline(file2, line);
		j = 0;
		while ((pos = line.find(delim)) != string::npos)
		{
			temp[j] = line.substr(0, pos);
			line.erase(0, pos + delim.length());
			j++;
		}
		temp[7] = line;
		for (j = 0; j < 8; j++)
		{
			pos = temp[j].find(delim2);
			GameSettings::SUBMAP[j].y = stof(temp[j].substr(0, pos));
			GameSettings::SUBMAP[j].x = stof(temp[j].substr(pos + 1));
		}
		file2.close();

		file3.open("maps/Characters.dat");
		if (!file3.is_open())
		{
			perror("Error opening file!");
			exit(EXIT_FAILURE);
		}
		j = 0;
		while (line != "--- Finish ---")
		{
			getline(file3, line);
			if (line == "--- Cstart ---")
			{
				getline(file3, line);
				GameSettings::MODELS[j].m_ATK = stoi(line);
				getline(file3, line);
				GameSettings::MODELS[j].m_Name = line;
				getline(file3, line);
				GameSettings::MODELS[j].m_HP = stoi(line);
				getline(file3, line);
				GameSettings::MODELS[j].m_ATKSPEED = stof(line);
				getline(file3, line);
				GameSettings::MODELS[j].m_bitmap = line;
			}
			else if (line == "--- Cend ---")
				j++;
		}
	}
	prepareGameObjects();
	generateTroops('P');
	generateTroops('C');
}

void GameScreen::prepareGameObjects()
{
	srand(time(NULL)*GameSettings::POOLSEED);
	for (int i = 0; i < GameSettings::POOLSIZE; i++)
	{
		int choice = rand() % 6;
		m_Pool.push_back(move(make_unique<Fighter>(WaitTroop::Instance(), GameSettings::AVAILABLE_ID++,
			GameSettings::MODELS[choice].m_ATK, GameSettings::MODELS[choice].m_Name, GameSettings::MODELS[choice].m_HP,
			GameSettings::MODELS[choice].m_ATKSPEED, Sprite(TextureHolder::GetTexture("graphics/" + GameSettings::MODELS[choice].m_bitmap)))));
	}
}