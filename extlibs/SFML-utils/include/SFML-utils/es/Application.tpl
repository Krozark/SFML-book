namespace sfutils
{
    namespace es
    {
        template<typename ENTITY>
        Application<ENTITY>::Application() : systems(entities)
        {
        }

        template<typename ENTITY>
        void Application<ENTITY>::update(sf::Time deltaTime)
        {
            systems.updateAll(deltaTime);
            entities.update();
        }
    }
}
