#include "Sandbox.hpp"
#include <iostream> 
#include <iterator> 
#include <map> 
#include <utility> 
#include <cmath>


Sandbox::Sandbox(long i_NumberOfParticles, float i_globalRadius, int i_Width, int i_Height, int i_variety)
{
    Sandbox::m_number_of_particles = i_NumberOfParticles;
    Sandbox::m_width = i_Width;
    Sandbox::m_height = i_Height;
    m_particles.resize(i_NumberOfParticles);
    m_global_radius = i_globalRadius;
    m_center_x = m_width * 0.5f;
    m_center_y = m_height * 0.5f;
    CreateColourMap();
    RandomizeParticles(i_variety);
}

void Sandbox::CreateColourMap()
{
    // White
    m_colour_map.insert(std::pair<int, sf::Color>(0, sf::Color(255, 255, 255)));
    // Red
    m_colour_map.insert(std::pair<int, sf::Color>(1, sf::Color(255, 0, 0)));
    // Green
    m_colour_map.insert(std::pair<int, sf::Color>(2, sf::Color(0, 255, 0)));
    // Blue
    m_colour_map.insert(std::pair<int, sf::Color>(3, sf::Color(0, 0, 255)));
    //Yellow
    m_colour_map.insert(std::pair<int, sf::Color>(4, sf::Color(255, 255, 0)));
    // Pink
    m_colour_map.insert(std::pair<int, sf::Color>(5, sf::Color(255, 0, 255)));
    // Cyan
    m_colour_map.insert(std::pair<int, sf::Color>(6, sf::Color(0, 255, 255)));
    // Orange
    m_colour_map.insert(std::pair<int, sf::Color>(7, sf::Color(255, 127, 0)));
    // Violet
    m_colour_map.insert(std::pair<int, sf::Color>(8, sf::Color(148, 0, 211)));
}

void Sandbox::ToCenter(int x, int y, float& cx, float& cy) const 
{
    cx = m_center_x + float(x - m_width / 2) / m_zoom;
    cy = m_center_y + float(y - m_height / 2) / m_zoom;
}

void Sandbox::Zoom(float cx, float cy, float zoom) 
{
    //Apply the zoom
    m_center_x = cx;
    m_center_y = cy;
    m_zoom = std::max(1.0f, zoom);

    //Clamp to make sure camera doesn't go out of bounds
    m_center_x = std::min(m_center_x, float(m_width) * (1.0f - 0.5f / m_zoom));
    m_center_y = std::min(m_center_y, float(m_height) * (1.0f - 0.5f / m_zoom));
    m_center_x = std::max(m_center_x, float(m_width) * (0.5f / m_zoom));
    m_center_y = std::max(m_center_y, float(m_height) * (0.5f / m_zoom));
}

void Sandbox::RandomizeParticles(int i_variety)
{
    int i;
    for (i = 0; i < m_particles.size(); i++)
    {
        // Set the position of particles from 0 - width/height and further check for boundary
        position pos;
        pos.x = rand() % m_width;
        pos.y = rand() % m_height;

        // Adjust to boundary
        if (pos.x <= m_global_radius)
        {
            pos.x = pos.x + m_global_radius - pos.x + 1;
        }
        if (pos.y <= m_global_radius)
        {
            pos.y = pos.y + m_global_radius - pos.y + 1;
        }
        if (pos.x >= (m_width - m_global_radius))
        {
            pos.x = pos.x - (m_width - m_global_radius) - 1;
        }
        if (pos.y >= (m_height - m_global_radius))
        {
            pos.y = pos.y - (m_height - m_global_radius) - 1;
        }

        // Generate random colour based of variety
        int col_index = rand() % i_variety;
        Particle particle(pos.x, pos.y, m_colour_map[col_index], m_global_radius, col_index);
        
        // Assign random path to the particle:
        // The paths are: -1, 0, 1
        // -1 is the negative on that axis, 1 is positive and 0 is no change

        position path;
        int temp_rand = rand() % 3;
        if (temp_rand % 3 == 0)
            path.x = 1;
        else if(temp_rand % 3 == 1)
            path.x = 0;
        else 
            path.x = -1;
        
        if (path.x == 0)
        {
            temp_rand = rand() % 2;
            if (temp_rand % 2 == 0)
            {
                path.y = 1;
            }
            else
            {
                path.y = -1;
            }
        }
        else
        {
            temp_rand = rand() % 3;
            if (temp_rand % 3 == 0)
                path.y = -1;
            else if (temp_rand % 3 == 1)
                path.y = 0;
            else
                path.y = 1;
        }
        particle.SetPath(path);
        m_particles[i] = particle;
    }
}

void Sandbox::ComputePath()
{
    int i;
    for (i = 0; i < m_particles.size(); i++)
    {
        Particle& particle = m_particles[i];
        position& path = particle.GetPath();
        position& pos = particle.GetPosition();
        
        // Check the boundaries and if hit: flip the path info
        // For example, a particle in straight line, when collides with wall will continue in opposite

        if (((pos.x - Sandbox::m_global_radius) <= 0) || ((pos.x + Sandbox::m_global_radius) >= Sandbox::m_width))
        {
            path.x *= -1;
        }

        if (((pos.y - Sandbox::m_global_radius) <= 0) || ((pos.y + Sandbox::m_global_radius) >= Sandbox::m_height))
        {
            path.y *= -1;
        }

        // After calculation: add to position after checking path
        if (path.x == -1)
        {
            pos.x = pos.x - 1;
        }
        else
        {
            pos.x = pos.x + 1;
        }
        if (path.y == -1)
        {
            pos.y = pos.y - 1;
        }
        else
        {
            pos.y = pos.y + 1;
        }
    }
}

void Sandbox::DrawLines(sf::RenderWindow& window, float opacity)
{
    // Draw lines
    int i;
    for (i = 0; i < m_particles.size(); i++)
    {
        Particle& particle = m_particles[i];
        position& path = particle.GetPath();
        position& pos = particle.GetPosition();
        int j;
        for (j = 0; j < m_particles.size(); j++)
        {
            if (i == j)
            {
                // Cannot draw with itself
                continue;
            }
            else
            {
                Particle& next_particle = m_particles[j];
                position& next_pos = next_particle.GetPosition();
                position& next_path = next_particle.GetPath();
                
                // We are interested if the particles are of the same colour, so we want to draw lines
                if (next_particle.GetColourTag() == particle.GetColourTag())
                {
                    // Calculate distance:
                    int dx = pos.x - next_pos.x;
                    int dy = pos.y - next_pos.y;
                    float distance = sqrt((dx * dx) + (dy * dy));
                    
                    // If distance is less than or equal to 50px
                    if ((ceil(distance) - (2.0f * Sandbox::m_global_radius)) <= 50.0f)
                    {
                        sf::Vertex line[] =
                         {
                            sf::Vertex(sf::Vector2f((pos.x - m_center_x) * m_zoom + float(m_width / 2) + m_global_radius, (pos.y - m_center_y) * m_zoom + float(m_height / 2) + m_global_radius), sf::Color(m_colour_map[particle.GetColourTag()])),
                            sf::Vertex(sf::Vector2f((next_pos.x - m_center_x) * m_zoom + float(m_width / 2) + m_global_radius, ( next_pos.y - m_center_y) * m_zoom + float(m_height / 2) + m_global_radius), sf::Color(m_colour_map[particle.GetColourTag()]))
                        };
                        window.draw(line, 2, sf::Lines);
                    }
                }
            }
        }
    }
}

void Sandbox::DrawParticles(sf::RenderWindow& window, float opacity)
{
    sf::CircleShape circle;
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    for (size_t i = 0; i < m_particles.size(); ++i) 
    {
        Particle& particle = m_particles[i];
        circle.setRadius(m_global_radius);
        const float x = (particle.GetX() - m_center_x)* m_zoom + float(m_width / 2);
        const float y = (particle.GetY() - m_center_y)* m_zoom + float(m_height / 2);
        circle.setPosition(x, y);
        sf::Color col = particle.GetColour();
        col.a = uint8_t(opacity * 255);
        circle.setFillColor(col);
        window.draw(circle);
    }
}