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




float moveScale = 0.1f; // skala przesuwania
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
            // regulacja pr�dko�ci przesuwania
            delta *= moveScale;
            // regulacja pr�dko�ci przesuwania w zale�no�ci od warto�ci skali
            float zoomLevel = view.getSize().x / window.getSize().x;
            float speed = 1.0f;
            if (zoomLevel > 1.0f) {
                speed = 1.0f / zoomLevel;
            }
            view.move(-delta.x * speed, -delta.y * speed);
            window.setView(view);
            lastPosition = sf::Mouse::getPosition(window);
        }
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                // zoom speed adjustment
                float zoomLevel = view.getSize().x / window.getSize().x;
                float speed = 0.1f;
                if (zoomLevel > 1.0f) {
                    speed = 0.1f / zoomLevel;
                }
                view.zoom(1 - event.mouseWheelScroll.delta * speed);
                window.setView(view);
            }
        }
    }

    window.clear(Color::White);
    window.draw(grid1x1);
    window.draw(axes);
    window.draw(plot);
    window.draw(zeros);
    window.display();
}

sf::Vector2f delta = sf::Vector2f(event.mouseMove.x - lastMousePos.x, event.mouseMove.y - lastMousePos.y);
float zoomLevel = view.getSize().x / window.getSize().x;
float moveScale = zoomLevel * 10.0f; // tu mo�esz dostosowa� warto��
delta *= moveScale;
lastMousePos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);






Vector2f previousMousePos; // zmienna przechowuj�ca poprzednie po�o�enie kursora myszy
bool isDragging = false;
sf::Vector2i lastPosition;
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
            previousMousePos = window.mapPixelToCoords(lastPosition); // dodane
            isDragging = true; // dodane
        }
        else if (event.type == sf::Event::MouseMoved && isDragging) // zmienione
        {
            // wyznaczenie r�nicy pomi�dzy aktualn� pozycj� kursora a pozycj� pocz�tkow�
            sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

            // przesuni�cie wykresu o odpowiedni� warto��
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            view.move(previousMousePos - mousePos);
            previousMousePos = mousePos;

            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz�tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) // dodane
        {
            isDragging = false;
        }
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                view.zoom(1 - event.mouseWheelScroll.delta / 10.0f);
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