

class Snake
{
public:
	static constexpr int SNAKE_SIZE = 30;

public:
	Snake();

	void update(gw::Time dt);

	void draw(gw::Graphics& gfx) const;

private:
	std::vector<gw::RectangleShape> m_body;
	std::pair<int, int> m_vel = { 30, 0 };
	gw::Time m_elapsedTime;
};