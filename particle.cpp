#pragma once

#include <SFML\Graphics.hpp>

struct Position
{
	long x;
	long y;
};

typedef struct Position position;

class Particle
{
private:
	position m_position;
	sf::Color m_colour;
	float m_radius;
	long m_colour_tag;
	// Denotes the movement: 1 is positive and -1 is negative path on that particular axis
	position m_path;

public:

	Particle()
	{
		m_colour = sf::Color();
		m_radius = 2.0f;
		m_colour_tag = -1;
		m_path.x = 0;
		m_path.y = 0;
		m_position.x = 0;
		m_position.y = 0;
	}

	Particle(long i_x, long i_y, sf::Color i_colour, float i_radius, long i_colour_tag)
	{
		m_position.x = i_x;
		m_position.y = i_y;
		m_colour = i_colour;
		m_radius = i_radius;
		m_path.x = 0;
		m_path.y = 0;
		m_colour_tag = i_colour_tag;
	}

	Particle(long i_x, long i_y, sf::Color i_colour)
	{
		m_position.x = i_x;
		m_position.y = i_y;
		m_colour = i_colour;
		m_radius = 2.0f;
		m_path.x = 0;
		m_path.y = 0;
		m_colour_tag = -1;
	}

	Particle(position i_pos, sf::Color i_colour)
	{
		m_position = i_pos;
		m_colour = i_colour;
		m_radius = 2.0f;
		m_path.x = 0;
		m_path.y = 0;
		m_colour_tag = -1;
	}

	long GetColourTag()
	{
		return m_colour_tag;
	}

	void SetColourTag(long i_colour)
	{
		m_colour_tag = i_colour;
	}

	position& GetPath()
	{
		return m_path;
	}

	void SetPath(position i_path)
	{
		m_path = i_path;
	}
	
	position& GetPosition()
	{
		return m_position;
	}

	void UpdatePath(long i_x, long i_y)
	{
		m_path.x = i_x;
		m_path.y = i_y;
	}

	void UpdatePosition(long x, long y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	long GetX() const
	{
		return m_position.x;
	}
	
	long GetY() const
	{
		return m_position.y;
	}

	long GetX()
	{
		return m_position.x;
	}

	long GetY()
	{
		return m_position.y;
	}
	
	sf::Color GetColour() const
	{
		return m_colour;
	}

	sf::Color GetColour()
	{
		return m_colour;
	}

	float GetRadius()
	{
		return m_radius;
	}

	void SetRadius(float i_radius)
	{
		m_radius = i_radius;
	}
};
