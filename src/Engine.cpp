#include <Antic/Engine.h>

std::string vertexShaderSource = "#version 330 core\n\\nlayout( location = 0 ) in vec3 vPosition;\nlayout( location = 1 ) in vec2 textureUV;\n\nout vec2 UV;\n\nvoid main()\n{\ngl_Position = vPosition;\nUV = textureUV;\n}\n";

std::string fragmentShaderSource = "#version 330 core\n\
\n\
in vec2 UV;\n\
out vec3 color;\n\
\n\
uniform sampler2D tex;\n\
\n\
void main()\n\
{\n\
	color = texture( tex, UV ).rgb;\n\
}";

antic::Engine::Engine()
{
	sm = nullptr;
	window = nullptr;
	context = nullptr;
}

antic::Engine::~Engine()
{
	//glDeleteProgram( programID );
	SDL_GL_DeleteContext( context );
	close();
}

void antic::Engine::close()
{
	if( sm != nullptr )
		delete sm;
	sm = nullptr;

	if( window != nullptr )
		SDL_DestroyWindow( window );
	window = nullptr;
	
	SDL_Quit();
}

bool antic::Engine::init( std::string title, int width, int height )
{
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
		return false;

	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	//SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

	//SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	//SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 32 );

	if( window != nullptr )
	{
		printf("Error: Window already exists.\n");
		close();
		return false;
	}
	window = SDL_CreateWindow( title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL );
	if( window == nullptr )
	{
		printf("Error: Window did not initialize.\n");
		close();
		return false;
	}
	context = SDL_GL_CreateContext( window );

	if( glewInit() != GLEW_OK )
		return false;

	ilInit();

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LESS );

	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho( 0, width, height, 0, 1, -1 );
	glViewport( 0, 0, width, height );
	glMatrixMode( GL_MODELVIEW );

	if( getServices().init() == false )
		return false;

	/*
	if( getServices().getEngineVars()->loadProgramFromString( name, vertexShaderSource, fragmentShaderSource) == false )
		return false;

	
	glUseProgram( getServices().getEngineVars()->getShader( name ) );
	*/
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	return true;
}

void antic::Engine::update()
{
	if( sm != nullptr )
	{
		sm->update();
	}
}

void antic::Engine::render()
{
	//glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if( sm != nullptr )
	{
		sm->render();
	}
	SDL_GL_SwapWindow( window );
}

void antic::Engine::setStateManager( StateManager* newSM )
{
	if( sm != nullptr )
		delete sm;
	sm = newSM;
}

SDL_Window* antic::Engine::getWindow()
{
	return window;
}

antic::Services & antic::Engine::getServices()
{
	return services;
}