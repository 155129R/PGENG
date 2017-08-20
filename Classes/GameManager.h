#include "Enemy.h"
#include "FeedBack.h"
#include "WarningSign.h"
#include <iostream>

using std::vector;
using std::string;

class PowerUp;

class GameManager
{
private:
	vector<Enemy*> enemyPool;
	vector<PowerUp*> powerPool;
	vector<WarningSign*> warningPool;
	FeedBack* playerFeedBack;

	bool warningSpawned;
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
	GameManager(Node*);
	~GameManager();

	void SpawnEnemy(float, float);
	void SpawnPowerUp(float x, float y);
	void SpawnWarningSign(float, float, WarningSign::WarningType);
	FeedBack* GetFeedBack();
	void Update(double dt, BaseEntity* character);
};