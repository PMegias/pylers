#include "SelectBox.hpp"
using namespace std;

SelectBox::SelectBox(float scale, float width, float height, sf::Vector2f position, std::string text, sf::Font font, sf::Vector2f offset) :
	f_scale(scale),
	s_text(text),
	f_font(font),
	v2f_offset(offset)
{
	rs_shape.setSize({ width, height });
	rs_shape.setPosition(position);
	rs_shape.setOutlineColor(sf::Color::White);
	rs_shape.setOutlineThickness(1.f);
}

void SelectBox::draw(sf::RenderWindow& window)
{
	sf::Color b = sf::Color::Black;
	sf::Color w = sf::Color::White;

	sf::Text text;
	text.setFont(f_font);
	text.setScale(f_scale, f_scale);

	auto position = rs_shape.getPosition();
	position += v2f_offset;
	text.move(position);
	text.setString(s_text);

	rs_shape.setFillColor(b);
	text.setFillColor(w);

	if (rs_shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		rs_shape.setFillColor(w);
		text.setFillColor(b);
	}

	window.draw(rs_shape);
	window.draw(text);
}

bool SelectBox::clicked(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed and sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		if (rs_shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			return true;
	return false;
}

void SelectBox::set_text(string text) {
	s_text = text;
}

void SelectBox::set_offset(sf::Vector2f offset) {
    v2f_offset = offset;
}
