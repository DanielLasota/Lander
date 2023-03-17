// utworzenie zmiennej przechowuj�cej punkt pocz�tkowy przesuwania wykresu
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
        }
        else if (event.type == sf::Event::MouseMoved && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // wyznaczenie r�nicy pomi�dzy aktualn� pozycj� kursora a pozycj� pocz�tkow�
            sf::Vector2i delta = sf::Mouse::getPosition(window) - lastPosition;

            // przesuni�cie wykresu o odpowiedni� warto��
            view.move(-delta.x, delta.y);
            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz�tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
    }

    // rysowanie wykresu funkcji
    window.clear(sf::Color::White);
    window.draw(plot);
    window.display();
}
