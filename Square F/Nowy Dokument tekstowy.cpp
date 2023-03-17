while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // obs³uga zamkniêcia okna
        if (event.type == sf::Event::Closed)
            window.close();
        // obs³uga przesuwania wykresu myszk¹
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // zapisanie pozycji kursora w momencie naciœniêcia przycisku myszy
            lastPosition = sf::Mouse::getPosition(window);
        }
        else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // wyznaczenie ró¿nicy pomiêdzy aktualn¹ pozycj¹ kursora a pozycj¹ pocz¹tkow¹
            sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

            // regulacja prêdkoœci przesuwania w zale¿noœci od wartoœci skali
            float zoomLevel = view.getSize().x / window.getSize().x;
            float speed = 1.0f;
            if (zoomLevel > 1.0f) {
                speed = 1.0f / zoomLevel;
            }
            // przesuniêcie wykresu o odpowiedni¹ wartoœæ z uwzglêdnieniem prêdkoœci
            view.move(-delta.x * speed, -delta.y * speed);
            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz¹tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                // regulacja prêdkoœci przybli¿ania w zale¿noœci od wartoœci skali
                float zoomLevel = view.getSize().x / window.getSize().x;
                float speed = 0.1f;
                if (zoomLevel > 1.0f) {
                    speed = 0.1f / zoomlevel;
            }
            // przybli¿anie z uwzglêdnieniem prêdkoœci
            view.zoom(1 - event.mouseWheelScroll.delta * speed);
            window.setView(view);
        }
    }
}

window.clear(Color::White); // czyszczenie ekranu
//window.draw(grid);
window.draw(grid1x1);
window.draw(axes);  // rysowanie osi uk³adu wspó³rzêdnych
window.draw(plot);  // rysowanie wykresu funkcji kwadratowe   
window.draw(zeros);
window.display(); // wyœwietlanie okna graficznego
}
