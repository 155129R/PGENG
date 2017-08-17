#include "Enemy.h"
#include <iostream>

using std::vector;
using std::string;

class PowerUp;

class EnemyManager
{
private:
	vector<Enemy*> enemyPool;
	vector<PowerUp*> powerPool;

	float spawnTimer;
	float currentSpawnTimer;
	bool waveSpawned;
	int waveNumber;
	float groundOffset;
	float enemyOffset;
	vector<vector<int>> enemyPattern;

	int currentPattern[9][5];
	string line;

	float enemySpeed;

	const char* getPathForFile(string);

public:
	EnemyManager(Node*);
	~EnemyManager();

	void SpawnEnemy(float, float);
	void SpawnPowerUp(float x, float y);
	void Update(double dt, BaseEntity* character);
};