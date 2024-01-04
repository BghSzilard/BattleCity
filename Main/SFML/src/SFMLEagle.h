#include "Eagle.h"
#include "TextureManager.h"

#include <SFML/Graphics.hpp>

class SFMLEagle : public sf::Drawable
{
public:

	SFMLEagle();

	Position getPosition();

private:

	void setTexture();
	void setSprite();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)  const;

	Eagle m_eagle;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	BattleCity::TextureManager m_textureManager;
};