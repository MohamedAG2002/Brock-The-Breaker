#pragma once

class Score
{
public:
	Score();
	~Score();

private:
	int m_score, m_highScore, m_wave;

public:
	void Update();

	void SetScore(int score) { m_score = score; }
	int& GetScore() { return m_score; }

	void SetHighScore(int highScore) { m_highScore = highScore; }
	int& GetHighScore() { return m_highScore; }
	
	void SetWave(int wave) { m_wave = wave; }
	int& GetWave() { return m_wave; }
};
extern Score score;