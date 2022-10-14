#include "Collision.h"
#include "Score.h"
#include "Assets.h"

// Extern variables init
Collision collision;

void Collision::Update()
{
	// Ball with the walls
	for (int i = 0; i < walls.size(); i++)
	{
		if (OnCollision(ball, walls.at(i)))
		{
			// Reverses the speed and sets the position based on which wall the ball hit
			if (i != 1)
			{
				if (i == 0)
					ball.SetPos(sf::Vector2f(walls.at(i).GetPos().x + ball.GetSize().x + 20, ball.GetPos().y));
				else
					ball.SetPos(sf::Vector2f(walls.at(i).GetPos().x - ball.GetSize().x, ball.GetPos().y));

				ball.SetSpeed(-ball.GetSpeed().x, ball.GetSpeed().y);
			}
			else
			{
				ball.SetPos(sf::Vector2f(ball.GetPos().x, walls.at(1).GetPos().y + ball.GetSize().y + 20));
				ball.SetSpeed(ball.GetSpeed().x, -ball.GetSpeed().y);
			}

			// Plays the appropriate sound
			Assets::GetInstance().GetAudio("wallHit").play();
		}
	}

	// Ball with the player
	if (OnCollision(ball, player))
	{
		ball.SetPos(sf::Vector2f(ball.GetPos().x, player.GetPos().y - ball.GetSize().x));
		ball.SetSpeed(ball.GetSpeed().x, -ball.GetSpeed().y);
	}

	// Ball with the bricks
	for (int i = 0; i < bricks.size(); i++)
	{
		for (int j = 0; j < bricks.at(i).size(); j++)
		{
			if (OnCollision(ball, bricks.at(i).at(j)))
			{
				score.SetScore(score.GetScore() + 1);

				ball.SetSpeed(ball.GetSpeed().x, -ball.GetSpeed().y);

				bricks.at(i).at(j).SetActive(false);

				Assets::GetInstance().GetAudio("hitBrick").play();
			}
		}
	}
}

bool Collision::OnCollision(GameObject& go1, GameObject& go2)
{
	if (go1.GetCollider().intersects(go2.GetCollider()))
		return true;

	return false;
}