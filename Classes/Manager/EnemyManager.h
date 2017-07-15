#include "BaseEntity\Enemy.h"
#include <iostream>

using std::vector;
using std::string;

class EnemyManager
{
private:
	vector<Enemy*> enemyPool;
	float spawnTimer;
	float currentSpawnTimer;
	bool waveSpawned;
	int waveNumber;
	float groundOffset;
	float enemyOffset;
	vector<vector<int>> enemyPattern;

	int currentPattern[9][5];
	string line;

	const char* getPathForFile(string);

public:
	EnemyManager(Node*);
	~EnemyManager();

	void SpawnEnemy(float, float);
	void Update(double dt, BaseEntity character);
	

};