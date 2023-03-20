sf::RenderWindow window(sf::VideoMode(800, 600), "My Window");

// Create views for plot and text layers
sf::View plotView(sf::FloatRect(0, 0, 800, 600));
sf::View textView(sf::FloatRect(0, 0, 800, 600));
textView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f)); // Set full window as viewport

// Create plot and text objects
sf::RectangleShape plot(sf::Vector2f(400, 300));
plot.setFillColor(sf::Color::Red);
plot.setPosition(200, 150);

sf::Text text("Hello, world!", font, 30);
text.setFillColor(sf::Color::Black);

// Main loop
while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    // Update plot view with mouse wheel
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        float zoom = 1.f - 0.1f * event.mouseWheelScroll.delta;
        plotView.zoom(zoom);
    }

    // Update text view with fixed zoom
    textView.setCenter(400, 300);
    textView.setSize(800, 600);
    textView.setRotation(0.f);
    textView.setViewport(sf::FloatRect(0, 0, 1.f, 1.f));

    // Draw plot and text with different views
    window.setView(plotView);
    window.draw(plot);

    window.setView(textView);
    window.draw(text);

    // Update window
    window.display();
}