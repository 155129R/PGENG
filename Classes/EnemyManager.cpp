#include "EnemyManager.h"

#include <sstream>
#include <fstream>

#include "PowerUp.h"

EnemyManager::EnemyManager(Node* scene)
{
    
	spawnTimer = 5.0f;
	currentSpawnTimer = spawnTimer;
	waveSpawned = false;
	waveNumber = 0;
	enemySpeed = 10.f;

	//Ground offset ratio is 1072/150 = 7.1467
	groundOffset = 0;
	enemyOffset = 25.0f;

	//Start of reading file
	std::ifstream file;
    
	//For CSV File
    file.open(FileUtils::sharedFileUtils()->fullPathForFilename("Levels/Level1.csv"));
    std::printf("mao ni\n");

    
	//For Text File
	//file.open("Levels\\Level1.txt");
	while (file)
	{
		vector<int> enemyPatternY;
		
        std::printf("ni mao\n");
        
		//For CSV File
		std::getline(file, line,'\r');
        
        if (line.size() == 0)
            break;
        
        
		
		//For Text File
		//std::getline(file, line);
		
		//Loop through the line
		for (int i = 0; i < line.size(); i++)
		{
			if (line.at(i) == '1' || line.at(i) == '0' || line.at(i) == '2')
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
		newEnemy->Init("Attack/Attack1.png", "Enemy", 0, 0, -1);
		enemyNode->addChild(newEnemy->getSprite(), 1);
		newEnemy->SetSpeed(enemySpeed);
		newEnemy->SetDirection(-1);
		newEnemy->SetAlive(false);
		newEnemy->getSprite()->setVisible(false);

		enemyPool.push_back(newEnemy);
	}

	for (int i = 0; i < 35; i++)
	{
		auto powerNode = Node::create();
		powerNode->setName("powerNode");
		powerNode->setPosition(10, 0);
		scene->addChild(powerNode, 1);

		PowerUp* newPower = new PowerUp();
		newPower->Init("heart.png", "LIFE", 0, 0);
		powerNode->addChild(newPower->getSprite(), 1);
		newPower->SetSpeed(enemySpeed);
		newPower->SetDirection(-1);
		newPower->SetAlive(false);
		newPower->getSprite()->setVisible(false);

		powerPool.push_back(newPower);
	}
}

EnemyManager::~EnemyManager()
{

}


const char* EnemyManager::getPathForFile(string fileName)
{
	string path = FileUtils::sharedFileUtils()->getWritablePath() + "//" + fileName;
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
			enemy->SetSpeed(enemySpeed);
			enemy->getSprite()->setPosition(posX, posY);
			enemy->SetAlive(true);
			break;
		}
	}
}

void EnemyManager::SpawnPowerUp(float x, float y)
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

	for (auto power : powerPool)
	{
		if (!power->GetAlive())
		{
			power->SetSpeed(enemySpeed);
			power->getSprite()->setPosition(posX, posY);
			power->SetAlive(true);
			break;
		}
	}
}


void EnemyManager::Update(double dt, BaseEntity* character)
{
    currentSpawnTimer -= dt;
    if (currentSpawnTimer <= 0.0f)
    {
        //Normal GamePlay
        currentSpawnTimer = spawnTimer;
        
        for (int y = 0; y < enemyPattern.size(); y++)
        {
            if (enemyPattern[y][waveNumber] == 1)
            {
                SpawnEnemy(waveNumber, y);
            }
            else if (enemyPattern[y][waveNumber] == 2)
            {
                SpawnPowerUp(waveNumber, y);
            }
        }
        
        waveNumber++;
        if (waveNumber == enemyPattern[0].size())
        {
            waveNumber = 0;
            enemySpeed += 2.5f;
        }
    }
    /*
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
		for (int x = waveNumber; x < enemyPattern.at(0).size() - 1; x++)
		{
			for (int y = 0; y < enemyPattern.size() - 1; y++)
			{
				if (enemyPattern[y][x] == 1)
				{
					SpawnEnemy(x, y);
				}
				else if (enemyPattern[y][x] == 2)
				{
					SpawnPowerUp(x, y);
				}
			}
f
			waveSpawned = true;
			waveNumber++;
			if (waveNumber == enemyPattern.at(0).size())
			{
				waveNumber = 0;
				enemySpeed += 2.5f;
			}
			break;
		}
        
		//For Text File
		for (int x = waveNumber; x < enemyPattern.size() - 1; x++)
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
    */

	for (auto enemy : enemyPool)
		if (enemy->GetAlive())
			enemy->Update(dt, character);

	for (auto power : powerPool)
		if (power->GetAlive())
			power->Update(dt, character);
}
