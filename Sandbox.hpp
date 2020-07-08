#pragma once
#include "particle.cpp"
#include <iostream> 
#include <iterator> 
#include <map> 


class Sandbox
{
private:
	int m_width;
	int m_height;
	std::vector<Particle> m_particles;
	long m_number_of_particles;
	std::map<int, sf::Color> m_colour_map;
	float m_global_radius;
	float m_center_y;
	float m_center_x;
	float m_zoom;

public:
	Sandbox(long i_NumberOfParticles, float m_globalRadius, int i_Width, int i_Height, int i_variety);

	// \brief Creates colour map, that has colour index and value as sf::Color
	void CreateColourMap();

	// \brief Randomize particle position, colour and the path to traverse
	void RandomizeParticles(int i_variety);

	// \brief Compute path based on the path variable: 1 adds to path, 0 no change and -1 adds to the negative axes
	// Check for collision too
	void ComputePath();

	// Method to draw circles on window
	void DrawParticles(sf::RenderWindow& window, float opacity);

	// Draw Line if L is pressed
	void DrawLines(sf::RenderWindow& window, float opacity);


	void ToCenter(int x, int y, float& cx, float& cy) const;

	void Zoom(float cx, float cy, float zoom);
};