#pragma once
#include "../EntityMaster.h"
#include "../Global.h"

#include "../C_RenderSprite.h"
#include "../C_Physics2d.h"
#include "../C_Collider2d.h"
class Cube :
    public EntityMaster
{
public:
    Cube(Global* globalVariables, std::string myName) : EntityMaster(globalVariables, myName)
    {

        collisionVertexArray.append(sf::Vertex(sf::Vector2f(0, 0)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(50, 0)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(50, 50)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(0, 50)));
        collisionVertexArray.append(sf::Vertex(sf::Vector2f(0, 0)));
        colliderComponent->drawDebug = true;

        isDynamic = true;
        // Adicionando os componentes
        componentHandler.addComponent(renderComponent);
        componentHandler.addComponent(physicsComponent);
        componentHandler.addComponent(colliderComponent);


    }

    //Quando fizer override da fun��o parent deve chamar a fun��o no Base
    void beginPlay() override;
    void process() override;

    // Boundaries of the collision polygon
    sf::VertexArray collisionVertexArray;

    // Criando os componenetes
    std::shared_ptr<C_RenderSprite> renderComponent = std::make_shared<C_RenderSprite>(global, "./resources/cube.png", sf::Vector2f(1, 1));
    std::shared_ptr<C_Collider2d> colliderComponent = std::make_shared<C_Collider2d>(global, collisionVertexArray);
    std::shared_ptr<C_Physics2d> physicsComponent = std::make_shared<C_Physics2d>(global, transform);

};
