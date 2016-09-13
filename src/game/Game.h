/*

*/

class Game {
	bool isRunning = false;
	int currentTime = 0;
	int previousTime = 0;

	public:
		Game();
		~Game();
		void Start();
		void Stop();
		void Update();
		float UpdateTime();
		void UpdateFPS(float);
};