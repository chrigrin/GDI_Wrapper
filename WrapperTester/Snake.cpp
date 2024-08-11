#include "stdafx.h"
#include "Snake.hpp"

Snake::Snake()
{
	m_body.emplace_back();
	m_body.back().setFillColor(gw::Color(0, 255, 0));
	m_body.back().setSize(SNAKE_SIZE, SNAKE_SIZE);
	m_body.back().setOutlineColor(gw::Color(0, 0, 0));
	m_body.back().setOutlineThickness(-1);
}

void Snake::update(gw::Time dt)
{
	m_elapsedTime += dt;
	if (m_elapsedTime > gw::Time(1000))
	{
		m_elapsedTime -= gw::Time(1000);
		for (size_t i = m_body.size() - 1; i > 0; i--)
		{
			m_body[i].setPosition(m_body[i - 1].getPosition());
		}
		m_body.front().move(m_vel);
	}
}

void Snake::draw(gw::Graphics& gfx) const
{
	for (const auto& elem : m_body)
	{
		gfx.draw(elem);
	}
}
