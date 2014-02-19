#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <Antic/Entity.h>
#include <Antic/RenderQueue.h>
#include <map>
#include <vector>

namespace antic
{
	class EntityManager
	{
	public:
		virtual ~EntityManager();
		virtual bool init();
		virtual void update();
		virtual void render();

		void addEntity( Entity* );
		Entity* getEntity( GLuint entityID );
		bool hasEntity( GLuint entityID );
		void removeEntity( GLuint entityID );

		//void runFunc( Functor );

	private:
		void close();

		std::map<GLuint, Entity*> entities;

		// Number of IDs that are currently in use.
		GLuint currIDs;

		// IDs that were used, but have since been freed.
		std::vector<GLuint> freeIDs;

		GLuint getNewID();

		RenderQueue *rq = nullptr;
	};
}

#endif