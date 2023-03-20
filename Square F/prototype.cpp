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
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// ###################################################
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// ###################################################
// XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// ###################################################
// Axes numerating protootype


// create a new VertexArray to store the grid lines
VertexArray grid1x1(Lines, (width + height) * 2);

// create a new Text object to display the numbers
sf::Text numberText("", font, 12);
numberText.setFillColor(sf::Color::Black);
numberText.setStyle(sf::Text::Regular);
numberText.setOrigin(sf::Vector2f(numberText.getGlobalBounds().width / 2.f, numberText.getGlobalBounds().height / 2.f));

// loop through the vertical grid lines
for (int i = -width / 2; i <= width / 2; i++) {
    if (i % 4 == 0) {
        // create a new Text object for this number
        numberText.setString(std::to_string(i));
        // set the position and rotation of the number
        numberText.setPosition(sf::Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) + 10.f));
        numberText.setRotation(90.f);
        // add the number to the grid VertexArray
        int index = (i + width / 2) * 2;
        grid1x1[index].position = sf::Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) - 0.5f);
        grid1x1[index + 1].position = sf::Vector2f(static_cast<float>(width / 2 + i), static_cast<float>(height / 2) + 0.5f);
        grid1x1[index].color = sf::Color(0, 0, 0, 100);
        grid1x1[index + 1].color = sf::Color(0, 0, 0, 100);
        // add the number to the grid VertexArray
        window.draw(numberText);
    }
}

// draw the grid lines and numbers to the window
window.draw(grid1x1);