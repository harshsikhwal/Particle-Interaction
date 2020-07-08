#include<SFML\Graphics.hpp>

#include "Sandbox.hpp"
#include <iostream>


static const int g_frame_rate = 3;

int main(int argc, char* argv[]) 
{
    // Produce pseudo-random integers based on the current timestamp seed
    srand((unsigned)time(0));
    
    std::cout << "=========================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "                      Particle Interations" << std::endl;
    std::cout << std::endl;
    std::cout << "  A small project written in C++ using SFML library." << std::endl;
    std::cout << "Please Enter the number of particles you need, the variety and radius of particle." << std::endl;
    std::cout << std::endl;
    std::cout << "Help:" << std::endl;
    std::cout << "        L     : To draw/clear lines" << std::endl;
    std::cout << "        P     : Pause the simulation" << std::endl;
    std::cout << "        Space : Slow-mo the effect" << std::endl;
    std::cout << "        ESC   : Exit" << std::endl;
    std::cout << std::endl;
    std::cout << "The number of particles should be based on your system configuration." << std::endl;
    std::cout << "The more number of particles can likely have a laggy experience" << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << std::endl;

    int number_of_particles;
    int variety;
    float radius;

    std::cout << "Number of particles: ";
    std::cin >> number_of_particles;

    std::cout << "Variety: ";
    std::cin >> variety;

    std::cout << "Radius of particle: ";
    std::cin >> radius;


    system("pause");

    bool pause_simulation = false;
    bool draw_lines = false;

    int screen_width = sf::VideoMode::getDesktopMode().width;
    int screen_height = sf::VideoMode::getDesktopMode().height;

    //Create the sandbox of particles
    Sandbox sandbox(number_of_particles, radius, screen_width, screen_height, variety);
    
    // Camera settings
    float cam_x = float(screen_width / 2);
    float cam_y = float(screen_height / 2);
    float cam_zoom = 1.0f;
    float cam_x_dest = cam_x;
    float cam_y_dest = cam_y;
    float cam_zoom_dest = cam_zoom;
    int32_t last_scroll_time = 0;
    int track_index = -1;
    int frame_rate = g_frame_rate;

    // openGL settings
    sf::ContextSettings settings;
    settings.depthBits = 24;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 8;
    settings.majorVersion = 3;
    settings.minorVersion = 0;

    //Create the window
    const sf::VideoMode screenSize = sf::VideoMode(screen_width, screen_height, 24);
    sf::RenderWindow window(screenSize, "Particles", sf::Style::Fullscreen, settings);
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(true);
    window.setActive(false);
    window.requestFocus();
    sf::Clock clock;

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed) 
            {
                window.close();
                break;
            }
            else if (event.type == sf::Event::KeyPressed) 
            {
                sf::Keyboard::Key keycode = event.key.code;
                if (keycode == sf::Keyboard::Escape) 
                {
                    window.close();
                    break;
                }
                // Enable Disable Pause
                else if (keycode == sf::Keyboard::P) 
                { 
                    pause_simulation = !pause_simulation;
                }
                // Enable Disable Interacting lines
                else if (keycode == sf::Keyboard::L)
                { 
                    draw_lines = !draw_lines;
                }
               // Set slow motion: or 
                else if (keycode == sf::Keyboard::Space) 
                {
                    frame_rate = 1;
                }
            }
            else if (event.type == sf::Event::KeyReleased) 
            {
                const sf::Keyboard::Key keycode = event.key.code;
                if (keycode == sf::Keyboard::Space) 
                {
                    frame_rate = g_frame_rate;
                }
            }
            else if (event.type == sf::Event::MouseWheelMoved) 
            {
                cam_zoom_dest *= std::pow(1.1f, event.mouseWheel.delta);
                cam_zoom_dest = std::max(std::min(cam_zoom_dest, 10.0f), 1.0f);
                const int32_t cur_time = clock.getElapsedTime().asMilliseconds();
                if (cur_time - last_scroll_time > 300) 
                {
                    //Only update position if scroll just started
                    const sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
                    sandbox.ToCenter(mouse_pos.x, mouse_pos.y, cam_x_dest, cam_y_dest);
                }
                last_scroll_time = cur_time;
            }
        }
        
        // Apply Zoom
        cam_x = cam_x * 0.9f + cam_x_dest * 0.1f;
        cam_y = cam_y * 0.9f + cam_y_dest * 0.1f;
        cam_zoom = cam_zoom * 0.8f + cam_zoom_dest * 0.2f;
        sandbox.Zoom(cam_x, cam_y, cam_zoom);
        
        if (!pause_simulation)
        {
            // CLear the window, compute and redraw
            window.clear();
            for (int i = 0; i < frame_rate; ++i)
            {
                const float opacity = float(i + 1) / float(frame_rate);
                sandbox.ComputePath();
                sandbox.DrawParticles(window, opacity);
                if (draw_lines)
                {
                    sandbox.DrawLines(window, opacity);
                }
            }
            window.display();
        }
    }

    return 0;
}
