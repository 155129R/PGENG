#include "BaseEntity\Enemy.h"

using std::vector;

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
	int currentPattern[9][5];

public:
	EnemyManager(Node*);
	~EnemyManager();

	void SpawnEnemy(float, float);
	void Update(double dt, BaseEntity character);
	

};