// utworzenie zmiennej przechowuj¹cej punkt pocz¹tkowy przesuwania wykresu
sf::Vector2i lastPosition;

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

            // przesuniêcie wykresu o odpowiedni¹ wartoœæ
            view.move(-delta.x, delta.y);
            window.setView(view);

            // zapisanie aktualnej pozycji kursora jako pozycji pocz¹tkowej
            lastPosition = sf::Mouse::getPosition(window);
        }
    }

    // rysowanie wykresu funkcji
    window.clear(sf::Color::White);
    window.draw(plot);
    window.display();
}
