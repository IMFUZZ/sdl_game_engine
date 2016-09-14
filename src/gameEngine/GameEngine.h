/*

*/

class GameEngine {
	bool isRunning = false;
	int currentTick = 0;
	int previousTick = 0;

	public:
		GameEngine();
		~GameEngine();
		void Start();
		void Stop();
		void Update();
		double Tick();
		void RegulateFPS(int, double);
};