#include <OSource.h>

class Sandbox : public OSource::Application{
public:
	virtual void Run() override{
	}
	virtual void Render() override{
		OSource::Shader shader = OSource::Shader("res/vs.glsl", "res/fs.glsl");
		OSource::Texture tex = OSource::Texture("res/image.png");
		
		float vertices[] = {
			0.5f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		float texCoords[] = {
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f 
		};
		unsigned int indices[] = {
			0, 1, 3,
			1, 2, 3
		};  

		unsigned int VAO, VBO, EBO, TBO;

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glGenBuffers(1, &TBO);

		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, TBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    	glEnableVertexAttribArray(1);

		glBindVertexArray(VAO);
		shader.Use();
		shader.SetInt("t", tex.getID());
        
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
	virtual void HandleInput(OSource::Input& input) override{
	}
};

OSource::Application* OSource::CreateApplication(){
	return new Sandbox();
}