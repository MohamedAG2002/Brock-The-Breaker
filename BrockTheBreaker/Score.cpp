#include "Score.h"
#include "GameObject.h"
#include "Assets.h"

// Extern variable init
Score score;

Score::Score()
{
	m_score = 0;
	m_wave = 0;
	m_highScore = 0;
}

Score::~Score()
{
}

void Score::Update()
{
	// Setting the high score
	m_highScore = m_score > m_highScore ? m_score : m_highScore;

	// Respawns the bricks once all of them are cleared
	if (m_score % (ROW * COLOMN) == 0)
	{
		// Play the aproppriate audio

		// Increase the waves
		if (m_score != 0)
		{
			Assets::GetInstance().GetAudio("stageClear").play();
			m_wave++;
		}

		// Respawn the bricks
		for (int i = 0; i < bricks.size(); i++)
		{
			for (int j = 0; j < bricks.at(i).size(); j++)
			{
				bricks.at(i).at(j).SetActive(true);
			}
		}
	}
}
