class Character :  public sf::Drawable, public sf::Transformable{

public:
	bool load(const std::string& tileset, sf::Vector2u tileSize,sf::Vector2u tileScale, int tileNumber)
    {
        // load the tileset texture
        if (!m_tileset.loadFromFile(tileset))
            return false;

        // resize the vertex array to fit the level size
        m_vertices.setPrimitiveType(sf::Quads);
        m_vertices.resize(4);

		// find its position in the tileset texture
		int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
		int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

		// get a pointer to the current tile's quad
		sf::Vertex* quad = &m_vertices[0];

		// define its 4 corners
		quad[0].position = sf::Vector2f(0, 0);
		quad[1].position = sf::Vector2f(tileSize.x*tileScale.x, 0);
		quad[2].position = sf::Vector2f(tileSize.x*tileScale.x, tileSize.y*tileScale.y);
		quad[3].position = sf::Vector2f(0,tileSize.y*tileScale.y);

		// define its 4 texture coordinates
		quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
		quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
		quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
		quad[3].texCoords = sf::Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);

        return true;
    }

    void updateposition()
    {
        float x = 0.0f;
        float y = 0.0f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            x -= 1.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            x += 1.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            y -= 1.0f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            y += 1.0f;
        }
        if(x==0.0f&&y==0.0f) return;
        float mag = sqrt(x*x + y*y);
        x/=mag;
        y/=mag;
        move(x,y);
    }

private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        // apply the transform
        states.transform *= getTransform();

        // apply the tileset texture
        states.texture = &m_tileset;

        // draw the vertex array
        target.draw(m_vertices, states);
    }

    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
};