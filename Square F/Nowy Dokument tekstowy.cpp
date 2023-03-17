while (window.isOpen())
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        // obs�uga zamkni�cia okna
        if (event.type == sf::Event::Closed)
            window.close();
        // obs�uga przesuwania wykresu myszk�
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            // zapisanie pozycji kursora w momencie naci�ni�cia przycisku myszy
            lastPosition = sf::Mouse::getPosition(window);
        }
        else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // wyznaczenie r�nicy pomi�dzy aktualn� pozycj� kursora a pozycj� pocz�tkow�
            sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

            // regulacja pr�dko�ci przesuwania w zale�no�ci od warto�ci skali
            float zoomLevel = view.getSize().x / window.getSize().x;
            float speed = 1.0f;
            if (zoomLevel > 1.0f) {
                speed = 1.0f / zoomLevel;
            }
            // przesuni�cie wykresu o odpowiedni� warto�� z uwzgl�dnieniem pr�dko�ci
            view.move(-delta.x * speed, -delta.y * speed);
            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz�tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                // regulacja pr�dko�ci przybli�ania w zale�no�ci od warto�ci skali
                float zoomLevel = view.getSize().x / window.getSize().x;
                float speed = 0.1f;
                if (zoomLevel > 1.0f) {
                    speed = 0.1f / zoomlevel;
            }
            // przybli�anie z uwzgl�dnieniem pr�dko�ci
            view.zoom(1 - event.mouseWheelScroll.delta * speed);
            window.setView(view);
        }
    }
}

window.clear(Color::White); // czyszczenie ekranu
//window.draw(grid);
window.draw(grid1x1);
window.draw(axes);  // rysowanie osi uk�adu wsp�rz�dnych
window.draw(plot);  // rysowanie wykresu funkcji kwadratowe   
window.draw(zeros);
window.display(); // wy�wietlanie okna graficznego
}
