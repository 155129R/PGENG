#include "EnemyManager.h"

EnemyManager::EnemyManager(Node* scene)
{
	spawnTimer = 5.0f;
	currentSpawnTimer = spawnTimer;
	waveSpawned = false;
	waveNumber = 0;

	//Ground offset ratio is 1072/150 = 7.1467
	groundOffset = 0;
	enemyOffset = 25.0f;

	int enemyPattern1[9][5] = { 
		{ 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 1, 1 },
		{ 1, 0, 0, 1, 0 },
		{ 1, 0, 0, 1, 0 },
		{ 0, 1, 0, 1, 0 },
		{ 0, 1, 1, 0, 1 },
		{ 0, 1, 1, 0, 1 },
		{ 1, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1 } 
	};

	std::copy(&enemyPattern1[0][0], &enemyPattern1[0][0] + 9 * 5, &currentPattern[0][0]);

	for (int i = 0; i < 45; i++)
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
		for (int x = waveNumber; x < 5; x++)
		{
			for (int y = 0; y < 9; y++)
			{
				if (currentPattern[y][x] == 1)
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
		if (currentSpawnTimer <= 0.0f && waveNumber < 5)
		{
			currentSpawnTimer = spawnTimer;
			waveSpawned = false;
		}
	}

	for (auto enemy : enemyPool)
		if (enemy->GetAlive())
			enemy->Update(dt,character);
}