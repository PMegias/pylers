#ifndef SELECT_BOX_HPP
#define SELECT_BOX_HPP

#pragma once
#include <SFML/Graphics.hpp>

class SelectBox
{
public:
						SelectBox() = default;
						SelectBox(float, float, float, sf::Vector2f, std::string, sf::Font, sf::Vector2f);

	bool				clicked(sf::RenderWindow&, const sf::Event&);
	void				draw(sf::RenderWindow&);

	void				set_text(std::string);
    void                set_offset(sf::Vector2f);

private:
	sf::RectangleShape	rs_shape;

	float				f_scale;
	std::string			s_text;
	sf::Font			f_font;

	sf::Vector2f		v2f_offset;
};

#endif // SELECT_BOX_HPP
