#pragma once

class RenderEngine {
public:
	void CreateWindow(int width, int height);
	void UpdateScreen();
	enum Status {RUNNING, ERROR, SHUTDOWN};
	Status GetStatus() { return status; };
	void SetStatus(Status stat) { status = stat; };

private:
	int window_height = 0;
	int window_width = 0;
	Status status;
};