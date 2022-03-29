//
// Created by nedo on 20.03.2022.
//

#include "DrawableHelper.hpp"
#include "../Core/Logger.hpp"

sf::Texture DrawableHelper::DrawWithShaders(const std::vector<sf::Drawable *> &objects,
											const std::vector<std::shared_ptr<sf::Shader>> &shaders,
											const sf::Vector2f &viewSize) {
	std::shared_ptr<sf::RenderTexture> front = std::make_shared<sf::RenderTexture>();
	std::shared_ptr<sf::RenderTexture> back = std::make_shared<sf::RenderTexture>();
	front->create(viewSize.x, viewSize.y);
	back->create(viewSize.x, viewSize.y);
	front->setSmooth(true);
	back->setSmooth(true);

	back->clear();
	for(auto* obj: objects) {
		back->draw(*obj);
	}
	back->display();

	for(auto& shader: shaders)
	{
		front->clear();
		front->draw(sf::Sprite(back->getTexture()), shader.get());
		front->display();
		std::swap(front, back);
	}

	return back->getTexture();
}
