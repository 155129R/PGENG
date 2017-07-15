#include "EnemyManager.h"

#include <sstream>
#include <fstream>


EnemyManager::EnemyManager(Node* scene)
{
	spawnTimer = 5.0f;
	currentSpawnTimer = spawnTimer;
	waveSpawned = false;
	waveNumber = 0;

	//Ground offset ratio is 1072/150 = 7.1467
	groundOffset = 0;
	enemyOffset = 25.0f;

	//Start of reading file
	std::ifstream file;
	//For CSV File
	file.open("Levels\\Level1.csv");

	//For Text File
	//file.open("Levels\\Level1.txt");
	while (file)
	{
		vector<int> enemyPatternY;
		
		//For CSV File
		std::getline(file, line,'\r');
		
		//For Text File
		//std::getline(file, line);
		
		//Loop through the line
		for (int i = 0; i < line.size(); i++)
		{
			if (line.at(i) == '1' || line.at(i) == '0')
			{
				enemyPatternY.push_back(line.at(i) - '0');
			}
		}

		//push in the Y pattern into X pattern
		enemyPattern.push_back(enemyPatternY);
	}

	for (int i = 0; i < 35; i++)
	{
		auto enemyNode = Node::create();
		enemyNode->setName("enemyNode");
		enemyNode->setPosition(10, 0);
		scene->addChild(enemyNode, 1);

		Enemy* newEnemy = new Enemy();
		newEnemy->Init("Blue_Front1.png", "Player", 0, 0, -1);
		enemyNode->addChild(newEnemy->getSprite(), 1);
		newEnemy->SetSpeed(10.0f);
		newEnemy->SetDirection(-1);
		newEnemy->SetAlive(false);
		newEnemy->getSprite()->setVisible(false);

		enemyPool.push_back(newEnemy);
	}
	
}

EnemyManager::~EnemyManager()
{

}


const char* EnemyManager::getPathForFile(string fileName)
{
	string path = CCFileUtils::sharedFileUtils()->getWritablePath() + "\\" + fileName;
	return path.c_str();
}
void EnemyManager::SpawnEnemy(float x, float y)
{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	groundOffset = visibleSize.height / 7.1467;

	float posX = visibleSize.width;

	//(visibleSize.height - groundOffset) is the distance between the ground and the top of the screen
	//(visibleSize.height - groundOffset) / 9 is the distance per round for the enemy
	//(9 - y) is to invert the 0 to 9 and 9 to 0 multiply
	float posY = groundOffset + (((visibleSize.height - groundOffset) / 9) * (9 - y) - (visibleSize.height - groundOffset) / 9);

	if (y == 9)
		posY = visibleSize.height - 100;

	for (auto enemy : enemyPool)
	{
		if (!enemy->GetAlive())
		{
			enemy->getSprite()->setPosition(posX, posY);
			enemy->SetAlive(true);
			break;
		}
	}
}
void EnemyManager::Update(double dt, BaseEntity character)
{
	if (!waveSpawned)
	{
		//Why i use enemyPattern.at(0).size() as the limit becuase
		//Right now i have to access the pattern then i can get the max wave size
		//Since the max wave size is determined by the number of X there is in csv
		//It is not the best method yet, best method would be pre set 2 array
		//by looping through the csv see what is the x and y capacity
		//then set it to 2d Array using memset, after that change the
		//enemyPattern.at(0).size() to the X capacity.

		//For CSV File
		for (int x = waveNumber; x < enemyPattern.at(0).size(); x++)
		{
			for (int y = 0; y < enemyPattern.size() - 1; y++)
			{
				if (enemyPattern[y][x] == 1)
				{
					SpawnEnemy(x, y);
				}

			}
			waveSpawned = true;
			waveNumber++;
			break;
		}

		//For Text File
		/*
		for (int x = waveNumber; x < enemyPattern.size(); x++)
		{
			for (int y = 0; y < enemyPattern.size(); y++)
			{
				if (enemyPattern[y][x] == 1)
				{
					SpawnEnemy(x, y);
				}

			}
			waveSpawned = true;
			waveNumber++;
			break;
		}*/
		

	}
	else
	{
		currentSpawnTimer -= dt;
		if (currentSpawnTimer <= 0.0f)
		{
			//Normal GamePlay
			currentSpawnTimer = spawnTimer;
			
			//For Debugging
			//currentSpawnTimer = 0.2f;
			
			waveSpawned = false;
		}
	}

	for (auto enemy : enemyPool)
		if (enemy->GetAlive())
			enemy->Update(dt,character);
}